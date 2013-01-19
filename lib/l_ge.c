#include <config.h>
#include "f2c.h"

logical l_ge(char *a, char *b, ftnlen la, ftnlen lb)
{
return(s_cmp(a,b,la,lb) >= 0);
}
