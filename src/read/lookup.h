#ifndef CTF_LOOKUP_H
#define CTF_LOOKUP_H

#include "../file.h"
#include "../type.h"

/**
 * Look up a type based on its ID.
 * 
 * @param file CTF data to use
 * @param id type ID
 * @return type on success, NULL otherwise
 */
struct ctf_type*
_ctf_lookup_type (struct ctf_file* file, uint16_t id);

#endif

