#ifndef CTF_DATA_OBJECT_H
#define CTF_DATA_OBJECT_H

#include "api/property.h"
#include "type/type.h"

#include <sys/stdint.h>

/**
 * Data object.
 *
 * Representation of a global variable stored in the symbol table.
 */
struct ctf_data_object
{
	char* name; /*< name of the data object */
	ctf_type type; /*< type of the data object */

	uint32_t value;
	uint32_t size;
};
#define CTF_DATA_OBJECT_SIZE sizeof(struct ctf_data_object)

typedef struct ctf_data_object* ctf_data_object;

_CTF_GET_PROPERTY_PROTO(ctf_data_object_get_name, ctf_data_object, char*)
_CTF_SET_PROPERTY_PROTO(ctf_data_object_set_name, ctf_data_object, char*)

_CTF_GET_PROPERTY_PROTO(ctf_data_object_get_type, ctf_data_object, ctf_type)
_CTF_SET_PROPERTY_PROTO(ctf_data_object_set_type, ctf_data_object, ctf_type)

#endif

