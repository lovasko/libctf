#include "labels.h"
#include "../label.h"
#include "../errors.h"

#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

int
_ctf_read_labels (struct ctf_file* file, struct _section* section, 
    struct _strings* strings)
{
	if (section->size % _CTF_LABEL_SIZE != 0)
		return CTF_E_LABEL_SECTION_CORRUPT;

	file->label_head = malloc(CTF_LABEL_HEAD_SIZE);
	TAILQ_INIT(file->label_head);

	struct _ctf_label *raw_labels = (struct _ctf_label*)section->data;	

	for (unsigned int i = 0; i < section->size/_CTF_LABEL_SIZE; i++)
	{
		struct ctf_label *to_add = malloc(CTF_LABEL_SIZE);
		to_add->index = raw_labels[i].index;
		to_add->name = strdup(_ctf_strings_lookup(strings, raw_labels[i].name));
		TAILQ_INSERT_TAIL(file->label_head, to_add, labels);
	}

	return CTF_OK;
}
