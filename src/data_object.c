#include "data_object.h"
#include "errors.h"

int
ctf_data_object_get_name (struct ctf_data_object *data_object, char **out_name)
{
	if (data_object && out_name)
	{
		*out_name = data_object->name;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_data_object_get_type (struct ctf_data_object *data_object,
    struct ctf_type **out_type)
{
	if (data_object && out_type)
	{
		*out_type = data_object->type;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

