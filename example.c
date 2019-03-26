#include <stdio.h>

#include "fft.h"

#define LEN	8

void
print(double complex const buf[LEN])
{
	size_t i;

	for (i = 0; i < LEN; ++i) {
		printf("(%.0f, %f) ", creal(buf[i]), cimag(buf[i]));
	}

	putchar('\n');
}

int
main(void)
{
	double complex buf[LEN] = {1, 1, 1, 1, 0, 0, 0, 0};

	printf("in: ");
	print(buf);

	if (fft(buf, LEN) == -1) {
		fputs("length is not a power of two\n", stderr);
		return 1;
	}

	printf("out: ");
	print(buf);

	return 0;
}

