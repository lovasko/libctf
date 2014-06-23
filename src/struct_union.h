#ifndef CTF_STRUCT_UNION_H
#define CTF_STRUCT_UNION_H

#include "member.h"

struct ctf_struct_union
{
	char *name;
	struct ctf_member_head *member_head;	
};
#define CTF_STRUCT_UNION_SIZE sizeof(struct ctf_struct_union)

int
ctf_struct_union_get_name (struct ctf_struct_union *struct_union, 
    char **out_name);

int
ctf_struct_union_get_next_member (struct ctf_struct_union *struct_union,
    struct ctf_member *member, struct ctf_member **out_member);

#endif

