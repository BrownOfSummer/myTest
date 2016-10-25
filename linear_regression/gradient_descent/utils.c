/*************************************************************************
    > File Name: utils.c
    > Author: li_pengju
    > Mail: li_pengju@vobile.cn 
    > Copyright (c) Vobile Inc. All Rights Reserved
    > Created Time: 2016-10-24 09:55:16
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

static int stochastic_gradient( const double *X, const double *Y, int m, double alpha, double epsilon, int max_itor, double *theta );
static int batch_gradient( const double *X, const double *Y, int m, double alpha, double epsilon, int max_itor, double *theta );

int main(int argc, char *argv[])
{
    int m = 0;
    char line[200];
    double X[1000] = {0};
    double Y[1000] = {0};
/*
    FILE *fp = fopen(argv[1], "rt");
    while( fgets(line, 200, fp) !=NULL ){
        double x, y, z;
        sscanf(line, "%lf %lf %lf\n", &x, &y, &z);
        X[m] = x;
        Y[m] = y;
        m ++;
    }
    fclose(fp);
*/
    double epsilon = 0.0001;
    double alpha = 0.000001;
    double theta[2] = {0.0};
    //stochastic_gradient(X, Y, m, alpha, epsilon, 1000, theta);
    //batch_gradient(X, Y, m, alpha, epsilon, 1000, theta);

    for(int i = 0; i < 1000; i ++) {
        Y[i] = 5.7 * i + 9;
        X[i] = i;
    }

    //stochastic_gradient(X, Y, 1000, alpha, epsilon, 1000, theta);
    batch_gradient(X, Y, 1000, alpha, epsilon, 1000, theta);

    fprintf(stdout, "%lf %lf %lf\n", theta[0], theta[1], epsilon);
}
// to fit y = ax + b
static int stochastic_gradient( const double *X, const double *Y, int m, double alpha, double epsilon, int max_itor, double *theta ) {
    double error1 = 0;
    double error0 = 0;
    int cnt = 0;
    double tmp;
    
    while(1) {
        double theta0 = theta[0];
        double theta1 = theta[1];
        cnt ++;
        for( int i = 0; i < m; i ++ ) {
            theta[0] -= alpha * (theta[0] + theta[1] * X[i] - Y[i] ) / m;
            theta[1] -= alpha * (theta[0] + theta[1] * X[i] - Y[i] ) * X[i] / m;
        }
        error1 = 0;
        for(int i = 0; i < m; i ++) {
            //double diff = theta[0] + theta[1] * X[i] - Y[i];
            double diff = theta0 + theta1 * X[i] - theta[0] - theta[1] * X[i];
            error1 += pow( diff, 2 ) ;
        }
        tmp = ( (error1 - error0) >= 0 ? (error1 - error0) : (error0 - error1) );

        if( tmp <= epsilon || cnt >= max_itor )
            break;
        else
            error0 = error1;

        printf("theta[0] = %lf, theta[1] = %lf, error = %lf\n", theta[0], theta[1], tmp);
    }
    return cnt;
}

static int batch_gradient( const double *X, const double *Y, int m, double alpha, double epsilon, int max_itor, double *theta )
{
    double error1, tmp, error0 = 0;
    int cnt = 0;
    while(1) {
        cnt ++;
        double theta0 = theta[0], theta1 = theta[1];
        double Sum = 0;
        double Sum0 = 0;
        for(int i = 0; i < m; i ++){
            double diff = Y[i] - (theta[0] + theta[1] * X[i]);
            Sum +=  diff * X[i] / m;
            Sum0 += diff * 1.0 / m;
        }
        theta[0] += alpha * Sum0;
        theta[1] += alpha * Sum;

        error1 = 0.0;
        for( int i = 0; i < m; i ++ ){
            double diff = theta0 + theta1 * X[i] - theta[0] - theta[1] * X[i];
            error1 += pow( diff, 2 ) ;
        }

        tmp = (error1 - error0) > 0 ? (error1 - error0) : (error0 -error1);
        if( error1 <= epsilon || cnt >= max_itor )
            break;
        else
            error0 = error1;

        printf("theta[0] = %lf, theta[1] = %lf, error = %lf\n", theta[0], theta[1], tmp);
    }
    return cnt;
}
