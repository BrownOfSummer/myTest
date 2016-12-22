/*************************************************************************
    > File Name: dectect_space_extremes.cpp
    > Author: li_pengju
    > Mail: li_pengju@vobile.cn 
    > Copyright (c) Vobile Inc. All Rights Reserved
    > Created Time: 2016-11-07 09:50:34
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include "sub_functions.h"

#define INTVLS 3
#define SIGMA 1.6
#define IMG_DBL 1
#define SIFT_INIT_SIGMA 0.5
#define SIFT_CONTR_THR 0.04
#define SIFT_CURV_THR 10
/* width of border in which to ignore keypoints */
#define SIFT_IMG_BORDER 5
#define ABS(x) ( ( (x) < 0 ) ? -(x) : (x) )
int main(int argc, char *argv[])
{
    IplImage *init_img;
    IplImage ***gauss_pyr, ***dog_pyr;
    CvMemStorage *storage;
    CvSeq *features;
    int octvs, i, o, r, c, n = 0;

    int img_dbl = IMG_DBL;
    double sigma = SIGMA;
    int intvls = INTVLS;
    double contr_thr = SIFT_CONTR_THR;
    int curv_thr = SIFT_CURV_THR;
    IplImage *img = cvLoadImage(argv[1], 0);
    if( ! img )
        fprintf(stderr, "NULL pointer error of img %s\n", argv[1]);
    /*build scale space pyramid; smallest dimension of top level is ~4 pixels*/
    init_img = create_init_img(img, img_dbl, sigma);
    octvs = log( MIN(init_img->width, init_img->height) ) / log(2) - 2;
    gauss_pyr = build_gauss_pyr(init_img, octvs, intvls, sigma);
    dog_pyr = build_dog_pyr(gauss_pyr, octvs, intvls);

    double prelim_contr_thr = 0.5 * contr_thr / intvls;
    struct feature *feat;
    struct detection_data *ddata;
    storage = cvCreateMemStorage( 0 );
    //features = scale_spcae_extrema(dog_pyr, octvs, intvls, contr_thr, 
    //        curv_thr, storage);

    features = cvCreateSeq(0, sizeof(CvSeq), sizeof(struct feature), storage);
    
    for( o = 0; o < octvs; o ++ )
        for( i = 1; i <= intvls; i ++ )
            for( r = SIFT_IMG_BORDER; r < dog_pyr[o][0]->height-SIFT_IMG_BORDER; r++ )
                for(c = SIFT_IMG_BORDER; c<dog_pyr[o][0]->width-SIFT_IMG_BORDER; c++)
                    if( ABS(pixval32f(dog_pyr[o][i], r, c)) > prelim_contr_thr )
                        if( is_extremum( dog_pyr, o, i, r, c ) )
                        {
                            //feat = interp_extremum(dog_pyr,o,i,r,c,intvls,contr_thr);
                        }
    return 0;

}

