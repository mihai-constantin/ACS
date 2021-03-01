#!/usr/bin/env bash

NUM_TASKS=3
TASKS=(task-1 task-2)
NUM_TESTS=(11 9)

TMP_FILE="$PWD"/".tmp"
LOG_NAME="$PWD"/".err.log"

FAILED_TOTAL=0

CXX=g++
CXXFLAGS="-std=c++11"

# Cross-platform timeout (using perl).
timeout() {
  perl -e 'alarm shift; exec @ARGV' "$@";
}

check_prerequisites() {
  for prereq in "$@"; do
    command -v "$prereq" >/dev/null 2>&1 || { echo "Eroare: Nu am gasit '${prereq}'. Instaleaza '${prereq}'."; exit 1; }
  done
}

check_prerequisites_cpp() {
  check_prerequisites python g++
}

check_prerequisites_java() {
  check_prerequisites python java javac
}

show_help() {
  echo "./check.sh <limbaj> [task] [test_number]"
  echo ""
  echo -e "Rulati ./check.sh avand ca director curent radacina scheletului"
  echo -e "de laborator."
  echo ""
  echo -e "<limbaj>: \"java\" sau \"cpp\""
  echo -e "Daca nu este specificat [test_number], se ruleaza toate testele"
  echo -e "Daca nu este specificat [task], se ruleaza toate taskurile"
  echo ""
  echo -e "De exemplu, pentru a rula testul 2 din taskul 1, limbajul Java:"
  echo -e "\t./check.sh java task-1 2"
  echo ""
  echo -e "De asemenea, \"./check.sh clean\" curata binarele create in timpul"
  echo -e "executiei."
  echo ""
  echo -e "Pentru a rula teste custom, modificati tests/<task>/custom.in si"
  echo -e "tests/<task>/custom.ref, ruland apoi:"
  echo -e "\t./check.sh <lang> <task> custom"

  exit 1
}

task_index() {
  task_name=$1

  for index in $(seq 0 $(($NUM_TASKS - 1))); do
    if [[ "${TASKS[$index]}" == "$task_name" ]]; then
      echo $index
      return
    fi
  done

  echo -1
}

compile_java() {
  result=0
  command pushd "$1" &>/dev/null
    if [[ ! ( -f bin/Main.class && bin/Main.class -nt src/Main.java ) ]]; then
      mkdir -p bin
      echo "Compiling $1..." >> "$LOG_NAME" 2>&1
      javac src/Main.java -d bin > "$TMP_FILE" 2>&1
      result=$?
      cat "$TMP_FILE" >> "$LOG_NAME"
      head -n 3 "$TMP_FILE"
      echo "========================================" >> "$LOG_NAME" 2>&1
    fi
  command popd &>/dev/null
  return $result
}

compile_cpp() {
  result=0
  command pushd "$1" &>/dev/null
    if [[ ! ( -f main && main -nt main.cpp ) ]]; then
      echo "Compiling $1..." >> "$LOG_NAME" 2>&1
      ${CXX} ${CXXFLAGS} -o main main.cpp > "$TMP_FILE" 2>&1
      result=$?
      cat "$TMP_FILE" >> "$LOG_NAME"
      head -n 3 "$TMP_FILE"
      echo "========================================" >> "$LOG_NAME" 2>&1
    fi
  command popd &>/dev/null
  return $result
}

run_java() {
  command pushd "$1" &>/dev/null
    echo "Running $1..." >> "$LOG_NAME" 2>&1
    timeout 1 java -cp bin Main >> "$LOG_NAME" 2>&1
    result=$?
    echo "========================================" >> "$LOG_NAME" 2>&1
  command popd &>/dev/null

  return $result
}

run_cpp() {
  command pushd "$1" &>/dev/null
    echo "Running $1..." >> "$LOG_NAME" 2>&1
    timeout 1 ./main >> "$LOG_NAME" 2>&1
    result=$?
    echo "========================================" >> "$LOG_NAME" 2>&1
  command popd &>/dev/null

  return $result
}

cleanup_java() {
  command pushd "$1" &>/dev/null
    rm -rf bin in out
  command popd &>/dev/null
}

cleanup_cpp() {
  command pushd "$1" &>/dev/null
    rm -rf main in out
  command popd &>/dev/null
}

