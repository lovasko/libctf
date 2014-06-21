#include "data_object.h"

char*
ctf_data_object_get_name (struct ctf_data_object *data_object)
{
	if (data_object)
		return data_object->name;
	else
		return NULL;
}

struct ctf_type*
ctf_data_object_get_type (struct ctf_data_object *data_object)
{
	if (data_object)
		return data_object->type;
	else
		return NULL;
}

