for i in `seq 1 10`;
do
  qsub -q all.q -cwd ./run.sh $1
  sleep 2
done
