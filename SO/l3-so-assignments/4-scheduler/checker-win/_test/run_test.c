/*
 * Testing framework
 *
 * 2019, Operating Systems
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

/* tests functions */
#include "run_test.h"
/* custom tests */
#include "scheduler_test.h"

#define FILE_NAME "output.ref"

/* global variables used by the test */
static unsigned long test_index;

static int init_world(void)
{
	return 0;
}

static int cleanup_world(void)
{
	return 0;
}

static void test_do_fail(void)
{
	exit(EXIT_FAILURE);
}


void basic_test(int test_passed)
{
	if (!test_passed)
		test_do_fail();

}


struct run_test_t test_fun_array[] = {
	/* tests schedule - see test_sched.c */
	{ test_sched_01 },
	{ test_sched_02 },
	{ test_sched_03 },
	{ test_sched_04 },
	{ test_sched_05 },
	{ test_sched_06 },
	{ test_sched_07 },
	{ test_sched_08 },
	{ test_sched_09 },
	{ test_sched_10 },
	{ test_sched_11 },

	{ test_sched_12 },
	{ test_sched_13 },
	{ test_sched_14 },
	{ test_sched_15 },
	{ test_sched_16 },

	{ test_sched_17 },
	{ test_sched_18 },
	{ test_sched_19 },
	{ test_sched_20 },
};

/* custom main testing thread */
int main(int argc, char **argv)
{
	unsigned long last_test;
	FILE *file;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <test_number> | init | cleanup\n",
			argv[0]);
		return -1;
	}

	/* check init and cleanup execution */
	if (strcmp(argv[1], "init") == 0) {
		if (init_world() < 0) {
			fprintf(stderr, "test init failed\n");
			return -1;
		}
		return 0;
	} else if (strcmp(argv[1], "cleanup") == 0) {
		if (cleanup_world() < 0) {
			fprintf(stderr, "test cleanup failed\n");
			return -1;
		}
		return 0;
	}

	test_index = strtoul(argv[1], NULL, 10);
	if (errno == EINVAL || errno == ERANGE) {
		fprintf(stderr, "%s not a number\n", argv[1]);
		return -1;
	}

	last_test = sizeof(test_fun_array) / sizeof(struct run_test_t);
	if (test_index < 0 || test_index > last_test) {
		fprintf(stderr, "Error: Test index is out of range"
			"(0 < test_index <= %lu).\n", last_test + 1);
		return -1;
	}

	/* randomize time quantums */
	srand((unsigned long)time(NULL));

 	test_fun_array[test_index].function();

	if (fopen_s(&file, FILE_NAME, "wt") == 0) {
		fprintf(file, "%d", 1);
		fclose(file);
	}

	return 0;
}
