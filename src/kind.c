#include "kind.h"

uint8_t
ctf_info_to_kind (uint16_t info)
{
	return (type_info & 0xf800) >> 11;
}

const char*
ctf_info_to_string (uint16_t info)
{
	const char *string_table[] = {"none", "int", "float", "pointer", "array",
	"function", "struct", "union", "enum", "forward", "typedef", "volatile",
	"const", "restrict"};	

	uint8_t kind = ctf_info_to_kind(info);
	if (kind <= CTF_KIND_MAX)
		return string_table[kind];
	else
		return "unresolvable";
}

