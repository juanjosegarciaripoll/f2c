#include <config.h>
#include <math.h>
#include "f2c.h"

double d_nint(doublereal *x)
{
return( (*x)>=0 ?
	floor(*x + .5) : -floor(.5 - *x) );
}
