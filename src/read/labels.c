#include "labels.h"
#include "space.h"
#include "../label.h"
#include "../errors.h"

#include <sys/queue.h>

#ifdef _KERNEL
	#include <sys/malloc.h>
	#include <sys/libkern.h>
#elif
	#include <stdlib.h>
	#include <string.h>
#endif

CTF_MALLOC_DECLARE(M_CTF);

int
_ctf_read_labels (struct ctf_file* file, struct _section* section, 
    struct _strings* strings)
{
	if (section->size % _CTF_LABEL_SIZE != 0)
		return CTF_E_LABEL_SECTION_CORRUPT;
	file->label_head = CTF_MALLOC(CTF_LABEL_HEAD_SIZE);

	TAILQ_INIT(file->label_head);
	struct _ctf_label* raw_labels = (struct _ctf_label*)section->data;	
	for (unsigned int i = 0; i < section->size/_CTF_LABEL_SIZE; i++)
	{
		struct ctf_label* label = CTF_MALLOC(CTF_LABEL_SIZE);
		label->name = CTF_STRDUP(_ctf_strings_lookup(strings, raw_labels[i].name));

		label->index = raw_labels[i].index;

		TAILQ_INSERT_TAIL(file->label_head, label, labels);
	}

	return CTF_OK;
}

