#include <config.h>
#include "f2c.h"

double c_abs(complex *z)
{
return( f__cabs( z->r, z->i ) );
}
