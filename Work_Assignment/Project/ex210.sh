#!/bin/sh

#PBS -l walltime=2:00:00
#PBS -l nodes=1:r662:ppn=1
#PBS -q mei

cd /home/a85731/CPD/AA/AA

source /share/apps/intel/parallel_studio_xe_2019/compilers_and_libraries_2019/linux/bin/compilervars.sh intel64

module load gcc/5.3.0

for size in 2048
do
    for version in 0 1 2
    do
        echo "Tamanho: $size, Versão: $version" >> results/BlockMatrixMultNoVec.txt
        for i in 0 1 2 3 4 5 6 7
        do
            ./bin/BlockMatrixMult $size $version >> results/BlockMatrixMultNoVec.txt
        done
    done
done