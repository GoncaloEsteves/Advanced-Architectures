#include "../headers/Extra.h"

void initMatrixes (float ***m1, float ***m2, float ***results, int N) {
    *m1 = (float**) malloc(N * sizeof(float*));
    *m2 = (float**) malloc(N * sizeof(float*));
    *results = (float**) malloc(N * sizeof(float*));

    srand(time(NULL));

    int i, j;

    for(i = 0; i < N; i++){
        (*m1)[i] = (float*) malloc(N * sizeof(float));
        (*m2)[i] = (float*) malloc(N * sizeof(float));
        (*results)[i] = (float*) malloc(N * sizeof(float));

        for(j = 0; j < N; j++){
            (*m1)[i][j] = (float) rand();
            (*m2)[i][j] = 1;
            (*results)[i][j] = 0;
        }
    }
}

int validatingColumns(float **m, int N) {
    int j, i;

    for(j = 0; j < N; j++){
        for(i = 1; i < N; i++){
            if(m[i-1][j] != m[i][j])
                return 0;
        }
    }

    return 1;
}

int validatingRows(float **m, int N) {
    int i, j;
    for(i = 0; i < N; i++){
        for(j = 1; j < N; j++){
            if(m[i][j-1] != m[i][j])
                return 0;
        }
    }

    return 1;
}