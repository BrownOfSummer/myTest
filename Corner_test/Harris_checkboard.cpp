/*************************************************************************
    > File Name: testHarris.cpp
    > Author: li_pengju
    > Mail: li_pengju@vobile.cn 
    > Copyright (c) Vobile Inc. All Rights Reserved
    > Created Time: 2016-09-29 16:28:23
 ************************************************************************/

#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

const double GaussWeight3[3][3] = {{0.001631, 0.037126, 0.001631},
                                   {0.037126, 0.844973, 0.037126},
                                   {0.001631, 0.037126, 0.001631}};
int main(int argc, char *argv[])
{
    int row = 200;
    int col = 200;
    double I[200][200] = {0.0};
    int i, j, m, n;
    //generate checkboard
    for(i=0; i<200; i++){
        for(j=0; j<200; j++){
            if( (i < 50) || (i>=100 && i<150) ){
                if(j>=50 && j<100)
                    I[i][j] = 1.0;
                if(j >= 150)
                    I[i][j] = 0.7;
            }
            else if( (i>=50 && i<100) || (i>=150) ){
                if(j<50)
                    I[i][j] = 1.0;
                if(j>=100 && j<150)
                    I[i][j] = 0.7;
            }
        }
    }
/*
    for(i=0; i<200; i+=50){
        for(j=0; j<200; j+=50){
            for(m=i; m<i+50; m++){
                for(n=j; n<j+50; n++){
                    cout<<I[i][j]<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
        }
    }
*/
    cout<<"row ="<<row<<endl;
    cout<<"col ="<<col<<endl;
    double Dx[200][200] = {0.0};
    double Dy[200][200] = {0.0};
    for(i = 0; i < row; i ++ ){
        for(j = 0; j < col - 1; j ++ ){
            Dx[i][j] = I[i][j+1] - I[i][j];
        }
    }

    for(i = 0; i < row - 1; i ++ ){
        for(j = 0; j < col; j ++){
            Dy[i][j] = I[i+1][j] - I[i][j];
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

    double tmp1, tmp2;
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
            double tmpR = tmpA * tmpB - tmpC * tmpC - 0.04 * (tmpA+tmpB)*(tmpA+tmpB);
            R[i][j] = tmpR;
            if( tmpR > maxR )
                maxR = tmpR;
        }
    }
    int pos[1000][2] = {0};
   
   double T = 0.04 * maxR;
   cout<<"T ="<<T<<endl;
   int count1 = 0;
   int count2 = 0;
   for(i = 1; i < row - 1; i ++){
       for(j = 1; j < col - 1; j ++){
           if(R[i][j] > T){
               count1 ++;
               double localMax = 0.0;
               for(m = i - 1; m <= i + 1; m ++){
                   for(n = j - 1; n <= j + 1; n ++){
                       if(R[m][n] > localMax)
                           localMax = R[m][n];  //should be R, not I
                   }
               }
               if(localMax <= R[i][j]){
                   pos[count2][0] = i;
                   pos[count2][1] = j;
                   count2 ++;
                   if(count2 >= 1000){
                       cout<<"error, count2 ="<<count2<<endl;
                       return -1;
                   }
               }
           }
       }
   }
   cout<<"harris without localMax ="<<count1<<endl;
   cout<<"harris width localMax ="<<count2<<endl;
   for(i=0; i<count2; i++)
       cout<<pos[i][0]<<" "<<pos[i][1]<<endl;
    return 0;
    
}

