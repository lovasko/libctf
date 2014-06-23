#include "member.h"
#include "errors.h"

#include <stdint.h>
#include <stdlib.h>

int
ctf_member_get_name (struct ctf_member *member, char **out_name)
{
	if (member && out_name)
	{
		*out_name = member->name;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_member_get_type (struct ctf_member *member, struct ctf_type **out_type)
{
	if (member && out_type)
	{
		*out_type = member->type;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_member_get_offset (struct ctf_member *member, uint64_t *out_offset)
{
	if (member && out_offset)
	{
		*out_offset = member->offset;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

