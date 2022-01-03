#!/bin/bash

make
./tema1

score=0

begin_test='test_'
begin_result='results/result_'
termination='.txt'

arr=( "easy_0" "easy_1" "easy_2" "medium_1" "medium_2" "complex_1" "complex_2" )
arr2=( "easy_0..." "easy_1..." "easy_2..." "medium_1." "medium_2." "complex_1" "complex_2" )
scores=( 5 10 10 10 10 20 20 )

for i in {0..6}
do
    element=${arr[$i]}
    testFileName=$begin_test$element$termination
    resultFileName=$begin_result$element$termination
    result=$(diff $testFileName $resultFileName | grep "^>" | wc -l)

    if [ -f $testFileName ] && [ -f $resultFileName ] && [ "$result" -eq "0" ]; then
        echo "Test ${arr2[$i]}...........................passed"
        score=$((score+${scores[$i]}))
    else
        echo "Test ${arr2[$i]}...........................failed"
    fi
done

echo "                                      Total: $score"

make clean
