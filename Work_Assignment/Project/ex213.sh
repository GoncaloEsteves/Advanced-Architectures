#!/bin/sh

#PBS -l walltime=2:00:00
#PBS -l nodes=1:k20:ppn=1
#PBS -q mei

cd /home/a85731/CPD/AA/AA

module load gcc/5.3.0
module load cuda/10.1

make CUDAMatrixMult

for size in 2048
do
    echo "Tamanho: $size, Versão: $version" >> results/CUDAMatrixMult.txt
    for i in 0 1 2 3 4 5 6 7
    do
        ./bin/CUDAMatrixMult $size >> results/CUDAMatrixMult.txt
    done
done