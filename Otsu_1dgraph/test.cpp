/*************************************************************************
    > File Name: main.cpp
    > Author: li_pengju
    > Mail: li_pengju@vobile.cn 
    > Copyright (c) Vobile Inc. All Rights Reserved
    > Created Time: 2016-10-10 16:26:59
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
typedef struct{
    int pos;
    double score;
}PosScore;
static int locmax(PosScore *d, int n);
static int cmpScore(const void *a1, const void *b1);
int main(int argc, char* argv[])
{
    FILE *fp = fopen(argv[1], "rt");
    if(!fp){
        fprintf(stderr,"Failed to open %s\n",argv[1]);
        return -1;
    }
    char line[200];
    int i, j, pos;
    double score;
    int count = 0;
    while( fgets(line, 200, fp) != NULL ){
        //sscanf(line,"%d %f\n", &pos, &score);
        count ++;
    }
    fprintf(stdout,"totally %d lines\n",count);
    
    PosScore *wav = (PosScore *)calloc(count, sizeof(PosScore));
    fseek(fp, 0, SEEK_SET);
    count = 0;
    while( fgets(line, 200, fp) != NULL ){
        sscanf(line, "%d %lf\n", &pos, &score);
        wav[count].pos = pos;
        wav[count].score = score;
        count ++;
    }

    int nPeaks = locmax(wav, count);
    fprintf(stdout,"find %d peaks\n",nPeaks);

    double sumTotal = 0.0;
    PosScore *data = (PosScore *)malloc(nPeaks * sizeof(PosScore));
    for(i = 0, j = 0; i < count; i ++){
        if(wav[i].score > 0){
            data[j].pos = wav[i].pos;
            data[j].score = wav[i].score;
            sumTotal += data[j].score;
            j ++;
        }
    }
    free(wav);

    qsort(data, nPeaks, sizeof(data[0]), cmpScore);
    fprintf(stdout, "record %d peaks\n", j);
    int between;
    double maxVar = 0;
    double realCnt = sumTotal;
    for(i = 0, sumTotal = 0; i < nPeaks; i ++)
        sumTotal += data[i].score * (i+1);
    double Avg = sumTotal / nPeaks;
    int Tscore;
    for(Tscore = 1; Tscore < nPeaks - 1; Tscore ++){
        double cntw0 = 0, sum0 = 0;
        for(i = 0; i < Tscore; i ++){
            cntw0 += data[i].score;
            sum0 += data[i].score * (i+1);
        }
        double cntw1 = realCnt - cntw0;
        double sum1 = sumTotal - sum0;
        double avg0 = sum0 / cntw0;
        double avg1 = sum1 / cntw1;
        double w0 = 1.0 * cntw0 / nPeaks;
        double w1 = 1.0 * cntw1 / nPeaks;
        double var = w0 * (avg0 - Avg) * (avg0 - Avg) + w1 * (avg1 - Avg) * (avg1 - Avg );
        //fprintf(stdout,"var = %lf\n",var);
        if(var > maxVar){
            maxVar = var;
            between = Tscore;
        }
    }

    fprintf(stdout, "between = %d\n", between);
    FILE *fout = fopen("1dout.dat","wt");
    for(i = 0; i < nPeaks; i ++)
        fprintf(fout,"%d %lf\n",i+10, data[i].score * (i+1));
    fclose(fout);
    return 0;
}

static int locmax(PosScore *d, int n) {
	if(!d)
		return -1;
	int i;
    int nPeak = 0;
	int *tmp = (int *)alloca(sizeof(int) * (n+1));
	if (tmp == NULL) return -1;
	tmp[0] = tmp[n] = 1;
	for(i = 1; i<n; i++)
	{
		if(d[i].score >= d[i-1].score)
			tmp[i] = 1;
		else
			tmp[i] = 0;
	}
    for(i = 0; i < n; i++){
        d[i].score = d[i].score*tmp[i]*(1-tmp[i+1]);
        if( d[i].score > 0 )
            nPeak ++;
    }
	return nPeak;
}

static int cmpScore(const void *a1, const void *b1){
    PosScore *a = (PosScore *)a1;
    PosScore *b = (PosScore *)b1;
    if(a->score > b->score) return 1;
    else if(a->score < b->score) return -1;
    else return 0;
}
