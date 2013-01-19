#include <config.h>
#include "f2c.h"

ftnint iargc_(void)
{
extern int xargc;
return ( xargc - 1 );
}
