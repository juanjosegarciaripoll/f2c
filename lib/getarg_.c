#include <config.h>
#include "f2c.h"

/*
 * subroutine getarg(k, c)
 * returns the kth unix command argument in fortran character
 * variable argument c
*/
int getarg_(ftnint *n, char *s, ftnlen ls)
{
	extern int xargc;
	extern char **xargv;
	const char *t;
	int i;
	
	if(*n>=0 && *n<xargc)
		t = xargv[*n];
	else
		t = "";
	for(i = 0; i<ls && *t!='\0' ; ++i)
		*s++ = *t++;
	for( ; i<ls ; ++i)
		*s++ = ' ';
	return 0;
}
