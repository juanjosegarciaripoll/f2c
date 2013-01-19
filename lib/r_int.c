#include <config.h>
#include <math.h>
#include "f2c.h"

double r_int(real *x)
{
return( (*x>0) ? floor(*x) : -floor(- *x) );
}
