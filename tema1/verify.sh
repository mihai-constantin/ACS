#!/bin/bash

number_of_tests=10

if [ $# -eq 0 ]
  then
    echo "Usage: ./verify.sh <number of iterations>"
    exit 0
fi

for ((i = 1; i <= $1; i++ )); 
do
	echo "Starting iteration $i"
	time ./run_tests.sh >> output
	# sleep 5
done

answer=$(grep -o 'PASSED' output | wc -l)
expected_answer=$(( $1 * $number_of_tests ))

echo "$answer/$expected_answer"