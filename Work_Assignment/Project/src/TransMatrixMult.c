#include "../headers/MatrixMult.h"
#include "../headers/Extra.h"
#include <stdlib.h>
#include <papi.h>

#define NUM_EVENTS 1
//#define NUM_EVENTS 2
//#define NUM_EVENTS 4

long long values[NUM_EVENTS];

int Events[NUM_EVENTS] = {PAPI_FP_OPS};
//int Events[NUM_EVENTS] = {PAPI_L3_TCM, PAPI_TOT_INS};
//int Events[NUM_EVENTS] = {PAPI_L2_DCR, PAPI_L3_DCR, PAPI_L2_TCM, PAPI_LD_INS}

int EventSet = PAPI_NULL;

int main (int argc, char *argv[]) {

    if(argc < 3){
        printf("./TransMatrizMult #MatrixSize #Algorithm\n");
        printf("Algorithms:\n");
        printf("  - 0 = ijkTranspose\n");
        printf("  - 1 = jkiTranspose\n");
        return 1;
    }

	PAPI_library_init(PAPI_VER_CURRENT);
    PAPI_create_eventset(&EventSet);
    PAPI_add_events(EventSet, Events, NUM_EVENTS);

    int N = atoi(argv[1]);
    float **m1, **m2, **results;

    initMatrixes(&m1, &m2, &results, N);

    PAPI_start(EventSet);
    double start = omp_get_wtime();

    switch (argv[2][0]) {
        case '0':
            ijkTranspose(&m1, &m2, &results, N);
            break;

        case '1':
            jkiTranspose(&m1, &m2, &results, N);
            break;
    
        default:
            break;
    }

    double end = omp_get_wtime();
	double exec_time = (end - start) * 1000;
	printf("      %gms\n", exec_time);
    PAPI_stop(EventSet, values);

    printf("    PAPI_FP_OPS: %lld\n", values[0]);
    //printf("    PAPI_L3_TCM: %lld\n    PAPI_TOT_INS: %lld\n", values[0], values[1]);
    //printf("    PAPI_L2_DCR: %lld\n    PAPI_L3_DCR: %lld\n    PAPI_L2_TCM: %lld\n    PAPI_LD_INS: %lld\n", values[0], values[1], values[2], values[3]);

    return 0;
}