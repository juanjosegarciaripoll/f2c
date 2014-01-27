#include <config.h>
#include "f2c.h"
#include "signal1.h"

ftnint signal_(integer *sigp, void *proc)
{
	int sig;
	sig = (int)*sigp;

	/* It is specified by GNU Fortran compiler that
	 * SIGNAL returns the output of signal(2), even
	 * if this is contradictory to the specification of
	 * signal(), which does not return an integer. */
	return (ftnint)signal(sig, (sig_pf)proc);
}
