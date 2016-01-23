touch o.txt
for i in $1/in*.txt
do
  echo $i
  valgrind --leak-check=full --error-exitcode=1 2>val_err.txt ./lab1 $1/$i o.txt
  rc=$?; if [[ $rc != 0 ]]; then echo "Valgrind failed "; fi
  diff o.txt $i/out${i:2:20}

done
