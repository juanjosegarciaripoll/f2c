#include <math.h>
#include <config.h>
#define F2C_NO_INLINE_H
#include <f2c.h>

double d_atn2(const doublereal *x, const doublereal *y)
{
  return atan2(*x,*y);
}
