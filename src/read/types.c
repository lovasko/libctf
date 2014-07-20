#include "types.h"
#include "lookup.h"
#include "vardata.h"
#include "../file.h"
#include "../data_object.h"
#include "../kind.h"
#include "../errors.h"
#include "../array.h"
#include "../typedef.h"
#include "../struct_union.h"
#include "../int.h"
#include "../float.h"
#include "../fwd_decl.h"
#include "../info.h"

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

static int
kind_is_pure_reference (uint8_t kind)
{
	if (kind == CTF_KIND_POINTER
	 || kind == CTF_KIND_VOLATILE 
	 || kind == CTF_KIND_CONST
	 || kind == CTF_KIND_RESTRICT)
		return 1;
	else
		return 0;
}

static int
kind_has_vardata (uint8_t kind)
{
	if (kind == CTF_KIND_INT
	 || kind == CTF_KIND_FLOAT
	 || kind == CTF_KIND_ARRAY
	 || kind == CTF_KIND_FUNC
	 || kind == CTF_KIND_ENUM
	 || kind == CTF_KIND_STRUCT
	 || kind == CTF_KIND_UNION)
		return 1;
	else
		return 0;
}

static int
solve_type_references (struct ctf_file* file)
{
	struct ctf_type* type;
	TAILQ_FOREACH (type, file->type_head, types)
	{
		if (kind_is_pure_reference(type->kind))
			type->data = _ctf_lookup_type(file, type->data_id);

		if (type->kind == CTF_KIND_TYPEDEF)
		{
			struct ctf_typedef *_typedef = type->data;
			_typedef->type = _ctf_lookup_type(file, _typedef->id);
		}

		if (type->kind == CTF_KIND_ARRAY)
		{
			struct ctf_array *array = type->data;
			array->content_type = _ctf_lookup_type(file, array->content_id);
		}

		if (type->kind == CTF_KIND_STRUCT 
		 || type->kind == CTF_KIND_UNION)
		{
			struct ctf_struct_union *struct_union = type->data;
			struct ctf_member *member;
			TAILQ_FOREACH (member, struct_union->member_head, members)
			{
				member->type = _ctf_lookup_type(file, member->id);
			}
		}

		if (type->kind == CTF_KIND_FUNC)
		{
			struct ctf_function *func = type->data;
			func->return_type = _ctf_lookup_type(file, func->return_id);

			struct ctf_argument *argument;
			TAILQ_FOREACH (argument, func->argument_head, arguments)
			{
				argument->type = _ctf_lookup_type(file, argument->id);
			}
		}
	}

	return CTF_OK;
}

static int
create_type_table (struct ctf_file* file)
{
	file->type_id_table = malloc(CTF_TYPE_SIZE * (file->type_count + 1));

	struct ctf_type* type;
	TAILQ_FOREACH (type, file->type_head, types)
	{
		file->type_id_table[type->id] = type;	
	}

	return CTF_OK;
}

int
_ctf_read_types (struct ctf_file* file, struct _section* section, 
    struct _strings* strings)
{
	uint64_t offset = 0;	
	ctf_id id = 1;

	file->type_head = malloc(CTF_TYPE_HEAD_SIZE);
	TAILQ_INIT(file->type_head);

