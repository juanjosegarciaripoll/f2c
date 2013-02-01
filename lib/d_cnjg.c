#include <math.h>
#include <config.h>
#define F2C_NO_INLINE_H
#include <f2c.h>

void
d_cnjg(doublecomplex *r, const doublecomplex *z)
{
	doublereal zi = z->i;
	r->r = z->r;
	r->i = -zi;
}
