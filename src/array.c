#include "array.h"

#include <stdlib.h>

uint32_t
ctf_array_get_element_count (struct ctf_array *array)
{
	if (array)
		return array->element_count;
	else
		return 0;
}

struct ctf_type*
ctf_array_get_type (struct ctf_array *array)
{
	if (array)
		return array->type;
	else
		return NULL;
}

