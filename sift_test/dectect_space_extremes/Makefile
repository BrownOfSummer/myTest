C++ = g++
CC = gcc
INCLUDE=$(shell pkg-config --cflags opencv)
LIBS=$(shell pkg-config --libs opencv)
SOURCE=detect_space_extremums.c sub_functions.c
BIN=detect_space_extremums
OBJS=sub_functions.o
all:
	make detect_space_extremums
detect_space_extremums: detect_space_extremums.o $(OBJS)
	$(CC) -O3 -o detect_space_extremums detect_space_extremums.o $(OBJS) $(LIBS)
.cpp.o:
	$(C++) -O3 -g -Wall $(INCLUDE) -c $< -o $@
.c.o:
	$(CC) -O3 -g -Wall $(INCLUDE) -c $< -o $@
clean:
	rm -f $(BIN)
	rm *.o
