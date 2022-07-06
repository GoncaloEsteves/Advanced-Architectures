#include "../headers/MatrixMult.h"
#include "../headers/Extra.h"
#include <stdlib.h>

int main (int argc, char *argv[]) {

    if(argc < 3){
        printf("./BlockMatrizMult #MatrixSize #Algorithm\n");
        printf("Algorithms:\n");
        printf("  - 0 = ijkBlocks\n");
        printf("  - 1 = ikjBlocks\n");
        printf("  - 2 = jkiBlocks\n");
        return 1;
    }

    int N = atoi(argv[1]);
    float **m1, **m2, **results;

    initMatrixes(&m1, &m2, &results, N);

    double start = omp_get_wtime();

    switch (argv[2][0]) {
        case '0':
            ijkBlocks(&m1, &m2, &results, N);
            break;

        case '1':
            ikjBlocks(&m1, &m2, &results, N);
            break;

        case '2':
            jkiBlocks(&m1, &m2, &results, N);
            break;
    
        default:
            break;
    }

    double end = omp_get_wtime();
	double exec_time = (end - start) * 1000;
	printf("      %gms\n", exec_time);
    
    return 0;
}