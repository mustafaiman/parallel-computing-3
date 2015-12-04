#!/bin/bash 
./lbp_seq 4 > iman_mustafa_seq_k4.output
echo "sequential with k=4 done";
./lbp_seq 8 > iman_mustafa_seq_k8.output
echo "sequential with k=8 done";
./lbp_seq 12 > iman_mustafa_seq_k12.output
echo "sequential with k=12 done";
./lbp_seq 16 > iman_mustafa_seq_k16.output
echo "sequential with k=16 done";
export OMP_NUM_THREADS=2
./lbp_omp 10 > iman_mustafa_omp_k10_t2.output
echo "parallel with k=10 and 2 threads done";
export OMP_NUM_THREADS=4
./lbp_omp 10 > iman_mustafa_omp_k10_t4.output
echo "parallel with k=10 and 4 threads done";
export OMP_NUM_THREADS=8
./lbp_omp 10 > iman_mustafa_omp_k10_t8.output
echo "parallel with k=10 and 8 threads done";
