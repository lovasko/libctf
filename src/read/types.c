#include "types.h"
#include "lookup.h"
#include "vardata.h"
#include "space.h"
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
#include "../pointer.h"

#include <sys/stdint.h>

#ifdef _KERNEL
	#include <sys/malloc.h>
	#include <sys/libkern.h>
#else
	#include <string.h>
	#include <stdlib.h>
#endif

CTF_MALLOC_DECLARE(M_CTF);

static int
kind_is_qualifier (uint8_t kind)
{
	if (kind == CTF_KIND_VOLATILE 
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

/*
 * Every type that contains a reference to another type (pointer, typedef, ...)
 * and even non-types like member of a struct_union or an argument of a
 * function, contains an union consisting of a ctf_type and ctf_id. It is
 * important to note the fact that these two variables are used in different
 * phases and therefore in order to save memory, the union is used. In the
 * first phase of the type parsing, only the ctf_id is used to store the ID of
 * the reference type. This allows for forward ctf_type references that do not
 * exist yet. In this last third the translation table is available, providing
 * conversion between ctf_id and ctf_type. 
 */
static int
solve_type_references (struct ctf_file* file)
{
	struct ctf_type* type;
	TAILQ_FOREACH (type, file->type_head, types)
	{
		if (kind_is_qualifier(type->kind))
			type->data = _ctf_lookup_type(file, type->data_id);

		if (type->kind == CTF_KIND_TYPEDEF)
		{
			struct ctf_typedef* _typedef = type->data;
			_typedef->type = _ctf_lookup_type(file, _typedef->id);
		}

		if (type->kind == CTF_KIND_ARRAY)
		{
			struct ctf_array* array = type->data;
			array->content_type = _ctf_lookup_type(file, array->content_id);
		}

		if (type->kind == CTF_KIND_STRUCT 
		 || type->kind == CTF_KIND_UNION)
		{
			struct ctf_struct_union* struct_union = type->data;
			struct ctf_member* member;
			TAILQ_FOREACH (member, struct_union->member_head, members)
			{
				member->type = _ctf_lookup_type(file, member->id);
			}
		}

		if (type->kind == CTF_KIND_FUNC)
		{
			struct ctf_function* func = type->data;
			func->return_type = _ctf_lookup_type(file, func->return_id);

			struct ctf_argument* argument;
			TAILQ_FOREACH (argument, func->argument_head, arguments)
			{
				argument->type = _ctf_lookup_type(file, argument->id);
			}
		}
	}

	return CTF_OK;
}

/*
 * Second phase of the type loading is the creation of the translation table.
 * Table keys are the type IDs and values are actual types.
 */
static int
create_type_table (struct ctf_file* file)
{
	file->type_id_table = CTF_MALLOC((CTF_TYPE_SIZE * (file->type_count + 1)));

	struct ctf_type* type;
	TAILQ_FOREACH (type, file->type_head, types)
	{
		file->type_id_table[type->id] = type;	
	}

	return CTF_OK;
}

static int
assign_qualifiers (struct ctf_file* file)
{
	struct ctf_type* type;
	TAILQ_FOREACH (type, file->type_head, types)
	{
		ctf_kind kind;
		ctf_type_get_kind(type, &kind);

		if (!kind_is_qualifier(kind))
			continue;

		ctf_type reference_type;
		reference_type = type->data;

		if (kind == CTF_KIND_CONST)
			reference_type->qualifiers |= CTF_QUALIFIER_CONST;	
		else if (kind == CTF_KIND_RESTRICT)
			reference_type->qualifiers |= CTF_QUALIFIER_RESTRICT;	
		else if (kind == CTF_KIND_VOLATILE)
			reference_type->qualifiers |= CTF_QUALIFIER_VOLATILE;	
		else
			return CTF_E_KIND_INVALID;

		TAILQ_REMOVE(file->type_head, type, types);
		free(type);
		continue;
	}

	return CTF_OK;
}

static int
low_level_parsing (struct ctf_file* file, struct _section* section, 
    struct _strings* strings)
{
	uint64_t offset = 0;	
	ctf_id id = 1;

	file->type_count = 0;
	while (offset < section->size)
	{
		file->type_count++;

		struct _ctf_small_type* small_type = section->data + offset;	
		uint8_t kind = _ctf_info_get_kind(small_type->info);
		uint16_t vardata_length = _ctf_info_get_vardata_length(small_type->info);
		uint8_t is_root = _ctf_info_is_root(small_type->info);

		struct ctf_type* type = CTF_MALLOC(CTF_TYPE_SIZE);			
		type->kind = kind;
		type->id = id;
		type->is_root = is_root;

		id++;

		if (kind_is_qualifier(kind))
		{
			type->data_id = small_type->type;

			offset += _CTF_SMALL_TYPE_SIZE;
		}

		if (kind == CTF_KIND_POINTER)
		{
			struct ctf_pointer* pointer = CTF_MALLOC(CTF_POINTER_SIZE);	
			pointer->id = small_type->type;

			type->data = pointer;

			offset += _CTF_SMALL_TYPE_SIZE;
		}

		if (kind == CTF_KIND_TYPEDEF)
		{
			struct ctf_typedef* _typedef = CTF_MALLOC(CTF_TYPEDEF_SIZE);
			_typedef->name = CTF_STRDUP(_ctf_strings_lookup(strings, 
			    small_type->name));
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
			struct ctf_fwd_decl* fwd_decl = CTF_MALLOC(CTF_FWD_DECL_SIZE);
			fwd_decl->name = CTF_STRDUP(_ctf_strings_lookup(strings, 
			    small_type->name));
			fwd_decl->kind = small_type->type;

			type->data = fwd_decl;

			offset += _CTF_SMALL_TYPE_SIZE;
		}

		if (kind_has_vardata(kind) && kind != CTF_KIND_FUNC)
		{
			uint64_t advance = _CTF_SMALL_TYPE_SIZE;
			uint64_t size = small_type->size;
			if (small_type->size > CTF_SMALL_TYPE_THRESHOLD)
			{
				struct _ctf_large_type* large_type = section->data + offset;
				size = (((uint64_t)large_type->high_size) << 32) + large_type->low_size;
				advance	+= (_CTF_LARGE_TYPE_SIZE - _CTF_SMALL_TYPE_SIZE);
			}
			offset += advance;

			char *name = CTF_STRDUP(_ctf_strings_lookup(strings, small_type->name));

			switch (kind)
			{
				case CTF_KIND_INT:
				{
					struct ctf_int* _int = _ctf_read_int_vardata(section->data + offset);	
					_int->name = name;
					type->data = _int;
					offset += 4;
				}	
				break;

				case CTF_KIND_FLOAT:
				{
					struct ctf_float* _float = _ctf_read_float_vardata(section->data + 
					    offset);
					_float->name = name;
					type->data = _float;
					offset += 4;
				}
				break;

				case CTF_KIND_ARRAY:
				{
					struct ctf_array* array = _ctf_read_array_vardata(section->data + 
					    offset);

					type->data = array;

					offset += _CTF_ARRAY_SIZE;
				}
				break;

				case CTF_KIND_ENUM:
				{
					struct ctf_enum* _enum = CTF_MALLOC(CTF_ENUM_SIZE);
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
					struct ctf_struct_union* struct_union = CTF_MALLOC(
					    CTF_STRUCT_UNION_SIZE);
					struct_union->name = name;
					struct_union->member_head = _ctf_read_struct_union_vardata(
					    section->data + offset, vardata_length, size, strings);

					ctf_member member;
					struct_union->member_count = 0;
					TAILQ_FOREACH(member, struct_union->member_head, members)
					{
						struct_union->member_count++;
					}

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

			struct ctf_function* function = CTF_MALLOC(CTF_FUNCTION_SIZE);
			function->argument_head = _ctf_read_function_vardata( section->data + 
			    offset, vardata_length);
			function->name = CTF_STRDUP(_ctf_strings_lookup(strings, small_type->name));
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

	return CTF_OK;
}

/* TODO update this algorithm with newer knowledge!
 * 
 * Algorithm
 *
 * Assume that the type under the pointer is small_type. Examine the kind of
 * the type: if it is pure reference kind = POINTER, TYPEDEF, VOLATILE, CONST,
 * RESTRICT or one of the special kinds = FORWARD or NONE, there is no need to
 * bring the large_type to the game. The data member of the ctf_type struct
 * will simply point to another ctf_type. This pointer will be acquired from
 * the "ID to pointer table". Each type that is read gets an incrementing
 * unique integer ID. Therefore, if e.g. a TYPEDEF says that the reference type
 * is 15, we need to look into our "ID to pointer table" at index 15 and just
 * return the pointer. This introduces potential problem: what if there is a
 * forward reference? For now, we hope there is no such thing. Future
 * implementation might put these types aside, still recording them into the
 * "ID to pointer table" and create some type of waiting queue that awaits its
 * forward reference/base type.
 * In case of other, more complex types INT, FLOAT, ARRAY, FUNC, STRUCT, UNION
 * or ENUM, we need to check the size member (the type has no meaningful value)
 * and decide, based on the comparison with the CTF_TYPE_THRESHOLD, whether to
 * use the large_type. Afterwards, we need to read the variant data following
 * the type data. This, as the name suggests, varies for every kind - we need a
 * special function for every kind.
 */

int
_ctf_read_types (struct ctf_file* file, struct _section* section, 
    struct _strings* strings)
{

	file->type_head = CTF_MALLOC(CTF_TYPE_HEAD_SIZE);
	TAILQ_INIT(file->type_head);

	low_level_parsing(file, section, strings);
	create_type_table(file);
	solve_type_references(file);
	assign_qualifiers(file);

	return CTF_OK;
}

