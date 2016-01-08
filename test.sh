for i in in*.txt
do
  echo $i
  ./lab1 $i > o.txt
  diff o.txt out${i:2:20}
done
