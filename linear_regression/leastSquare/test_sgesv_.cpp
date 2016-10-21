/*************************************************************************
    > File Name: test.cpp
    > Author: li_pengju
    > Mail: li_pengju@vobile.cn 
    > Copyright (c) Vobile Inc. All Rights Reserved
    > Created Time: 2016-10-18 14:00:24
 ************************************************************************/

#include<iostream>
#include "include/f2c.h"
#include "include/clapack.h"
using namespace std;
int main(void)
{
    integer M = 3;
    integer N = 1;

    real a[9] = {4,3,11,2,-1,0,-1,2,3};
    real b[3] = {2, 10, 8};

    integer lda;
    integer ldb;
    integer INFO;

    lda = M;
    ldb = M;
    integer ipiv[M];

    sgesv_(&M, &N, a, &lda, ipiv, b, &ldb, &INFO);

    if( INFO == 0 )
    {
        for( int i = 0; i < M; i ++ ){
            cout<<b[i]<<endl;
        }
    }
    else
    {
        cout<<"Failed"<<endl;
    }
    return 0;
}
