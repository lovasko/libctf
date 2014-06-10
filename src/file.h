#ifndef CTF_FILE_H
#define CTF_FILE_H

#include "label.h"
#include "type.h"

struct ctf_label_head;

/**
 * Root CTF data strcture.
 *
 * Does not represent the exact binary reflection of the saved data. Instead,
 * it is suited for consuming the data by applications.
 */
struct ctf_file
{
	int compressed; /**< 0/1 false/true flag for the compression */
	int version; /**< version indicator */

	struct ctf_label_head *label_head; /**< linked list containing labels */
	struct ctf_type_head *type_head; /**< linked list containing types */

	struct ctf_file *parent_file;
	uint16_t type_id_offset;
	struct ctf_type **type_id_table;
};
#define CTF_FILE_SIZE sizeof(struct ctf_file)

#endif

