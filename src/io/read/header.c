#include "file/errors.h"
#include "io/read/read.h"

int
_ctf_preface_check (struct _ctf_preface* preface)
{
	if (preface->magic != _CTF_MAGIC)
		return CTF_E_MAGIC;

	if (preface->version != _CTF_VERSION_2)
		return CTF_E_VERSION;

	return CTF_OK;
}

int
_ctf_header_offset_sanity_check (struct _ctf_header* header)
{
	if (header->label_offset    < header->object_offset   &&
	    header->object_offset   < header->function_offset &&
	    header->function_offset < header->type_offset     &&
	    header->type_offset     < header->string_offset)
		return CTF_OK;
	else
		return CTF_E_OFFSETS_CORRUPT;
}

