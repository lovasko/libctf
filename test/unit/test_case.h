#ifndef CTF_UNIT_TEST_TEST_CASE
#define CTF_UNIT_TEST_TEST_CASE

#include <sys/queue.h>

#define _CTF_UNIT_TEST_SUCCESS 1
#define _CTF_UNIT_TEST_FAILURE 0

struct test_case
{
	char* description;
	void* input;
	void* expected;
	void* actual;

	TAILQ_ENTRY(test_case) test_cases;
};

TAILQ_HEAD(test_case_head, test_case);

#endif

