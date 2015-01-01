#include <string.h>
#include <libctf.h>

#include "string_conversion/kind.h"

struct test_case_head*
init_kind_string_conversion ()
{
	struct test_case_head* head;

	head = malloc(sizeof(struct test_case_head));
	TAILQ_INIT(head);

	struct test_case* none_test_case;
	none_test_case = malloc(sizeof(struct test_case));
	none_test_case->description = "None";
	none_test_case->input = malloc(sizeof(ctf_kind));
	*((int*)none_test_case->input) = CTF_KIND_NONE;
	none_test_case->expected = strdup("none");
	TAILQ_INSERT_TAIL(head, none_test_case, test_cases);

	struct test_case* int_test_case;
	int_test_case = malloc(sizeof(struct test_case));
	int_test_case->description = "Int";
	int_test_case->input = malloc(sizeof(ctf_kind));
	*((int*)int_test_case->input) = CTF_KIND_INT;
	int_test_case->expected = strdup("int");
	TAILQ_INSERT_TAIL(head, int_test_case, test_cases);

	struct test_case* float_test_case;
	float_test_case = malloc(sizeof(struct test_case));
	float_test_case->description = "Float";
	float_test_case->input = malloc(sizeof(ctf_kind));
	*((int*)float_test_case->input) = CTF_KIND_FLOAT;
	float_test_case->expected = strdup("float");
	TAILQ_INSERT_TAIL(head, float_test_case, test_cases);

	struct test_case* pointer_test_case;
	pointer_test_case = malloc(sizeof(struct test_case));
	pointer_test_case->description = "Pointer";
	pointer_test_case->input = malloc(sizeof(ctf_kind));
	*((int*)pointer_test_case->input) = CTF_KIND_POINTER;
	pointer_test_case->expected = strdup("pointerr");
	TAILQ_INSERT_TAIL(head, pointer_test_case, test_cases);

	struct test_case* array_test_case;
	array_test_case = malloc(sizeof(struct test_case));
	array_test_case->description = "Array";
	array_test_case->input = malloc(sizeof(ctf_kind));
	*((int*)array_test_case->input) = CTF_KIND_ARRAY;
	array_test_case->expected = strdup("array");
	TAILQ_INSERT_TAIL(head, array_test_case, test_cases);

	struct test_case* function_test_case;
	function_test_case = malloc(sizeof(struct test_case));
	function_test_case->description = "Function";
	function_test_case->input = malloc(sizeof(ctf_kind));
	*((int*)function_test_case->input) = CTF_KIND_FUNC;
	function_test_case->expected = strdup("function");
	TAILQ_INSERT_TAIL(head, function_test_case, test_cases);

	struct test_case* struct_test_case;
	struct_test_case = malloc(sizeof(struct test_case));
	struct_test_case->description = "Struct";
	struct_test_case->input = malloc(sizeof(ctf_kind));
	*((int*)struct_test_case->input) = CTF_KIND_STRUCT;
	struct_test_case->expected = strdup("struct");
	TAILQ_INSERT_TAIL(head, struct_test_case, test_cases);

	struct test_case* union_test_case;
	union_test_case = malloc(sizeof(struct test_case));
	union_test_case->description = "Union";
	union_test_case->input = malloc(sizeof(ctf_kind));
	*((int*)union_test_case->input) = CTF_KIND_UNION;
	union_test_case->expected = strdup("union");
	TAILQ_INSERT_TAIL(head, union_test_case, test_cases);

	struct test_case* enum_test_case;
	enum_test_case = malloc(sizeof(struct test_case));
	enum_test_case->description = "Enum";
	enum_test_case->input = malloc(sizeof(ctf_kind));
	*((int*)enum_test_case->input) = CTF_KIND_ENUM;
	enum_test_case->expected = strdup("enum");
	TAILQ_INSERT_TAIL(head, enum_test_case, test_cases);

	struct test_case* fwd_decl_test_case;
	fwd_decl_test_case = malloc(sizeof(struct test_case));
	fwd_decl_test_case->description = "Forward declaration";
	fwd_decl_test_case->input = malloc(sizeof(ctf_kind));
	*((int*)fwd_decl_test_case->input) = CTF_KIND_FWD_DECL;
	fwd_decl_test_case->expected = strdup("forward declaration");
	TAILQ_INSERT_TAIL(head, fwd_decl_test_case, test_cases);

	struct test_case* typedef_test_case;
	typedef_test_case = malloc(sizeof(struct test_case));
	typedef_test_case->description = "Typedef";
	typedef_test_case->input = malloc(sizeof(ctf_kind));
	*((int*)typedef_test_case->input) = CTF_KIND_TYPEDEF;
	typedef_test_case->expected = strdup("typedef");
	TAILQ_INSERT_TAIL(head, typedef_test_case, test_cases);

	struct test_case* volatile_test_case;
	volatile_test_case = malloc(sizeof(struct test_case));
	volatile_test_case->description = "Volatile";
	volatile_test_case->input = malloc(sizeof(ctf_kind));
	*((int*)volatile_test_case->input) = CTF_KIND_VOLATILE;
	volatile_test_case->expected = strdup("volatile");
	TAILQ_INSERT_TAIL(head, volatile_test_case, test_cases);

	struct test_case* const_test_case;
	const_test_case = malloc(sizeof(struct test_case));
	const_test_case->description = "Const";
	const_test_case->input = malloc(sizeof(ctf_kind));
	*((int*)const_test_case->input) = CTF_KIND_CONST;
	const_test_case->expected = strdup("const");
	TAILQ_INSERT_TAIL(head, const_test_case, test_cases);

	struct test_case* restrict_test_case;
	restrict_test_case = malloc(sizeof(struct test_case));
	restrict_test_case->description = "Restrict";
	restrict_test_case->input = malloc(sizeof(ctf_kind));
	*((int*)restrict_test_case->input) = CTF_KIND_RESTRICT;
	restrict_test_case->expected = strdup("restrict");
	TAILQ_INSERT_TAIL(head, restrict_test_case, test_cases);

	struct test_case* min_test_case;
	min_test_case = malloc(sizeof(struct test_case));
	min_test_case->description = "Below CTF\\_KIND\\_MIN";
	min_test_case->input = malloc(sizeof(ctf_kind));
	*((int*)min_test_case->input) = CTF_KIND_MIN - 1;
	min_test_case->expected = strdup("unresolvable");
	TAILQ_INSERT_TAIL(head, min_test_case, test_cases);

	struct test_case* max_test_case;
	max_test_case = malloc(sizeof(struct test_case));
	max_test_case->description = "Above CTF\\_KIND\\_MAX";
	max_test_case->input = malloc(sizeof(ctf_kind));
	*((int*)max_test_case->input) = CTF_KIND_MAX + 1;
	max_test_case->expected = strdup("unresolvable");
	TAILQ_INSERT_TAIL(head, max_test_case, test_cases);

	return head;
}

int
test_kind_string_conversion (struct test_case* tc)
{
	/* prepare values */
	ctf_kind kind = *((ctf_kind*)tc->input);
	char* expected_string = (char*)tc->expected;

	/* perform the function */
	const char* actual_string = ctf_kind_to_string(kind);

	/* store the actual result */
	tc->actual = strdup(actual_string);

	/* perform the equality test */
	if (strcmp(actual_string, expected_string) == 0)
		return _CTF_UNIT_TEST_SUCCESS;
	else
		return _CTF_UNIT_TEST_FAILURE;
}

void
free_kind_string_conversion (struct test_case_head* head)
{
	struct test_case* runner;

	while (!TAILQ_EMPTY(head))
	{
		runner = TAILQ_FIRST(head);
		TAILQ_REMOVE(head, runner, test_cases);
		free(runner);
	}
}

