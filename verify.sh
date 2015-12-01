for ((i=1;i<=17;i+=1)); do ./lbp_omp $i > outputs-omp/output.k$i.txt; echo "test for k=$i of 17 done. Diff:"; diff outputs-seq/output.k$i.txt outputs-omp/output.k$i.txt; done;

