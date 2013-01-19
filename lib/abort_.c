#include <config.h>
#include <stdio.h>
#include "f2c.h"

int abort_(void)
{
sig_die("Fortran abort routine called", 1);
return 0;	/* not reached */
}
