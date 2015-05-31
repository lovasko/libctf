#ifndef CTF_STRUCT_UNION_H
#define CTF_STRUCT_UNION_H

#include <m_list.h>

#include "api/add.h"
#include "api/create.h"
#include "api/count.h"
#include "api/foreach.h"
#include "api/from_type.h"
#include "api/memory_usage.h"
#include "api/property.h"
#include "type/member.h"
#include "util/count.h"

struct ctf_struct_union
{
	char* name;
	struct m_list members;
};
#define CTF_STRUCT_UNION_SIZE sizeof(struct ctf_struct_union)

typedef struct ctf_struct_union* ctf_struct_union;

_CTF_GET_PROPERTY_PROTO(ctf_struct_union_get_name, ctf_struct_union, char*)
_CTF_SET_PROPERTY_PROTO(ctf_struct_union_set_name, ctf_struct_union, char*)

_CTF_FOREACH_PROTO(ctf_struct_union_foreach_member, ctf_struct_union, ctf_member)
_CTF_COUNT_PROTO(ctf_struct_union_get_member_count, ctf_struct_union)
_CTF_ADD_PROTO(ctf_struct_union_add_member, ctf_struct_union, ctf_member)

_CTF_MEMORY_USAGE_PROTO(ctf_struct_union_memory_usage, ctf_struct_union)

_CTF_FROM_TYPE_PROTO(ctf_struct_union_init, ctf_struct_union)
_CTF_CREATE_PROTO(ctf_struct_union_create, ctf_struct_union)

#endif

