#include <string.h>
#include "lfsr.h"

uint8_t lfsr_get_byte(LFSR_t *l)
{
	uint8_t output = 0;
	uint8_t new_bit;
	uint32_t masked;
	uint32_t i, j;

	for (j = 0; j < 8; j++)
	{
		masked = l->r & l->poly;
		new_bit = 1;

		for (i = 0; i < 32; i++)
			new_bit ^= masked >> i & 1;

		output = output << 1;
		output |= l->r >> 31 & 1;
		l->r = (l->r << 1 | new_bit) & 0xffffffff;

	}

	return output;
}

void lfsr_reset(LFSR_t *l)
{
	int i;
	l->r = l->iv;

	for (i = 0; i < sizeof(l->r); i++)
		(void)lfsr_get_byte(l); /* first 4 bytes are always the iv itself, skip them */
}

void lfsr_init(LFSR_t *l, uint32_t iv, uint32_t poly)
{
	l->iv = iv;
	l->poly = poly;

	lfsr_reset(l);
}

void lfsr_crypt(LFSR_t *l, char *input, char *output)
{
	int i;
	uint8_t key_b;
	
	if (output == 0) /* inplace crypt */
		output = input;

	for (i = 0; i < strlen(input); i++)
	{
		key_b = lfsr_get_byte(l);
		output[i] = input[i] ^ key_b;
	}
}
