#include <string.h>
#include <config.h>
#define F2C_NO_INLINE_H
#include <f2c.h>

ftnint iargc_(void)
{
  return xargc - 1;
}
