#ifndef _KERNEL

#include <string.h>
#include <zlib.h>
#include <stdlib.h>

#include "io/read/read.h"

#define _CTF_DECOMPRESS_CHUNK_SIZE 16384 

struct _section*
_ctf_decompress(struct _section* to_decompress)
{
	int ret;
	z_stream stream;
	unsigned char in[_CTF_DECOMPRESS_CHUNK_SIZE];
	unsigned char out[_CTF_DECOMPRESS_CHUNK_SIZE];
	unsigned int available;
	unsigned int offset;
	unsigned int have;

	struct _section* result = malloc(_SECTION_SIZE);
	result->data = NULL;
	result->size = 0;

	stream.zalloc = Z_NULL;
	stream.zfree = Z_NULL;
	stream.opaque = Z_NULL;
	stream.avail_in = 0;
	stream.next_in = Z_NULL;

	ret = inflateInit(&stream);
	if (ret != Z_OK)
	{
		inflateEnd(&stream);
		free(result);
		return NULL;
	}

	offset = 0;
	do 
	{
		if (offset + _CTF_DECOMPRESS_CHUNK_SIZE > to_decompress->size)
			available = to_decompress->size - offset;
		else 
			available = _CTF_DECOMPRESS_CHUNK_SIZE;

		memcpy(in, to_decompress->data + offset, available);
		stream.avail_in = available;
		stream.next_in = in;

		do
		{
			stream.avail_out = _CTF_DECOMPRESS_CHUNK_SIZE;
			stream.next_out = out;

			ret = inflate(&stream, Z_NO_FLUSH);
			if (ret != Z_OK && ret != Z_STREAM_END)
			{
				inflateEnd(&stream);
				free(result->data);
				free(result);
				return NULL;
			}

			have = _CTF_DECOMPRESS_CHUNK_SIZE - stream.avail_out;

			result->data = realloc(result->data, result->size + have);
			memcpy(result->data + result->size, out, have);
			result->size += have;
		}
		while (stream.avail_out == 0);

		offset += _CTF_DECOMPRESS_CHUNK_SIZE;
	}
	while (ret != Z_STREAM_END);

	inflateEnd(&stream);
	return result;
}

#endif

