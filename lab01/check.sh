#!/usr/bin/env bash

NUM_TASKS=4
TASKS=(task-1 task-2 task-3 task-4)
NUM_TESTS=(4 4 9 4)

TIMEOUT_CPP=1
TIMEOUT_JAVA=2

source ./tests/base_check.sh
