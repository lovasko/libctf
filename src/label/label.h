#ifndef CTF_LABEL_H
#define CTF_LABEL_H

#include <sys/stdint.h>

#include "api/create.h"
#include "api/memory_usage.h"
#include "api/property.h"

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

typedef uint32_t ctf_label_index;
#define CTF_LABEL_INDEX_MIN 0
#define CTF_LABEL_INDEX_MAX 429

/**
 * Parsed and resolved CTF label.
 */
struct ctf_label
{
	char* name; /**< resolved name */
	ctf_label_index index; /**< starting index in the type table */
};
#define CTF_LABEL_SIZE sizeof(struct ctf_label)

typedef struct ctf_label* ctf_label;

_CTF_GET_PROPERTY_PROTO(ctf_label_get_name, ctf_label, char*)
_CTF_SET_PROPERTY_PROTO(ctf_label_set_name, ctf_label, char*)

_CTF_GET_PROPERTY_PROTO(ctf_label_get_index, ctf_label, ctf_label_index)
_CTF_SET_PROPERTY_PROTO(ctf_label_set_index, ctf_label, ctf_label_index)

_CTF_CREATE_PROTO(ctf_label_create, ctf_label)

_CTF_MEMORY_USAGE_PROTO(ctf_label_memory_usage, ctf_label)

#endif

