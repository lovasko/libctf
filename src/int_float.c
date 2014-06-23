#include "int_float.h"
#include "errors.h"

int
ctf_int_float_get_size (struct ctf_int_float *int_float, uint16_t *out_size)
{
	if (int_float && out_size)
	{
		*out_size = int_float->size;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_int_float_get_offset (struct ctf_int_float *int_float, uint8_t *out_offset)
{
	if (int_float && out_offset)
	{
		*out_offset = int_float->offset;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_int_is_signed (struct ctf_int_float *int_float, int *out_is_signed)
{
	if (int_float && out_is_signed)
	{
		*out_is_signed = (int_float->encoding & CTF_INT_SIGNED);
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_int_is_char (struct ctf_int_float *int_float, int *out_is_char)
{
	if (int_float && out_is_char)
	{
		*out_is_char = (int_float->encoding & CTF_INT_CHAR);
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_int_is_boolean (struct ctf_int_float *int_float, int *out_is_boolean)
{
	if (int_float && out_is_boolean)
	{
		*out_is_boolean = (int_float->encoding & CTF_INT_BOOLEAN);
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_int_is_varargs (struct ctf_int_float *int_float, int *out_is_varargs)
{
	if (int_float && out_is_varargs)
	{
		*out_is_varargs = (int_float->encoding & CTF_INT_VARARGS);
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

int
ctf_float_get_encoding (struct ctf_int_float *int_float, int *out_encoding)
{
	if (int_float && out_encoding)
	{
		*out_encoding = int_float->encoding;
		return CTF_OK;
	}
	else
		return CTF_E_NULL;
}

