#include <string.h>

#include "label/label.h"

_CTF_GET_PROPERTY_IMPL(
	ctf_label_get_name,
	ctf_label,
	char*,
	name)

_CTF_SET_PROPERTY_IMPL(
	ctf_label_set_name,
	ctf_label,
	char*,
	name)

_CTF_GET_PROPERTY_IMPL(
	ctf_label_get_index,
	ctf_label,
	ctf_label_index,
	index)

_CTF_SET_PROPERTY_IMPL(
	ctf_label_set_index,
	ctf_label,
	ctf_label_index,
	index)

_CTF_CREATE_IMPL(
	ctf_label_create,
	ctf_label,
	CTF_LABEL_SIZE)

size_t
ctf_label_memory_usage (ctf_label label)
{
	size_t usage = 0;

	usage += CTF_LABEL_SIZE;
	usage += strlen(label->name);

	return usage;
}

