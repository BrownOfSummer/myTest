/*************************************************************************
    > File Name: test.c
    > Author: li_pengju
    > Mail: li_pengju@vobile.cn 
    > Copyright (c) Vobile Inc. All Rights Reserved
    > Created Time: 2016-11-29 12:51:05
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main()
{
    int cnt = 0;
    float table[4][4] = {0};
    float pi = 3.14159f;
    float sig = 1.5f;
    for(int i = 0; i < 4; i ++){
        float x = i - 1.5;
        for(int j = 0; j < 4; j ++) {
            float y = j - 1.5;
            table[i][j] = 1.0/(2*pi*sig*sig) * exp(-(x*x+y*y)/(2*sig*sig));
        }
    }
    for(int i = 0; i < 4; i ++) {
        for(int j = 0; j < 4; j ++) {
            fprintf(stdout, "%f ", table[i][j]);
        }
        fprintf(stdout,"\n");
    }
    
    for(int octave = 1; octave <= 4; octave ++)
        for(int interval = 1; interval <= 4; interval ++)
            fprintf(stdout, "%d ", (int)(pow(2, octave) * interval + 1) );
    fprintf(stdout, "\n");
    return 0;
}
