CC = g++
CC_1 = gcc
LINKER = g++
CFLAGS = -O3 -g -Wall -I include/
LDLIBS = lib/lapack_LINUX.a lib/blas_LINUX.a lib/libf2c.a #-lm -lc

SUFFIXES = .cpp .o
PROG = multi_leastSquare
OBJS = multi_leastSquare.o
all: $(PROG)
$(PROG): $(OBJS)
	$(LINKER) -O3 -o $(PROG) $(OBJS) $(LDLIBS)
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@
.c.o:
	$(CC_1) $(CFLAGS) -c $< -o $@

clean:
	-rm -f $(PROG) *.o
