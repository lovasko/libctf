#ifndef CTF_FILE_H
#define CTF_FILE_H

#include <sys/stdint.h>

#include <m_list.h>

#include "api/create.h"
#include "api/count.h"
#include "api/foreach.h"
#include "api/property.h"
#include "label/label.h"
#include "object/data/data_object.h"
#include "object/function/function.h"
#include "type/type.h"
#include "util/count.h"
#include "version.h"

/**
 * Root CTF data structure.
 *
 * Does not represent the exact binary reflection of the saved data. Instead,
 * it is suited for consuming the data by applications.
 */
struct ctf_file
{
	uint8_t is_compressed; /**< 0/1 false/true flag for the compression */
	ctf_version version; /**< version indicator */
	char* path_basename; /**< basename of the current file containing the CTF data */

	struct m_list labels;
	struct m_list types;
	struct m_list data_objects;
	struct m_list function_objects;

	struct ctf_file* parent_file; /**< pointer to parent file */
	uint16_t type_id_offset; /**< offset of the type IDs in this file */
	struct ctf_type** type_id_table; /**< array of ctf_type pointers that is
	    indexed without the offset */
	uint16_t type_count; /**< number of types in this CTF file */
};
#define CTF_FILE_SIZE sizeof(struct ctf_file)

typedef struct ctf_file* ctf_file;

_CTF_GET_PROPERTY_PROTO(ctf_file_get_version, ctf_file, ctf_version)
_CTF_SET_PROPERTY_PROTO(ctf_file_set_version, ctf_file, ctf_version)

_CTF_GET_PROPERTY_PROTO(ctf_file_get_is_compressed, ctf_file, uint8_t)
_CTF_SET_PROPERTY_PROTO(ctf_file_set_is_compressed, ctf_file, uint8_t)

_CTF_GET_PROPERTY_PROTO(ctf_file_get_parent_file, ctf_file, ctf_file)
_CTF_SET_PROPERTY_PROTO(ctf_file_set_parent_file, ctf_file, ctf_file)

_CTF_GET_PROPERTY_PROTO(ctf_file_get_basename, ctf_file, char*)
_CTF_SET_PROPERTY_PROTO(ctf_file_set_basename, ctf_file, char*)

_CTF_FOREACH_PROTO(ctf_file_foreach_label, ctf_file, ctf_label)
_CTF_COUNT_PROTO(ctf_file_get_label_count, ctf_file)

_CTF_FOREACH_PROTO(ctf_file_foreach_type, ctf_file, ctf_type)
_CTF_COUNT_PROTO(ctf_file_get_type_count, ctf_file)

_CTF_FOREACH_PROTO(ctf_file_foreach_function, ctf_file, ctf_function)
_CTF_COUNT_PROTO(ctf_file_get_function_count, ctf_file)

_CTF_FOREACH_PROTO(ctf_file_foreach_data_object, ctf_file, ctf_data_object)
_CTF_COUNT_PROTO(ctf_file_get_data_object_count, ctf_file)

_CTF_CREATE_PROTO(ctf_file_create, ctf_file)

size_t
ctf_file_memory_usage (ctf_file file);

#endif

