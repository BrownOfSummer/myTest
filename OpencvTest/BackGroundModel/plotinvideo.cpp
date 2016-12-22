/*************************************************************************
    > File Name: plotinvideo.cpp
    > Author: li_pengju
    > Mail: li_pengju@vobile.cn 
    > Copyright (c) Vobile Inc. All Rights Reserved
    > Created Time: 2016-10-16 10:57:33
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<opencv/cv.h>
#include<opencv/highgui.h>
using namespace std;

int main(int argc, char *argv[])
{
    fprintf(stdout, "Capture from file %s\n",argv[1]);
    cvNamedWindow("src", 1);
    CvCapture *capture = cvCreateFileCapture(argv[1]);
    IplImage *frame = NULL;
    if( !capture ) fprintf(stdout, "Could not open %s\n",argv[1]);
    int N = 0;
    if( capture ){
        for(;;){
            //IplImage *frame = cvRetrieveFrame( capture );
            frame = cvQueryFrame( capture );
            if( !frame )
                break;
            N += 5;
            int x = N % 100;
            int y = N % 200;
            cvRectangle(frame, cvPoint(x,y), cvPoint(x+150,y+150), cvScalar(0,255,0));
            cvShowImage("src",frame);
            
            int c = cvWaitKey(10) & 0xFF;
            //End processing on esc q, or Q
            if(c == 27 || c == 'q' || c == 'Q')
                break;

        }
        cvReleaseCapture( &capture );
    }
    cvDestroyWindow( "src" );
    return 0;
}
