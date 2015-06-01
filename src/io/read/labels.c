#ifdef _KERNEL
	#include <sys/malloc.h>
	#include <sys/libkern.h>
#else
	#include <stdlib.h>
	#include <string.h>
#endif

#include "file/errors.h"
#include "io/read/read.h"
#include "label/label.h"
#include "space.h"

CTF_MALLOC_DECLARE();

int
_ctf_read_labels(struct ctf_file* file,
                 struct _section* section, 
                 struct _strings* strings)
{
	struct _ctf_label* raw_labels;
	struct ctf_label* label;
	unsigned int i;

	if (section->size % _CTF_LABEL_SIZE != 0)
		return CTF_E_LABEL_SECTION_CORRUPT;

	m_list_init(&file->labels);
	raw_labels = (struct _ctf_label*)section->data;
	for (i = 0; i < section->size/_CTF_LABEL_SIZE; i++)
	{
		label = CTF_MALLOC(CTF_LABEL_SIZE);
		label->name = CTF_STRDUP(_ctf_strings_lookup(strings, raw_labels[i].name));
		label->index = raw_labels[i].index;

		m_list_append(&file->labels, M_LIST_COPY_SHALLOW, label, 0);
	}

	return CTF_OK;
}

