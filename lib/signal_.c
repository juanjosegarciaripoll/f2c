#include <config.h>
#include "f2c.h"
#include "signal1.h"

ftnint signal_(integer *sigp, void *proc)
{
	int sig;
	sig = (int)*sigp;

	return (ftnint)signal(sig, (sig_pf)proc);
}
