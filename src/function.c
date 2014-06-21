#include "function.h"
#include "errors.h"

char*
ctf_function_get_name (struct ctf_function *function)
{
	if (function)
		return function->name;
	else
		return NULL;
}

struct ctf_type*
ctf_function_get_return_type (struct ctf_function *function)
{
	if (function)
		return function->return_type;
	else
		return NULL;
}

int
ctf_function_get_next_argument (struct ctf_function *function, 
    struct ctf_argument *argument, struct ctf_argument **out_next)
{
	if (argument == NULL)
	{
		if (TAILQ_EMPTY(function->argument_head))
			return CTF_EMPTY;

		*out_next = TAILQ_FIRST(function->argument_head);
		return CTF_OK;
	}
	else
	{
		struct ctf_argument *next = TAILQ_NEXT(argument, arguments);
		if (next == NULL)
			return CTF_END;
		else
		{
			*out_next = next;
			return CTF_OK;	
		}
	}
}

