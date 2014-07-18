#ifndef CTF_READ_READ_H
#define CTF_READ_READ_H

#include "../file.h"

/**
 * Parse the file and extract all CTF data.
 * 
 * @param filename filename
 * @param out_file parsed CTF data
 * @return CTF_OK on success, one of CTF_E_* otherwise
 */
int
ctf_file_read (const char* filename, ctf_file* out_file);

#endif

