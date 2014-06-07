#include "compression.h"

#include <string.h>

#define CHUNK_SIZE 1024

struct ctf_section*
decompress (struct ctf_section *to_decompress)
{
	int ret;
	z_stream stream;
	unsigned char in[CHUNK_SIZE];
	unsigned char out[CHUNK_SIZE];
	unsigned int available;
	unsigned int offset;
	unsigned int have;

	struct ctf_section *result;
	result = malloc(CTF_SECTION_SIZE);
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
		if (offset + CHUNK_SIZE > to_decompress->size)
			available = to_decompress->size - offset;
		else 
			available = CHUNK_SIZE;

		memcpy(in, to_decompress->data + offset, available);
		stream.avail_in = available;
		stream.next_in = in;

		do
		{
			stream.avail_out = CHUNK_SIZE;
			stream.next_out = out;

			ret = inflate(&stream, Z_NO_FLUSH);
			if (ret != Z_OK)
			{
				inflateEnd(&stream);
				free(result);
				return NULL;
			}

			have = CHUNK_SIZE - stream.avail_out;
			realloc(result->data, result->size + have);
			memcpy(result->data + result->size, out, have);
		}
		while (stream.avail_out == 0);

		offset += CHUNK_SIZE;
	}
	while (ret != Z_STREAM_END);

	inflateEnd(&stream);
	return result;
}

