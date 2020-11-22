/* -*- mode: c; fill-column: 80; c-basic-offset: 2; indent-tabs-mode: nil -*- */
#include <config.h>
#include <limits.h>
#include "f2c.h"

#ifdef INTEGER_STAR_8

longint qbit_bits(longint a, integer b, integer len)
{
	/* Assume 2's complement arithmetic */

	ulongint x, y;

	x = (ulongint) a;
	y = (ulongint)-1L;
	x >>= b;
	y <<= len;
	return (longint)(x & ~y);
}

#define F2C_LONG_LONG_BITS CHAR_BIT*sizeof(ulongint)

longint qbit_cshift(longint a, integer b, integer len)
{
	ulongint x, y, z;

	x = (ulongint)a;
	if (len <= 0) {
		if (len == 0)
			return 0;
		goto full_len;
		}
	if (len >= F2C_LONG_LONG_BITS) {
 full_len:
		if (b >= 0) {
			b %= F2C_LONG_LONG_BITS;
			return (longint)(x << b | x >> F2C_LONG_LONG_BITS - b );
			}
		b = -b;
		b %= F2C_LONG_LONG_BITS;
		return (longint)(x << F2C_LONG_LONG_BITS - b | x >> b);
		}
	y = z = (unsigned long)-1;
	y <<= len;
	z &= ~y;
	y &= x;
	x &= z;
	if (b >= 0) {
		b %= len;
		return (longint)(y | z & (x << b | x >> len - b));
		}
	b = -b;
	b %= len;
	return (longint)(y | z & (x >> b | x << len - b));
}

#endif /* INTEGER_STAR_8 */
