#include "kind.h"

uint8_t
ctf_kind_from_info (uint16_t info)
{
	return (info & 0xf800) >> 11;
}

const char*
ctf_kind_to_string (uint8_t kind)
{
	const char *string_table[] = {"none", "int", "float", "pointer", "array",
	"function", "struct", "union", "enum", "forward", "typedef", "volatile",
	"const", "restrict"};	

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

int
ctf_kind_is_complex (uint8_t kind)
{
	if (kind == CTF_KIND_INT
	 || kind == CTF_KIND_FLOAT
	 || kind == CTF_KIND_ARRAY
	 || kind == CTF_KIND_FUNC
	 || kind == CTF_KIND_ENUM
	 || kind == CTF_KIND_STRUCT
	 || kind == CTF_KIND_UNION)
		return 1;
	else
		return 0;
}

