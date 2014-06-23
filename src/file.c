#include "file.h"
#include "errors.h"

int
ctf_file_get_version (struct ctf_file *file)
{
	if (file)
		return file->version;
	else
		return -1;
}

int
ctf_file_is_compressed (struct ctf_file *file)
{
	if (file)
		return file->compressed;	
	else
		return 0;
}

struct ctf_file*
ctf_file_get_parent_file (struct ctf_file *file)
{
	if (file)
		return file->parent_file;
	else
		return NULL;
}

int
ctf_file_get_next_label (struct ctf_file *file, struct ctf_label *label, 
    struct ctf_label **out_next)
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

int
ctf_file_get_next_type (struct ctf_file *file, struct ctf_type *type, 
    struct ctf_type **out_next)
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

int
ctf_file_get_next_function (struct ctf_file *file, 
    struct ctf_function *function, struct ctf_function **out_next)
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

int
ctf_file_get_next_data_object (struct ctf_file *file, 
    struct ctf_data_object *data_object, struct ctf_data_object **out_next)
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

