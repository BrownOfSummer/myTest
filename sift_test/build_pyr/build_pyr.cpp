/*************************************************************************
    > File Name: build_pyr.cpp
    > Author: li_pengju
    > Mail: li_pengju@vobile.cn 
    > Copyright (c) Vobile Inc. All Rights Reserved
    > Created Time: 2016-10-13 10:12:18
 ************************************************************************/

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>

#define INTVLS 3
#define SIGMA 1.6
#define IMG_DBL 1
#define SIFT_INIT_SIGMA 0.5 
using namespace std;
using namespace cv;

static IplImage *downsample( IplImage *img );
static void release_pyr( IplImage**** pyr, int octvs, int n );
int main(int argc, char *argv[])
{
    IplImage *img = cvLoadImage(argv[1],0);

    double img_dbl = IMG_DBL, sigma = SIGMA;
    int intvls = INTVLS;
    /* create_init_img img---->dbl*/
    IplImage *gray32, *gray8, *dbl, *init_img;
    gray32 = cvCreateImage( cvGetSize(img), IPL_DEPTH_32F, 1 );
    //gray = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 1 );
    gray8 = cvCloneImage( img );
    cvConvertScale( gray8, gray32, 1.0 / 255.0, 0 );
    cvReleaseImage( &gray8 );
    if( img_dbl )
    {
        double sig_diff = sqrt( sigma * sigma - SIFT_INIT_SIGMA *SIFT_INIT_SIGMA * 4 );
        dbl = cvCreateImage( cvSize(img->width*2, img->height*2), IPL_DEPTH_32F, 1);
        cvResize( gray32, dbl, CV_INTER_CUBIC );
        cvSmooth(dbl, dbl, CV_GAUSSIAN, 0, 0, sig_diff, sig_diff);
        init_img = cvCloneImage( dbl );
        cvReleaseImage( &gray32 );
        cvReleaseImage( &dbl );
    }
    else
    {
        double sig_diff = sqrt( sigma * sigma - SIFT_INIT_SIGMA * SIFT_INIT_SIGMA );
        cvSmooth( gray32, gray32, CV_GAUSSIAN, 0, 0, sig_diff, sig_diff );
        init_img = cvCloneImage( gray32 );
        cvReleaseImage( &gray32 );
    }
    //cvNamedWindow("dbl",1)
    //cvShowImage("dbl",dbl);
    //cvWaitKey(-1);

    /* build gauss_pyr: downsample && gauss smooth*/
    int octvs = log( MIN(init_img->height, init_img->height) ) / log(2) - 2;
    const int _intvls = intvls;
    double sig[_intvls+3], k;
    int i, o;

    IplImage ***gauss_pyr = (IplImage ***)calloc(octvs, sizeof(IplImage **) );
    for( i = 0; i < octvs; i ++ )
        gauss_pyr[i] = (IplImage **)calloc( intvls + 3, sizeof(IplImage *) );

    k = pow( 2.0, 1.0 / intvls );
    sig[0] = sigma;
    sig[1] = sigma * sqrt( k*k - 1 );
    for (i = 2; i < intvls + 3; i ++)
        sig[i] = sig[i - 1] * k;

    for( o = 0; o < octvs; o ++ )
        for( i = 0; i < intvls + 3; i ++ ){
            if(o == 0 && i == 0)
                gauss_pyr[o][i] = cvCloneImage( init_img );
            else if( i == 0 )
                gauss_pyr[o][i] = downsample( gauss_pyr[o-1][intvls] );// downsample for intvls, not intvls + 2
            else{
                gauss_pyr[o][i] = cvCreateImage( cvGetSize(gauss_pyr[o][i-1]),
                                    IPL_DEPTH_32F, 1 );
                cvSmooth( gauss_pyr[o][i-1], gauss_pyr[o][i],
                        CV_GAUSSIAN, 0, 0, sig[i], sig[i] );
            }
        }

/*
    fprintf(stdout, "octvs = %d\n", octvs);
    char title[10];
    for( o = 0; o < octvs; o ++){
        sprintf(title, "%d", o);
        cvNamedWindow(title, 1);
        cvShowImage(title, gauss_pyr[o][intvls]);
    }
    cvWaitKey(-1);
*/

    /* build_dog_pyr: */
    IplImage ***dog_pyr = (IplImage ***)calloc( octvs, sizeof(IplImage **) );
    for(i = 0; i < octvs; i ++)
        dog_pyr[i] = (IplImage **)calloc(intvls + 2, sizeof(IplImage *));

    for( o = 0; o < octvs; o ++ )
        for( i = 0; i < intvls + 2; i ++ ){
            dog_pyr[o][i] = cvCreateImage( cvGetSize(gauss_pyr[o][i]),
                                IPL_DEPTH_32F, 1);
            cvSub( gauss_pyr[o][i+1], gauss_pyr[o][i], dog_pyr[o][i], NULL );
        }

    fprintf(stdout, "octvs = %d\n", octvs);
    char title[10];
    for( o = 0; o < octvs; o ++){
        sprintf(title, "%d", o);
        cvNamedWindow(title, 1);
        cvShowImage(title, dog_pyr[o][intvls]);
    }
    cvWaitKey(-1);

      release_pyr( &gauss_pyr, octvs, intvls + 3 );
    release_pyr( &dog_pyr, octvs, intvls + 2 );
    return 0;
}

static IplImage *downsample( IplImage *img )
{
    IplImage *smaller = cvCreateImage( cvSize(img->width / 2, img->height / 2),
                        img->depth, img->nChannels);
    cvResize( img, smaller, CV_INTER_NN );
    return smaller;
}


static void release_pyr( IplImage**** pyr, int octvs, int n )
{
  int i, j;
  for( i = 0; i < octvs; i++ )
    {
      for( j = 0; j < n; j++ )
	cvReleaseImage( &(*pyr)[i][j] );
      free( (*pyr)[i] );
    }
  free( *pyr );
  *pyr = NULL;
}
