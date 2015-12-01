gcc -std=c99 -o lbp_sec lbp_sec.c util.c
gcc -std=c99 -o lbp_omp lbp_omp.c util.c -fopenmp
