#include "label.h"
#include "util/section.h"

#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

/* TODO check for the duplicates based on the name */
int
ctf_label_add (struct ctf_label_head *head, struct ctf_label *to_add)
{
	LIST_INSERT_HEAD(head, to_add, labels);
	return 0;
}

int
ctf_label_remove (struct ctf_label_head *head, struct ctf_label *to_remove)
{
	struct ctf_label *runner;
	LIST_FOREACH(runner, head, labels)
	{
		if (strcmp(runner->name, to_remove->name) == 0)
		{
			LIST_REMOVE(runner, labels);
			break;
		}
	}

	return 0;
}

int
read_labels (struct ctf_label_head *head, struct _section *section, struct
    _strings *strings)
{
	if (section->size % _CTF_LABEL_SIZE != 0)
		return 1;

	struct _ctf_label *raw_labels = (struct _ctf_label*)section->data;	

	for (unsigned int i = 0; i < section->size/_CTF_LABEL_SIZE; i++)
	{
		struct ctf_label *to_add = malloc(CTF_LABEL_SIZE);
		to_add->index = raw_labels[i].index;
		to_add->name = strdup(strings_lookup(strings, raw_labels[i].name));
		ctf_label_add(head, to_add);
	}

	return 0;
}

