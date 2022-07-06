#include "../headers/MatrixMult.h"

/*-----------------------------------------Auxiliary Functions-------------------------------------------*/

void transpose (float ***m, int N) {
    float aux;
    int i, j;

    for(i = 0; i < N; i++){
        for(j = i+1; j < N; j++){
            aux = (*m)[i][j];
            (*m)[i][j] = (*m)[j][i];
            (*m)[j][i] = aux;
        }
    }
}

/*-------------------------------------Regular Matrix Multiplications------------------------------------*/

void ijk (float ***m1, float ***m2, float ***results, int N) {
    int i, j, k;

    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            for(k = 0; k < N; k++)
                (*results)[i][j] += (*m1)[i][k] * (*m2)[k][j];
        }
    }
}

void ikj (float ***m1, float ***m2, float ***results, int N) {
    int i, j, k;
    
    for(i = 0; i < N; i++){
        for(k = 0; k < N; k++){
            for(j = 0; j < N; j++)
                (*results)[i][j] += (*m1)[i][k] * (*m2)[k][j];
        }
    }
}

void jki (float ***m1, float ***m2, float ***results, int N) {
    int i, j, k;
    
    for(j = 0; j < N; j++){
        for(k = 0; k < N; k++){
            for(i = 0; i < N; i++)
                (*results)[i][j] += (*m1)[i][k] * (*m2)[k][j];
        }
    }
}

/*----------------------------Matrix Multiplications with Transposed Matrixes----------------------------*/

void ijkTranspose (float ***m1, float ***m2, float ***results, int N) {
    transpose(m2, N);
    int i, j, k;

    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            for(k = 0; k < N; k++)
                (*results)[i][j] += (*m1)[i][k] * (*m2)[j][k];
        }
    }
}

void jkiTranspose (float ***m1, float ***m2, float ***results, int N) {
    transpose(m1, N);
    transpose(m2, N);
    int i, j, k;

    for(j = 0; j < N; j++){
        for(k = 0; k < N; k++){
            for(i = 0; i < N; i++)
                (*results)[j][i] += (*m1)[k][i] * (*m2)[j][k];
        }
    }

    transpose(results, N);
}

/*-----------------------------Matrix Multiplications with Block Optimization----------------------------*/

void ijkBlocks (float ***m1, float ***m2, float ***results, int N) {
    transpose(m2, N);
    int i, j, k, jj, ii;

    for(jj = 0; jj < N; jj += BLOCK){
        for(ii = 0; ii < N; ii += BLOCK){
            for(i = 0; i < N; i++){
                for(j = jj; j < jj+BLOCK; j++){
                    #pragma ivdep
                    for(k = ii; k < ii+BLOCK; k++)
                        (*results)[i][j] += (*m1)[i][k] * (*m2)[j][k];
                }
            }
        }
    }
}

void ikjBlocks (float ***m1, float ***m2, float ***results, int N) {
    int i, j, k, jj, ii;

    for(ii = 0; ii < N; ii += BLOCK){
        for(jj = 0; jj < N; jj += BLOCK){
            for(i = 0; i < N; i++){
                for(k = ii; k < ii+BLOCK; k++){
                    #pragma ivdep
                    for(j = jj; j < jj+BLOCK; j++)
                        (*results)[i][j] += (*m1)[i][k] * (*m2)[k][j];
                }
            }
        }
    }
}

void jkiBlocks (float ***m1, float ***m2, float ***results, int N) {
    transpose(m1, N);
    transpose(m2, N);
    int i, j, k, jj, ii;

    for(jj = 0; jj < N; jj += BLOCK){
        for(ii = 0; ii < N; ii += BLOCK){
            for(j = 0; j < N; j++){
                for(k = jj; k < jj+BLOCK; k++){
                    #pragma ivdep
                    for(i = ii; i < ii+BLOCK; i++)
                        (*results)[j][i] += (*m1)[k][i] * (*m2)[j][k];
                }
            }
        }
    }

    transpose(results, N);
}

/*------------------------Parallel Matrix Multiplications with Block Optimization-------------------------*/

void ijkParallelBlocks (float ***m1, float ***m2, float ***results, int N) {
    transpose(m2, N);
    int i, j, k, jj, ii, threads;

    #pragma omp parallel
    {
        #pragma omp single
        threads = omp_get_num_threads();
    }

    #pragma omp parallel num_threads(threads) private(i, j, k, jj, ii)
    {
        for(jj = 0; jj < N; jj += BLOCK){
            for(ii = 0; ii < N; ii += BLOCK){
                #pragma omp for
                for(i = 0; i < N; i++){
                    for(j = jj; j < jj+BLOCK; j++){
                        #pragma omp simd
                        for(k = ii; k < ii+BLOCK; k++)
                            (*results)[i][j] += (*m1)[i][k] * (*m2)[j][k];
                    }
                }
            }
        }
    }
}

void ikjParallelBlocks (float ***m1, float ***m2, float ***results, int N) {
    int i, j, k, jj, ii, threads;

    #pragma omp parallel
    {
        #pragma omp single
        threads = omp_get_num_threads();
    }

    #pragma omp parallel num_threads(threads) private(i, j, k, jj, ii)
    {
        for(ii = 0; ii < N; ii += BLOCK){
            for(jj = 0; jj < N; jj += BLOCK){
                #pragma omp for
                for(i = 0; i < N; i++){
                    for(k = ii; k < ii+BLOCK; k++){
                        #pragma omp simd
                        for(j = jj; j < jj+BLOCK; j++)
                            (*results)[i][j] += (*m1)[i][k] * (*m2)[k][j];
                    }
                }
            }
        }
    }
}

void jkiParallelBlocks (float ***m1, float ***m2, float ***results, int N) {
    transpose(m1, N);
    transpose(m2, N);
    int i, j, k, jj, ii, threads;

    #pragma omp parallel
    {
        #pragma omp single
        threads = omp_get_num_threads();
    }

    #pragma omp parallel num_threads(threads) private(i, j, k, jj, ii)
    {
        for(jj = 0; jj < N; jj += BLOCK){
            for(ii = 0; ii < N; ii += BLOCK){
                #pragma omp for
                for(j = 0; j < N; j++){
                    for(k = jj; k < jj+BLOCK; k++){
                        #pragma omp simd
                        for(i = ii; i < ii+BLOCK; i++)
                            (*results)[j][i] += (*m1)[k][i] * (*m2)[j][k];
                    }
                }
            }
        }
    }

    transpose(results, N);
}