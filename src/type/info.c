#include "info.h"

uint8_t
_ctf_info_get_kind (uint16_t info)
{
	return (info & 0xf800) >> 11;
}

uint8_t
_ctf_info_is_root (uint16_t info)
{
	return (info & 0x0400) >> 10;
}

uint16_t
_ctf_info_get_vardata_length (uint16_t info)
{
	return (info & 0x3ff);
}

