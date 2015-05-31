#include "type/struct_union.h"

_CTF_GET_PROPERTY_IMPL(
	ctf_struct_union_get_name,
	ctf_struct_union,
	char*,
	name)

_CTF_SET_PROPERTY_IMPL(
	ctf_struct_union_set_name,
	ctf_struct_union,
	char*,
	name)

_CTF_FOREACH_IMPL(
	ctf_struct_union_foreach_member, 
	ctf_struct_union,
	ctf_member,
	members)

_CTF_COUNT_IMPL(
	ctf_struct_union_get_member_count,
	ctf_struct_union,
	members)

_CTF_ADD_IMPL(
	ctf_struct_union_add_member,
	ctf_struct_union,
	ctf_member,
	members)

_CTF_FROM_TYPE_IMPL(
	ctf_struct_union_init,
	ctf_struct_union)

_CTF_CREATE_1_LIST_IMPL(
	ctf_struct_union_create,
	ctf_struct_union,
	CTF_STRUCT_UNION_SIZE,
	members)

size_t
ctf_struct_union_memory_usage (ctf_struct_union struct_union)
{
	size_t usage;
	struct m_elem* runner;
	ctf_member member;

	usage = CTF_STRUCT_UNION_SIZE;
	usage += strlen(struct_union->name);

	m_list_first(&struct_union->members, &runner);
	while (runner != NULL)
	{
		m_elem_data(runner, (void**)&member);
		usage += ctf_member_memory_usage(member);
		m_elem_next(runner, &runner);
	}

	return usage;
}

