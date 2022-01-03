#!/bin/bash

TOTAL=0
INPUT_DIR="input"
REF_DIR="ref"
OUTPUT_DIR="output"

BASIC_DIR="basic"
ADVANCED_DIR="advanced"
RANDOM_DIR="random"
BONUS_DIR="bonus"

PROGRAM="./$1"
TIMEOUT_SMALL=10
TIMEOUT_BIG=10
LOG="/dev/null"
DIFF_OPTIONS="--text --ignore-trailing-space --ignore-blank-lines"

TEST_BASIC_POINTS="30"
TEST_ADVANCED_POINTS="20"
TEST_RANDOM_POINTS="10"
TEST_BONUS_POINTS="10"

function print_header {
    echo "============== Tema 2 ============================="
}


function print_total {
    echo "TOTAL: $TOTAL"
}

function print_pass {
    TEST_NR="$1"
    TEST_POINTS="$2"
    PASSED_POINTS="$3"
    echo "Test$TEST_NR ........................... [$PASSED_POINTS/$TEST_POINTS]"
    TOTAL=$((TOTAL + PASSED_POINTS))
}

function check_test {
    TEST_NR="$1"
    TEST_POINTS="$2"
    TEST_DIR="$3"
    TIMEOUT_T="$4"
    TEST_INPUT_PATH="$INPUT_DIR/$TEST_DIR/test$1.in"
    TEST_REF_PATH="$REF_DIR/$TEST_DIR/test$1.ref"
    TEST_OUTPUT_PATH="$OUTPUT_DIR/$TEST_DIR/test$1.out"

    CURRENT_TOTAL=0
    gtimeout $TIMEOUT_T $PROGRAM < "$TEST_INPUT_PATH" > "$TEST_OUTPUT_PATH"
    diff $DIFF_OPTIONS "$TEST_OUTPUT_PATH" "$TEST_REF_PATH" &> "$LOG"

    if [ $? -eq 0 ]; then
        CURRENT_TOTAL=$((CURRENT_TOTAL + TEST_POINTS * 9 / 10))
        timeout $TIMEOUT_T valgrind --leak-check=full --error-exitcode=1 $PROGRAM < "$TEST_INPUT_PATH" > "$TEST_OUTPUT_PATH" 2>$LOG
        if [ $? -eq 0 ]; then
            CURRENT_TOTAL=$((CURRENT_TOTAL + TEST_POINTS * 1 / 10))
        fi
    fi

    print_pass "$TEST_NR" "$TEST_POINTS" "$CURRENT_TOTAL"
}

function init {
    rm -rf "$OUTPUT_DIR"
    mkdir "$OUTPUT_DIR"
    mkdir "$OUTPUT_DIR/$BASIC_DIR"
    mkdir "$OUTPUT_DIR/$ADVANCED_DIR"
    mkdir "$OUTPUT_DIR/$RANDOM_DIR"
    mkdir "$OUTPUT_DIR/$BONUS_DIR"
}

function run_basic {
    TEST_NR=$1

    echo "============== Basic Tests (15) ==================="

    if [ "$TEST_NR" == "" ]; then
        NR_TESTS=$(ls -l $INPUT_DIR/$BASIC_DIR/test*.in 2>$LOG | wc -l)
        for ((i=0; i<NR_TESTS; i++)); do
            check_test "$i" "$TEST_BASIC_POINTS" "$BASIC_DIR" "$TIMEOUT_SMALL"
        done
    else
        check_test "$TEST_NR" "$TEST_BASIC_POINTS" "$BASIC_DIR" "$TIMEOUT_SMALL"
    fi
}

function run_advanced {
    TEST_NR=$1

    echo "============ Advanced Tests (15) =================="

    if [ "$TEST_NR" == "" ]; then

        NR_TESTS=$(ls -l $INPUT_DIR/$ADVANCED_DIR/test*.in 2>$LOG | wc -l)
        for ((i=0; i<NR_TESTS; i++)); do
            check_test "$i" "$TEST_ADVANCED_POINTS" "$ADVANCED_DIR" "$TIMEOUT_SMALL"
        done
    else
        check_test "$TEST_NR" "$TEST_ADVANCED_POINTS" "$ADVANCED_DIR" "$TIMEOUT_SMALL"
    fi
}

function run_random {
    TEST_NR=$1

    echo "============ Random Tests (15) ===================="

    if [ "$TEST_NR" == "" ]; then
        NR_TESTS=$(ls -l $INPUT_DIR/$RANDOM_DIR/test*.in 2>$LOG | wc -l)
        for ((i=0; i<NR_TESTS; i++)); do
            check_test "$i" "$TEST_RANDOM_POINTS" "$RANDOM_DIR" "$TIMEOUT_BIG"
        done
    else
        check_test "$TEST_NR" "$TEST_RANDOM_POINTS" "$RANDOM_DIR" "$TIMEOUT_BIG"
    fi
}

function run_bonus {
    TEST_NR=$1

    echo "============ Bonus Tests (15) ====================="

    if [ "$TEST_NR" == "" ]; then
        NR_TESTS=$(ls -l $INPUT_DIR/$BONUS_DIR/test*.in 2>$LOG | wc -l)
        for ((i=0; i<NR_TESTS; i++)); do
            check_test "$i" "$TEST_BONUS_POINTS" "$BONUS_DIR" "$TIMEOUT_BIG"
        done
    else
        check_test "$TEST_NR" "$TEST_BONUS_POINTS" "$BONUS_DIR" "$TIMEOUT_BIG"
    fi
}

function run_all {

    print_header
    init

    run_basic
    run_advanced
    run_random
    run_bonus

    print_total
}

function check_is_number {
    REGEX='^[0-9]+$'
    NUMBER=$1

    if ! [[ $NUMBER =~ $REGEX ]]; then 
        echo "error: Not a number $NUMBER" >&2
        echo "Usage: bash checker.sh <name_executable> [basic|advanced|random|bonus|i] [<test_number>]"
        exit 1
    fi
}


function run_one_group {
    print_header
    init

    if [ "$1" == "basic" ]; then
        run_basic "$2"
    else
        if [ "$1" == "advanced" ]; then
            run_advanced "$2"
        else
            if [ "$1" == "random" ]; then
                run_random "$2"
            else
                if [ "$1" == "bonus" ]; then
                    run_bonus "$2"
                else
                    echo "Usage: bash checker.sh <name_executable> [basic|advanced|random|bonus|i] [<test_number>]"
                    exit 1
                fi
            fi
        fi
    fi

    print_total
}


if [ $# -eq 1 ]; then
    run_all
else
    if [ $# -eq 2 ]; then
        run_one_group "$2"
    else
        if [ $# -eq 3 ]; then
            check_is_number "$3"
            run_one_group "$2" "$3"
        else
            echo "Usage: bash checker.sh <name_executable> [basic|advanced|random|bonus] [<test_number>]"
            exit 1
        fi
    fi
fi

exit 0
