#include <config.h>
#include <math.h>
#include "f2c.h"

integer i_dnnt(doublereal *x)
{
return (integer)(*x >= 0. ? floor(*x + .5) : -floor(.5 - *x));
}
