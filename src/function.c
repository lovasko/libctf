#include "function.h"
#include "errors.h"

int
ctf_function_get_name (struct ctf_function *function, char **out_name);
{
	if (function && out_name)
	{
		*out_name = function->name;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_function_get_return_type (struct ctf_function *function, 
    struct ctf_type **out_return_type);
{
	if (function && out_return_type)
	{
		*out_return_type = function->return_type;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_function_get_next_argument (struct ctf_function *function, 
    struct ctf_argument *argument, struct ctf_argument **out_argument)
{
	if (argument == NULL)
	{
		if (TAILQ_EMPTY(function->argument_head))
			return CTF_EMPTY;

		*out_argument = TAILQ_FIRST(function->argument_head);
		return CTF_OK;
	}
	else
	{
		struct ctf_argument *next = TAILQ_NEXT(argument, arguments);
		if (next == NULL)
			return CTF_END;
		else
		{
			*out_argument = next;
			return CTF_OK;	
		}
	}
}

