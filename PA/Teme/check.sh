#!/bin/bash

# Darius-Florentin Neatu <neatudarius@gmail.com>
# Copyright 2018

# DEBUG=on

total=0						# don't change
MAX_POINTS=130      		# you can change it
UTILS=_utils				# don't change
SOURCE_TMP_DIR=src_check	# don't change

# Put your tasks in this function
test_homework() {
	test_p1
	test_p2
	test_p3
	test_p4
}

# Task 1
test_p1() {
	src_names=(p1.c p1.cpp P1.java p1.py)
	tests=(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19)
	points=(1 1 1 1 1 1 1 1 1 1 1.5 1.5 1.5 1.5 1.5 1.5 1.5 1.5 1.5 1.5)
	pmax=25.0

	run_problem p1 1
}

# Task 2
test_p2() {
	src_names=(p2.c p2.cpp P2.java p2.py)
	tests=(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19)
	points=(1.75 1.75 1.75 1.75 1.75 1.75 1.75 1.75 1.75 1.75 1.75 1.75 1.75 1.75 1.75 1.75 1.75 1.75 1.75 1.75)
	pmax=35.0

	run_problem p2 2
}

# Task 3
test_p3() {
	src_names=(p3.c p3.cpp P3.java p3.py)
	tests=(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19)
	points=(2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2)
	pmax=40.0

	run_problem p3 3
}

# Task 4 - a.k.a bonus
test_p4() {
	src_names=(p4.c p4.cpp P4.java p4.py)
	tests=(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19)
	points=(1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1)
	pmax=20.0

	run_problem p4 4
}

###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################

check_readme() {
	README=README

	echo "------------------------------------------------------------"
	echo "------------------------------------------------------------"
	echo "================>>>>>> Check $README <<<<<< ================"

	score=0
	max_score=10

	if (( $(echo "scale = 2; $total == 0" |bc -l)  )); then
		echo "Punctaj $README neacordat. Punctajul pe teste este $total!"
	elif [ ! -f $README ]; then
		echo "$README lipsa."
	elif [ -f $README ] && [ "`ls -l $README | awk '{print $5}'`" == "0" ]; then
		echo "$README gol."
	else
		score=$max_score
		echo "$README OK. Punctajul final se va acorda la corectare."
	fi

	total=$(bc <<< "scale = 2; $total + $score")

	echo "===============>>>>>> $README: $score/$max_score <<<<<< ==============="
	echo "-------------------------------------------------------------"
	echo "-------------------------------------------------------------"
}

check_cpp_errors() {
	cnt_cpp=$(cat $1 | grep "Total errors found" | cut -d ':' -f2 | cut -d ' ' -f2)
}

check_java_errors() {
	cnt_java=$(cat $1 | grep -E "(WARN)|(ERR)" | wc -l)
}

timeout_test() {
	tag=$1
	timeout=$2

	(time gtimeout $timeout make $tag) &> error

	cnt=`cat error | grep "'$tag' failed" | wc -l`

	if [ $cnt -gt 0 ]; then
		t=`cat error | grep "real" | cut -d 'm' -f2 | cut -d 's' -f1 | tail -n 1`
		if [  $(echo "$t > $timeout" | bc) -eq 1  ]; then
			rm -f error
			echo "$t s" > tle
		fi
	else
		t=`cat error | grep "real" | cut -d 'm' -f2 | cut -d 's' -f1 | tail -n 1`
		echo "$t s" > output.time
		rm -f error
	fi
}

