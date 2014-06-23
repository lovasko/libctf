#include "label.h"
#include "errors.h"

#include <stdlib.h>

int
ctf_label_get_name (struct ctf_label *label, char **out_name)
{
	if (label && out_name)
	{
		*out_name = label->name;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_label_get_index (struct ctf_label *label, uint32_t *out_index)
{
	if (label && out_index)
	{
		*out_index = label->index;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

