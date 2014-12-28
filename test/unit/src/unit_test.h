#ifndef CTF_UNIT_TEST_UNIT_TEST
#define CTF_UNIT_TEST_UNIT_TEST

#include <sys/queue.h>

#include "test_case.h"

struct unit_test
{
	char* name;

	struct test_case_head* (*init)();
	int (*test)(struct test_case*);
	void (*clean)(struct test_case_head*);
};

#endif

