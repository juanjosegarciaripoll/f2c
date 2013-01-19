/*	copy of ftypes from the compiler */
/* variable types
 * numeric assumptions:
 *	int < reals < complexes
 *	TYDREAL-TYREAL = TYDCOMPLEX-TYCOMPLEX
 */

/* 0-10 retain their old (pre LOGICAL*1, etc.) */
/* values to allow mixing old and new objects. */

#define TYUNKNOWN 0
#define TYADDR 1
#define TYSHORT 2
#define TYLONG 3
#define TYREAL 4
#define TYDREAL 5
#define TYCOMPLEX 6
#define TYDCOMPLEX 7
#define TYLOGICAL 8
#define TYCHAR 9
#define TYSUBR 10
#define TYINT1 11
#define TYLOGICAL1 12
#define TYLOGICAL2 13
#ifdef Allow_TYQUAD
#undef TYQUAD
#define TYQUAD 14
#endif

#define	LINTW	24
#define	LINE	80
#define	LLOGW	2
#define	LGFMT	"%.9G"
/* LEFBL 20 should suffice; 24 overcomes a NeXT bug. */
#define	LEFBL	24

typedef union
{
	char	flchar;
	short	flshort;
	ftnint	flint;
#ifdef Allow_TYQUAD
	longint fllongint;
#endif
	real	flreal;
	doublereal	fldouble;
} flex;
