#include "file.h"
#include "errors.h"

int
ctf_file_get_version (struct ctf_file *file, int *out_version)
{
	if (file && out_version)
	{
		*out_version = file->version;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_file_is_compressed (struct ctf_file *file, int *out_is_compressed)
{
	if (file && out_is_compressed)
	{
		*out_is_compressed = file->compressed;	
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_file_get_parent_file (struct ctf_file *file, 
    struct ctf_file **out_parent_file)
{
	if (file && out_parent_file)
	{
		*out_parent_file = file->parent_file;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_file_get_next_label (struct ctf_file *file, struct ctf_label *label, 
    struct ctf_label **out_label)
{
	if (file && out_label)
	{
		if (label == NULL)
		{
			if (TAILQ_EMPTY(file->label_head))
				return CTF_EMPTY;

			*out_next = TAILQ_FIRST(file->label_head);
			return CTF_OK;
		}
		else
		{
			struct ctf_label *next = TAILQ_NEXT(label, labels);
			if (next == NULL)
				return CTF_END;
			else
			{
				*out_next = next;
				return CTF_OK;	
			}
		}
	}
	else
		return CTF_E_NULL;
}

int
ctf_file_get_next_type (struct ctf_file *file, struct ctf_type *type, 
    struct ctf_type **out_type)
{
	if (file && out_type)
	{
		if (type == NULL)
		{
			if (TAILQ_EMPTY(file->type_head))
				return CTF_EMPTY;

			*out_next = TAILQ_FIRST(file->type_head);
			return CTF_OK;
		}
		else
		{
			struct ctf_type *next = TAILQ_NEXT(type, types);
			if (next == NULL)
				return CTF_END;
			else
			{
				*out_next = next;
				return CTF_OK;	
			}
		}
	}
	else
		return CTF_E_NULL;
}

int
ctf_file_get_next_function (struct ctf_file *file, 
    struct ctf_function *function, struct ctf_function **out_function)
{
	if (file && out_function)
	{
		if (function == NULL)
		{
			if (TAILQ_EMPTY(file->function_head))
				return CTF_EMPTY;

			*out_next = TAILQ_FIRST(file->function_head);
			return CTF_OK;
		}
		else
		{
			struct ctf_function *next = TAILQ_NEXT(function, functions);
			if (next == NULL)
				return CTF_END;
			else
			{
				*out_next = next;
				return CTF_OK;	
			}
		}
	}
	else
		return CTF_E_NULL;
}

int
ctf_file_get_next_data_object (struct ctf_file *file, 
    struct ctf_data_object *data_object, 
    struct ctf_data_object **out_data_object)
{
	if (file && out_data_object)
	{
		if (data_object == NULL)
		{
			if (TAILQ_EMPTY(file->data_object_head))
				return CTF_EMPTY;

			*out_next = TAILQ_FIRST(file->data_object_head);
			return CTF_OK;
		}
		else
		{
			struct ctf_data_object *next = TAILQ_NEXT(data_object, data_objects);
			if (next == NULL)
				return CTF_END;
			else
			{
				*out_next = next;
				return CTF_OK;	
			}
		}
	}
	else
		return CTF_E_NULL;
}

