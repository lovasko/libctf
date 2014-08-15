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

#ifdef _KERNEL
	file->label_head = malloc(CTF_LABEL_HEAD_SIZE, M_CTF, M_WAITOK);
#elif
	file->label_head = malloc(CTF_LABEL_HEAD_SIZE);
#endif

	TAILQ_INIT(file->label_head);

	struct _ctf_label* raw_labels = (struct _ctf_label*)section->data;	

	for (unsigned int i = 0; i < section->size/_CTF_LABEL_SIZE; i++)
	{
#ifdef _KERNEL
		struct ctf_label* label = malloc(CTF_LABEL_SIZE, M_CTF, M_WAITOK);
		label->name = strdup(_ctf_strings_lookup(strings, raw_labels[i].name),
		    M_CTF);
#elif
		struct ctf_label* label = malloc(CTF_LABEL_SIZE);
		label->name = strdup(_ctf_strings_lookup(strings, raw_labels[i].name));
#endif

		label->index = raw_labels[i].index;

		TAILQ_INSERT_TAIL(file->label_head, label, labels);
	}

	return CTF_OK;
}

