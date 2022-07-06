#!/bin/sh

#PBS -l walltime=2:00:00
#PBS -l nodes=1:r662:ppn=24
#PBS -q mei

cd /home/a85731/CPD/AA/AA

source /share/apps/intel/parallel_studio_xe_2019/compilers_and_libraries_2019/linux/bin/compilervars.sh intel64

module load gcc/5.3.0

for size in 2048
do
    for thread in 2 4 8 16 24
    do
        export OMP_NUM_THREADS=$thread
    
        for version in 0 1 2
        do
            echo "Tamanho: $size, Versão: $version, Threads: $thread" >> results/ParallelMatrixMult.txt
            for i in 0 1 2 3 4 5 6 7
            do
                ./bin/ParallelMatrixMult $size $version >> results/ParallelMatrixMult.txt
            done
        done
    done
done