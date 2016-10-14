/*************************************************************************
    > File Name: main.c
    > Author: li_pengju
    > Mail: li_pengju@vobile.cn 
    > Copyright (c) Vobile Inc. All Rights Reserved
    > Created Time: 2016-09-20 16:58:30
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include "fft_utils.h"
static int32_t fft_once(const int16_t *indata, int n, int window, int overlap, double *outdata);
int main(int argc, char *argv[])
{
    FILE *fpcm = fopen(argv[1],"rb");
    if( fpcm == NULL){
        fprintf(stderr,"failed to open pcm file!\n");
        return -1;
    }
    fseek(fpcm, 0, SEEK_END);
    unsigned int size = ftell(fpcm);
    fseek(fpcm, 0, SEEK_SET);
    unsigned char *pcmBuf = malloc(size);
    fread(pcmBuf, size, 1, fpcm);
    unsigned int len = size / sizeof(int16_t);
    //fprintf(stdout,"pcmfile: %u bytes, %u signal numbers\n",size, len);
    const short *tmp = (short *)pcmBuf;

    int i ,j=0;
    for(i=128; i<= len / 2; i*=2 ){
        clock_t start = clock();
        int Window = i;
        int fftstep = Window / 2;
        int overlap = Window - fftstep;
        int width = Window / 2 + 1;
        double *S = (double *)malloc( sizeof(double) * width * len / fftstep );
        uint32_t m = fft_once(tmp, len, Window, overlap ,S);
        free(S);
        clock_t end = clock();
        double duration = 1000.0 * (double)(end - start) / CLOCKS_PER_SEC;
        double per_fft = duration*1000.0 / m;
        fprintf(stdout,"%d %f %f %u\n", j++, duration, per_fft, m);
    }
    //int n = len / Window * 2 + 1;
    return 0;
}
static int32_t fft_once(const int16_t *indata, int n, int window, int overlap, double *outdata) {
    if (indata == NULL || outdata == NULL) return -1;
    int i, j;
#ifndef USE_FFTWF
    //fprintf(stdout,"I am in USE_FFTWF\n");
    FFT_INFO *finfo = (FFT_INFO *)malloc(sizeof(FFT_INFO));
    if (finfo == NULL) return -1;
    if (finfo_init(finfo, window) != 0) {
        fprintf(stderr, "finfo_init error.\n");
        finfo_close(finfo);
        return -1;
    }
    for(i = j = 0; i + window <= n; i += window - overlap, j ++) {
        fft_it(indata + i, window, outdata + j * (finfo->nfft / 2 + 1), finfo);
    }
    finfo_close(finfo);
    free(finfo);
    finfo = NULL;
#else
    //fprintf(stdout,"I am in else\n");
    MY_FFT_T *myfft = fft_init(window);
    if (myfft == NULL) return -1;
    for(i = j = 0; i + window <= n; i += window - overlap, j ++) {
        fft_it(window, indata + i, outdata + j * (window / 2 + 1), myfft);
    }
    fft_close(myfft);
    myfft = NULL;
#endif
    return j;
}

