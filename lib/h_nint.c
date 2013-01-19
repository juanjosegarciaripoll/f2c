#include <config.h>
#include <math.h>
#include "f2c.h"

shortint h_nint(real *x)
{
return (shortint)(*x >= 0 ? floor(*x + .5) : -floor(.5 - *x));
}
