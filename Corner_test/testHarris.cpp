/*************************************************************************
    > File Name: testHarris.cpp
    > Author: li_pengju
    > Mail: li_pengju@vobile.cn 
    > Copyright (c) Vobile Inc. All Rights Reserved
    > Created Time: 2016-09-29 16:28:23
 ************************************************************************/

#include<iostream>
#include<opencv/cv.h>
#include<opencv/highgui.h>
#include<string.h>
#include<stdlib.h>
using namespace std;
using namespace cv;

const double GaussWeight3[3][3] = {{0.001631, 0.037126, 0.001631},
                                   {0.037126, 0.844973, 0.037126},
                                   {0.001631, 0.037126, 0.001631}};
int main(int argc, char *argv[])
{
    int i, j, m, n;
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
    double Dx[200][200] = {0.0};
    double Dy[200][200] = {0.0};
    
    for(i = 0; i < row; i ++ ){
        double *ptr = (double *)(checkboard->imageData + i*checkboard->widthStep);
        for(j = 0; j < col - 1; j ++ ){
            Dx[i][j] = (ptr[j+1] - ptr[j]);
        }
    }

    for(i = 0; i < row - 1; i ++ ){
        double *ptr1 = (double *)(checkboard->imageData + i*checkboard->widthStep);
        double *ptr2 = (double *)(checkboard->imageData + (i+1)*checkboard->widthStep);
        for(j = 0; j < col; j ++){
            Dy[i][j] = (ptr2[j] - ptr1[j]);
        }
    }

    double Ix2[200][200] = {0.0};
    double Iy2[200][200] = {0.0};
    double Ixy[200][200] = {0.0};
    for(i = 0; i < row; i ++){
        for(j = 0; j < col; j ++){
            Ix2[i][j] = Dx[i][j] * Dx[i][j];
            Iy2[i][j] = Dy[i][j] * Dy[i][j];
            Ixy[i][j] = Dx[i][j] * Dy[i][j];
        }
    }
    
    double maxR = 0.0;
    // do filter
    double R[200][200]={0.0};
   for(i = 1; i < row - 1; i ++){
        for(j = 1; j < col - 1; j ++){
            double tmpA = 0.0;
            double tmpB = 0.0;
            double tmpC = 0.0;
            for(m = -1; m <= 1; m ++)
                for(n = -1; n <= 1; n ++){
                    tmpA += GaussWeight3[m + 1][n + 1] * Ix2[i + m][j + n];
                    tmpB += GaussWeight3[m + 1][n + 1] * Iy2[i + m][j + n];
                    tmpC += GaussWeight3[m + 1][n + 1] * Ixy[i + m][j + n];
                }
            //R = detM - alpha*(traceM)^2
            double tmpR = tmpA * tmpB - tmpC * tmpC - 0.04 * (tmpA+tmpB)*(tmpA+tmpB);
            R[i][j] = tmpR;
            if( tmpR > maxR )
                maxR = tmpR;
        }
    }
   
   int pos[1000][2] = {0};
   double T = 0.01 * maxR;
   cout<<"Threshold ="<<T<<endl;

   //filter corners using Threshold
   int count1 = 0;
   int count2 = 0;
   for(int i = 1; i < row - 1; i ++){
       for(int j = 1; j < col - 1; j ++){
           if(R[i][j] > T){
               count1 ++;
               double localMax = 0.0;
               for(int m = i - 1; m <= i + 1; m ++){
                   for(int n = j - 1; n <= j + 1; n ++){
                       if(R[m][n] > localMax)
                           localMax = R[m][n];
                   }
               }
               if(localMax <= R[i][j]){
                   pos[count2][0] = i;
                   pos[count2][1] = j;
                   count2 ++;
                   if(count2 >= 1000){
                       cout<<"error, exceed the pos size, count2 ="<<count2<<endl;
                       return -1;
                   }
               }
           }
       }
   }

   cout<<"count1 ="<<count1<<endl;
   cout<<"count2 ="<<count2<<endl;

   // draw corners
   IplImage *HarrisCorner = cvCreateImage(cvGetSize(checkboard), checkboard->depth, checkboard->nChannels);
   cvCopy(checkboard, HarrisCorner);
   for(i = 0; i < count2; i ++){
       cvCircle(HarrisCorner, cvPoint(pos[i][0], pos[i][1]), 1, CvScalar(0,150,0), 1);
   }
   cvNamedWindow("checkboard",1);
   cvShowImage("checkboard",checkboard);
   cvNamedWindow("harris",1);
   cvShowImage("harris", HarrisCorner);
   cvWaitKey(-1);
   cvReleaseImage(&checkboard);
   cvReleaseImage(&HarrisCorner);
   cvDestroyWindow("checkboard");
   cvDestroyWindow("harris");
   return 0;
    
}

