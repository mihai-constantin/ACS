#!/bin/bash

## CONSTANTS ##
TOTAL=0
NR_TESTS=9
EXEC_NAME=tester

## FUNCTIONS ##

echo "======== Evaluator ========"

function checkTests
{
    time=0

    if [ ! -d "out" ]; then
        mkdir "out"
    fi

    for i in $(seq 0 $(($NR_TESTS))); do
        cp $EXEC_NAME "in"
        cd "in"
        mv "test"$i".in" "lca.in"
        ./$EXEC_NAME

        rm -f $EXEC_NAME

        mv "lca.in" "test"$i".in"
        mv "lca.out" "test"$i".out"

        mv "test"$i".out" ../"out"

        # mv "time"$i".out" ../out

        temp=$(head -n 1 time.out)
        time=`echo "$time+$temp" | bc`

        mv "time.out" "time"$i".out"

        rm -f "time"$i".out"

        cd ..

        if [[ -z $(diff --strip-trailing-cr "out/test"$i".out" "ref/test"$i".ref") ]]; then
                echo "Test"$i".............$(tput setaf 2)PASSED$(tput sgr0)"
                TOTAL=$((TOTAL + 10))
        else
            echo "Test"$i".............$(tput setaf 1)FAILED$(tput sgr0)"
        fi
    done
}

## CHECK TESTS
checkTests

echo ""

echo "TOTAL.............$TOTAL";
echo "TIME .............$time seconds";

