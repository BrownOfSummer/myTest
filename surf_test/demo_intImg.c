/*************************************************************************
    > File Name: demo_intImg.c
    > Author: li_pengju
    > Mail: li_pengju@vobile.cn 
    > Copyright (c) Vobile Inc. All Rights Reserved
    > Created Time: 2016-11-28 17:03:22
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
void printit(float *data, int width, int height);
int main()
{
    int height = 30, width = 30;
    float *img = (float *)malloc(width * height * sizeof(float));
    float *intImg = (float *)malloc(width * height * sizeof(float));
    for(int i = 0; i < height; i ++){
        for(int j = 0; j < width; j ++){
            img[i * width + j] = 1;
        }
    }

    printit(img, width, height);
    /*
    for(int i = 0; i < height; i ++){
        for(int j = 0; j < width; j ++){
            float sum = 0;
            for(int m = 0; m <= i; m ++)
                for(int n = 0; n <= j; n ++)
                    sum += img[m][n];
            intImg[i][j] = sum;
        }
    }
    */
    printf("-------------------------------\n");
    float rs = 0;
    for(int j = 0; j < width; j ++) {
        rs += img[j];
        intImg[j] = rs;
    }
    for(int i = 1; i < height; i ++) {
        rs = 0.0;
        for(int j = 0; j < width; j ++) {
            rs += img[i * width + j];
            intImg[i * width + j] = rs + intImg[(i - 1) * width + j];
        }
    }
    printit(intImg, height, width);


    return 0;
}

float *Integral(unsigned char *img, int width, int height, int widthStep) {
    float *intImg = (float *)malloc(width*height*sizeof(float));
    if (!intImg)
        exit(0);
    float rs = 0.0;
    unsigned char *pOriData = (unsigned char *)img;
    float *pIntData = intImg;

    for(int j = 0; j < width; j ++) {
        rs += (float)(pOriData[j] / 255.0);
        pIntData[j] = rs;
    }
    for(int i = 1; i < height; i ++) {
        rs = 0.0;
        for( int j = 0; j < width; j ++ ) {
            rs += (float)(pOriData[i*widthStep+j] / 255.0);
            pIntData[i*width+j] = rs + pIntData[(i-1)*width+j];
        }
    }
    return intImg;
}
void printit(float *data, int width, int height) {
    for(int i = 0; i < height; i ++){
        for(int j = 0; j < width; j ++){
            fprintf(stdout, "%.1f ", data[i * width + j]);
        }
        fprintf(stdout, "\n");
    }
}
