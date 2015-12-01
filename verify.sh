for ((i=1;i<=17;i+=1)); do ./lbp_omp $i > outputs-omp/output.k$i.txt; echo "test for k=$i of 17 done. Diff:"; diff <( tail -n 1 outputs-omp/output.k$i.txt ) <( tail -n 1 outputs-seq/output.k$i.txt ); done;

