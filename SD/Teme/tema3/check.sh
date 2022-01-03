#!/bin/bash

# Copyright 2018

# DEBUG=on

total=0						# don't change
MAX_POINTS=100      		# you can change it
UTILS=_utils				# don't change
SOURCE_TMP_DIR=src_check	# don't change

# Put your tasks in this function
test_homework() {
	test_scoala
}

test_scoala() {
	src_names=(scoala.c)
	tests=(1 2 3 4 5 6 7 8 9 10)
	points=(8.5 8.5 8.5 8.5 8.5 8.5 8.5 8.5 8.5 8.5 8.5)
	pmax=85.0

	run_problem scoala 1
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
	max_score=5

	if (( $(echo "$total == 0" |bc -l)  )); then
		echo "Punctaj $README neacordat. Punctajul pe teste este $total!"
	elif [ ! -f $README ]; then
		echo "$README lipsa."
	elif [ -f $README ] && [ "`ls -l $README | awk '{print $5}'`" == "0" ]; then
		echo "$README gol."
	else
		score=$max_score
		echo "$README OK. Punctajul final se va acorda la corectare."
	fi

	total=$(bc <<< "$total + $score")

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

check_coding_style_dummy() {
	echo "-------------------------------------------------------------"
	echo "-------------------------------------------------------------"
	echo "===============>>>>>> SKIP coding style <<<<<< ==============="


	max_score=10
	score=$max_score
	total=$(bc <<< "$total + $score")
	echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
	echo "Punctajul final se va acorda la corectare (inclusiv testare valgrind)."
	echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
	echo "===============>>>>>> Coding style: $score/$max_score <<<<<< ==============="
	echo "-------------------------------------------------------------"
	echo "-------------------------------------------------------------"

	rm -f cpp.errors java.errors
}

check_coding_style_full() {
	echo "-------------------------------------------------------------"
	echo "-------------------------------------------------------------"
	echo "===============>>>>>> Check coding style <<<<<< ==============="


	max_score=5
	score=$max_score

	if (( $(echo "$total == 0" |bc -l)  )); then
		score=0
		echo "Punctaj Coding style neacordat. Punctajul pe teste este $total!"
	else
		# Make a copy of sources in a temporary directory
		rm -rf $SOURCE_TMP_DIR
		mkdir $SOURCE_TMP_DIR
		cd $SOURCE_TMP_DIR
		sources=$(find .. -name *  -a \( -name '*.cpp' -o -name '*.c' -o -name '*.java' -o -name '*.h' -o -name '*.hpp'  \))
		cp $sources .

		check_cpp=../$UTILS/coding_style/check_cpp.py
		python $check_cpp *.cpp &> cpp.errors

		check_java=../$UTILS/coding_style/check_java.jar
		java_errors=../$UTILS/coding_style/java_errors.xml
		java -jar $check_java -c $java_errors *.java 2&> java.errors

		check_cpp_errors cpp.errors
		check_java_errors java.errors

		cat cpp.errors
		cat java.errors
		if [ $cnt_cpp -gt 0 ] || [ $cnt_java -gt 0 ]; then
			score=0


			echo "$cnt_cpp C/C++ errors found."
			echo "$cnt_java Java errors found."
		else
			echo "Coding style OK. Punctajul final se poate modifica la corectare."
		fi

		# Clean temporary directory
		cd ..
		rm -rf $SOURCE_TMP_DIR
	fi

	total=$(bc <<< "$total + $score")

	echo "===============>>>>>> Coding style: $score/$max_score <<<<<< ==============="
	echo "-------------------------------------------------------------"
	echo "-------------------------------------------------------------"

	rm -f cpp.errors java.errors
}


check_coding_style() {
	# Check if platform is online

	check_coding_style_dummy
}

timeout_test() {
	tag=$1
	timeout=$2

	(time timeout $timeout make $tag) &> error

	cnt=`cat error | grep "'$tag' failed" | wc -l`

	if [ $cnt -gt 0 ]; then
		t=`cat error | grep "real" | cut -d 'm' -f2 | cut -d 's' -f1`
		if [  $(echo "$t > $timeout" | bc) -eq 1  ]; then
			rm -f error
			echo "$t s" > tle
		fi
	else
		t=`cat error | grep "real" | cut -d 'm' -f2 | cut -d 's' -f1`
		echo "$t s" > output.time
		rm -f error
	fi
}

run_problem() {
	name=$1
	id=$2

	echo "------------------------------------------------------------"
	echo "------------------------------------------------------------"
	echo "---------------------- Problema $name -----------------"

	score=0

	if  [ `find -name ${src_names[0]} | wc -l` -gt 1  ]; then
		echo "Surse multiple pentru problema $name! Trimite doar una!"
		echo "Numele sursei care contine functia main trebuie sa fie:"
		echo "${src_names[0]}"
		echo "=============>>>>>> Scor : $score/$pmax <<<<<< ============="
		echo "------------------------------------------------------------"
		echo "------------------------------------------------------------"
		return
	elif [ `find -name ${src_names[0]} | wc -l` -eq 1  ]; then
		timeout=`cat $UTILS/timeout/c.timeout$id`
		echo "---------------------- timp C => $timeout s -----------------"
	elif [ `find -name ${src_names[1]} | wc -l` -eq 1  ]; then
		timeout=`cat $UTILS/timeout/c.timeout$id`
		echo "---------------------- timp C++ => $timeout s -----------------"
	elif [ `find -name ${src_names[2]} | wc -l` -eq 1  ]; then
		timeout=`cat $UTILS/timeout/java.timeout$id`
		echo "---------------------- timp Java => $timeout s -----------------"
	else
		echo "Numele sursei care contine functia main trebuie sa fie:"
		echo "${src_names[0]}, ${src_names[1]} sau ${src_names[2]}"
		echo "=============>>>>>> Scor : $score/$pmax <<<<<< ============="
		echo "------------------------------------------------------------"
		echo "------------------------------------------------------------"
		return
	fi


	rm -rf $TESTS_DIR/$name/out/
	mkdir -p $TESTS_DIR/$name/out/
	
	for i in "${tests[@]}"; do
		if [ -z "`cat Makefile | grep run`" ]; then
			echo "Test $i .......... 0/${points[$i]} - Regula make inexistenta!"
			continue
		fi

		IN=$TESTS_DIR/$name/in/$i.in
		REF=$TESTS_DIR/$name/ref/$i.ref
		OUT=$TESTS_DIR/$name/out/$i.out

		if [ ! -f $IN ]; then
			echo "Test $i .......... 0/${points[$i]} - $IN lipseste!"
			continue
		fi

		cp $IN $name.in
		cp $REF res.ok

		touch $name.out
		chmod 666 $name.out

		timeout_test run $timeout
		# echo "Test $i problema $id , puncte ${points[$i]}"

		if [ -f error ]; then
			echo "Test $i problema $id .......... 0.0/${points[$i]} - Run time error!"
			# TODO
			# cat error
		elif [ -f tle ]; then
			echo "Test $i problema $id .......... 0.0/${points[$i]} - TLE - $(cat tle)!"
		else
			./verif $name ${points[$i]}

			STATUS=$(cat output.verif)
			TIME=$(cat output.time)
			SCORE=$(cat score.verif)
			echo "Test $i problema $id .......... $SCORE/${points[$i]} - $STATUS - $TIME"
			total=$(bc <<< "$total + $SCORE")
			score=$(bc <<< "$score + $SCORE")
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

	if [ $id -eq 3 ]; then
		if (( $(echo "$score == $pmax" |bc -l)  )); then
	    	cat $TESTS_DIR/numaratoare/kiss
		fi
	fi
}


# Choose set: public_tests vs private_tests
if [ -z $1 ]; then
  TESTS_DIR=public_tests
else
  TESTS_DIR=$1

  # Check if platform is online
  ONLINE_JUDGE=
  if [ "$1" == "ONLINE_JUDGE" ]; then
  	ONLINE_JUDGE="ONLINE_JUDGE=\"-D=ONLINE_JUDGE\""
  	TESTS_DIR=private_tests
  fi
fi

# Check if Makefile exists
if [ ! -f Makefile ]; then
	echo "Makefile lipsa. STOP"
	echo "=============>>>>>> Total: $total/$MAX_POINTS <<<<<< ============="
	exit
fi


# Compile and check errors
make -f Makefile build &> out.make
cnt=$(cat out.make| grep failed | wc -l)

#javac -version
#g++ --version &> tmp; cat tmp | head -1
gcc --version &> tmp; cat tmp | head -1
#python -V
#python3 -V

# cat out.make
rm -f out.make
if [ $cnt -gt 0 ]; then
	echo "Erori de compilare. Verifica versiunea compilatorului. STOP"
	echo "=============>>>>>> Total: $total/$MAX_POINTS <<<<<< ============="
	exit
fi

# Compile checker
make -f Makefile.SD all $ONLINE_JUDGE &> /dev/null
rm -rf $SOURCE_TMP_DIR

# Display tests set
echo "---------------------- Run $TESTS_DIR -------------------"

# Run tests - change functions test_*
test_homework
check_readme
check_coding_style

# Clean junk
make -f Makefile clean &> /dev/null
make -f Makefile.SD clean &> /dev/null
rm -rf tmp

# Display result
echo "=============>>>>>> Total: $total/$MAX_POINTS <<<<<< ============="
