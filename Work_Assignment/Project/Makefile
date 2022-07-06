CC = gcc

PAPI = -lpapi -DPAPI

FLAGS = -O2 -L/share/apps/papi/5.5.0/lib -I/share/apps/papi/5.5.0/include -Wall -Wextra -fopenmp -Wno-unused-parameter

VEC = -O3 -Wall -Wextra -qopenmp -Wno-unused-parameter -qopt-report=3 -qopt-report-phase=vec

all: RegMatrixMult TransMatrixMult BlockMatrixMult ParallelMatrixMult

RegMatrixMult: src/RegMatrixMult.c src/Extra.c headers/Extra.h src/MatrixMult.c headers/MatrixMult.h
	$(CC) -o bin/RegMatrixMult $(FLAGS) $(PAPI) src/Extra.c src/MatrixMult.c src/RegMatrixMult.c

TransMatrixMult: src/TransMatrixMult.c src/Extra.c headers/Extra.h src/MatrixMult.c headers/MatrixMult.h
	$(CC) -o bin/TransMatrixMult $(FLAGS) $(PAPI) src/Extra.c src/MatrixMult.c src/TransMatrixMult.c

BlockMatrixMult: src/BlockMatrixMult.c src/Extra.c headers/Extra.h src/MatrixMult.c headers/MatrixMult.h
	icc -o bin/BlockMatrixMult $(VEC) src/Extra.c src/MatrixMult.c src/BlockMatrixMult.c

ParallelMatrixMult: src/ParallelMatrixMult.c src/Extra.c headers/Extra.h src/MatrixMult.c headers/MatrixMult.h
	icc -o bin/ParallelMatrixMult $(VEC) src/Extra.c src/MatrixMult.c src/ParallelMatrixMult.c

CUDAMatrixMult: src/CUDAMatrixMult.cu
	nvcc -o bin/CUDAMatrixMult -O3 -DD_GPU -arch=sm_30 src/CUDAMatrixMult.cu

.PHONY: clean

clean:
	rm -f bin/*