#include <string.h>
#include <config.h>
#define F2C_NO_INLINE_H
#include <f2c.h>

integer i_len_trim(const char *s, ftnlen n)
{
  int i;
  for (i=n-1; i>=0; i--)
    if (s[i] != ' ')
      return i + 1;
  return 0;
}
