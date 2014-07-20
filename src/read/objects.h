#ifndef CTF_READ_OBJECTS_H
#define CTF_READ_OBJECTS_H

#include "strings.h"
#include "../file.h"
#include "../util/section.h"

/**
 * Parse function and data objects with the help from the symbol table.
 *
 * @param file
 * @param symtab_section 
 * @param object_section 
 * @param function_section
 * @param strings 
 * @return CTF_OK on success, one of CTF_E_* otherwise
 */
int
_ctf_read_functions_and_objects (
    struct ctf_file* file, 
		struct _section* symtab_section, 
		struct _section* object_section, 
		struct _section* function_section, 
		struct _strings* strings);

#endif

