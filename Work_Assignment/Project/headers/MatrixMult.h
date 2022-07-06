#ifndef MATRIXMULT_H
#define MATRIXMULT_H
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define BLOCK 16

//Regular matrix multiplication
void ijk (float ***m1, float ***m2, float ***results, int N);
//Matrix multiplication by rows
void ikj (float ***m1, float ***m2, float ***results, int N);
//Matrix multiplication by columns
void jki (float ***m1, float ***m2, float ***results, int N);

//Regular matrix multiplication but transposing m2
void ijkTranspose (float ***m1, float ***m2, float ***results, int N);
//Matrix multiplication by columns but transposing both matrixes
void jkiTranspose (float ***m1, float ***m2, float ***results, int N);

//Regular matrix multiplication but transposing m2 and using the block optimization
void ijkBlocks (float ***m1, float ***m2, float ***results, int N);
//Matrix multiplication by rows using the block optimization
void ikjBlocks (float ***m1, float ***m2, float ***results, int N);
//Matrix multiplication by columns but transposing both matrixes and using the block optimization
void jkiBlocks (float ***m1, float ***m2, float ***results, int N);

//Regular matrix multiplication but transposing m2, using the block optimization and OpenMP
void ijkParallelBlocks (float ***m1, float ***m2, float ***results, int N);
//Matrix multiplication by rows but using the block optimization and OpenMP
void ikjParallelBlocks (float ***m1, float ***m2, float ***results, int N);
//Matrix multiplication by columns but transposing both matrixes, using the block optimization and OpenMP
void jkiParallelBlocks (float ***m1, float ***m2, float ***results, int N);

#endif