#ifndef CTF_ELF_SECTION_FIND_H
#define CTF_ELF_SECTION_FIND_H

#include "util/section.h"

#include <libelf.h>

#define CTF_ELF_SECTION_STRTAB   ".strtab"
#define CTF_ELF_SECTION_SYMTAB   ".symtab"
#define CTF_ELF_SECTION_DYNSYM   ".dynsym"
#define CTF_ELF_SECTION_SUNW_CTF ".SUNW_ctf"

struct _section*
elf_section_find (Elf *elf, Elf32_Ehdr *elf_header, const char *to_find);

#endif

