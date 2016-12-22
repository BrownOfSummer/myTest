/*************************************************************************
    > File Name: read_save_img_data.c
    > Author: li_pengju
    > Mail: li_pengju@vobile.cn 
    > Copyright (c) Vobile Inc. All Rights Reserved
    > Created Time: 2016-11-29 14:57:19
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<opencv/cv.h>
#include<opencv/highgui.h>

int main(int argc, char *argv[])
{
    IplImage *img = cvLoadImage(argv[1], 0);
    int width = img->width;
    int height = img->height;
    int widthStep = img->widthStep;
    fprintf(stdout, "width= %d, height= %d, widthStep= %d\n", width, height, widthStep);
    unsigned char *data = (unsigned char *)img->imageData;
    FILE *imgtxt = fopen("img.txt","wt");
    for(int i = 0; i < height; i ++) {
        for(int j = 0; j < width; j ++){
            fprintf(imgtxt,"%d ", data[i*widthStep+j]);
        }
        fprintf(imgtxt,"\n");
    }
    return 0;
}
