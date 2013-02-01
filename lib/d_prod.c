#include <math.h>
#include <config.h>
#define F2C_NO_INLINE_H
#include <f2c.h>

double d_prod(const real *x, const real *y)
{
  return (double)(*x) * (double)(*y) ;
}
