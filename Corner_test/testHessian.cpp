/*************************************************************************
    > File Name: testHessian.cpp
    > Author: li_pengju
    > Mail: li_pengju@vobile.cn 
    > Copyright (c) Vobile Inc. All Rights Reserved
    > Created Time: 2016-10-12 16:51:21
 ************************************************************************/

#include<iostream>
#include<opencv/cv.h>
#include<opencv/highgui.h>
#include<string.h>
#include<stdlib.h>

#define CURV_THR 10
using namespace std;
using namespace cv;

static inline double pixval64f(IplImage *img, int r, int c);
int main(int argc, char *argv[])
{
    int i, j;
    CvSize checkboard_size;
    checkboard_size.width = 200;
    checkboard_size.height = 200;
    IplImage *checkboard = cvCreateImage(checkboard_size, IPL_DEPTH_64F, 1);
    for(i = 0; i < checkboard->height; i ++){
        for(j = 0; j < checkboard->width; j ++){
            if( (i < 50) || (i >= 100 && i < 150) ){
                if( j >= 50 && j < 100 )
                    ( (double*)(checkboard->imageData + i*checkboard->widthStep) )[j] = 1.0;
                if(j >= 150)
                    ( (double*)(checkboard->imageData + i*checkboard->widthStep) )[j] = 0.7;
            }
            else if( (i>=50 && i<100) || (i >= 150) ){
                if( j < 50 )
                    ( (double*)(checkboard->imageData + i*checkboard->widthStep) )[j] = 1.0;
                if( j >= 100 && j<150 )
                    ( (double*)(checkboard->imageData + i*checkboard->widthStep) )[j] = 0.7;
            }
        }
    }
    int row = checkboard->height;
    int col = checkboard->width;
    cout<<"row ="<<row<<endl;
    cout<<"col ="<<col<<endl;
    if( row != 200 || col != 200 ){
        cout<<"size error"<<endl;
        return -1;
    }

    //double dxx[200][200] = {0.0};
    //double dxy[200][200] = {0.0};
    //double dyy[200][200] = {0.0};
    int pos[1000][2];
    int count = 0;
    double curv_thr = CURV_THR;
    for(i = 1; i < row-1; i ++){
        for(j = 1; j < col -1; j ++){
            double dxx = pixval64f(checkboard, i, j+1) + pixval64f(checkboard, i, j-1) - 2*pixval64f(checkboard, i, j);
            double dyy = pixval64f(checkboard, i+1, j) + pixval64f(checkboard, i-1, j) - 2*pixval64f(checkboard, i, j);
            double dxy = ( pixval64f(checkboard, i+1, j+1) + pixval64f(checkboard, i-1, j-1)
                            - pixval64f(checkboard, i+1, j-1) - pixval64f(checkboard, i-1, j+1) ) / 4.0;

            double det = dxx * dyy - dxy * dxy;
            double trace = dxx + dyy;
            if(det > 0){
                if( trace*trace / det < (curv_thr + 1.0)*(curv_thr + 1.0) / curv_thr ){
                    pos[count][0] = i;
                    pos[count][1] = j;
                    count ++;
                    if(count >= 1000)
                        break;
                }
            }
            else
                continue;
        }
    }

    cout<<"num of corners ="<<count<<endl;
    IplImage *HessianCorner = cvCreateImage(cvGetSize(checkboard), checkboard->depth, checkboard->nChannels);
    cvCopy(checkboard, HessianCorner);
    for(i = 0; i < count; i ++){
        cvCircle(HessianCorner, cvPoint(pos[i][0], pos[i][1]), 1, CvScalar(0,150,0), 1);
        //cout<<"row ="<<pos[i][0]<<" "<<"col ="<<pos[i][1]<<endl;
    }
    cvNamedWindow("checkboard",1);
    cvShowImage("checkboard",checkboard);
    cvNamedWindow("HessianCorner",1);
    cvShowImage("HessianCorner", HessianCorner);
    cvWaitKey(-1);
    cvReleaseImage(&checkboard);
    cvReleaseImage(&HessianCorner);
    cvDestroyWindow("checkboard");
    cvDestroyWindow("HessianCorner");

    return 0;
}

static inline double pixval64f(IplImage *img, int r, int c){
    return ( (double *)(img->imageData + r*img->widthStep) )[c];
}
