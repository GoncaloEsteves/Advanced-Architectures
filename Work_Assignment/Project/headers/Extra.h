#ifndef EXTRA_H
#define EXTRA_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Initialize all matrixes using N size
void initMatrixes (float ***m1, float ***m2, float ***results, int N);

//Validating A*B dot multiplication
int validatingRows(float **m, int N);

//Validating B*A dot multiplication
int validatingColumns(float **m, int N);

#endif