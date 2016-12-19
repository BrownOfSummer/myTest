/*************************************************************************
    > File Name: tmp.c
    > Author: li_pengju
    > Mail: li_pengju@vobile.cn 
    > Copyright (c) Vobile Inc. All Rights Reserved
    > Created Time: 2016-12-08 10:19:10
 ************************************************************************/
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <time.h>

# include "blas1_d.h"
# include "linpack_d.h"

void dqrdc ( double a[], int lda, int n, int p, double qraux[], int jpvt[], 
  double work[], int job )

/******************************************************************************/
/*
  Purpose:

    DQRDC computes the QR factorization of a real rectangular matrix.

  Discussion:

    DQRDC uses Householder transformations.

    Column pivoting based on the 2-norms of the reduced columns may be
    performed at the user's option.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    07 June 2005

  Author:

    Original FORTRAN77 version by Jack Dongarra, Cleve Moler, Jim Bunch, 
    Pete Stewart,
    C version by John Burkardt.

  Reference:

    Jack Dongarra, Cleve Moler, Jim Bunch and Pete Stewart,
    LINPACK User's Guide,
    SIAM, (Society for Industrial and Applied Mathematics),
    3600 University City Science Center,
    Philadelphia, PA, 19104-2688.
    ISBN 0-89871-172-X

  Parameters:

    Input/output, double A(LDA,P).  On input, the N by P matrix
    whose decomposition is to be computed.  On output, A contains in
    its upper triangle the upper triangular matrix R of the QR
    factorization.  Below its diagonal A contains information from
    which the orthogonal part of the decomposition can be recovered.
    Note that if pivoting has been requested, the decomposition is not that
    of the original matrix A but that of A with its columns permuted
    as described by JPVT.

    Input, int LDA, the leading dimension of the array A.  LDA must
    be at least N.

    Input, int N, the number of rows of the matrix A.

    Input, int P, the number of columns of the matrix A.

    Output, double QRAUX[P], contains further information required
    to recover the orthogonal part of the decomposition.

    Input/output, integer JPVT[P].  On input, JPVT contains integers that
    control the selection of the pivot columns.  The K-th column A(*,K) of A
    is placed in one of three classes according to the value of JPVT(K).
      > 0, then A(K) is an initial column.
      = 0, then A(K) is a free column.
      < 0, then A(K) is a final column.
    Before the decomposition is computed, initial columns are moved to
    the beginning of the array A and final columns to the end.  Both
    initial and final columns are frozen in place during the computation
    and only free columns are moved.  At the K-th stage of the
    reduction, if A(*,K) is occupied by a free column it is interchanged
    with the free column of largest reduced norm.  JPVT is not referenced
    if JOB == 0.  On output, JPVT(K) contains the index of the column of the
    original matrix that has been interchanged into the K-th column, if
    pivoting was requested.

    Workspace, double WORK[P].  WORK is not referenced if JOB == 0.

    Input, int JOB, initiates column pivoting.
    0, no pivoting is done.
    nonzero, pivoting is done.
*/
{
  int j;
  int jp;
  int l;
  int lup;
  int maxj;
  double maxnrm;
  double nrmxl;
  int pl;
  int pu;
  int swapj;
  double t;
  double tt;

  pl = 1;
  pu = 0;
/*
  If pivoting is requested, rearrange the columns.
*/
  if ( job != 0 )
  {
    for ( j = 1; j <= p; j++ )
    {
      swapj = ( 0 < jpvt[j-1] );

      if ( jpvt[j-1] < 0 )
      {
        jpvt[j-1] = -j;
      }
      else
      {
        jpvt[j-1] = j;
      }

      if ( swapj )
      {
        if ( j != pl )
        {
          dswap ( n, a+0+(pl-1)*lda, 1, a+0+(j-1), 1 );
        }
        jpvt[j-1] = jpvt[pl-1];
        jpvt[pl-1] = j;
        pl = pl + 1;
      }
    }
    pu = p;

    for ( j = p; 1 <= j; j-- )
    {
      if ( jpvt[j-1] < 0 )
      {
        jpvt[j-1] = -jpvt[j-1];

        if ( j != pu )
        {
          dswap ( n, a+0+(pu-1)*lda, 1, a+0+(j-1)*lda, 1 );
          jp = jpvt[pu-1];
          jpvt[pu-1] = jpvt[j-1];
          jpvt[j-1] = jp;
        }
        pu = pu - 1;
      }
    }
  }
/*
  Compute the norms of the free columns.
*/
  for ( j = pl; j <= pu; j++ )
  {
    qraux[j-1] = dnrm2 ( n, a+0+(j-1)*lda, 1 );
  }

  for ( j = pl; j <= pu; j++ )
  {
    work[j-1] = qraux[j-1];
  }
/*
  Perform the Householder reduction of A.
*/
  lup = i4_min ( n, p );

  for ( l = 1; l <= lup; l++ )
  {
/*
  Bring the column of largest norm into the pivot position.
*/
    if ( pl <= l && l < pu )
    {
      maxnrm = 0.0;
      maxj = l;
      for ( j = l; j <= pu; j++ )
      {
        if ( maxnrm < qraux[j-1] )
        {
          maxnrm = qraux[j-1];
          maxj = j;
        }
      }

      if ( maxj != l )
      {
        dswap ( n, a+0+(l-1)*lda, 1, a+0+(maxj-1)*lda, 1 );
        qraux[maxj-1] = qraux[l-1];
        work[maxj-1] = work[l-1];
        jp = jpvt[maxj-1];
        jpvt[maxj-1] = jpvt[l-1];
        jpvt[l-1] = jp;
      }
    }
/*
  Compute the Householder transformation for column L.
*/
    qraux[l-1] = 0.0;

    if ( l != n )
    {
      nrmxl = dnrm2 ( n-l+1, a+l-1+(l-1)*lda, 1 );

      if ( nrmxl != 0.0 )
      {
        if ( a[l-1+(l-1)*lda] < 0.0 )
        {
          nrmxl = - nrmxl;
        }

        dscal ( n-l+1, 1.0 / nrmxl, a+l-1+(l-1)*lda, 1 );
        a[l-1+(l-1)*lda] = 1.0 + a[l-1+(l-1)*lda];
/*
  Apply the transformation to the remaining columns, updating the norms.
*/
        for ( j = l + 1; j <= p; j++ )
        {
          t = - ddot ( n-l+1, a+l-1+(l-1)*lda, 1, a+l-1+(j-1)*lda, 1 ) 
            / a[l-1+(l-1)*lda];
          daxpy ( n-l+1, t, a+l-1+(l-1)*lda, 1, a+l-1+(j-1)*lda, 1 );

          if ( pl <= j && j <= pu )
          {
            if ( qraux[j-1] != 0.0 )
            {
              tt = 1.0 - pow ( fabs ( a[l-1+(j-1)*lda] ) / qraux[j-1], 2 );
              if ( tt < 0.0 )
              {
                tt = 0.0;
              }
              t = tt;
              tt = 1.0 + 0.05 * tt * pow ( qraux[j-1] / work[j-1], 2 );

              if ( tt != 1.0 )
              {
                qraux[j-1] = qraux[j-1] * sqrt ( t );
              }
              else
              {
                qraux[j-1] = dnrm2 ( n-l, a+l+(j-1)*lda, 1 );
                work[j-1] = qraux[j-1];
              }
            }
          }
        }
/*
  Save the transformation.
*/
        qraux[l-1] = a[l-1+(l-1)*lda];
        a[l-1+(l-1)*lda] = -nrmxl;
      }
    }
  }
  return;
}
/******************************************************************************/

