#include <math.h>
#include <config.h>
#define F2C_NO_INLINE_H
#include <f2c.h>

double d_dim(const doublereal *a, const doublereal *b)
{
  double x = *a - *b;
  return (x > 0)? x : 0;
}
