#!/bin/bash


function init {

    numberOfTests=100

    points_per_task[1]=2
    points_per_task[2]=3
    points_per_task[3]=3
    points_per_task[4]=2

    total_per_task[1]=0
    total_per_task[2]=0
    total_per_task[3]=0
    total_per_task[4]=0

    make build
    if [ $? -ne 0 ]; then
        echo "Makefile failed!"
        exit 1
    fi
}

function prepare_test {
    cp "input/input_files/input${1}.txt" input.txt
    cp "input/captcha_files/captcha${1}.bmp" "captcha${1}.bmp"
    cp "input/captcha_bonus_files/captchaB${1}.bmp" "captchaB${1}.bmp"

    echo "TEST $1:"
}

function clean_test {
    rm -rf "input.txt" "captcha${1}.bmp" "captchaB${1}.bmp"

    # Comment this if you would like to keep the results of the tests
    rm -rf "captcha${1}_task1.bmp"
    rm -rf "captcha${1}_task2.txt"
    rm -rf "captcha${1}_task3.bmp"
    rm -rf "${1}.log"
    rm -rf "captchaB${1}_bonus.bmp"
}

function check_task {

    if [ $1 -eq 1 ]; then
	output_file="captcha"$2"_task1.bmp"
	ref_directory="ref/task$1"
    elif [ $1 -eq 2 ]; then
	output_file="captcha"$2"_task2.txt"
	ref_directory="ref/task$1"
    elif [ $1 -eq 3 ]; then
	output_file="captcha"$2"_task3.bmp"
	ref_directory="ref/task$1"
    else
	output_file="captchaB"$2"_bonus.bmp"
	ref_directory="ref/bonus"
    fi

    if [ -f $output_file ]; then
        diff -w $output_file "${ref_directory}/${output_file}" &>/dev/null
        if [ $? -eq 0 ]; then
	    total_per_task[$1]=$((total_per_task[$1]+points_per_task[$1]))
            if [ $1 -eq 4 ]; then
		echo "	Bonus: OK!"
	    else
		echo "	Task $1: OK!"
	    fi
        else
            if [ $1 -eq 4 ]; then
		echo " $test	Bonus: Wrong!"
	    else
		echo "	Task $1: Wrong!"
	    fi
        fi
    else
        if [ $1 -eq 4 ]; then
	    echo "	Bonus: Output file is missing"
	else
	    echo "	Task $1: Output file is missing"
	fi
    fi
}

function print_total {

    total_task1=`bc <<< "scale=2;${total_per_task[1]}/10"`
    total_task2=`bc <<< "scale=2;${total_per_task[2]}/10"`
    total_task3=`bc <<< "scale=2;${total_per_task[3]}/10"`
    total_bonus=`bc <<< "scale=2;${total_per_task[4]}/10"`
    echo "Total Task 1: $total_task1"
    echo "Total Task 2: $total_task2"
    echo "Total Task 3: $total_task3"
    echo "Total Bonus: $total_bonus"
    echo ""

    total=0;
    for ((i=1;i<=4;i++)) do
	total=$((total+total_per_task[i]))
    done

    echo "Total For Homework: " $((total / 10))
}


init

for ((test=1; test<=$numberOfTests; test++))
do

    prepare_test $test
    gtimeout 1 make -s run &>$test.log
    if [ $? -ne 0 ]; then
	echo "Test" $test "failed - no such target OR timeout."
        continue
    fi

    check_task 1 $test   
    check_task 2 $test
    check_task 3 $test
    check_task 4 $test

    clean_test $test
done
   
print_total
make clean
