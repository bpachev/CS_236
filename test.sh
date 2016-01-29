cd $1
touch o.txt
for i in in*.txt
do
  echo $i
  valgrind --leak-check=full --error-exitcode=1 2>val_err.txt ./../$2 $i o.txt
  rc=$?; if [[ $rc != 0 ]]; then echo "Valgrind failed "; exit 1; fi
  diff o.txt out${i:2:20}

done
