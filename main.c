#include <stdio.h>
#include "lfsr.h"

int main(void)
{
	char buf[] = "This text will be encrypted/decrypted";
	LFSR_t l;

	lfsr_init(&l, 0x73159272, 0x83403911);

	printf("input text: %s\n", buf);

	lfsr_crypt(&l, buf, NULL);

	printf("encrypted: %s\n", buf);

	lfsr_reset(&l);
	lfsr_crypt(&l, buf, buf);

	printf("decrypted: %s\n", buf);
}

