C++ = g++
CC = gcc
INCLUDE=$(shell pkg-config --cflags opencv)
LIBS=$(shell pkg-config --libs opencv)
SOURCE=build_pyr.cpp
BIN=build_pyr
all:
	make build_pyr
	#make testHessian
build_pyr: build_pyr.o
	$(C++) -O3 -o build_pyr build_pyr.o $(LIBS)
.cpp.o:
	$(C++) -O3 -g -Wall $(INCLUDE) -c $< -o $@
.c.o:
	$(CC) -O3 -g -Wall $(INCLUDE) -c $< -o $@
clean:
	rm -rf $(BIN)  
	rm *.o
