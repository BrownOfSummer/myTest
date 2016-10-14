C++ = g++
CC = gcc
INCLUDE=$(shell pkg-config --cflags opencv)
LIBS=$(shell pkg-config --libs opencv)
SOURCE=testHarris.cpp
BIN=testHarris testHessian
all:
	make testHarris
	make testHessian
testHarris: testHarris.o
	$(C++) -O3 -o testHarris testHarris.o $(LIBS)
testHessian: testHessian.o
	$(C++) -O3 -o testHessian testHessian.o $(LIBS)
.cpp.o:
	$(C++) -O3 -g -Wall $(INCLUDE) -c $< -o $@
.c.o:
	$(CC) -O3 -g -Wall $(INCLUDE) -c $< -o $@
clean:
	rm -rf $(BIN)  
	rm *.o
