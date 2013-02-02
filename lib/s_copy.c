/* This variant of s_copy allows the target of an assignment to appear
 * on its right-hand side (contrary to the Fortran 77 Standard, but in
 * accordance with Fortran 90), as in a(2:5) = a(4:7) .
 */

#include <string.h>
#include <config.h>
#define F2C_NO_INLINE_H
#include <f2c.h>

/* assign strings:  a = b */

int s_copy(char *a, const char *b, ftnlen la, ftnlen lb)
{
  if (la <= lb) {
    memmove(a, b, la);
  } else {
    memset(memmove(a, b, lb) + lb, ' ', la - lb);
  }
  return 0;
}
