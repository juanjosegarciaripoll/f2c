/* STARTUP PROCEDURE FOR UNIX FORTRAN PROGRAMS */
#include <config.h>
#include <stdlib.h>
#include "stdio.h"
#include "signal1.h"

#ifndef SIGIOT
#ifdef SIGABRT
#define SIGIOT SIGABRT
#endif
#endif

#include "stdlib.h"

#include "f2c.h"
#include "fio.h"

#ifdef HAVE_ATEXIT
# define ONEXIT atexit
#else
# ifdef HAVE_ONEXIT
#  define ONEXIT onexit
# endif
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_WEAK
/* Create dummy MAIN__ function and make MAIN__ a weak alias to it.
 * If linked against a program that exports MAIN__, i.e. one compiled
 * by f2c, this MAIN__ will resolve to the program's MAIN__ instead,
 * whereas normal C programs will still be able to link against this
 * library. */
static int weak_MAIN__()
{
  return -1;
}
extern int MAIN__() __attribute__((weak, alias("weak_MAIN__")));
#else
extern int MAIN__(void);
#endif

static void sigfdie(Sigarg)
{
Use_Sigarg;
sig_die("Floating Exception", 1);
}


static void sigidie(Sigarg)
{
Use_Sigarg;
sig_die("IOT Trap", 1);
}

#ifdef SIGQUIT
static void sigqdie(Sigarg)
{
Use_Sigarg;
sig_die("Quit signal", 1);
}
#endif


static void sigindie(Sigarg)
{
Use_Sigarg;
sig_die("Interrupt", 0);
}

static void sigtdie(Sigarg)
{
Use_Sigarg;
sig_die("Killed", 0);
}

#ifdef SIGTRAP
static void sigtrdie(Sigarg)
{
Use_Sigarg;
sig_die("Trace trap", 1);
}
#endif


int xargc;
char **xargv;

#ifdef HAVE_FUNC_ATTRIBUTE_WEAK
/* Make main() a weak symbol. */
int main(int argc, char **argv) __attribute__((weak));
int main(int argc, char **argv)
{
  libf2c_init(argc, argv);
  MAIN_();
  libf2c_exit();
  exit(0);	/* exit(0) rather than return(0) to bypass Cray bug */
  return 0;	/* For compilers that complain of missing return values; */
		/* others will complain that this is unreachable code. */
}
#endif

void libf2c_init(int argc, char **argv)
{
xargc = argc;
xargv = argv;
signal1(SIGFPE, sigfdie);	/* ignore underflow, enable overflow */
#ifdef SIGIOT
signal1(SIGIOT, sigidie);
#endif
#ifdef SIGTRAP
signal1(SIGTRAP, sigtrdie);
#endif
#ifdef SIGQUIT
if(signal1(SIGQUIT,sigqdie) == SIG_IGN)
	signal1(SIGQUIT, SIG_IGN);
#endif
if(signal1(SIGINT, sigindie) == SIG_IGN)
	signal1(SIGINT, SIG_IGN);
signal1(SIGTERM,sigtdie);

#ifdef pdp11
	ldfps(01200); /* detect overflow as an exception */
#endif

f_init();
#ifdef ONEXIT
ONEXIT(f_exit);
#endif
}

void libf2c_close()
{
f_exit();
}
