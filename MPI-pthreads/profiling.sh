for i in `seq 1 1`; 
do
  make run ARGS="$((2 ** $1)) 2" >> temp.out
  sleep 5
done

cat temp.out | grep Time > time.out
rm -f temp.out

count=0;
total=0; 
for i in $( awk '{ print $4 }' time.out )
  do 
    total=$(echo $total+$i | bc )
    ((count++))
  done
echo "scale=5; $total / $count" | bc
