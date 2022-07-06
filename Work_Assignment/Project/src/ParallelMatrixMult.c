#include "../headers/MatrixMult.h"
#include "../headers/Extra.h"
#include <stdlib.h>

int main (int argc, char *argv[]) {

    if(argc < 3){
        printf("./BlockMatrizMult #MatrixSize #Algorithm\n");
        printf("Algorithms:\n");
        printf("  - 0 = ijkParallelBlocks\n");
        printf("  - 1 = ikjParallelBlocks\n");
        printf("  - 2 = jkiParallelBlocks\n");
        return 1;
    }

    int N = atoi(argv[1]);
    float **m1, **m2, **results;

    initMatrixes(&m1, &m2, &results, N);

    double start = omp_get_wtime();

    switch (argv[2][0]) {
        case '0':
            ijkParallelBlocks(&m1, &m2, &results, N);
            break;

        case '1':
            ikjParallelBlocks(&m1, &m2, &results, N);
            break;

        case '2':
            jkiParallelBlocks(&m1, &m2, &results, N);
            break;
    
        default:
            break;
    }

    double end = omp_get_wtime();
	double exec_time = (end - start) * 1000;
	printf("      %gms\n", exec_time);

    return 0;
}