run_problem() {
	name=$1
	id=$2

	echo "------------------------------------------------------------"
	echo "------------------------------------------------------------"
	echo "---------------------- Problema $id: $name -----------------"

	score=0

	if  [ `find . -name ${src_names[0]} -o -name ${src_names[1]} -o -name ${src_names[2]} -o -name ${src_names[3]} | wc -l` -gt 1  ]; then
		echo "Surse multiple pentru problema $name! Trimite doar una!"
		echo "Numele sursei care contine functia main trebuie sa fie:"
		echo "${src_names[0]}, ${src_names[1]}, ${src_names[2]} sau ${src_names[3]}"
		echo "=============>>>>>> Scor : $score/$pmax <<<<<< ============="
		echo "------------------------------------------------------------"
		echo "------------------------------------------------------------"
		return
	elif [ `find . -name ${src_names[0]} | wc -l` -eq 1  ]; then
		timeout=`cat $UTILS/timeout/c.timeout$id`
		echo "---------------------- timp C => $timeout s -----------------"
	elif [ `find . -name ${src_names[1]} | wc -l` -eq 1  ]; then
		timeout=`cat $UTILS/timeout/c.timeout$id`
		echo "---------------------- timp C++ => $timeout s -----------------"
	elif [ `find . -name ${src_names[2]} | wc -l` -eq 1  ]; then
		timeout=`cat $UTILS/timeout/java.timeout$id`
		echo "---------------------- timp Java => $timeout s -----------------"
	elif [ `find . -name ${src_names[3]} | wc -l` -eq 1  ]; then
		timeout=`cat $UTILS/timeout/python.timeout$id`
		echo "---------------------- timp Python => $timeout s -----------------"
	else
		echo "Numele sursei care contine functia main trebuie sa fie:"
		echo "${src_names[0]}, ${src_names[1]}, ${src_names[2]} sau ${src_names[3]}"
		echo "=============>>>>>> Scor : $score/$pmax <<<<<< ============="
		echo "------------------------------------------------------------"
		echo "------------------------------------------------------------"
		return
	fi


	rm -rf $TESTS_DIR/$name/out/
	mkdir -p $TESTS_DIR/$name/out/
	
	for i in "${tests[@]}"; do
		if [ -z "`cat Makefile | grep run-p$id`" ]; then
			echo "Test $i problema $id .......... 0/${points[$i]} - Regula make inexistenta!"
			continue
		fi

		IN=$TESTS_DIR/$name/input/$i-$name.in
		REF=$TESTS_DIR/$name/ref/$i-$name.ref
		OUT=$TESTS_DIR/$name/out/$i-$name.out

		if [ ! -f $IN ]; then
			echo "Test $i problema $id .......... 0/${points[$i]} - $IN lipseste!"
			continue
		fi

		cp $IN $name.in
		cp $REF res.ok

		touch $name.out
		chmod 666 $name.out

		timeout_test run-p$id $timeout

		if [ -f error ]; then
			echo "Test $i problema $id .......... 0.0/${points[$i]} - Run time error!"
			# TODO
			# cat error
		elif [ -f tle ]; then
			echo "Test $i problema $id .......... 0.0/${points[$i]} - TLE - $(cat tle)!"
		else
			if [ $name == "p1" ]; then
				./verif_p1 $name.in $name.out res.ok ${points[$i]}	
			else
				./verif $name ${points[$i]}
			fi

			STATUS=$(cat output.verif)
			TIME=$(cat output.time)
			SCORE=$(cat score.verif)
			echo "Test $i problema $id .......... $SCORE/${points[$i]} - $STATUS - $TIME"
			total=$(bc <<< "scale = 2; $total + $SCORE")
			score=$(bc <<< "scale = 2; $score + $SCORE")
		fi

		if [ ! -z $DEBUG ]; then
			cp $name.out  $OUT
		fi

		rm -f $name.in $name.out res.ok score.verif output.verif output.time \
		  error.time error.exec error expected.time tle time.err run.err sd run.out 
	done

	echo "=============>>>>>> Scor : $score/$pmax <<<<<< ============="
	echo "------------------------------------------------------------"
	echo "------------------------------------------------------------"
}


TESTS_DIR=public_tests

# Check if Makefile exists
if [ ! -f Makefile ]; then
	echo "Makefile lipsa. STOP"
	echo "=============>>>>>> Total: $total/$MAX_POINTS <<<<<< ============="
	exit
fi


# Compile and check errors
make -f Makefile build &> out.make
cnt=$(cat out.make| grep failed | wc -l)

javac -version
g++ --version &> tmp; cat tmp | head -1
gcc --version &> tmp; cat tmp | head -1
python -V
python3 -V

# cat out.make
rm -f out.make
if [ $cnt -gt 0 ]; then
	echo "Erori de compilare. Verifica versiunea compilatorului. STOP"
	echo "=============>>>>>> Total: $total/$MAX_POINTS <<<<<< ============="
	exit
fi

# Compile checker
make -f Makefile.PA all $ONLINE_JUDGE &> /dev/null
rm -rf $SOURCE_TMP_DIR

# Display tests set
echo "---------------------- Run $TESTS_DIR -------------------"

# Run tests - change functions test_*
test_homework
check_readme

# Clean junk
make -f Makefile clean &> /dev/null
make -f Makefile.PA clean &> /dev/null
rm -rf tmp

# Display result
echo "=============>>>>>> Total: $total/$MAX_POINTS <<<<<< ============="
