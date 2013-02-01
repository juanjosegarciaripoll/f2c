#include <math.h>
#include <config.h>
#define F2C_NO_INLINE_H
#include <f2c.h>

double erfc_(const real *x)
{
  return erfc((double)*x);
}
