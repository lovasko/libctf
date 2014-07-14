#ifndef CTF_FILE_H
#define CTF_FILE_H

#include "label.h"
#include "type.h"
#include "data_object.h"
#include "function.h"
#include "util/property.h"
#include "util/listing.h"

/**
 * Root CTF data structure.
 *
 * Does not represent the exact binary reflection of the saved data. Instead,
 * it is suited for consuming the data by applications.
 */
struct ctf_file
{
	int compressed; /**< 0/1 false/true flag for the compression */
	int version; /**< version indicator */
	char* path_basename;

	struct ctf_label_head* label_head; /**< linked list containing labels */
	struct ctf_type_head* type_head; /**< linked list containing types */
	struct ctf_data_object_head* data_object_head;
	struct ctf_function_head* function_head;

	struct ctf_file* parent_file;
	uint16_t type_id_offset;
	struct ctf_type** type_id_table;
	uint16_t type_count;
};
#define CTF_FILE_SIZE sizeof(struct ctf_file)

typedef struct ctf_file* ctf_file;

_CTF_GET_PROPERTY_PROTO(ctf_file_get_version, struct ctf_file*, int)
_CTF_GET_PROPERTY_PROTO(ctf_file_is_compressed, struct ctf_file*, int)
_CTF_GET_PROPERTY_PROTO(ctf_file_get_parent_file, struct ctf_file*, 
    struct ctf_file*)
_CTF_GET_PROPERTY_PROTO(ctf_file_get_basename, struct ctf_file*, char*)

_CTF_LISTING_PROTO(ctf_file_get_next_label, struct ctf_file*, struct ctf_label*)
_CTF_LISTING_PROTO(ctf_file_get_next_type, struct ctf_file*, struct ctf_type*)
_CTF_LISTING_PROTO(ctf_file_get_next_function, struct ctf_file*, 
    struct ctf_function*)
_CTF_LISTING_PROTO(ctf_file_get_next_data_object, struct ctf_file*, 
    struct ctf_data_object*)

#endif

