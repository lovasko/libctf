#include <string.h>
#include <stdio.h>

#include "type/type.h"
#include "api/from_type.h"
#include "object/function/argument.h"
#include "object/function/function.h"
#include "type/array.h"
#include "type/enum.h"
#include "type/float.h"
#include "type/fwd_decl.h"
#include "type/int.h"
#include "type/kind.h"
#include "type/pointer.h"
#include "type/struct_union.h"
#include "type/typedef.h"

_CTF_GET_PROPERTY_IMPL(
	ctf_type_get_kind,
	ctf_type,
	ctf_kind,
	kind)

_CTF_SET_PROPERTY_IMPL(
	ctf_type_set_kind,
	ctf_type,
	ctf_kind,
	kind)

_CTF_GET_PROPERTY_IMPL(
	ctf_type_get_id,
	ctf_type,
	ctf_id,
	id)

_CTF_SET_PROPERTY_IMPL(
	ctf_type_set_id,
	ctf_type,
	ctf_id,
	id)

_CTF_GET_PROPERTY_IMPL(
	ctf_type_get_is_root,
	ctf_type,
	uint8_t,
	is_root)

_CTF_SET_PROPERTY_IMPL(
	ctf_type_set_is_root,
	ctf_type,
	uint8_t,
	is_root)

_CTF_SET_PROPERTY_IMPL(
	ctf_type_set_data,
	ctf_type,
	void*,
	data)

_CTF_FROM_TYPE_IMPL(
	ctf_type_init,
	ctf_type)

_CTF_CREATE_IMPL(
	ctf_type_create,
	ctf_type,
	CTF_TYPE_SIZE)

static int
function_arguments_string(ctf_function function, char** string)
{
	char result[2048];
	unsigned int head;
	ctf_argument argument;
	struct m_elem* runner;
	uint64_t size;

	argument = NULL;
	head = 0;
	memset(result, '\0', 2048);

	m_list_size(&function->arguments, &size);
	if (size == 0)
	{
		*string = strdup("void");
		return CTF_OK;
	}

	m_list_first(&function->arguments, &runner);
	while (runner == NULL)
	{
		m_elem_data(runner, (void**)&argument);

		ctf_type argument_type;
		ctf_argument_get_type(argument, &argument_type);

		char* argument_type_string;
		if (ctf_type_to_string(argument_type, &argument_type_string) != CTF_OK)
			return CTF_E_CONVERSION_FAULT;

		snprintf(&result[head], 2048-head, "%s, ", argument_type_string);
		head += strlen(argument_type_string);

		free(argument_type_string);

		m_elem_next(runner, &runner);
	}

	/* delete the last ", " (comma and space) */
	result[head--] = '\0';
	result[head--] = '\0';

	*string = strdup(result);
	return CTF_OK;
}

