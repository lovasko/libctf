#ifndef CTF_LABEL_H
#define CTF_LABEL_H

#include <stdint.h>

/**
 * Binary reflection of the stored CTF data. 
 *
 * Designated for internal use only.
 */
struct _ctf_label
{
	uint32_t name; /**< reference to the name */
	uint32_t index; /**< starting index in the type table */
};
#define _CTF_LABEL_SIZE sizeof(struct _ctf_label)

/**
 * Parsed and resolved CTF label.
 */
struct ctf_label
{
	char *name; /**< resolved name */
	uint32_t index; /**< starting index in the type table */

	struct ctf_label *next; /**< pointer to next label */
};
#define CTF_LABEL_SIZE sizeof(struct ctf_label)

/**
 * Add new label to the end of the list.
 *
 * If *head is NULL, it is assigned to be the newly added label. 
 * This functions makes a copy of the data inside to_add. Be sure to free it
 * afterwards.
 *
 * @param head pointer to the head of the linked list (or any node in fact)
 * @param to_add label to be added
 * @return 0 on success, 1 otherwise
 */
int
ctf_label_add (struct ctf_label **head, struct ctf_label *to_add);

/**
 * Remove the specified label from the list.
 *
 * If *head is NULL, this function behaves as no-op.
 * Note that only the name of the label is being matched, since it is the
 * member variable that needs to be unique. 
 *
 * @param head pointer to the head of the linked list (or any node in fact)
 * @param to_remove label to be removed 
 * @return 0 on success, 1 otherwise
 */
int
ctf_label_remove (struct ctf_label **head, struct ctf_label *to_remove);

#endif

