#include <config.h>
#include <math.h>
#include "f2c.h"

double d_int(doublereal *x)
{
return( (*x>0) ? floor(*x) : -floor(- *x) );
}
