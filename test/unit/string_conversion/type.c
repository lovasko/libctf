#include <string.h>
#include <libctf.h>

#include "type.h"

struct test_case_head*
init_type_string_conversion ()
{
	struct test_case_head* head;

	head = malloc(sizeof(struct test_case_head));
	TAILQ_INIT(head);

	return head;
}

int
test_type_string_conversion (struct test_case* tc)
{
	return _CTF_UNIT_TEST_SUCCESS;
}

void
free_type_string_conversion (struct test_case_head* head)
{
	struct test_case* runner;

	TAILQ_FOREACH(runner, head, test_cases)
	{
		free(runner->input);
		free(runner->expected);
		free(runner->actual);

		TAILQ_REMOVE(head, runner, test_cases);
	}
}

