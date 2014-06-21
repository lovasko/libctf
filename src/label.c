#include "label.h"
#include "util/section.h"
#include "errors.h"

#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

/* TODO check for the duplicates based on the name */
int
ctf_label_add (struct ctf_label_head *head, struct ctf_label *to_add)
{
	TAILQ_INSERT_TAIL(head, to_add, labels);
	return CTF_OK;
}

int
ctf_label_remove (struct ctf_label_head *head, struct ctf_label *to_remove)
{
	struct ctf_label *runner;
	TAILQ_FOREACH (runner, head, labels)
	{
		if (strcmp(runner->name, to_remove->name) == 0)
		{
			TAILQ_REMOVE(head, runner, labels);
			return CTF_OK;
		}
	}

	return CTF_E_NOT_FOUND;
}

char*
ctf_label_get_name (struct ctf_label *label)
{
	if (label != NULL)
		return label->name;
	else
		return NULL;
}

uint32_t
ctf_label_get_index (struct ctf_label *label)
{
	if (label != NULL)
		return label->index;
	else
		return 0;
}

