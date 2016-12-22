C++ = g++
CC=gcc
LINKER=g++
CFLAGS=-O3 -g -Wall $(shell pkg-config --cflags opencv)
LDLIBS=$(shell pkg-config --libs opencv)

BINS=avg_background cv_yuv_codebook
all:
	make avg_background
	#make avg_yuv_codebook
avg_background: avg_background.o
	$(LINKER) -O3 -o avg_background avg_background.o $(LDLIBS)
.cpp.o:
	$(C++) $(CFLAGS) -c $< -o $@
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm $(BINS)
