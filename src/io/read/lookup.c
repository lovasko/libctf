#include "io/read/read.h"

struct ctf_type*
_ctf_lookup_type (struct ctf_file* file, uint16_t id)
{
	if (id < file->type_id_offset)
	{
		if (file->parent_file != NULL)
			return _ctf_lookup_type(file->parent_file, id);
		else
			return NULL;
	}
	else if (id < file->type_count)
	{
		return file->type_id_table[id - file->type_id_offset];	
	}
	else
		return NULL;
}

