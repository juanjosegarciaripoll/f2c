#include <string.h>
#include <config.h>
#define F2C_NO_INLINE_H
#include <f2c.h>

shortlogical hl_gt(const char *a, const char *b, ftnlen la, ftnlen lb)
{
  return s_cmp(a,b,la,lb) > 0;
}
