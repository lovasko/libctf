#ifndef CTF_STRUCT_UNION_H
#define CTF_STRUCT_UNION_H

#include "member.h"
#include "util/property.h"
#include "util/listing.h"

struct ctf_struct_union
{
	char* name;
	struct ctf_member_head* member_head;
};
#define CTF_STRUCT_UNION_SIZE sizeof(struct ctf_struct_union)

typedef struct ctf_struct_union* ctf_struct_union;

_CTF_GET_PROPERTY_PROTO(ctf_struct_union_get_name, ctf_struct_union, char*)

_CTF_LISTING_PROTO(ctf_struct_union_get_next_member, ctf_struct_union,
    ctf_member)

#endif

