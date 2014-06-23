#include "struct_union.h"
#include "errors.h"

#include <stdlib.h>

int
ctf_struct_union_get_name (struct ctf_struct_union *struct_union, 
    char **out_name)
{
	if (struct_union && out_name)
	{
		*out_name = struct_union->name;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_struct_union_get_next_member (struct ctf_struct_union *struct_union,
    struct ctf_member *member, struct ctf_member **out_member)
{
	if (struct_union && out_member)
	{
		if (member)
		{
			struct ctf_member *next = TAILQ_NEXT(member, members);
			if (next == NULL)
				return CTF_END;
			else
			{
				*out_member = next;
				return CTF_OK;	
			}
		}
		else
		{
			if (TAILQ_EMPTY(struct_union->member_head))
				return CTF_EMPTY;

			*out_member = TAILQ_FIRST(struct_union->member_head);
		}

		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

