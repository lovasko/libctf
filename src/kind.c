#include "kind.h"

uint8_t
ctf_info_to_kind (uint16_t info)
{
	return (info & 0xf800) >> 11;
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

int
ctf_kind_is_pure_reference (uint8_t kind)
{
	if (kind == CTF_KIND_POINTER
	 || kind == CTF_KIND_TYPEDEF
	 || kind == CTF_KIND_VOLATILE 
	 || kind == CTF_KIND_CONST
	 || kind == CTF_KIND_RESTRICT)
		return 1;
	else
		return 0;
}

int
ctf_kind_is_special (uint8_t kind)
{
	if (kind == CTF_KIND_NONE
	 || kind == CTF_KIND_FORWARD)
		return 1;
	else
		return 0;
}

