#!/bin/bash 
gcc -std=c99 -o lbp_seq lbp_seq.c util.c
gcc -std=c99 -o lbp_omp lbp_omp.c util.c -fopenmp
