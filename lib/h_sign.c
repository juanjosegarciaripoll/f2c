#include <string.h>
#include <config.h>
#define F2C_NO_INLINE_H
#include <f2c.h>

shortint h_sign(const shortint *a, const shortint *b)
{
  shortint x = abs(*a);
  return *b >= 0 ? x : -x;
}
