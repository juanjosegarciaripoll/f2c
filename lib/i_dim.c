#include <string.h>
#include <config.h>
#define F2C_NO_INLINE_H
#include <f2c.h>

integer i_dim(const integer *a, const integer *b)
{
  integer d = *a - *b;
  return (d > 0)? d : 0;
}
