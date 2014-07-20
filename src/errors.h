#ifndef CTF_ERRORS_H
#define CTF_ERRORS_H

#define CTF_E_MIN 0

#define CTF_OK 0
#define CTF_E_NO_FILE 1
#define CTF_E_ELF_HEADER_CORRUPT 2
#define CTF_E_ELF_VERSION 3
#define CTF_E_ELF_OPEN 4
#define CTF_E_NO_CTF_SECTION 5
#define CTF_E_NO_STRTAB 6
#define CTF_E_NO_SYMTAB 7
#define CTF_E_COMPRESSION 8
#define CTF_E_DECOMPRESSED_DATA_SIZE 9
#define CTF_E_PARENT_LABEL_NOT_FOUND 10
#define CTF_E_MAGIC 11
#define CTF_E_VERSION 12
#define CTF_E_LABEL_SECTION_CORRUPT 13
#define CTF_E_NOT_FOUND 14
#define CTF_END 15
#define CTF_EMPTY 16
#define CTF_E_NULL 17
#define CTF_E_OFFSETS_CORRUPT 18
#define CTF_E_KIND_INVALID 19
#define CTF_E_TYPE_ID_NOT_FOUND 20

#define CTF_E_MAX 32

const char*
ctf_get_error_string (int error);

#endif

