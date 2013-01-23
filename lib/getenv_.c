#include <config.h>
#include "f2c.h"
#undef abs
#include <stdlib.h>
#include <string.h>

/*
 * getenv - f77 subroutine to return environment variables
 *
 * called by:
 *	call getenv (ENV_NAME, char_var)
 * where:
 *	ENV_NAME is the name of an environment variable
 *	char_var is a character variable which will receive
 *		the current value of ENV_NAME, or all blanks
 *		if ENV_NAME is not defined
 */

int getenv_(char *fname, char *value, ftnlen flen, ftnlen vlen)
{
	char buf[256], *ep, *fp;
	integer i;

	if (flen <= 0)
		goto add_blanks;
	for(i = 0; i < sizeof(buf); i++) {
		if (i == flen || (buf[i] = fname[i]) == ' ') {
			buf[i] = 0;
			ep = getenv(buf);
			goto have_ep;
			}
		}
	while(i < flen && fname[i] != ' ')
		i++;
	strncpy(fp = F77_aloc(i+1, "getenv_"), fname, (int)i);
	fp[i] = 0;
	ep = getenv(fp);
	free(fp);
 have_ep:
	if (ep)
		while(*ep && vlen-- > 0)
			*value++ = *ep++;
 add_blanks:
	while(vlen-- > 0)
		*value++ = ' ';
	return 0;
}