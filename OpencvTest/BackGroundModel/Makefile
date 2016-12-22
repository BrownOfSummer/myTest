C++ = g++
CC = gcc
LINKER = g++
CFLAGS = -O3 -g -Wall $(shell pkg-config --cflags opencv)
LDLIBS = $(shell pkg-config --libs opencv)

SUFFIXES = .cpp .o

all:
	make plotinvideo
plotinvideo: plotinvideo.o
	$(LINKER) -O3 -o plotinvideo plotinvideo.o $(LDLIBS)
.cpp.o:
	$(C++) $(CFLAGS) -c $< -o $@
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -f *.o
	-rm  $(BINS)
