#!/bin/bash

num_points=90
num_tests=27
points_per_test=$((num_points/num_tests))
EXE_1=task1
EXE_2=pacman
TESTING=checker
TOTAL=0

if [ ! -f 'README' ] && [ ! -f 'Readme' ]; then
    echo "README file not found!"       
fi

make clean
if [ $? -ne 0 ]; then
    exit 1
fi

make build
if [ $? -ne 0 ]; then
    exit 1
fi

function check_task() {
    # @params: TASK_ID
    INPUT=input_$1
    OUTPUT=output_$1
    REF=ref_$1

    if [ ! -f $1 ]; then
        echo "Executable file $1 was not generated!"
        exit 1
    fi

    echo

    for i in $(ls $INPUT); do
        IN_FILE=$INPUT/$i
        OUT_FILE=$OUTPUT/$(basename $i .in).out
        REF_FILE=$REF/$(basename $i .in).out

        ./$1 < $IN_FILE > $OUT_FILE

        #iwBu
        diff $OUT_FILE $REF_FILE &> /dev/null
        if [ $? -eq 0 ]; then
            TOTAL=$((TOTAL + points_per_test))
            echo -e "Test $i: ok ... $TOTAL/90"
        else
            echo -e "Test $i: failed ... $TOTAL/90"
        fi    
        # exit
    done
}

mkdir -p output_pacman output_task1

echo -e "\nRunning tests for TASK1: "
check_task $EXE_1

if [ $TOTAL -eq 15 ]; then
    echo "Task 1 solved!"
fi

echo -e "\nRunning tests for PACMAN: "
check_task $EXE_2


echo -e "\n=============="
echo "TOTAL: "$TOTAL"/90"
if [ $TOTAL -eq 90 ]; then
    echo "Congrats!"
fi
echo "=============="



echo -e "\nRemember: For the remaining 10% of the grade you need to include an informative Readme file and"
echo -e "and have a consistent coding style."
