/*************************************************************************
    > File Name: test_dqrsl.c
    > Author: li_pengju
    > Mail: li_pengju@vobile.cn 
    > Copyright (c) Vobile Inc. All Rights Reserved
    > Created Time: 2016-12-06 17:09:58
 ************************************************************************/

#include<stdio.h>
#include<math.h>
#include<complex.h>
#include<stdlib.h>
#include<time.h>

#include "linpack_d.h"
#include "blas0.h"
#include "blas1_d.h"
void dqrsl_test ();
int main()
{
    dqrsl_test( );
    return 0;
}
void dqrsl_test( )

/******************************************************************************/
/*
  Purpose:

    DQRSL_TEST tests DQRSL.
  Discussion:
    DQRSL can solve a linear system that was factored by DQRDC.
*/
{
# define N 5
# define P 3
# define LDA N

  double a[LDA*P] = {
    1.0,  1.0,  1.0,  1.0,  1.0,
    1.0,  2.0,  3.0,  4.0,  5.0,
    1.0,  4.0,  9.0, 16.0, 25.0 };
  double b[P];
  double b2[P] = {
    -3.02, 4.4914286, -0.72857143 };
  int i;
  int info;
  int ipvt[N];
  int j;
  int job;
  double qraux[P];
  double qty[N];
  double qy[N];
  double r[N];
  double work[P];
  double xb[N];
  double y[N] = {
    1.0,
    2.3,
    4.6,
    3.1,
    1.2 };

  printf ( "\n" );
  printf ( "DQRSL_TEST\n" );
  printf ( "  DQRSL solves a rectangular linear system A*x=b in the\n" );
  printf ( "  least squares sense after A has been factored by DQRDC.\n" );

  printf ( "\n" );
  printf ( "  The matrix A:\n" );
  printf ( "\n" );

  for ( i = 0; i < N; i++ )
  {
    for ( j = 0; j < P; j++ )
    {
      printf ( "  %12f", a[i+j*LDA] );
    }
    printf ( "\n" );
  }
/*
  Decompose the matrix.
*/
  printf ( "\n" );
  printf ( " Decompose the matrix.\n" );

  job = 0;

  for ( j = 0; j < P; j++ )
  {
    ipvt[j] = 0;
  }

  dqrdc ( a, LDA, N, P, qraux, ipvt, work, job );
/*
  Call DQRSL to compute the least squares solution A*x=b.
*/
  job = 110;

  info = dqrsl ( a, LDA, N, P, qraux, y, qy, qty, b, r, xb, job );

  if ( info != 0 )
  {
    fprintf ( stderr, "\n" );
    fprintf ( stderr, "DQRSL_TEST - Warning!\n" );
    fprintf ( stderr, "  DQRSL returns INFO = %d\n", info );
    return;
  }

  printf ( "\n" );
  printf ( "      X          X(expected):\n" );
  printf ( "\n" );

  for ( i = 0; i < P; i++ )
  {
    printf ( "  %14.6g  %14.6g\n", b[i], b2[i] );
  }

  return;
# undef LDA
# undef N
# undef P
}

