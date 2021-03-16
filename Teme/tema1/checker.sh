#!/bin/bash

INPUT_DIR=tests/in
REF_DIR=tests/ref
OUTPUT_DIR=tests/out

mkdir -p "$OUTPUT_DIR"

SCORE=0
MAX_SCORE=120

trap ctrl_c INT

function ctrl_c() {
        echo "Exiting..."
        rm -rf byterun.log
        rm -rf "$OUTPUT_DIR"
        exit
}

print_header()
{
	header="${1}"
	header_len=${#header}
	printf "\n"
	if [ $header_len -lt 71 ]; then
		padding=$(((71 - $header_len) / 2))
		for ((i = 0; i < $padding; i++)); do
			printf " "
		done
	fi
	printf "= %s =\n\n" "${header}"
}

clean()
{
	rm -rf byterun.log
}

function checkTest
{
  clean
	racket byterun.rkt "$INPUT_DIR/test_$1.in" > "$OUTPUT_DIR/test_$1.out" 2> /dev/null

	if [ $? -eq 0 ]; then
		`diff -Bw -u --ignore-all-space "$REF_DIR/test_$1.ref" byterun.log &> /dev/null`
		DIFF_RESULT=$?

		if [ $DIFF_RESULT -eq 0 ]; then
			if (($1 >= 45 && $1 <= 49)); then
				`diff "$REF_DIR/test_$1.out" "$OUTPUT_DIR/test_$1.out" &> /dev/null`
				DIFF_RESULT=$?
				if [ $DIFF_RESULT -eq 0 ]; then
					result=1
					SCORE=$((SCORE+$3))
					echo -ne "+"$3": "
				else
					result=0
					echo -ne "+"$3": "
				fi
			else
				result=1
				SCORE=$((SCORE+$3))
				echo -ne "+"$3": "
			fi
		else
			result=0
			echo -ne "+"$3": "
		fi
		printf "Test $1 "
		if [ "$1" -gt 9 ]; then
			size=4
		else
			size=5
		fi

		for ((i = 0; i < $size; i++)); do
			printf "."
		done

		echo -ne " $2 "

		for ((i = 0; i < 56 - ${#2}; i++)); do
			printf "."
		done
		printf " "
		if [ $result -eq 1 ]; then
			echo -ne "OK\n"
		else
			echo -ne "FAIL (files differ)\n"
			diff "$REF_DIR/test_$1.ref" byterun.log
		fi
	else
		echo -ne "-0.0: Test $1 .... $2 "
		for ((i = 0; i < 56 - ${#2}; i++)); do
			printf "."
		done
		echo -ne " "
		echo -ne "FAIL (program error)\n"
	fi
	clean
}

print_header "Testing - Internal checker"
OUTPUT="$(racket checker.rkt)"
printf "$OUTPUT"
echo ""
score="${OUTPUT##*$'\n'}"
if [[ $score == "total"* ]]; then
	score=$(echo $score | cut -d ' ' -f 2)
	SCORE=${score%.*}
fi

print_header "Testing - PyPP byterun"

for i in {0..9}
do
	checkTest $i "Test LOAD_CONST/STORE_FAST/LOAD_FAST" 1
done
printf "\n"

for i in {10..24}
do
	checkTest $i "Test BINARY_ADD/BINARY_SUBTRACT/BINARY_MODULO" 2
done
printf "\n"

for i in {25..34}
do
	checkTest $i "Test IF" 2
done
printf "\n"

for i in {35..44}
do
	checkTest $i "Test FOR/WHILE" 2
done
printf "\n"

for i in {45..49}
do
	checkTest $i "Bonus CALL_FUNCTION(print)" 1
done
printf "\n"

for i in {50..54}
do
	checkTest $i "Bonus CALL_FUNCTION(range)" 1
done
printf "\n"

for i in {55..59}
do
	checkTest $i "Bonus CALL_FUNCTION(sqrt)" 1
done
printf "\n"

for i in {60..64}
do
	checkTest $i "Bonus CALL_FUNCTION(pow)" 1
done
printf "\n"

echo "Total ............... [$SCORE / $MAX_SCORE]"
rm -rf "$OUTPUT_DIR"