int
ctf_type_to_string(ctf_type type, char** string)
{
	if (type == NULL || string == NULL)
		return CTF_E_NULL;
	
	ctf_kind kind;
	ctf_type_get_kind(type, &kind);

	switch (kind)
	{
		case CTF_KIND_INT:
		{
			ctf_int _int;
			ctf_int_init(type, &_int);

			char* name;
			ctf_int_get_name(_int, &name);

			*string = strdup(name);
			return CTF_OK;
		}

		case CTF_KIND_FLOAT:
		{
			ctf_float _float;
			ctf_float_init(type, &_float);

			char* name;
			ctf_float_get_name(_float, &name);

			*string = strdup(name);
			return CTF_OK;
		}

		case CTF_KIND_POINTER:
		{
			ctf_pointer pointer;
			ctf_pointer_init(type, &pointer);

			ctf_type ref_type;
			ctf_pointer_get_type(pointer, &ref_type);

			char* ref_type_string;
			if (ctf_type_to_string(ref_type, &ref_type_string) != CTF_OK)
				return CTF_E_CONVERSION_FAULT;

			char result[1024];
			memset(result, '\0', 1024);
			snprintf(result, 1024, "%s*", ref_type_string);
			free(ref_type_string);

			*string = strdup(result);
			return CTF_OK;
		}

		/* FALL THROUGH */
		case CTF_KIND_STRUCT:
		case CTF_KIND_UNION:
		{
			ctf_struct_union struct_union;
			ctf_struct_union_init(type, &struct_union);

			char* name;
			ctf_struct_union_get_name(struct_union, &name);

			char result[1024];
			memset(result, '\0', 1024);
			snprintf(result, 1024, "%s %s", 
			    (kind == CTF_KIND_STRUCT ? "struct" : "union"), name);

			*string = strdup(result);
			return CTF_OK;
		}

		case CTF_KIND_TYPEDEF:
		{
			ctf_typedef _typedef;
			ctf_typedef_init(type, &_typedef);

			char* name;
			ctf_typedef_get_name(_typedef, &name);

			*string = strdup(name);
			return CTF_OK;
		}

		/* FALL THROUGH */
		case CTF_KIND_CONST:
		case CTF_KIND_RESTRICT:
		case CTF_KIND_VOLATILE:
		{
			ctf_type ref_type;
			ctf_type_init(type, &ref_type);

			ctf_kind ref_kind;
			ctf_type_get_kind(ref_type, &ref_kind);
			const char* kind_string = ctf_kind_to_string(kind);

			char* ref_type_string;
			if (ctf_type_to_string(ref_type, &ref_type_string) != CTF_OK)
				return CTF_E_CONVERSION_FAULT;

			char result[1024];
			memset(result, '\0', 1024);

			/* switch the order in case of a following pointer */
			if (ref_kind == CTF_KIND_POINTER)
				snprintf(result, 1024, "%s %s", ref_type_string, kind_string);
			else
				snprintf(result, 1024, "%s %s", kind_string, ref_type_string);

			free(ref_type_string);

			*string = strdup(result);
			return CTF_OK;
		}

		case CTF_KIND_FWD_DECL:
		{
			ctf_fwd_decl fwd_decl;
			ctf_fwd_decl_init(type, &fwd_decl);

			char* name;
			ctf_fwd_decl_get_name(fwd_decl, &name);

			char result[1024];
			memset(result, '\0', 1024);
			snprintf(result, 1024, "forward declaration of %s", name);

			*string = strdup(result);
			return CTF_OK;
		}

		case CTF_KIND_ARRAY:
		{
			ctf_array array;
			ctf_array_init(type, &array);
			
			ctf_array_length length;
			ctf_array_get_length(array, &length);

			ctf_type content_type;
			ctf_array_get_content_type(array, &content_type);

			char* content_type_string;
			if (ctf_type_to_string(content_type, &content_type_string) != CTF_OK)
				return CTF_E_CONVERSION_FAULT;

			char result[1024];
			memset(result, '\0', 1024);
			snprintf(result, 1024, "%s [%d]", content_type_string, length);
			free(content_type_string);

			*string = strdup(result);
			return CTF_OK;
		}

		case CTF_KIND_ENUM:
		{
			ctf_enum _enum;
			ctf_enum_init(type, &_enum);

			char* name;
			ctf_enum_get_name(_enum, &name);

			char result[1024];
			memset(result, '\0', 1024);
			snprintf(result, 1024, "enum %s", name);
			
			*string = strdup(result);
			return CTF_OK;
		}

		case CTF_KIND_FUNC:
		{
			ctf_function function;
			ctf_function_init(type, &function);

			char* name;
			ctf_function_get_name(function, &name);

			ctf_type return_type;
			ctf_function_get_return_type(function, &return_type);

			char* return_type_string;
			if (ctf_type_to_string(return_type, &return_type_string) != CTF_OK)
				return CTF_E_CONVERSION_FAULT;

			char* arguments_string;
			if (function_arguments_string(function, &arguments_string) != CTF_OK)
			{
				free(return_type_string);
				return CTF_E_CONVERSION_FAULT;
			}

			char result[1024];
			memset(result, '\0', 1024);
			snprintf(result, 1024, "%s (*%s)(%s)", return_type_string, name, 
			    arguments_string);
			free(return_type_string);
			free(arguments_string);

			*string = strdup(result);
			return CTF_OK;
		}

		case CTF_KIND_NONE:
		{
			*string = strdup("none");
			return CTF_OK;
		}
	}

	return CTF_E_CONVERSION_FAULT;
}

int
ctf_type_polycall(ctf_type type, void* arg, ctf_polycall polycall[])
{
	if (type->kind < CTF_KIND_MIN || type->kind > CTF_KIND_MAX)
		return CTF_E_KIND_INVALID;

	return polycall[type->kind](type, arg);
}

