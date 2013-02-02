#include <string.h>
#include <config.h>
#define F2C_NO_INLINE_H
#include <f2c.h>

integer i_sign(const integer *a, const integer *b)
{
  integer x = abs(*a);
  return *b >= 0 ? x : -x;
}
