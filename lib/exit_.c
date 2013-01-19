/* This gives the effect of

	subroutine exit(rc)
	integer*4 rc
	stop
	end

 * with the added side effect of supplying rc as the program's exit code.
 */
#include <stdlib.h>
#include <config.h>
#include "f2c.h"

void exit_(integer *rc)
{
	f_exit();
	exit(*rc);
}
