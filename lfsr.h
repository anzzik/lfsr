#ifndef LFSR_H
#define LFSR_H

#include <inttypes.h>

typedef struct LFSR_s LFSR_t;
struct LFSR_s {
	uint32_t r;
	uint32_t iv;
	uint32_t poly;
};

uint8_t lfsr_get_byte(LFSR_t *l);
void lfsr_reset(LFSR_t *l);
void lfsr_init(LFSR_t *l, uint32_t iv, uint32_t poly);
void lfsr_crypt(LFSR_t *l, char *input, char *output);

#endif

