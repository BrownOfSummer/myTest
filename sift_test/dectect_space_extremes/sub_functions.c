/*************************************************************************
    > File Name: sub_functions.cpp
    > Author: li_pengju
    > Mail: li_pengju@vobile.cn 
    > Copyright (c) Vobile Inc. All Rights Reserved
    > Created Time: 2016-11-07 09:58:17
 ************************************************************************/

#include<opencv/cv.h>
#include<opencv/highgui.h>
#include<opencv/cxcore.h>
#include<math.h>

#define SIFT_INIT_SIGMA 0.5
/************************ Functions prototyped here **************************/
/*
  Converts an image to 32-bit grayscale

  @param img a 3-channel 8-bit color (BGR) or 8-bit gray image

  @return Returns a 32-bit grayscale image
*/
IplImage* convert_to_gray32( IplImage* img )
{
  IplImage* gray8, * gray32;
  
  gray32 = cvCreateImage( cvGetSize(img), IPL_DEPTH_32F, 1 );
  if( img->nChannels == 1 )
    gray8 = cvClone( img );
  else
    {
      gray8 = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 1 );
      cvCvtColor( img, gray8, CV_BGR2GRAY );
    }
  cvConvertScale( gray8, gray32, 1.0 / 255.0, 0 );

  cvReleaseImage( &gray8 );
  return gray32;
}

/*
  Downsamples an image to a quarter of its size (half in each dimension)
  using nearest-neighbor interpolation

  @param img an image

  @return Returns an image whose dimensions are half those of img
*/
IplImage* downsample( IplImage* img )
{
  IplImage* smaller = cvCreateImage( cvSize(img->width / 2, img->height / 2),
				     img->depth, img->nChannels );
  cvResize( img, smaller, CV_INTER_NN );

  return smaller;
}

/*
  Converts an image to 8-bit grayscale and Gaussian-smooths it.  The image is
  optionally doubled in size prior to smoothing.

  @param img input image
  @param img_dbl if true, image is doubled in size prior to smoothing
  @param sigma total std of Gaussian smoothing
*/
IplImage* create_init_img( IplImage* img, int img_dbl, double sigma )
{
  IplImage *gray, *dbl;
  double sig_diff;

  gray = convert_to_gray32( img );
  if( img_dbl )
    {
      sig_diff = sqrt( sigma * sigma - SIFT_INIT_SIGMA * SIFT_INIT_SIGMA * 4 );
      dbl = cvCreateImage( cvSize( img->width*2, img->height*2 ),
			   IPL_DEPTH_32F, 1 );
      cvResize( gray, dbl, CV_INTER_CUBIC );
      cvSmooth( dbl, dbl, CV_GAUSSIAN, 0, 0, sig_diff, sig_diff );
      cvReleaseImage( &gray );
      return dbl;
    }
  else
    {
      sig_diff = sqrt( sigma * sigma - SIFT_INIT_SIGMA * SIFT_INIT_SIGMA );
      cvSmooth( gray, gray, CV_GAUSSIAN, 0, 0, sig_diff, sig_diff );
      return gray;
    }
}



/*
  Builds Gaussian scale space pyramid from an image

  @param base base image of the pyramid
  @param octvs number of octaves of scale space
  @param intvls number of intervals per octave
  @param sigma amount of Gaussian smoothing per octave

  @return Returns a Gaussian scale space pyramid as an octvs x (intvls + 3)
    array
*/
IplImage*** build_gauss_pyr( IplImage* base, int octvs,
			     int intvls, double sigma )
{
  IplImage ***gauss_pyr;
  const int _intvls = intvls;
  double sig[_intvls+3], sig_total, sig_prev, k;
  int i, o;

  gauss_pyr = calloc( octvs, sizeof( IplImage** ) );
  for( i = 0; i < octvs; i++ )
    gauss_pyr[i] = calloc( intvls + 3, sizeof( IplImage *) );

  /*
    precompute Gaussian sigmas using the following formula:

    \sigma_{total}^2 = \sigma_{i}^2 + \sigma_{i-1}^2

    sig[i] is the incremental sigma value needed to compute 
    the actual sigma of level i. Keeping track of incremental
    sigmas vs. total sigmas keeps the gaussian kernel small.
  */
  k = pow( 2.0, 1.0 / intvls );
  sig[0] = sigma;
  sig[1] = sigma * sqrt( k*k- 1 );
  for (i = 2; i < intvls + 3; i++)
      sig[i] = sig[i-1] * k;

  for( o = 0; o < octvs; o++ )
    for( i = 0; i < intvls + 3; i++ )
      {
	if( o == 0  &&  i == 0 )
	  gauss_pyr[o][i] = cvCloneImage(base);

	/* base of new octvave is halved image from end of previous octave */
	else if( i == 0 )
	  gauss_pyr[o][i] = downsample( gauss_pyr[o-1][intvls] );
	  
	/* blur the current octave's last image to create the next one */
	else
	  {
	    gauss_pyr[o][i] = cvCreateImage( cvGetSize(gauss_pyr[o][i-1]),
					     IPL_DEPTH_32F, 1 );
	    cvSmooth( gauss_pyr[o][i-1], gauss_pyr[o][i],
		      CV_GAUSSIAN, 0, 0, sig[i], sig[i] );
	  }
      }

  return gauss_pyr;
}



/*
  Builds a difference of Gaussians scale space pyramid by subtracting adjacent
  intervals of a Gaussian pyramid

  @param gauss_pyr Gaussian scale-space pyramid
  @param octvs number of octaves of scale space
  @param intvls number of intervals per octave

  @return Returns a difference of Gaussians scale space pyramid as an
    octvs x (intvls + 2) array
*/
IplImage*** build_dog_pyr( IplImage*** gauss_pyr, int octvs, int intvls )
{
  IplImage*** dog_pyr;
  int i, o;

  dog_pyr = calloc( octvs, sizeof( IplImage** ) );
  for( i = 0; i < octvs; i++ )
    dog_pyr[i] = calloc( intvls + 2, sizeof(IplImage*) );

  for( o = 0; o < octvs; o++ )
    for( i = 0; i < intvls + 2; i++ )
      {
	dog_pyr[o][i] = cvCreateImage( cvGetSize(gauss_pyr[o][i]),
				       IPL_DEPTH_32F, 1 );
	cvSub( gauss_pyr[o][i+1], gauss_pyr[o][i], dog_pyr[o][i], NULL );
      }

  return dog_pyr;
}

float pixval32f( IplImage *img, int r, int c )
{
    return ( (float *)(img->imageData + img->widthStep * r) )[c];
}

int is_extremum( IplImage ***dog_pyr, int octv, int intvl, int r, int c )
{
    double val = pixval32f( dog_pyr[octv][intvl], r, c );
    int i, j, k;
    /* check for maximum */
    if( val > 0 )
    {
        for( i = -1; i <= 1; i ++ )
            for( j = -1; j <= 1; j ++ )
                for( k = -1; k <= 1; k ++ )
                    if( val < pixval32f( dog_pyr[octv][intvl + i], r + j, c + k ) )
                        return 0;
    }
    else
    {
        for( i = -1; i <= 1; i ++ )
            for( j = -1; j <= 1; j ++ )
                for( k = -1; k <= 1; k ++ )
                    if( val > pixval32f(dog_pyr[octv][intvl + i], r + j, c + k) )
                        return 0;
    }

    return 1;
}


