#include <string.h>
#include <config.h>
#define F2C_NO_INLINE_H
#include <f2c.h>

shortint h_nint(const real *x)
{
  return (shortint)round(*x);
}
