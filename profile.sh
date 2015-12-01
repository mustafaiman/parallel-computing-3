gcc -std=c99 -o lbp_sec_profiling lbp_sec.c util.c -pg
for ((i=1;i<=17;i+=1)); do ./lbp_sec_profiling $i > reports-seq/output.k$i.txt; gprof lbp_sec_profiling gmon.out > reports-seq/report.k$i.txt; echo "profiling for k=$i of 17 done";  done;
