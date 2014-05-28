#include "read.h"
#include "header.h"

#include <stdlib.h>
#include <string.h>

struct ctf_file*
ctf_read_buffer (struct ctf_section ctf, struct ctf_section elf_string_table)
{
	struct _ctf_header header;
	memcpy(&header, ctf.data, _CTF_HEADER_SIZE);

	if (header.preface.magic != CTF_MAGIC)
		return NULL;

	if (header.preface.version != CTF_VERSION)
		return NULL;

	size_t label_section_size = header.object_offset - header.label_offset;
	if (label_section_size % _CTF_LABEL_SIZE != 0)
		return NULL;

	struct _ctf_label *labels = (struct _ctf_label*)malloc(label_section_size);
	memcpy(labels, ctf.data + _CTF_HEADER_SIZE + header.label_offset, 
	    label_section_size);

	struct ctf_file *file = (struct ctf_file*)malloc(sizeof(struct ctf_file));
	file->labels = NULL;
	file->version = 2;
	file->compressed = 0;

	size_t label_count = label_section_size / _CTF_LABEL_SIZE;
	for (unsigned int i = 0; i < label_count; i++)
	{
		struct ctf_label to_add;

		to_add.index = labels[i].index;
		to_add.name = (char*)ctf.data + _CTF_HEADER_SIZE + header.string_offset 
		    + labels[i].name;
		ctf_label_add(&file->labels, &to_add);
	}

	return file;
}

