#include <config.h>
#include <math.h>
#include "f2c.h"

void pow_zz(doublecomplex *r, doublecomplex *a, doublecomplex *b)
{
double logr, logi, x, y;

logr = log( hypot(a->r, a->i) );
logi = atan2(a->i, a->r);

x = exp( logr * b->r - logi * b->i );
y = logr * b->i + logi * b->r;

r->r = x * cos(y);
r->i = x * sin(y);
}
