/*************************************************************************
    > File Name: leastSquare.c
    > Author: li_pengju
    > Mail: li_pengju@vobile.cn 
    > Copyright (c) Vobile Inc. All Rights Reserved
    > Created Time: 2016-10-18 09:59:05
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
    //load data.txt
    //just y = alpha * x + beta
    char line[200];
    int n = 0;
    double sumX = 0.0;
    double sumY = 0.0;
    double sumXX = 0.0;
    double sumXY = 0.0;
    double x, y, z;
    FILE *fp = fopen(argv[1],"rt");
    if( !fp ){
        fprintf(stdout, "Failed to open %s !\n",argv[1]);
        return -1;
    }
    
    while( fgets(line, 200, fp) != NULL ){
        sscanf(line, "%lf %lf %lf\n", &x, &y, &z);
        sumX += x;
        sumY += y;
        sumXY += x * y;
        sumXX += x * x;
        n ++;
    }

    double alpha = ( n * sumXY - sumX * sumY ) / ( n * sumXX - sumX * sumX );
    double beta = ( sumXX * sumY - sumX*sumXY ) / ( n * sumXX - sumX * sumX );

    fprintf(stdout, "alpha = %lf, beta = %lf\n", alpha, beta);
    return 0;
}