	file->type_count = 0;
	while (offset < section->size)
	{
		file->type_count++;

		struct _ctf_small_type *small_type = section->data + offset;	
		uint8_t kind = _ctf_info_get_kind(small_type->info);
		uint16_t vardata_length = _ctf_info_get_vardata_length(small_type->info);
		uint8_t is_root = _ctf_info_is_root(small_type->info);

		struct ctf_type *type = malloc(CTF_TYPE_SIZE);			
		type->kind = kind;
		type->id = id;
		type->is_root = is_root;

		id++;

		if (kind_is_pure_reference(kind))
		{
			type->data_id = small_type->type;

			offset += _CTF_SMALL_TYPE_SIZE;
		}

		if (kind == CTF_KIND_TYPEDEF)
		{
			struct ctf_typedef *_typedef = malloc(CTF_TYPEDEF_SIZE);
			_typedef->name = strdup(_ctf_strings_lookup(strings, small_type->name));
			_typedef->id = small_type->type;

			type->data = _typedef;

			offset += _CTF_SMALL_TYPE_SIZE;
		}

		if (kind == CTF_KIND_NONE)
		{
			type->data = NULL;

			offset += _CTF_SMALL_TYPE_SIZE;
		}

		if (kind == CTF_KIND_FWD_DECL)
		{
			struct ctf_fwd_decl* fwd_decl = malloc(CTF_FWD_DECL_SIZE);
			fwd_decl->name = strdup(_ctf_strings_lookup(strings, small_type->name));
			fwd_decl->kind = small_type->type;

			type->data = fwd_decl;

			offset += _CTF_SMALL_TYPE_SIZE;
		}

		if (kind_has_vardata(kind) && kind != CTF_KIND_FUNC)
		{
			uint64_t advance = _CTF_SMALL_TYPE_SIZE;
			uint16_t size = small_type->size;
			if (small_type->size > CTF_SMALL_TYPE_THRESHOLD)
			{
				struct _ctf_large_type *large_type = section->data + offset;
				size = large_type->size;
				advance	+= (_CTF_LARGE_TYPE_SIZE - _CTF_SMALL_TYPE_SIZE);
			}
			offset += advance;

			char *name = strdup(_ctf_strings_lookup(strings, small_type->name));

			switch (kind)
			{
				case CTF_KIND_INT:
				{
					struct ctf_int *_int = _ctf_read_int_vardata(section->data + offset);	
					_int->name = name;
					type->data = _int;
					offset += 4;
				}	
				break;

				case CTF_KIND_FLOAT:
				{
					struct ctf_float *_float = _ctf_read_float_vardata(section->data + 
					    offset);
					_float->name = name;
					type->data = _float;
					offset += 4;
				}
				break;

				case CTF_KIND_ARRAY:
				{
					struct ctf_array *array = _ctf_read_array_vardata(section->data + 
					    offset);
					array->name = name;

					type->data = array;

					offset += _CTF_ARRAY_SIZE;
				}
				break;

				case CTF_KIND_ENUM:
				{
					struct ctf_enum *_enum = malloc(CTF_ENUM_SIZE);
					_enum->name = name;
					_enum->enum_head = _ctf_read_enum_vardata(section->data + offset, 
					    vardata_length, strings);

					type->data = _enum;
					
					offset += vardata_length * _CTF_ENUM_ENTRY_SIZE;
				}
				break;

				case CTF_KIND_STRUCT:
				case CTF_KIND_UNION:
				{
					struct ctf_struct_union *struct_union = malloc(CTF_STRUCT_UNION_SIZE);
					struct_union->name = name;
					struct_union->member_head = _ctf_read_struct_union_vardata(
					    section->data + offset, vardata_length, size, strings);

					type->data = struct_union;	
					
					offset += vardata_length * (small_type->size >= CTF_MEMBER_THRESHOLD ? 
					    _CTF_LARGE_MEMBER_SIZE : _CTF_SMALL_MEMBER_SIZE);
				}
				break;
			}
		}

		/* 
		 * We need to handle the function type with special touch, since it is a
		 * combination of both reference and complex type: it uses rather type then
		 * size from the small_type union but still needs additional parsing of the
		 * vardata. But we can not afford to check the type against the
		 * SMALL_TYPE_THRESHOLD and potentially load the large_type, which would
		 * make us skip either 4 arguments or even cut the header of next type.
		 */
		if (kind == CTF_KIND_FUNC)
		{
			offset += _CTF_SMALL_TYPE_SIZE;

			struct ctf_function *function = malloc(CTF_FUNCTION_SIZE);
			function->argument_head = _ctf_read_function_vardata( section->data + 
			    offset, vardata_length);
			function->name = strdup(_ctf_strings_lookup(strings, small_type->name));
			function->return_id = small_type->type;

			type->data = function;

			/* 
			 * TRICK SECTION
			 * Operation (n + (n & 1)) is a clever, but not very obvious, way to
			 * convert an even/odd number to an even one.
			 */
			offset += (vardata_length + (vardata_length & 1)) * sizeof(uint16_t);
		}

		TAILQ_INSERT_TAIL(file->type_head, type, types);
	}

	create_type_table(file);
	solve_type_references(file);

	return CTF_OK;
}
