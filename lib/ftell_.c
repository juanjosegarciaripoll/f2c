#include <config.h>
#include "f2c.h"
#include "fio.h"

static FILE *unit_chk(integer Unit, const char *who)
{
	if (Unit >= MXUNIT || Unit < 0)
		f__fatal(101, who);
	return f__units[Unit].ufd;
}

integer ftell_(integer *Unit)
{
	FILE *f;
	return (f = unit_chk(*Unit, "ftell")) ? ftell(f) : -1L;
}

int fseek_(integer *Unit, integer *offset, integer *whence)
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
		|| fseek(f, *offset, w) ? 1 : 0;
}
