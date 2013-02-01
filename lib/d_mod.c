#include <math.h>
#include <config.h>
#define F2C_NO_INLINE_H
#include <f2c.h>

#ifdef IEEE_drem
double drem(double, double);
#endif

double d_mod(const doublereal *x, const doublereal *y)
{
#ifdef IEEE_drem
	double xa, ya, z;
	if ((ya = *y) < 0.)
		ya = -ya;
	z = drem(xa = *x, ya);
	if (xa > 0) {
		if (z < 0)
			z += ya;
	}
	else if (z > 0)
		z -= ya;
	return z;
#else
	double quotient;
	if( (quotient = *x / *y) >= 0)
		quotient = floor(quotient);
	else
		quotient = -floor(-quotient);
	return(*x - (*y) * quotient );
#endif
}

