gcc -std=c99 -o lbp_omp_profiling lbp_omp.c util.c -pg
for ((i=1;i<=17;i+=1)); do ./lbp_omp_profiling $i > reports-omp/output.k$i.txt; gprof lbp_omp_profiling gmon.out > reports-omp/report.k$i.txt; echo "profiling for k=$i of 17 done";  done;
