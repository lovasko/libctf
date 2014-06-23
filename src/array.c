#include "array.h"
#include "errors.h"

#include <stdlib.h>

int
ctf_array_get_element_count (struct ctf_array *array, 
    uint32_t *out_element_count)
{
	if (array && out_element_count)
	{
		*out_element_count = array->element_count;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_array_get_type (struct ctf_array *array, struct ctf_type **out_type)
{
	if (array && out_type)
	{
		*out_type = array->type;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

