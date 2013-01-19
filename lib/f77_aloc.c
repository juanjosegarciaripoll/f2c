#include <config.h>
#include "f2c.h"
#undef abs
#undef min
#undef max
#include <stdio.h>
#include <stdlib.h>

static integer memfailure = 3;

char *F77_aloc(integer Len, const char *whence)
{
	char *rv;
	unsigned int uLen = (unsigned int) Len;	/* for K&R C */

	if (!(rv = (char*)malloc(uLen))) {
		fprintf(stderr, "malloc(%u) failure in %s\n",
			uLen, whence);
		exit_(&memfailure);
		}
	return rv;
}
