#include <config.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "f2c.h"
#include "arith.h"

#define TYSHORT 2
#define TYLONG 3
#define TYREAL 4
#define TYDREAL 5
#define TYCOMPLEX 6
#define TYDCOMPLEX 7
#define TYINT1 11
#define TYQUAD 14

#define FA7UL 0xfa7a7a7aUL

#ifdef NAN
#define REAL_NAN NAN
#define DREAL_NAN NAN
#else
#define REAL_NAN 0
#define DREAL_NAN 0
#endif

static void ieee0(void);

double _0 = 0.;

static void
fill_noise(unsigned char *x, size_t len)
{
	size_t n;
	for (n= len >> 2; n--;) {
	  *(x++) = 0xa7;
	  *(x++) = 0xa7;
	  *(x++) = 0xa7;
	  *(x++) = 0xfa;
	}
	switch (len & 3) {
	case 3:
	  *(x++) = 0xa7;
	case 2:
	  *(x++) = 0xa7;
	case 1:
	  *(x++) = 0xa7;
	case 0:
	  break;
	}
}

void
_uninit_f2c(void *x, int type, long len)
{
	static int first = 1;

	if (first) {
		first = 0;
		ieee0();
		}
	if (len == 1)
	 switch(type) {
	  case TYINT1:
		*(integer1*)x = 'Z';
		return;
	  case TYSHORT:
		*(shortint*)x = 0xfa7a;
		break;
	  case TYLONG:
		*(integer*)x = FA7UL;
		return;
#ifdef Allow_TYQAD
	  case TYQUAD:
		fill_noise((unsigned char*)x, sizeof(longint));
		return;
#endif
	  case TYCOMPLEX:
	  case TYDCOMPLEX:
		break;
	  case TYREAL:
		*(real*)x = REAL_NAN;
		return;
	  case TYDREAL:
	  	*(doublereal*)x = DREAL_NAN;
		return;
	  default:
		printf("Surprise type %d in _uninit_f2c\n", type);
	  }
	switch(type) {
	  case TYINT1:
		memset(x, 'Z', len);
		break;
	  case TYSHORT:
		fill_noise((unsigned char*)x, len * sizeof(shortint));
		break;
#ifdef Allow_TYQAD
	  case TYQUAD:
		fill_noise((unsigned char*)x, len * sizeof(longint));
		break;
#endif
	  case TYLONG:
		fill_noise((unsigned char*)x, len * sizeof(integer));
		break;
	  case TYCOMPLEX:
		len *= 2;
		/* no break */
	  case TYREAL: {
		real *p;
		for (p = (real*)x; len--; p++) {
			*p = REAL_NAN;
		}
		break;
	  }
	  case TYDCOMPLEX:
		len *= 2;
		/* no break */
	  case TYDREAL: {
		doublereal *p = (doublereal*)x;
		for (p = (doublereal*)x; len--; p++) {
			*p = DREAL_NAN;
		}
	  }
	}
}

#ifndef MSpc
#ifdef MSDOS
#define MSpc
#else
#ifdef _WIN32
#define MSpc
#endif
#endif
#endif

#ifdef MSpc
#define IEEE0_done
#include "float.h"
#include "signal.h"

static void ieee0(void)
{
#ifndef __alpha
#ifndef EM_DENORMAL
#define EM_DENORMAL _EM_DENORMAL
#endif
#ifndef EM_UNDERFLOW
#define EM_UNDERFLOW _EM_UNDERFLOW
#endif
#ifndef EM_INEXACT
#define EM_INEXACT _EM_INEXACT
#endif
#ifndef MCW_EM
#define MCW_EM _MCW_EM
#endif
	_control87(EM_DENORMAL | EM_UNDERFLOW | EM_INEXACT, MCW_EM);
#endif
	/* With MS VC++, compiling and linking with -Zi will permit */
	/* clicking to invoke the MS C++ debugger, which will show */
	/* the point of error -- provided SIGFPE is SIG_DFL. */
	signal(SIGFPE, SIG_DFL);
	}
#endif /* MSpc */

#ifdef __mips	/* must link with -lfpe */
#define IEEE0_done
/* code from Eric Grosse */
#include <stdlib.h>
#include <stdio.h>
#include "/usr/include/sigfpe.h"	/* full pathname for lcc -N */
#include "/usr/include/sys/fpu.h"

static void ieeeuserhand(unsigned exception[5], int val[2])
{
	fflush(stdout);
	fprintf(stderr,"ieee0() aborting because of ");
	if(exception[0]==_OVERFL) fprintf(stderr,"overflow\n");
	else if(exception[0]==_UNDERFL) fprintf(stderr,"underflow\n");
	else if(exception[0]==_DIVZERO) fprintf(stderr,"divide by 0\n");
	else if(exception[0]==_INVALID) fprintf(stderr,"invalid operation\n");
	else fprintf(stderr,"\tunknown reason\n");
	fflush(stderr);
	abort();
}

static void ieeeuserhand2(unsigned int **j)
{
	fprintf(stderr,"ieee0() aborting because of confusion\n");
	abort();
}

