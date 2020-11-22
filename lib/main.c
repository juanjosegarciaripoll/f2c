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

extern int MAIN__(void);

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

#if 0
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
atexit(f_exit);
}

void libf2c_close()
{
f_exit();
}
