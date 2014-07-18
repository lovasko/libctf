#ifndef CTF_FILE_H
#define CTF_FILE_H

#include "header.h"
#include "label.h"
#include "type.h"
#include "data_object.h"
#include "function.h"
#include "util/property.h"
#include "util/listing.h"
#include "util/bool.h"

#include <stdint.h>

/**
 * Root CTF data structure.
 *
 * Does not represent the exact binary reflection of the saved data. Instead,
 * it is suited for consuming the data by applications.
 */
struct ctf_file
{
	ctf_bool is_compressed; /**< 0/1 false/true flag for the compression */
	ctf_version version; /**< version indicator */
	char* path_basename; /**< basename of the current file containing the CTF
	    data */

	struct ctf_label_head* label_head;
	struct ctf_type_head* type_head;
	struct ctf_data_object_head* data_object_head;
	struct ctf_function_head* function_head;

	struct ctf_file* parent_file; /**< pointer to parent file */
	uint16_t type_id_offset; /**< offset of the type IDs in this file */
	struct ctf_type** type_id_table; /**< array of ctf_type pointers that is
	    indexed without the offset */
	uint16_t type_count; /**< number of types in this CTF file */
};
#define CTF_FILE_SIZE sizeof(struct ctf_file)

typedef struct ctf_file* ctf_file;

_CTF_GET_PROPERTY_PROTO(ctf_file_get_version, ctf_file, ctf_version)
_CTF_GET_PROPERTY_PROTO(ctf_file_is_compressed, ctf_file, ctf_bool)
_CTF_GET_PROPERTY_PROTO(ctf_file_get_parent_file, ctf_file, ctf_file)
_CTF_GET_PROPERTY_PROTO(ctf_file_get_basename, ctf_file, char*)

_CTF_LISTING_PROTO(ctf_file_get_next_label, ctf_file, ctf_label)
_CTF_LISTING_PROTO(ctf_file_get_next_type, ctf_file, ctf_type)
_CTF_LISTING_PROTO(ctf_file_get_next_function, ctf_file, ctf_function)
_CTF_LISTING_PROTO(ctf_file_get_next_data_object, ctf_file, ctf_data_object)

#endif

