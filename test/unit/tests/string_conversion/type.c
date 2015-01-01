#include <string.h>
#include <libctf.h>

#include "type.h"

struct test_case*
float_pointer ()
{
	ctf_float float_data = ctf_float_create();
	ctf_float_set_name(float_data, "float");
	ctf_float_set_encoding(float_data, CTF_FLOAT_ENCODING_SINGLE);

	ctf_type float_type = ctf_type_create();
	ctf_type_set_kind(float_type, CTF_KIND_FLOAT);
	ctf_type_set_data(float_type, float_data);

	ctf_pointer pointer_data = ctf_pointer_create();
	ctf_pointer_set_type(pointer_data, float_type);

	ctf_type pointer_type = ctf_type_create();
	ctf_type_set_kind(pointer_type, CTF_KIND_POINTER);
	ctf_type_set_data(pointer_type, pointer_data);
	
	struct test_case* tc = malloc(sizeof(struct test_case));
	tc->description = "Pointer to float";
	tc->expected = "float*";
	tc->input = pointer_type;

	return tc;
}

struct test_case*
const_int ()
{
	ctf_int int_data = ctf_int_create();
	ctf_int_set_name(int_data, "long");

	ctf_type int_type = ctf_type_create();
	ctf_type_set_kind(int_type, CTF_KIND_INT);
	ctf_type_set_data(int_type, int_data);
	
	ctf_type const_type = ctf_type_create();
	ctf_type_set_kind(const_type, CTF_KIND_CONST);
	ctf_type_set_data(const_type, int_type);

	struct test_case* tc = malloc(sizeof(struct test_case));
	tc->description = "Const long";
	tc->expected = "const long";
	tc->input = const_type;

	return tc;
}

struct test_case*
array_of_5_chars ()
{
	ctf_int char_data = ctf_int_create();
	ctf_int_set_content(char_data, CTF_INT_CONTENT_CHAR);
	ctf_int_set_size(char_data, 8);
	ctf_int_set_name(char_data, "char");

	ctf_type char_type = ctf_type_create();
	ctf_type_set_kind(char_type, CTF_KIND_INT);
	ctf_type_set_data(char_type, char_data);

	ctf_array array_data = ctf_array_create();
	ctf_array_set_length(array_data, 5);
	ctf_array_set_content_type(array_data, char_type);

	ctf_type array_type = ctf_type_create();
	ctf_type_set_kind(array_type, CTF_KIND_ARRAY);
	ctf_type_set_data(array_type, array_data);

	struct test_case* tc = malloc(sizeof(struct test_case));
	tc->description = "Array of 5 chars";
	tc->expected = "char[5]";
	tc->input = array_type;

	return tc;
}

struct test_case_head*
init_type_string_conversion ()
{
	struct test_case_head* head;

	head = malloc(sizeof(struct test_case_head));
	TAILQ_INIT(head);

	struct test_case* fp_tc = float_pointer();
	TAILQ_INSERT_TAIL(head, fp_tc, test_cases);

	struct test_case* ci_tc = const_int();
	TAILQ_INSERT_TAIL(head, ci_tc, test_cases);

	return head;
}

int
test_type_string_conversion (struct test_case* tc)
{
	/* prepare values */
	ctf_type type = tc->input;
	char* expected_string = (char*)tc->expected;

	/* perform the function */
	char* actual_string = NULL;
	int retval = CTF_OK;
	if ((retval = ctf_type_to_string(type, &actual_string)) != CTF_OK)
		return _CTF_UNIT_TEST_FAILURE;

	/* store the actual result */
	tc->actual = strdup(actual_string);

	/* free the computed string */
	free(actual_string);

	/* perform the equality test */
	if (strcmp(tc->actual, expected_string) == 0)
		return _CTF_UNIT_TEST_SUCCESS;
	else
		return _CTF_UNIT_TEST_FAILURE;
}

void
free_type_string_conversion (struct test_case_head* head)
{
	struct test_case* runner;

	while (!TAILQ_EMPTY(head))
	{
		runner = TAILQ_FIRST(head);
		TAILQ_REMOVE(head, runner, test_cases);
		free(runner);
	}
}

