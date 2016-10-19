/*************************************************************************
    > File Name: leastSquare.c
    > Author: li_pengju
    > Mail: li_pengju@vobile.cn 
    > Copyright (c) Vobile Inc. All Rights Reserved
    > Created Time: 2016-10-18 09:59:05
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include "include/f2c.h"
#include "include/clapack.h"
static float *calc_tans_muti_oriMatrix(const float *X, const int height, const int width);
int main(int argc, char *argv[])
{
    //load data.txt
    int k = 3; // polyfit max order
    char line[200];
    int count = 0;
    FILE *fp = fopen(argv[1],"rt");
    if( !fp ){
        fprintf(stdout, "Failed to open %s !\n",argv[1]);
        return -1;
    }
    while( fgets(line, 200, fp) != NULL )
        count ++;
    float *x = (float *)malloc( count * sizeof(float) );
    float *y = (float *)malloc( count * sizeof(float) );
    float *X = (float *)malloc( count * (k+1) * sizeof(float) );
    //memset(X, 1, count*sizeof(float));
    fseek(fp, 0, SEEK_SET);
    float a, b, c;
    count = 0;
    while( fgets(line, 200, fp) != NULL ){
        sscanf(line, "%f %f %f\n", &a, &b, &c);
        x[count] = a;
        y[count] = b;
        count ++;
    }

    for(int i = 0; i<k+1; i ++){
        for(int j = 0; j < count; j ++){
            X[ count * i + j] = pow( x[j], i );
        }
    }

/*
    for(int i = 0; i < count; i ++){
        fprintf(stdout, "%f %f %f\n",X[i], X[count + i], X[2*count + i]);
    }
*/
    //X'*X
/*
    float *A = (float *)malloc( (k+1)*(k+1)*sizeof(float));//A = X' * X = k*k
    float tmpsum = 0;
    for(int m = 0; m < k+1; m ++){
        for(int n = 0; n < k+1; n ++){
            //A[m*(k+1) + n] = sum( X[m].*X[n] );
            for(int i = 0; i < count; i ++){
                tmpsum += X[ m*count + i ] * X[ n*count + i ];
            }
            A[ m * (k+1) + n ] = tmpsum;
            tmpsum = 0;
        }
    }
*/
    float *A = calc_tans_muti_oriMatrix(X, count, k+1);
    if(A == NULL){
        fprintf(stderr, "calc A failed !\n");
        return -1;
    }
/*
    for(int i = 0; i < k+1; i ++){
        for(int j = 0; j < k+1; j ++){
            fprintf(stdout, "%f ", A[j*(k+1) + i]);
        }
        fprintf(stdout, "\n");
    }
*/
    // calc B = X'*Y
    float *B = (float *)calloc((k+1), sizeof(float));
    for(int i = 0; i < k+1; i ++)
        for(int j = 0; j < count; j ++){
            B[i] += X[i*count + j] * y[j];
        }

    // calc (X'X)^-1*B
    //////////////////////////////
    integer lda;
    integer ldb;
    integer INFO;

    integer M = k+1; // A cols and rows
    integer N = 1; //B cols
    lda = M;
    ldb = M;
    integer ipiv[M];

    sgesv_(&M, &N, A, &lda, ipiv, B, &ldb, &INFO);
    if(INFO == 0){
        for( int i = 0; i < M; i ++ ){
            fprintf(stdout, "%f\n", B[i]);
            //fprintf(stdout, "%ld\n", ipiv[i]);
        }
        fprintf(stdout, "the polyfit result:\n");
        for( int i = 0; i < M; i ++) {
            fprintf(stdout, "%f*x^%d + ",B[i],i);
        }
        fprintf(stdout,"\n");
    }
    else{
        fprintf(stderr, "failed !\n");
    }

    return 0;
}

static float *calc_tans_muti_oriMatrix(const float *X, const int height, const int width)
{
    // calc: X'*X
    //X: the matrix, each col has height elements, step = height
    //width: num of cols
    //return A, width*width, each step=width, record result row;
    float *A = (float *)malloc(width * width * sizeof(float));
    if(A == NULL || X == NULL)
        return NULL;
    float tmpsum = 0;
    for(int m = 0; m < width; m ++){
        for(int n = 0; n < width; n ++){
            //A[m*height + n] = sum(X[m].*X[n])
            for(int i = 0; i < height; i ++){
                tmpsum += X[m * height + i] * X[n * height + i];
            }
            A[m * width + n] = tmpsum;
            tmpsum = 0;
        }
    }
    return A;
}
