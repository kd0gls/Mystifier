#include "mystifier.h"

static union
{
	struct
	{
		uint8_t q16 : 1;		// LSB
		uint8_t q15 : 1;
		uint8_t q14 : 1;
		uint8_t q13 : 1;
		uint8_t q12 : 1;
		uint8_t q11 : 1;
		uint8_t q10 : 1;
		uint8_t q9  : 1;
		uint8_t q8  : 1;
		uint8_t q7  : 1;
		uint8_t q6  : 1;
		uint8_t q5  : 1;
		uint8_t q4  : 1;
		uint8_t q3  : 1;
		uint8_t q2  : 1;
		uint8_t q1  : 1;		// MSB
	} bits;
	uint16_t word;
} sr;

void random_init( uint16_t seed )
{
	sr.word = seed;		// must not be 0xFFFF
}

uint16_t random( void )
{
	static bit d;

	d = !(sr.bits.q16 ^ sr.bits.q11 ^ sr.bits.q10 ^ sr.bits.q5);
	sr.word >>= 1;
	sr.bits.q1 = d;

	return sr.word;
}
