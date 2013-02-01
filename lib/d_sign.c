#include <math.h>
#include <config.h>
#define F2C_NO_INLINE_H
#include <f2c.h>

double d_sign(const doublereal *a, const doublereal *b)
{
  double x = fabs(*a);
  return *b >= 0 ? x : -x;
}
