#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#define TIMEDUR 1.0
typedef struct{
	int cnt;
	int xoff;
}PointSlope;
typedef struct{
	int x;
	int y;
    char ID[100];
	float rate;
}CoordRate;
typedef struct{
    int cnt;
    char ID[100];
    int xoff;
}Res;
static int cmpRes(const void *a1, const void *b1);
static int cmpID(const void *a1, const void *b1);
static int get_statistic(CoordRate *data, int n, Res *Result);
int main(int argc, char* argv[])  
{
	float dur;
    dur = TIMEDUR;
    FILE *fp = fopen(argv[1], "rt");
    if (!fp) {
        fprintf(stderr,"Failed to open files !\n");
        return 1;
    }
    char line[200];
    int i, j;
    int t_smp, t_mst;
	float rate;
    char id[100];

    //int tmin_smp = 0, tmax_smp = 0;
    //int tmin_mst = 0, tmax_mst = 0;
	int countline = 0;
	while( fgets(line, 200, fp) != NULL )
		 countline++;
    if( countline < 1 ) {
        fprintf(stderr, "Empty file !\n");
        return -1;
    }
	CoordRate *point = (CoordRate *)calloc( countline, sizeof(CoordRate) ); 
    if( point == NULL ) {
        fprintf(stderr, "calloc error !\n");
        return -1;
    }
	fseek(fp, 0, SEEK_SET);
	countline = 0;
    while (fgets(line, 200, fp) != NULL){
        sscanf(line, "%d %d %s %f\n", &t_smp, &t_mst, id, &rate);
		point[countline].x = t_smp;
		point[countline].y = t_mst;
        strcpy(point[countline].ID, id);
		point[countline].rate = rate;
		countline++;
   }
    fclose(fp);
    
    qsort(point, countline, sizeof(CoordRate), cmpID);

    int idNum = 1, cntn = 1;
    strcpy(id, point[0].ID);
    for( i = 1; i < countline; i ++ )
        if( strcmp(id, point[i].ID) != 0 ) {
            idNum ++;
            strcpy(id, point[i].ID);
        }

    Res *Result = malloc(idNum * sizeof(Res));
    if( Result == NULL ) {
        fprintf(stderr, "Result malloc error !\n");
        return -1;
    }
    j = 0;
    strcpy(id, point[0].ID);
    for(i = 1; i < countline; i ++) {
        if( strcmp(id, point[i].ID) != 0) {
            get_statistic(point + i - cntn, cntn, &Result[j]);
            strcpy(Result[j].ID, point[i-1].ID);
            strcpy(id, point[i].ID);
            j++;
            cntn = 0;
        }
        cntn ++;
    }
    get_statistic(point + i - cntn, cntn, &Result[j]);
    strcpy(Result[j].ID, point[countline -1].ID);

    if( idNum > 1 )
        qsort(Result, idNum, sizeof(Res), cmpRes);
    if(Result[0].cnt < 2) {
        fprintf(stderr, "No match !\n");
        return -1;
    }
    else {
        for( i = 0; i < idNum; i ++ )
            fprintf(stdout, "%s %d\n", Result[i].ID, Result[i].xoff);
        FILE *outfile = fopen(argv[2], "w");
        if(!outfile) {
            fprintf(stderr, "Cannot write to linepoint.log!\n");
            return -1;
        }
        for(i = 0; i < countline; i ++) {
            if(strcmp(point[i].ID, Result[0].ID) == 0){
                if(point[i].x - point[i].y == Result[0].xoff)
                    fprintf(outfile, "%d %d\n", point[i].x, point[i].y);
            }
            else
                continue;
        }
        fclose(outfile);
    }

	free( point );
    free( Result );
    return 0;
}  
static int cmpRes(const void *a1, const void *b1){
	Res *a = (Res *)a1, *b = (Res *)b1;
	if( a->cnt > b->cnt ) return -1;
	else if( a->cnt < b->cnt ) return 1;
	else if( a->xoff > b->xoff) return -1;
	else if( a->xoff < b->xoff) return 1;
	else return 0;
}

static int cmpID(const void *a1, const void *b1) {
    CoordRate *a = (CoordRate *)a1, *b = (CoordRate *)b1;
    if( strcmp(a->ID, b->ID) < 0 ) return -1;
    else if(strcmp(a->ID, b->ID) > 0) return 1;
    else if(a->x < b->x) return -1;
    else if(a->x > b->x) return 1;
    else if(a->y < b->y) return -1;
    else if(a->y > a->y) return 1;
    else return 0;
}

static int get_statistic(CoordRate *data, int n, Res *Result)
{
    int tmax_smp = data[n-1].x;
    int tmax_mst = data[n-1].y;
    PointSlope *cntit = (PointSlope *)calloc(tmax_mst + tmax_smp + 1, sizeof(PointSlope));
    if( cntit == NULL )
        return -1;
    int i, sn, maxcnt = 0;
    for(i=0; i < n; i ++) {
        sn = data[i].x - data[i].y + tmax_mst;
        cntit[sn].cnt++;
        cntit[sn].xoff = sn - tmax_mst;
    }

    for(i = 0; i < tmax_mst + tmax_smp + 1; i ++) {
        if( cntit[i].cnt > maxcnt ) {
            maxcnt = cntit[i].cnt;
            Result->cnt = maxcnt;
            Result->xoff = cntit[i].xoff;
        }
    }
    free(cntit);
    //return maxcnt;
    return 0;
}
