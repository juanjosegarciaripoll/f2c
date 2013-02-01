/* f2c_inline.h  --  Standard Fortran to C header file */

#ifndef F2C_INLINE_H
#define F2C_INLINE_H

#ifndef F2C_INCLUDE
#error f2c_include.h cannot be included as is
#endif

static inline double c_abs(const complex *z) { return hypot(z->r, z->i); }
static inline double d_abs(const double *x) { return fabs(*x); }
static inline double d_acos(const double *x) { return acos(*x); }
static inline double d_acosh(const double *x) { return acosh(*x); }
static inline double d_asin(const double *x) { return asin(*x); }
static inline double d_asinh(const double *x) { return asinh(*x); }
static inline double d_atan(const double *x) { return atan(*x); }
static inline double d_atanh(const double *x) { return atanh(*x); }
static inline double d_atn2(const double *x, double *y) { return atan2(*x, *y); }

static inline void d_cnjg(doublecomplex *r, const doublecomplex *z)
{
	r->r = z->r;
	r->i = -z->i;
}

static inline double d_cos(const double *x) { return cos(*x); }
static inline double d_cosh(const double *x) { return cosh(*x); }

static inline double d_dim(const double *a, double *b) 
{
  double d = (*a - *b);
  return (d > 0)? d : 0;
}

static inline double d_exp(const double *x) { return exp(*x); }
static inline double d_imag(doublecomplex *x) { return x->i; }

static inline double d_int(const double *x) {
  double y = *x;
  return (y < 0)? floor(y) : -floor(-y);
}

static inline double d_lg10(const double *x) { return log10(*x); }

static inline double d_log(const double *x) { return log(*x); }
static inline double d_nint(const double *x) { return round(*x); }
static inline double d_prod(const float *x, const float *y) { return ((double)*x) * ((double)*x); }
static inline double d_sin(const double *x) { return sin(*x); }
static inline double d_tan(const double *x) { return tan(*x); }
static inline double d_sinh(const double *x) { return sinh(*x); }
static inline double d_sqrt(const double *x) { return sqrt(*x); }
static inline double d_tanh(const double *x) { return tanh(*x); }

static inline double d_sign(const double *a, const double *b)
{
  double x = fabs(*a);
  return (*b >= 0 ? x : -x);
}

static inline double derfc_(const double *x) { return erfc(*x); }
static inline double derf_(const double *x) { return erf(*x); }
static inline double erf_(const float *x) { return erf((double)(*x)); }
static inline double erfc_(const float *x) { return erfc((double)(*x)); }

static inline double z_abs(const complex *z) { return hypot(z->r, z->i); }

#endif /* !F2C_INLINE_H */
