#include <config.h>
/* EFL support routine to compare two character strings */

#include "f2c.h"

integer ef1cmc_(ftnint *a, ftnlen *la, ftnint *b, ftnlen *lb)
{
return( s_cmp( (char *)a, (char *)b, *la, *lb) );
}
