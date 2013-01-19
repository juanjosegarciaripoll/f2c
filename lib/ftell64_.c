#include <config.h>
#include "f2c.h"
#include "fio.h"

#ifdef INTEGER_STAR_8

static FILE *unit_chk(integer Unit, char *who)
{
	if (Unit >= MXUNIT || Unit < 0)
		f__fatal(101, who);
	return f__units[Unit].ufd;
}

longint ftell64_(integer *Unit)
{
	FILE *f;
	return (f = unit_chk(*Unit, "ftell")) ? FTELL(f) : -1L;
}

int fseek64_(integer *Unit, longint *offset, integer *whence)
{
	FILE *f;
	int w = (int)*whence;
#ifdef SEEK_SET
	static int wohin[3] = { SEEK_SET, SEEK_CUR, SEEK_END };
#endif
	if (w < 0 || w > 2)
		w = 0;
#ifdef SEEK_SET
	w = wohin[w];
#endif
	return	!(f = unit_chk(*Unit, "fseek"))
		|| FSEEK(f, (OFF_T)*offset, w) ? 1 : 0;
}

#endif