# Returns:
# 1 = COMPILE ERROR
# 2 = RUNTIME ERROR OR TIMEOUT
# 3 = WRONG ANSWER
compile_and_run() {
  lang="$1"
  task="$2"
  num="$3"

  compile_${lang} "${lang}/${task}"
  if [[ $? -ne 0 ]]; then
    return 1
  fi
  cp "tests/${task}/${num}.in" "${lang}/${task}/in"
  run_${lang} "${lang}/${task}"
  if [[ $? -ne 0 ]]; then
    result=2
  fi

  if [[ $result -eq 0 ]]; then
    "tests/${task}/checker/main" "tests/${task}/${num}.in" \
      "tests/${task}/${num}.ref" "${lang}/${task}/out" > "$TMP_FILE" 2>&1
    checker_result=$?
    cat "$TMP_FILE" >> "$LOG_NAME"
    head -n 3 "$TMP_FILE"
    if [[ $checker_result -ne 0 ]]; then
      result=3
    fi
  fi

  # If not WA, remove in/out files.
  if [[ $result -ne 3 ]]; then
    rm "${lang}/${task}/in"
    rm "${lang}/${task}/out"
  fi

  return $result
}

run_single_test() {
  lang="$1"
  task="$2"
  num="$3"

  echo -n "Running ${task}, test ${num}, language ${lang}... "

  compile_and_run "$lang" "$task" "$num"
  result=$?

  RUN_STATUS=("OK" "COMPILE ERROR" "RUNTIME/TIMELIMIT" "WRONG ANSWER")
  if [[ $result -ne 0 ]]; then
    FAILED_TOTAL=$(($FAILED_TOTAL+1))
    echo "Failed with status ${RUN_STATUS[$result]}!"

    # If WA, print diffs.
    if [[ $result -eq 3 ]]; then
      echo -ne "Expected: "
      cat "tests/${task}/${num}.ref" | head -n 2 | grep -Ev "^$"
      echo -ne "Got: "
      cat "${lang}/${task}/out" | head -n 2 | grep -Ev "^$"

      # Clean up in/out now.
      rm "${lang}/${task}/in"
      rm "${lang}/${task}/out"
    fi
  else
    echo "Successful!"
  fi

  return $result
}

run_task_tests() {
  lang=$1
  task=$2

  task_num=$(task_index $task)
  if [[ $task_num -eq -1 ]]; then
    echo "Invalid task name: $task" >&2
    exit 1
  fi

  num=1
  while [[ $num -le ${NUM_TESTS[$task_num]} ]]; do
    run_single_test "$lang" "$task" "$num"
    if [[ $? -ne 0 ]]; then
      failed=$(($failed + 1))
    fi
    num=$(($num + 1))
  done

  if [[ $failed -eq 0 ]]; then
    echo "Problema $task completa."
  fi
}

run_all_tests() {
  lang=$1

  for task in ${TASKS[@]}; do
    run_task_tests "$lang" "$task"
    echo "========================================"
  done
}

cleanup() {
  rm -f "$LOG_NAME" "$TMP_FILE"
  for task in ${TASKS[@]}; do
    cleanup_cpp  "cpp/${task}"
    cleanup_java "java/${task}"
  done
}

# Clear log.
echo > "$LOG_NAME"

# Check argc > 0.
if [[ $# -eq 0 ]]; then
  show_help
fi

# Check argv[1] == (clean|cpp|java).
if [[ "$1" != "clean" && "$1" != "cpp" && "$1" != "java" ]]; then
  show_help
fi

# "clean" is only valid with 1 argument.
if [[ "$1" == "clean" && $# -ge 2 ]]; then
  show_help
fi

# If "clean", do cleanup.
if [[ "$1" == "clean" ]]; then
  cleanup
  exit 0
fi

check_prerequisites_"$1"

if [[ $# -eq 1 ]]; then
  run_all_tests "$1"
elif [[ $# -eq 2 ]]; then
  run_task_tests "$1" "$2"
elif [[ $# -eq 3 ]]; then
  run_single_test "$1" "$2" "$3"
else
  show_help
fi

if [[ $FAILED_TOTAL -gt 0 ]]; then
  echo "Rulati urmatoarea comanda pentru a vedea log-ul de compile/run: "
  echo -e "\tless .err.log"
  echo "Nota: In .err.log se afla si afisarile la stdout si stderr din implementarea voastra."
fi
