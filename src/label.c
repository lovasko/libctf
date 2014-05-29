#include "label.h"

#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

/* TODO check for the duplicates based on the name */
/* TODO return the pointer to the newly added node */
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

