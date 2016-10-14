#ifndef FFTUTILS_H
#define FFTUTILS_H

#ifndef USE_FFTWF

typedef struct _FFT_INFO
{
	unsigned int nfft;
	float *fft_buf, *w;
	float *wts;
	int *ip;
} FFT_INFO;

int finfo_init(FFT_INFO *finfo, unsigned n);
void finfo_close(FFT_INFO *finfo);
void fft_it(const int16_t *indata, uint32_t n, double *outdata, FFT_INFO *finfo);

#else

#include <fftw3.h>

typedef struct _MY_FFT_T {
	fftwf_complex *in;
	fftwf_complex *out;
	fftwf_plan plan;
	char *Wisfile;
} MY_FFT_T;

typedef float AFP_REAL;

MY_FFT_T *fft_init(unsigned int nfft);
void fft_close(MY_FFT_T *work);
void fft_it(unsigned int nfft, const int16_t* in_data0, double* out_data0, MY_FFT_T *work);

#endif

uint32_t stft(const int16_t *indata, uint32_t n, uint32_t window, uint32_t overlap, double *outdata);

#endif
