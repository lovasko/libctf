#ifndef CTF_READ_H
#define CTF_READ_H

#include "file.h"
#include "section.h"

/**
 * Parse the CTF data inside the section ctf.
 * 
 * @param ctf content of the .SUNW_ctf ELF section 
 * @param elf_string_table content of the .strtab ELF section 
 * @return filled ctf_file or NULL on error
 */
struct ctf_file*
ctf_read_buffer (struct ctf_section ctf, struct ctf_section elf_string_table);

#endif

