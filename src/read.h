#ifndef CTF_READ_H
#define CTF_READ_H

#include "file.h"

/**
 * Parse the file and extract all CTF data.
 * 
 * @param filename filename
 * @return filled ctf_file or NULL on error
 */
int
ctf_read_file (char *filename, struct ctf_file **out_file);

#endif

