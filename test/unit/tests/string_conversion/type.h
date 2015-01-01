#ifndef CTF_UNIT_TEST_STRING_CONVERSION_TYPE
#define CTF_UNIT_TEST_STRING_CONVERSION_TYPE

#include "test_case.h"

struct test_case_head*
init_type_string_conversion ();

int
test_type_string_conversion (struct test_case* tc);

void
free_type_string_conversion (struct test_case_head* head);

#endif

