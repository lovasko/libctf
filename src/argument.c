#include "argument.h"
#include "errors.h"

int
ctf_argument_get_type (struct ctf_argument *argument, 
    struct ctf_type **out_type)
{
	if (argument && out_type)
	{
		*out_type = argument->type;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

