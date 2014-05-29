#ifndef CTF_LABEL_H
#define CTF_LABEL_H

#include <stdint.h>
#include <sys/queue.h>

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

	LIST_ENTRY(ctf_label) labels; /**< pointer to next labels */
};
#define CTF_LABEL_SIZE sizeof(struct ctf_label)

LIST_HEAD(ctf_label_head, ctf_label);
#define CTF_LABEL_HEAD_SIZE sizeof(struct ctf_label_head)

/**
 * Add new label to the end of the list.
 *
 * This function does not make copy of the to_add parameter. Be sure to keep
 * the memory available during the lifetime of the list.
 *
 * @param head pointer to the head of the linked list (or any node in fact)
 * @param to_add label to be added
 * @return 0 on success, 1 otherwise
 */
int
ctf_label_add (struct ctf_label_head *head, struct ctf_label *to_add);

/**
 * Remove the specified label from the list.
 *
 * Note that only the name of the label is being matched, since it is the
 * member variable that needs to be unique. 
 *
 * @param head pointer to the head of the linked list (or any node in fact)
 * @param to_remove label to be removed 
 * @return 0 on success, 1 otherwise
 */
int
ctf_label_remove (struct ctf_label_head *head, struct ctf_label *to_remove);

#endif

