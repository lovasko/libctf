#ifndef CTF_UNIT_TEST_STRING_CONVERSION_KIND
#define CTF_UNIT_TEST_STRING_CONVERSION_KIND

#include "../test_case.h"

struct test_case_head*
init_kind_string_conversion ();

int
test_kind_string_conversion (struct test_case* tc);

void
free_kind_string_conversion (struct test_case_head* head);

#endif

