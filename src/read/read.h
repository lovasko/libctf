#ifndef CTF_READ_READ_H
#define CTF_READ_READ_H

#include "../file.h"
#include "../util/section.h"

/**
 * Parse the raw uncompressed CTF data.
 *
 * @param [in] ctf_data uncompressed CTF data (also with header)
 * @param [in] symbol_table symbol table of the ELF object
 * @param [in] string_table string table of the ELF object
 * @param [out] file parsed CTF data
 */
int
ctf_file_read_data (
    struct _ctf_section* ctf_data, 
    struct _ctf_section* symbol_table, 
    struct _ctf_section* string_table,
    ctf_file* file);


#ifndef _KERNEL

/**
 * Parse the file and extract all CTF data.
 * 
 * @param filename filename
 * @param out_file parsed CTF data
 * @return CTF_OK on success, one of CTF_E_* otherwise
 */
int
ctf_file_read (const char* filename, ctf_file* out_file);

#endif /* not _KERNEL */

#endif

