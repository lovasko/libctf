#include "vardata.h"

#ifdef _KERNEL
	#include <sys/malloc.h>
	#include <sys/libkern.h>
#elif
	#include <stdint.h>
	#include <stdlib.h>
	#include <string.h>
#endif

#define _CTF_INT_FLOAT_ENCODING_MASK 0xff000000
#define _CTF_INT_FLOAT_OFFSET_MASK   0x00ff0000 
#define _CTF_INT_FLOAT_SIZE_MASK     0x0000ffff 

#define _CTF_INT_SIGNED  1
#define _CTF_INT_CHAR    2
#define _CTF_INT_BOOLEAN 4
#define _CTF_INT_VARARGS 8

struct ctf_int*
_ctf_read_int_vardata (void* data)
{
	uint32_t* raw = (uint32_t*)data;

#ifdef _KERNEL
	struct ctf_int* vardata = malloc(CTF_INT_SIZE, M_CTF, M_WAITOK);
#elif
	struct ctf_int* vardata = malloc(CTF_INT_SIZE);
#endif


	vardata->offset = (*raw & _CTF_INT_FLOAT_OFFSET_MASK) >> 16;
	vardata->size = *raw & _CTF_INT_FLOAT_SIZE_MASK;

	uint8_t encoding = (*raw & _CTF_INT_FLOAT_ENCODING_MASK) >> 24; 
	vardata->is_signed = encoding & _CTF_INT_SIGNED;

	if (encoding & _CTF_INT_CHAR)
		vardata->content = CTF_INT_CONTENT_CHAR;
	else if (encoding & _CTF_INT_BOOLEAN)
		vardata->content = CTF_INT_CONTENT_BOOLEAN;
	else if (encoding & _CTF_INT_VARARGS)
		vardata->content = CTF_INT_CONTENT_VARARGS;
	else
		vardata->content = CTF_INT_CONTENT_NUMBER;

	return vardata;
}

struct ctf_float*
_ctf_read_float_vardata (void* data)
{
	uint32_t* raw = (uint32_t*)data;

#ifdef _KERNEL
	struct ctf_float* vardata = malloc(CTF_FLOAT_SIZE, M_CTF, M_WAITOK);
#elif
	struct ctf_float* vardata = malloc(CTF_FLOAT_SIZE);
#endif

	vardata->encoding = (*raw & _CTF_INT_FLOAT_ENCODING_MASK) >> 24; 
	vardata->offset = (*raw & _CTF_INT_FLOAT_OFFSET_MASK) >> 16;
	vardata->size = *raw & _CTF_INT_FLOAT_SIZE_MASK;

	return vardata;
}

struct ctf_array*
_ctf_read_array_vardata (void* data)
{
	struct _ctf_array* raw = (struct _ctf_array*)data;
	struct ctf_array* array = malloc(CTF_ARRAY_SIZE);

	array->length = raw->element_count;
	array->content_id = raw->content_type;

	return array;
}

struct ctf_argument_head*
_ctf_read_function_vardata (void* data, uint16_t length)
{
	struct ctf_argument_head* argument_head = malloc(CTF_ARGUMENT_HEAD_SIZE);
	TAILQ_INIT(argument_head);

	uint16_t* raw_arguments = (uint16_t*)data;
	for (uint16_t i = 0; i < length; i++)
	{
		struct ctf_argument* argument = malloc(CTF_ARGUMENT_SIZE);
		argument->id = raw_arguments[i];

		TAILQ_INSERT_TAIL(argument_head, argument, arguments);
	}

	return argument_head;
}

struct ctf_enum_head*
_ctf_read_enum_vardata (void* data, uint16_t length, struct _strings* strings)
{
	struct ctf_enum_head* enum_head = malloc(CTF_ENUM_HEAD_SIZE);
	TAILQ_INIT(enum_head);

	struct _ctf_enum_entry* raw_enum_entries = (struct _ctf_enum_entry*)data;
	for (uint16_t i = 0; i < length; i++)
	{
		struct ctf_enum_entry* enum_entry = malloc(CTF_ENUM_ENTRY_SIZE);
		enum_entry->name = strdup(_ctf_strings_lookup(strings, 
		    raw_enum_entries[i].name));
		enum_entry->value = raw_enum_entries[i].value; 

		TAILQ_INSERT_TAIL(enum_head, enum_entry, entries);
	}

	return enum_head;
}

struct ctf_member_head*
_ctf_read_struct_union_vardata (void* data, uint16_t length, uint64_t size, 
    struct _strings* strings)
{
	struct _ctf_small_member* small_member;
	struct _ctf_large_member* large_member;
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

	struct ctf_member_head* member_head = malloc(CTF_MEMBER_HEAD_SIZE);
	TAILQ_INIT(member_head);

	for (unsigned int i = 0; i < length; i++)
	{
		struct ctf_member* member = malloc(CTF_MEMBER_SIZE);

		member->name = strdup(_ctf_strings_lookup(strings, (member_type ? 
		    large_member[i].name : small_member[i].name)));

		member->id = (member_type ? large_member[i].type :
		    small_member[i].type);

		member->offset = (member_type ? 
		    (((uint64_t)large_member[i].high_offset << 32) + 
		    (uint64_t)large_member[i].low_offset) : small_member[i].offset);

		TAILQ_INSERT_TAIL(member_head, member, members);
	}

	return member_head;
}

