#ifndef CTF_FILE_H
#define CTF_FILE_H

#include "label.h"
#include "type.h"
#include "data_object.h"
#include "function.h"

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
	struct ctf_data_object_head *data_object_head;
	struct ctf_function_head *function_head;

	struct ctf_file *parent_file;
	uint16_t type_id_offset;
	struct ctf_type **type_id_table;
	uint16_t type_count;
};
#define CTF_FILE_SIZE sizeof(struct ctf_file)

int
ctf_file_get_version (struct ctf_file *file);

int
ctf_file_is_compressed (struct ctf_file *file);

struct ctf_file*
ctf_file_get_parent_file (struct ctf_file *file);

struct ctf_type*
lookup_type (struct ctf_file *file, uint16_t id);

struct ctf_label;

int
ctf_file_get_next_label (struct ctf_file *file, struct ctf_label *label, 
    struct ctf_label **out_next);

int
ctf_file_get_next_type (struct ctf_file *file, struct ctf_type *type, 
    struct ctf_type **out_next);

int
ctf_file_get_next_function (struct ctf_file *file, 
    struct ctf_function *function, struct ctf_function **out_next);

int
ctf_file_get_next_data_object (struct ctf_file *file, 
    struct ctf_data_object *data_object, struct ctf_data_object **out_next);

#endif

