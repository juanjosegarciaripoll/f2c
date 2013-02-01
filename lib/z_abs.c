#include <math.h>
#include <config.h>
#define F2C_NO_INLINE_H
#include <f2c.h>

double z_abs(const doublecomplex *z)
{
  return hypot(z->r, z->i);
}
