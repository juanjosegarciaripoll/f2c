#
# Main program
#
AM_CPPFLAGS = $(CPPFLAGS) -I$(top_builddir)/config_aux

bin_PROGRAMS = f2c

f2c_SOURCES = \
	main.c \
	init.c \
	gram.c \
	lex.c \
	proc.c \
	equiv.c \
	data.c \
	format.c \
	expr.c \
	exec.c \
	intr.c \
	io.c \
	misc.c \
	error.c \
	mem.c \
	names.c \
	output.c \
	p1output.c \
	pread.c \
	put.c \
	putpcc.c \
	vax.c \
	formatdata.c \
	parse_args.c \
	niceprintf.c \
	cds.c \
	sysdep.c \
	version.c

EXTRA_DIST = defines.h defs.h format.h ftypes.h iob.h machdefs.h	\
    names.h niceprintf.h output.h p1defs.h parse.h pccdefs.h sysdep.h

EXTRA_DIST += sysdeptest.c tokdefs.h tokens usignal.h malloc.c	\
    memset.c

EXTRA_DIST += gram.dcl gram.exec gram.expr gram.head gram.io readme
