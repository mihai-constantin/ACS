#!/bin/bash

TIMEFORMAT=%R

FILE=file.txt
for i in {1..100}
do
	(time mpirun -np $3 tema3 $1 $2 blur smooth sharpen emboss mean blur smooth sharpen emboss mean) >> $FILE 2>&1
done
