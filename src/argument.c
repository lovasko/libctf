#include "argument.h"

struct ctf_type*
ctf_argument_get_type (struct ctf_argument *argument)
{
	if (argument)
		return argument->type;
	else
		return NULL;
}

