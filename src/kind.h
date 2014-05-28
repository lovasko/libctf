#ifndef CTF_KIND_H
#define CTF_KIND_H

#include <stdint.h>

#define CTF_KIND_NONE 0
#define CTF_KIND_INT 1
#define CTF_KIND_FLOAT 2
#define CTF_KIND_POINTER 3
#define CTF_KIND_ARRAY 4
#define CTF_KIND_FUNC 5
#define CTF_KIND_STRUCT 6
#define CTF_KIND_UNION 7
#define CTF_KIND_ENUM 8
#define CTF_KIND_FORWARD 9
#define CTF_KIND_TYPEDEF 10
#define CTF_KIND_VOLATILE 11
#define CTF_KIND_CONST 12
#define CTF_KIND_RESTRICT 13

#define CTF_KIND_MAX 13

uint8_t
ctf_info_to_kind (uint16_t info);

const char*
ctf_info_to_string (uint16_t info);

#endif