static void ieee0(void)
{
	int i;
	for(i=1; i<=4; i++){
		sigfpe_[i].count = 1000;
		sigfpe_[i].trace = 1;
		sigfpe_[i].repls = _USER_DETERMINED;
		}
	sigfpe_[1].repls = _ZERO;	/* underflow */
	handle_sigfpes( _ON,
		_EN_UNDERFL|_EN_OVERFL|_EN_DIVZERO|_EN_INVALID,
		ieeeuserhand,_ABORT_ON_ERROR,ieeeuserhand2);
	}
#endif /* mips */

#ifdef __linux__
#define IEEE0_done
#include "fpu_control.h"

#ifdef __alpha__
#ifndef USE_setfpucw
#define __setfpucw(x) __fpu_control = (x)
#endif
#endif

#ifndef _FPU_SETCW
#undef  Can_use__setfpucw
#define Can_use__setfpucw
#endif

static void ieee0(void)
{
#if (defined(__mc68000__) || defined(__mc68020__) || defined(mc68020) || defined (__mc68k__))
/* Reported 20010705 by Alan Bain <alanb@chiark.greenend.org.uk> */
/* Note that IEEE 754 IOP (illegal operation) */
/* = Signaling NAN (SNAN) + operation error (OPERR). */
#ifdef Can_use__setfpucw
	__setfpucw(_FPU_IEEE + _FPU_DOUBLE + _FPU_MASK_OPERR + _FPU_MASK_DZ + _FPU_MASK_SNAN+_FPU_MASK_OVFL);
#else
	__fpu_control = _FPU_IEEE + _FPU_DOUBLE + _FPU_MASK_OPERR + _FPU_MASK_DZ + _FPU_MASK_SNAN+_FPU_MASK_OVFL;
	_FPU_SETCW(__fpu_control);
#endif

#elif (defined(__powerpc__)||defined(_ARCH_PPC)||defined(_ARCH_PWR)) /* !__mc68k__ */
/* Reported 20011109 by Alan Bain <alanb@chiark.greenend.org.uk> */

#ifdef Can_use__setfpucw

/* The following is NOT a mistake -- the author of the fpu_control.h
for the PPC has erroneously defined IEEE mode to turn on exceptions
other than Inexact! Start from default then and turn on only the ones
which we want*/

	__setfpucw(_FPU_DEFAULT +  _FPU_MASK_IM+_FPU_MASK_OM+_FPU_MASK_UM);

#else /* PPC && !Can_use__setfpucw */

	__fpu_control = _FPU_DEFAULT +_FPU_MASK_OM+_FPU_MASK_IM+_FPU_MASK_UM;
	_FPU_SETCW(__fpu_control);

#endif /*Can_use__setfpucw*/

#else /* !(mc68000||powerpc) */

#ifdef _FPU_IEEE
#ifndef _FPU_EXTENDED /* e.g., ARM processor under Linux */
#define _FPU_EXTENDED 0
#endif
#ifndef _FPU_DOUBLE
#define _FPU_DOUBLE 0
#endif
#ifdef Can_use__setfpucw /* pre-1997 (?) Linux */
	__setfpucw(_FPU_IEEE - _FPU_MASK_IM - _FPU_MASK_ZM - _FPU_MASK_OM);
#else
#ifdef UNINIT_F2C_PRECISION_53 /* 20051004 */
	/* unmask invalid, etc., and change rounding precision to double */
	__fpu_control = _FPU_IEEE - _FPU_EXTENDED + _FPU_DOUBLE - _FPU_MASK_IM - _FPU_MASK_ZM - _FPU_MASK_OM;
	_FPU_SETCW(__fpu_control);
#else
	/* unmask invalid, etc., and keep current rounding precision */
	fpu_control_t cw;
	_FPU_GETCW(cw);
	cw &= ~(_FPU_MASK_IM | _FPU_MASK_ZM | _FPU_MASK_OM);
	_FPU_SETCW(cw);
#endif
#endif

#else /* !_FPU_IEEE */

	fprintf(stderr, "\n%s\n%s\n%s\n%s\n",
		"WARNING:  _uninit_f2c in libf2c does not know how",
		"to enable trapping on this system, so f2c's -trapuv",
		"option will not detect uninitialized variables unless",
		"you can enable trapping manually.");
	fflush(stderr);

#endif /* _FPU_IEEE */
#endif /* __mc68k__ */
}
#endif /* __linux__ */

#ifdef __alpha
#ifndef IEEE0_done
#define IEEE0_done
#include <machine/fpu.h>
static void ieee0(void)
{
	ieee_set_fp_control(IEEE_TRAP_ENABLE_INV);
}
#endif /*IEEE0_done*/
#endif /*__alpha*/

#ifdef __hpux
#define IEEE0_done
#define _INCLUDE_HPUX_SOURCE
#include <math.h>

#ifndef FP_X_INV
#include <fenv.h>
#define fpsetmask fesettrapenable
#define FP_X_INV FE_INVALID
#endif

 static void
ieee0(void)
{
	fpsetmask(FP_X_INV);
}
#endif /*__hpux*/

#ifdef _AIX
#define IEEE0_done
#include <fptrap.h>

 static void
ieee0(void)
{
	fp_enable(TRP_INVALID);
	fp_trap(FP_TRAP_SYNC);
}
#endif /*_AIX*/

#ifdef __sun
#define IEEE0_done
#include <ieeefp.h>

static void ieee0(void)
{
	fpsetmask(FP_X_INV);
}
#endif /*__sparc*/

#ifndef IEEE0_done
static void ieee0(void) {}
#endif
