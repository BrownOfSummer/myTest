#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "fft_utils.h"

#ifndef USE_FFTWF

#include "fft/fft4f.c"


int finfo_init(FFT_INFO *finfo, unsigned n)
{
    double PI = acos(-1.);
    if (NULL == finfo) return -1;

    for(finfo->nfft = 1; finfo->nfft < n; finfo->nfft <<= 1);
    unsigned int mfft = 1;
    while(mfft * mfft < finfo->nfft) mfft <<= 1;

    finfo->ip = NULL;
    finfo->fft_buf = finfo->w = finfo->wts = NULL;
    finfo->ip = (int *)malloc(sizeof(int) * (mfft + 100));
    finfo->fft_buf = (float *)malloc(sizeof(float) * finfo->nfft * 2);
    finfo->w = (float *)malloc(sizeof(float) * finfo->nfft * 2);
    finfo->wts = (float *)malloc(sizeof(float) * n);

    if (finfo->ip == NULL || finfo->fft_buf == NULL || finfo->w == NULL || finfo->wts == NULL) {
        if (finfo->ip != NULL) free(finfo->ip);
        if (finfo->fft_buf != NULL) free(finfo->fft_buf);
        if (finfo->w != NULL) free(finfo->w);
        if (finfo->wts != NULL) free(finfo->wts);

        return -1;
    }

    memset(finfo->ip, 0, sizeof(int) * (mfft + 100));
    int i;
    for(i = 0; i < n; i ++) finfo->wts[i] = 0.5 - 0.5 * cos(2.0 * PI * i / (n - 1));

    return 0;
}

void finfo_close(FFT_INFO *finfo)
{
    if (NULL == finfo)
    {
        fprintf(stderr, "Error.\n");
        exit(-1);
    }
    free(finfo->w);
    free(finfo->ip);
    free(finfo->fft_buf);
    free(finfo->wts);
}

void fft_it(const int16_t *indata, uint32_t n, double *outdata, FFT_INFO *finfo) {
    if (NULL == finfo) {
        fprintf(stderr, "Fatal error.\n");
        exit(-1);
    }
    int i;
    for(i = 0; i < n; i ++) {
        finfo->fft_buf[i * 2] = indata[i] * finfo->wts[i];
        finfo->fft_buf[i * 2 + 1] = 0;
    }
    for(; i < finfo->nfft; i ++) {
        finfo->fft_buf[i * 2] = finfo->fft_buf[i * 2 + 1] = 0;
    }
    cdft(finfo->nfft * 2, -1, finfo->fft_buf, finfo->ip, finfo->w);
    for(i = 0; i <= finfo->nfft / 2; i ++) {
        outdata[i] = sqrt(finfo->fft_buf[i * 2] * finfo->fft_buf[i * 2] +
                finfo->fft_buf[i * 2 + 1] * finfo->fft_buf[i * 2 + 1]);
    }
}

#else


static const  char *Wistemplate = "%s/.fftwis_%d";
#define WISLEN (8+64)

static int set_wisfile(MY_FFT_T *work, int nfft)
{
    char *home;
    if (work == NULL) return -1;
    if (work->Wisfile) return 1;
    home = getenv("HOME");
    if (!home)
        home = ".";
    work->Wisfile = (char *)malloc(strlen(home) + WISLEN + 2);
    if (work->Wisfile == NULL)
    {
        return -2;
    }
    sprintf(work->Wisfile, Wistemplate, home, nfft);
    return 0;
}

static int load_wisdom(MY_FFT_T *work, int nfft)
{
    FILE *wisdom = NULL;
    if (work == NULL) return -1;
    /* Get any accumulated wisdom. */
    if (set_wisfile(work, nfft) < 0) return -2;
    wisdom = fopen(work->Wisfile, "r");
    if (wisdom) {
        fftwf_import_wisdom_from_file(wisdom);
        fclose(wisdom);
        return 0;
    }  
    return -3;
}

static int save_wisdom(MY_FFT_T *work)
{
    FILE *wisdom = NULL;
    if (work == NULL) return -1;
    wisdom = fopen(work->Wisfile, "w");
    if (wisdom) {
        fftwf_export_wisdom_to_file(wisdom);
        fclose(wisdom);
        return 0;
    }
    return -2;
}

MY_FFT_T *fft_init(unsigned int nfft)
{
    FILE *wisdom = NULL;
    MY_FFT_T *work = NULL;

    work = (MY_FFT_T*) calloc(1, sizeof(MY_FFT_T));
    if (work == NULL) return work;
    work->in = (fftwf_complex*) malloc(nfft * sizeof(fftwf_complex));
    work->out = (fftwf_complex*) malloc(nfft * sizeof(fftwf_complex));
    if (work->in == NULL || work->out == NULL) {
        if (work->in != NULL) free(work->in);
        if (work->out != NULL) free(work->out);
        return NULL;
    }

    int loaded = (load_wisdom(work, nfft) == 0);

    work->plan=fftwf_plan_dft_1d(nfft,work->in,work->out,FFTW_FORWARD,FFTW_MEASURE);  

    if ( !loaded) { //not exist
        save_wisdom(work);
    }
    return work;
}

void fft_close(MY_FFT_T *work)
{
    if (work) {
        if (work->in) {     
            free(work->in);  work->in = NULL;
        }                     
        if (work->out) {    
            free(work->out); work-> out = NULL;
        }     
        fftwf_destroy_plan(work->plan);    
        free(work);
        work = NULL;
    }
}

void fft_it(unsigned int nfft, const int16_t* in_data0, double* out_data0,
        MY_FFT_T *work)
{
    int i;
    fftwf_complex*in  = work->in;
    fftwf_complex*out = work->out;
    if (work == NULL) return;
    for(i=0; i<nfft; i++) {
        in[i][0] = in_data0[i];
        in[i][1] = 0;
    }

    fftwf_execute(work->plan);

    for(i=0; i<=nfft/2; i++) {
        out_data0[i]  = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
    }
}

#endif

uint32_t stft(const int16_t *indata, uint32_t n, uint32_t window, uint32_t overlap, double *outdata) {
    int i, j;

#ifndef USE_FFTWF
    FFT_INFO *finfo = (FFT_INFO *)malloc(sizeof(FFT_INFO));
    if (finfo == NULL) {
        perror("Allocation error");
        exit(-1);
    }
    finfo_init(finfo, window);
#else
    MY_FFT_T *myfft = fft_init(window);
#endif

    for(i = j = 0; i + window <= n; i += window - overlap, j ++) {
#ifndef USE_FFTWF
        fft_it(indata + i, window, outdata + j * (finfo->nfft / 2 + 1), finfo);
#else
        fft_it(window, indata + i, outdata + j * (window / 2 + 1), myfft);
#endif
    }
#ifndef USE_FFTWF
    finfo_close(finfo);
    free(finfo);
#else
    fft_close(myfft);
#endif
    return j;
}
