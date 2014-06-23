#include "typedef.h"
#include "errors.h"

int
ctf_typedef_get_name (struct ctf_typedef *_typedef, char **out_name)
{
	if (_typedef && out_name)
	{
		*out_name = _typedef->name;	
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_typedef_get_type (struct ctf_typedef *_typedef, struct ctf_type **out_type)
{
	if (_typedef && out_type)
	{
		*out_type = _typedef->type;	
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

