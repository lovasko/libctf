#include "vardata.h"
#include "array.h"
#include "type.h"
#include "enum.h"
#include "function.h"
#include "argument.h"
#include "member.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void*
read_int_float_vardata (void *data)
{
	uint32_t *raw = (uint32_t*)data;
	struct ctf_int_float_vardata *vardata = malloc(CTF_INT_FLOAT_VARDATA_SIZE);

	vardata->encoding = (*raw & CTF_INT_FLOAT_ENCODING_MASK) >> 24; 
	vardata->offset = (*raw & CTF_INT_FLOAT_OFFSET_MASK) >> 16;
	vardata->size = *raw & CTF_INT_FLOAT_SIZE_MASK;

	return (void*)vardata;
}

void*
read_array_vardata (void *data)
{
	struct _ctf_array *raw = (struct _ctf_array*)data;
	struct ctf_array *array = malloc(CTF_ARRAY_SIZE);

	array->element_count = raw->element_count;
	array->type_reference = raw->content_type;

	return (void*)array;
}

void*
read_function_vardata (void *data, uint16_t length)
{
	struct ctf_argument_head *argument_head = malloc(CTF_ARGUMENT_HEAD_SIZE);
	LIST_INIT(argument_head);

	uint16_t *raw_arguments = (uint16_t*)data;
	for (uint16_t i = 0; i < length; i++)
	{
		struct ctf_argument *argument = malloc(CTF_ARGUMENT_SIZE);
		argument->type_reference = raw_arguments[i];

		LIST_INSERT_HEAD(argument_head, argument, arguments);
	}

	struct ctf_function *function = malloc(CTF_FUNCTION_SIZE);
	function->name = NULL;
	function->return_type = NULL;
	function->argument_head = argument_head;

	return (void*)function;
}

void*
read_enum_vardata (void *data, uint16_t length, struct _strings *strings)
{
	struct ctf_enum_head *enum_head = malloc(CTF_ENUM_HEAD_SIZE);
	LIST_INIT(enum_head);

	struct _ctf_enum_entry *raw_enum_entries = (struct _ctf_enum_entry*)data;
	for (uint16_t i = 0; i < length; i++)
	{
		struct ctf_enum_entry *enum_entry = malloc(CTF_ENUM_ENTRY_SIZE);
		enum_entry->name = strdup(strings_lookup(strings, raw_enum_entries[i].name));
		enum_entry->value = raw_enum_entries[i].value; 

		LIST_INSERT_HEAD(enum_head, enum_entry, entries);
	}

	return (void*)enum_head;
}

void*
read_struct_union_vardata (void *data, uint16_t length, uint16_t size, 
    struct _strings *strings)
{
	struct _ctf_small_member *small_member;
	struct _ctf_large_member *large_member;
	uint8_t member_type = 0;

	if (size >= CTF_MEMBER_THRESHOLD)
	{
		member_type = 1;
		small_member = NULL;
		large_member = data;
	}
	else
	{
		member_type = 0;
		small_member = data;
		large_member = NULL;
	}

	struct ctf_member_head *member_head = malloc(CTF_MEMBER_HEAD_SIZE);
	LIST_INIT(member_head);

	for (unsigned int i = 0; i < length; i++)
	{
		struct ctf_member *member = malloc(CTF_MEMBER_SIZE);

		member->name = strdup(strings_lookup(strings, (member_type ? 
		    large_member[i].name : small_member[i].name)));

		member->type_reference = (member_type ? large_member[i].type :
		    small_member[i].type);

		member->offset = (member_type ? large_member[i].low_offset :
		    small_member[i].offset);

		LIST_INSERT_HEAD(member_head, member, members);
	}

	return (void*)member_head;
}

