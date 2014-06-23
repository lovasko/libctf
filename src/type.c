#include "type.h"
#include "file.h"
#include "kind.h"
#include "vardata.h"
#include "array.h"
#include "member.h"
#include "enum.h"
#include "function.h"
#include "errors.h"

#include <string.h>

/*
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
ctf_type_get_kind (struct ctf_type *type, uint8_t *out_kind)
{
	if (type && out_kind)
	{
		*out_kind = type->kind;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_type_get_id (struct ctf_type *type, uint16_t *out_id)
{
	if (type && out_id)
	{
		*out_id = type->id;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_type_is_root (struct ctf_type *type, int *out_is_root)
{
	if (type && out_is_root)
	{
		*out_is_root = type->is_root;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_type_get_data (struct ctf_type *type, void **out_data)
{
	if (type && out_data)
	{
		*out_data = type->data;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

