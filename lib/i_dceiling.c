#include <string.h>
#include <config.h>
#define F2C_NO_INLINE_H
#include <f2c.h>

integer i_dceiling(const doublereal *r)
{
  doublereal x = *r;
  return ((integer)(x) + ((x) > 0 && (x) != (integer)(x)));
}
