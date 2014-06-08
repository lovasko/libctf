#ifndef CTF_READ_H
#define CTF_READ_H

#include "file.h"

/**
 * Parse the file and extract all CTF data.
 * 
 * @param filename filename
 * @return filled ctf_file or NULL on error
 */
struct ctf_file*
ctf_read_file (char *filename);

#endif

