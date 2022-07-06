#!/bin/sh

#PBS -l walltime=2:00:00
#PBS -l nodes=1:r662:ppn=1
#PBS -q mei

cd /home/a85731/CPD/AA/AA

module load gcc/5.3.0
module load papi/5.5.0

make RegMatrixMult
make TransMatrixMult

for size in 32 128 1024 2048
do
    for version in 0 1 2
    do
        echo "Tamanho: $size, Versão: $version" >> results/RegMatrixMultFPOps.txt
        for i in 0 1 2 3 4 5 6 7
        do
            ./bin/RegMatrixMult $size $version >> results/RegMatrixMultFPOps.txt
        done
    done
done

for size in 32 128 1024 2048
do
    for version in 0 1
    do
        echo "Tamanho: $size, Versão: $version" >> results/TransMatrixMultFPOps.txt
        for i in 0 1 2 3 4 5 6 7
        do
            ./bin/TransMatrixMult $size $version >> results/TransMatrixMultFPOps.txt
        done
    done
done