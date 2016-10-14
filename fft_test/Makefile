CFLAGS=-Wall -g
LDFLAGS=-lm
OBJECTS=fft_utils.o
CC=gcc
testfft: testfft.c $(OBJECTS)
	$(CC) -o testfft testfft.c $(OBJECTS) $(CFLAGS) $(LDFLAGS)
fft_utils.o: fft_utils.c
	$(CC) -c fft_utils.c
clean:
	rm *.o
	rm testfft
