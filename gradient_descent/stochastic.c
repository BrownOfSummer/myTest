/*************************************************************************
    > File Name: test_gradient_descen.c
    > Author: li_pengju
    > Mail: li_pengju@vobile.cn 
    > Copyright (c) Vobile Inc. All Rights Reserved
    > Created Time: 2016-10-19 17:16:36
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main(void)
{
    // training set
    // each sample has 3 branch
    double x[5][3] = {{1, 0.0, 3},
                     {1, 1.0, 3},
                     {1, 2.0, 3},
                     {1, 3.0, 2},
                     {1, 4.0, 4}};
    // the corresponding result
    double y[5] = {95.364, 97.217205, 75.195834, 60.105519, 49.342380};

    //iteration threshold
    double epsilon = 0.0001;

    //learning rate
    double alpha = 0.01;
    double diff[2] = {0, 0};
    int max_itor = 1000;
    double error1 = 0;
    double error0 = 0;
    int cnt = 0;
    int m = 5;

    //initial para
    double theta0 = 0, theta1 = 0, theta2 = 0;
    while(1)
    {
        cnt ++;
        for(int i = 0; i < m; i ++){
            //polyfit function: y = thera0*x[0] + thera1 * x[1] + thera2 * x[2]
            //calc
            diff[0] = (theta0 + theta1 * x[i][1] + theta2 * x[i][2]) - y[i];

            // calc gradient = diff[0] * x[i][j]
            theta0 -= alpha * diff[0] * x[i][0];
            theta1 -= alpha * diff[0] * x[i][1];
            theta2 -= alpha * diff[0] * x[i][2];
        }
        // calc loss function
        error1 = 0;
        for(int i = 0; i < m; i ++){
            error1 += pow( (y[i] - (theta0 + theta1 * x[i][1] + theta2 * x[i][2])), 2 ) / 2;
        }
        double tmp = error1 - error0 >= 0 ? error1 - error0 : error0 - error1;
        if( tmp < epsilon)
            break;
        else
            error0 = error1;

        fprintf(stdout, "theta0 : %lf, theta1 : %lf, theta2 : %lf, error1 : %lf\n",theta0, theta1, theta2, error1);

    }
    fprintf(stdout, "Done : theta0 : %lf, theta1 : %lf, theta2: %lf\n", theta0, theta1, theta2);
    fprintf(stdout, "iteration times: %d\n",cnt);

    return 0;
}
