#include <config.h>
#include "f2c.h"

double z_abs(doublecomplex *z)
{
return( f__cabs( z->r, z->i ) );
}

