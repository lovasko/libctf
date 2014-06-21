#include "member.h"

#include <stdint.h>
#include <stdlib.h>

char*
ctf_member_get_name (struct ctf_member *member)
{
	if (member)
		return member->name;
	else
		return NULL;
}

struct ctf_type*
ctf_member_get_type (struct ctf_member *member)
{
	if (member)
		return member->type;
	else
		return NULL;
}

uint64_t
ctf_member_get_offset (struct ctf_member *member)
{
	if (member)
		return member->offset;
	else
		return 0;
}

