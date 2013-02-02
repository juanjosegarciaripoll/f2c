#include <string.h>
#include <config.h>
#define F2C_NO_INLINE_H
#include <f2c.h>

integer i_dnnt(const doublereal *x)
{
  return (integer)round(*x);
}
