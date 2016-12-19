gcc -c blas0.c -o blas0.o
gcc -c blas1_d.c -o blas1_d.o
gcc -c linpack_d.c -o linpack_d.o
gcc -c linpack_d_prb.c -o linpack_d_prb.o

gcc blas0.o blas1_d.o linpack_d.o linpack_d_prb.o -o test

gcc -c test_dqrsl.c -o test_dqrsl.o
gcc blas0.o blas1_d.o linpack_d.o test_dqrsl.o -o test_dqrsl


