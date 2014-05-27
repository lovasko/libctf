#include "label.h"

#include <stdlib.h>
#include <string.h>

/* TODO check for the duplicates based on the name */
/* TODO return the pointer to the newly added node */
int
ctf_label_add (struct ctf_label **head, struct ctf_label *to_add)
{
	if (*head == NULL)
	{
		*head = (struct ctf_label*)malloc(CTF_LABEL_SIZE);
		(*head)->index = to_add->index;
		(*head)->name = strdup(to_add->name);
		(*head)->next = NULL;
	}
	else
	{
		struct ctf_label *node;
		for (node = (*head)->next; node->next; node = node->next);	

		node->next = (struct ctf_label*)malloc(CTF_LABEL_SIZE);
		node->next->index = to_add->index;
		node->next->name = strdup(to_add->name);
		node->next->next = NULL;
	}

	return 0;
}

int
ctf_label_remove (struct ctf_label **head, struct ctf_label *to_remove)
{
	struct ctf_label *next;
	struct ctf_label **prev;
	struct ctf_label **node;

	/* check first node */
	if (strcmp(to_remove->name, (*head)->name) == 0)
	{
		next = (*head)->next;
		free(*head);
		*head = next;

		return 0;
	}

	/* 
	 * continue from the second node until the end of list in case of match in
	 * node n, point previous node to n->next 
	 */
	prev = head;
	node = &(*head)->next;

	while (*node != NULL)
	{
		if (strcmp(to_remove->name, (*node)->name) == 0)
		{
			(*prev)->next = (*node)->next;
			free(*node);

			return 0;
		}

		*node = (*node)->next;
	}

	return 1;
}

