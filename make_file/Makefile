#
#  Top Level Makefile for LAPACK
#  Version 3.2.1
#  June 2009
#

include make.inc

all: f2clib lapack_install lib
#all: f2clib lapack_install lib lapack_testing blas_testing
#all: f2clib lapack_install lib lapack_testing blas_testing variants_testing

#lib: lapacklib tmglib
#lib: f2clib lapacklib tmglib
#lib: f2clib blaslib variants lapacklib tmglib
lib: f2clib blaslib lapacklib

#clean: cleanlib cleantesting cleanblas_testing 
clean: cleanlib 

lapack_install:
	( cd INSTALL; $(MAKE); ./testlsame; ./testslamch; \
	  ./testdlamch; ./testsecond; ./testdsecnd; ./testversion )

blaslib:
	( cd BLAS/SRC; $(MAKE) )

lapacklib:	lapack_install
	( cd SRC; $(MAKE) )

f2clib:
	    ( cd F2CLIBS/libf2c; $(MAKE) )

cleanall: cleanlib cleanblas_testing cleantesting 
	rm -f *.a TESTING/*.out INSTALL/test*  BLAS/*.out
