#include <config.h>
#include "f2c.h"
#include "fio.h"

integer do_lio(ftnint *type, ftnint *number, char *ptr, ftnlen len)
{
	return((*f__lioproc)(number,ptr,len,*type));
}
