#ifdef _KERNEL
	#include <sys/malloc.h>
	#include <sys/libkern.h>
#else
	#include <stdint.h>
	#include <stdlib.h>
	#include <string.h>
#endif

#include "io/read/read.h"
#include "space.h"

#define _CTF_INT_FLOAT_ENCODING_MASK 0xff000000
#define _CTF_INT_FLOAT_OFFSET_MASK   0x00ff0000 
#define _CTF_INT_FLOAT_SIZE_MASK     0x0000ffff 

#define _CTF_INT_SIGNED  1
#define _CTF_INT_CHAR    2
#define _CTF_INT_BOOLEAN 4
#define _CTF_INT_VARARGS 8

CTF_MALLOC_DECLARE();

struct ctf_int*
_ctf_read_int_vardata (void* data)
{
	uint32_t* raw;
	struct ctf_int* vardata;
	uint8_t encoding;

	raw = (uint32_t*)data;
	encoding = (*raw & _CTF_INT_FLOAT_ENCODING_MASK) >> 24; 

	vardata = CTF_MALLOC(CTF_INT_SIZE);
	vardata->offset = (*raw & _CTF_INT_FLOAT_OFFSET_MASK) >> 16;
	vardata->size = *raw & _CTF_INT_FLOAT_SIZE_MASK;
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
_ctf_read_float_vardata(void* data)
{
	uint32_t* raw;
	struct ctf_float* vardata;

	raw = (uint32_t*)data;

	vardata = CTF_MALLOC(CTF_FLOAT_SIZE);
	vardata->encoding = (*raw & _CTF_INT_FLOAT_ENCODING_MASK) >> 24; 
	vardata->offset = (*raw & _CTF_INT_FLOAT_OFFSET_MASK) >> 16;
	vardata->size = *raw & _CTF_INT_FLOAT_SIZE_MASK;

	return vardata;
}

struct ctf_array*
_ctf_read_array_vardata(void* data)
{
	struct _ctf_array* raw;
	struct ctf_array* array;

	raw = (struct _ctf_array*)data;

	array = CTF_MALLOC(CTF_ARRAY_SIZE);
	array->length = raw->element_count;
	array->content_id = raw->content_type;

	return array;
}

void
_ctf_read_function_vardata(struct m_list* arguments,
                           void* data,
                           uint16_t length)
{
	struct ctf_argument* argument;
	uint16_t i;
	uint16_t* raw_arguments;

	m_list_init(arguments);
	raw_arguments = (uint16_t*)data;
	for (i = 0; i < length; i++)
	{
		argument = CTF_MALLOC(CTF_ARGUMENT_SIZE);
		argument->id = raw_arguments[i];

		m_list_append(arguments, M_LIST_COPY_SHALLOW, argument, 0);
	}
}

void
_ctf_read_enum_vardata(struct m_list* entries,
                       void* data,
                       uint16_t length,
                       struct _strings* strings)
{
	struct _ctf_enum_entry* raw_entries;
	struct ctf_enum_entry* entry;
	uint16_t i;

	m_list_init(entries);
	raw_entries = (struct _ctf_enum_entry*)data;
	for (i = 0; i < length; i++)
	{
		entry = CTF_MALLOC(CTF_ENUM_ENTRY_SIZE);
		entry->name = CTF_STRDUP(_ctf_strings_lookup(strings, raw_entries[i].name));
		entry->value = raw_entries[i].value; 

		m_list_append(entries, M_LIST_COPY_SHALLOW, entry, 0);
	}
}

void
_ctf_read_struct_union_vardata(struct m_list* members,
                               void* data,
                               uint16_t length,
                               uint64_t size, 
                               struct _strings* strings)
{
	struct ctf_member* member;
	struct _ctf_small_member* small_member;
	struct _ctf_large_member* large_member;
	uint8_t member_type;
	uint16_t i;

	member_type = 0;
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

	m_list_init(members);
	for (i = 0; i < length; i++)
	{
		member = CTF_MALLOC(CTF_MEMBER_SIZE);

		member->name = CTF_STRDUP(_ctf_strings_lookup(strings, (member_type ?  large_member[i].name : small_member[i].name)));
		member->id = (member_type ? large_member[i].type : small_member[i].type);
		member->offset = (member_type ? 
		    (((uint64_t)large_member[i].high_offset << 32) + 
		    (uint64_t)large_member[i].low_offset) : small_member[i].offset);

		m_list_append(members, M_LIST_COPY_SHALLOW, member, 0);
	}
}

