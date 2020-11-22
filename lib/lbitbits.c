#include <string.h>
#include <config.h>
#define F2C_NO_INLINE_H
#include <f2c.h>
#include <limits.h>

integer lbit_bits(integer a, integer b, integer len)
{
	/* Assume 2's complement arithmetic */

	unsigned long x, y;

	x = (unsigned long) a;
	y = (unsigned long)-1L;
	x >>= b;
	y <<= len;
	return (integer)(x & ~y);
}

#define F2C_LONG_BITS CHAR_BIT*sizeof(unsigned long)

integer lbit_cshift(integer a, integer b, integer len)
{
	unsigned long x, y, z;

	x = (unsigned long)a;
	if (len <= 0) {
		if (len == 0)
			return 0;
		goto full_len;
		}
	if (len >= F2C_LONG_BITS) {
 full_len:
		if (b >= 0) {
			b %= F2C_LONG_BITS;
			return (integer)(x << b | x >> F2C_LONG_BITS -b );
			}
		b = -b;
		b %= F2C_LONG_BITS;
		return (integer)(x << F2C_LONG_BITS - b | x >> b);
		}
	y = z = (unsigned long)-1;
	y <<= len;
	z &= ~y;
	y &= x;
	x &= z;
	if (b >= 0) {
		b %= len;
		return (integer)(y | z & (x << b | x >> len - b));
		}
	b = -b;
	b %= len;
	return (integer)(y | z & (x >> b | x << len - b));
}
