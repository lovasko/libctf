#include <string.h>

#include "label/label.h"

_CTF_GET_PROPERTY_IMPL(ctf_label_get_name, ctf_label, char*, name)
_CTF_GET_PROPERTY_IMPL(ctf_label_get_index, ctf_label, ctf_label_index, index)

size_t
ctf_label_memory_usage (ctf_label label)
{
	size_t usage = 0;

	usage += CTF_LABEL_SIZE;
	usage += strlen(label->name);

	return usage;
}