int dqrsl ( double a[], int lda, int n, int k, double qraux[], double y[], 
  double qy[], double qty[], double b[], double rsd[], double ab[], int job )

/******************************************************************************/
/*
  Purpose:

    DQRSL computes transformations, projections, and least squares solutions.

  Discussion:

    DQRSL requires the output of DQRDC.

    For K <= min(N,P), let AK be the matrix

      AK = ( A(JPVT[0]), A(JPVT(2)), ..., A(JPVT(K)) )

    formed from columns JPVT[0], ..., JPVT(K) of the original
    N by P matrix A that was input to DQRDC.  If no pivoting was
    done, AK consists of the first K columns of A in their
    original order.  DQRDC produces a factored orthogonal matrix Q
    and an upper triangular matrix R such that

      AK = Q * (R)
               (0)

    This information is contained in coded form in the arrays
    A and QRAUX.

    The parameters QY, QTY, B, RSD, and AB are not referenced
    if their computation is not requested and in this case
    can be replaced by dummy variables in the calling program.
    To save storage, the user may in some cases use the same
    array for different parameters in the calling sequence.  A
    frequently occuring example is when one wishes to compute
    any of B, RSD, or AB and does not need Y or QTY.  In this
    case one may identify Y, QTY, and one of B, RSD, or AB, while
    providing separate arrays for anything else that is to be
    computed.

    Thus the calling sequence

      dqrsl ( a, lda, n, k, qraux, y, dum, y, b, y, dum, 110, info )

    will result in the computation of B and RSD, with RSD
    overwriting Y.  More generally, each item in the following
    list contains groups of permissible identifications for
    a single calling sequence.

      1. (Y,QTY,B) (RSD) (AB) (QY)

      2. (Y,QTY,RSD) (B) (AB) (QY)

      3. (Y,QTY,AB) (B) (RSD) (QY)

      4. (Y,QY) (QTY,B) (RSD) (AB)

      5. (Y,QY) (QTY,RSD) (B) (AB)

      6. (Y,QY) (QTY,AB) (B) (RSD)

    In any group the value returned in the array allocated to
    the group corresponds to the last member of the group.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    07 June 2005

  Author:

    Original FORTRAN77 version by Jack Dongarra, Cleve Moler, Jim Bunch, 
    Pete Stewart,
    C version by John Burkardt.

  Reference:

    Jack Dongarra, Cleve Moler, Jim Bunch and Pete Stewart,
    LINPACK User's Guide,
    SIAM, (Society for Industrial and Applied Mathematics),
    3600 University City Science Center,
    Philadelphia, PA, 19104-2688.
    ISBN 0-89871-172-X

  Parameters:

    Input, double A[LDA*P], contains the output of DQRDC.

    Input, int LDA, the leading dimension of the array A.

    Input, int N, the number of rows of the matrix AK.  It must
    have the same value as N in DQRDC.

    Input, int K, the number of columns of the matrix AK.  K
    must not be greater than min(N,P), where P is the same as in the
    calling sequence to DQRDC.

    Input, double QRAUX[P], the auxiliary output from DQRDC.

    Input, double Y[N], a vector to be manipulated by DQRSL.

    Output, double QY[N], contains Q * Y, if requested.

    Output, double QTY[N], contains Q' * Y, if requested.

    Output, double B[K], the solution of the least squares problem
      minimize norm2 ( Y - AK * B),
    if its computation has been requested.  Note that if pivoting was
    requested in DQRDC, the J-th component of B will be associated with
    column JPVT(J) of the original matrix A that was input into DQRDC.

    Output, double RSD[N], the least squares residual Y - AK * B,
    if its computation has been requested.  RSD is also the orthogonal
    projection of Y onto the orthogonal complement of the column space
    of AK.

    Output, double AB[N], the least squares approximation Ak * B,
    if its computation has been requested.  AB is also the orthogonal
    projection of Y onto the column space of A.

    Input, integer JOB, specifies what is to be computed.  JOB has
    the decimal expansion ABCDE, with the following meaning:
      if A != 0, compute QY.
      if B != 0, compute QTY.
      if C != 0, compute QTY and B.
      if D != 0, compute QTY and RSD.
      if E != 0, compute QTY and AB.
    Note that a request to compute B, RSD, or AB automatically triggers
    the computation of QTY, for which an array must be provided in the
    calling sequence.

    Output, int DQRSL, is zero unless the computation of B has
    been requested and R is exactly singular.  In this case, INFO is the
    index of the first zero diagonal element of R, and B is left unaltered.
*/
{
  int cab;
  int cb;
  int cqty;
  int cqy;
  int cr;
  int i;
  int info;
  int j;
  int jj;
  int ju;
  double t;
  double temp;
/*
  Set info flag.
*/
  info = 0;
/*
  Determine what is to be computed.
*/
  cqy =  (   job / 10000          != 0 );
  cqty = ( ( job %  10000 )       != 0 );
  cb =   ( ( job %   1000 ) / 100 != 0 );
  cr =   ( ( job %    100 ) /  10 != 0 );
  cab =  ( ( job %     10 )       != 0 );

  ju = i4_min ( k, n-1 );
/*
  Special action when N = 1.
*/
  if ( ju == 0 )
  {
    if ( cqy )
    {
      qy[0] = y[0];
    }

    if ( cqty )
    {
      qty[0] = y[0];
    }

    if ( cab )
    {
      ab[0] = y[0];
    }

    if ( cb )
    {
      if ( a[0+0*lda] == 0.0 )
      {
        info = 1;
      }
      else
      {
        b[0] = y[0] / a[0+0*lda];
      }
    }

    if ( cr )
    {
      rsd[0] = 0.0;
    }
    return info;
  }
/*
  Set up to compute QY or QTY.
*/
  if ( cqy )
  {
    for ( i = 1; i <= n; i++ )
    {
      qy[i-1] = y[i-1];
    }
  }

  if ( cqty )
  {
    for ( i = 1; i <= n; i++ )
    {
      qty[i-1] = y[i-1];
    }
  }
/*
  Compute QY.
*/
  if ( cqy )
  {
    for ( jj = 1; jj <= ju; jj++ )
    {
      j = ju - jj + 1;

      if ( qraux[j-1] != 0.0 )
      {
        temp = a[j-1+(j-1)*lda];
        a[j-1+(j-1)*lda] = qraux[j-1];
        t = -ddot ( n-j+1, a+j-1+(j-1)*lda, 1, qy+j-1, 1 ) / a[j-1+(j-1)*lda];
        daxpy ( n-j+1, t, a+j-1+(j-1)*lda, 1, qy+j-1, 1 );
        a[j-1+(j-1)*lda] = temp;
      }
    }
  }
/*
  Compute Q'*Y.
*/
  if ( cqty )
  {
    for ( j = 1; j <= ju; j++ )
    {
      if ( qraux[j-1] != 0.0 )
      {
        temp = a[j-1+(j-1)*lda];
        a[j-1+(j-1)*lda] = qraux[j-1];
        t = -ddot ( n-j+1, a+j-1+(j-1)*lda, 1, qty+j-1, 1 ) / a[j-1+(j-1)*lda];
        daxpy ( n-j+1, t, a+j-1+(j-1)*lda, 1, qty+j-1, 1 );
        a[j-1+(j-1)*lda] = temp;
      }
    }
  }
/*
  Set up to compute B, RSD, or AB.
*/
  if ( cb )
  {
    for ( i = 1; i <= k; i++ )
    {
      b[i-1] = qty[i-1];
    }
  }

  if ( cab )
  {
    for ( i = 1; i <= k; i++ )
    {
      ab[i-1] = qty[i-1];
    }
  }

  if ( cr && k < n )
  {
    for ( i = k+1; i <= n; i++ )
    {
      rsd[i-1] = qty[i-1];
    }
  }

  if ( cab && k+1 <= n )
  {
    for ( i = k+1; i <= n; i++ )
    {
      ab[i-1] = 0.0;
    }
  }

  if ( cr )
  {
    for ( i = 1; i <= k; i++ )
    {
      rsd[i-1] = 0.0;
    }
  }
/*
  Compute B.
*/
  if ( cb )
  {
    for ( jj = 1; jj <= k; jj++ )
    {
      j = k - jj + 1;

      if ( a[j-1+(j-1)*lda] == 0.0 )
      {
        info = j;
        break;
      }

      b[j-1] = b[j-1] / a[j-1+(j-1)*lda];

      if ( j != 1 )
      {
        t = -b[j-1];
        daxpy ( j-1, t, a+0+(j-1)*lda, 1, b, 1 );
      }
    }
  }
/*
  Compute RSD or AB as required.
*/
  if ( cr || cab )
  {
    for ( jj = 1; jj <= ju; jj++ )
    {
      j = ju - jj + 1;

      if ( qraux[j-1] != 0.0 )
      {
        temp = a[j-1+(j-1)*lda];
        a[j-1+(j-1)*lda] = qraux[j-1];

        if ( cr )
        {
          t = -ddot ( n-j+1, a+j-1+(j-1)*lda, 1, rsd+j-1, 1 ) 
            / a[j-1+(j-1)*lda];
          daxpy ( n-j+1, t, a+j-1+(j-1)*lda, 1, rsd+j-1, 1 );
        }

        if ( cab )
        {
          t = -ddot ( n-j+1, a+j-1+(j-1)*lda, 1, ab+j-1, 1 ) 
            / a[j-1+(j-1)*lda];
          daxpy ( n-j+1, t, a+j-1+(j-1)*lda, 1, ab+j-1, 1 );
        }
        a[j-1+(j-1)*lda] = temp;
      }
    }
  }

  return info;
}
/******************************************************************************/

