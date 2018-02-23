dnl -*- Autoconf -*-
AC_INIT([F2C Fortran to C99 compiler],[12.02.01],[jjgarcia@users.sourceforge.net],[f2c])

#
# Initialize Autoconf. Note that all files in config_aux are created by
# the automatic tools.
#
AC_PREREQ([2.69])
AC_CONFIG_SRCDIR([./README.md])		dnl Unique file where sources are
AC_CONFIG_MACRO_DIR([m4])		dnl Additional macro directories
AC_CONFIG_AUX_DIR([config_aux])		dnl Where to put autoconf files
AC_CONFIG_HEADERS([config_aux/config.h])	dnl Automatically generated
AC_CONFIG_FILES([Makefile src/Makefile lib/Makefile include/Makefile scripts/Makefile doc/Makefile])
AC_CONFIG_FILES([scripts/f77], [chmod +x scripts/f77])
AC_CONFIG_HEADERS([include/f2c_types.h])

#
# Initialize Automake, minimal version 1.9, with options to make it less
# pedantic, various distribution targets and placing object files together
# inside source dirs.
#
AM_INIT_AUTOMAKE([1.9 foreign dist-bzip2 dist-zip subdir-objects -Wall])

# Option Processing
AC_MSG_CHECKING([enable_docs])
AC_ARG_ENABLE([docs],
       [AS_HELP_STRING([--enable-docs],[build and install documentation (default)])
AS_HELP_STRING([--disable-docs],[do not build or install documentation])],,
       [enable_docs=yes])
AC_MSG_RESULT([$enable_docs])
AM_CONDITIONAL([DOCS], [test x${enable_docs} = xyes])

# Programs used to build the library
AC_PROG_CC
AM_PROG_CC_C_O # needed to build in subdirs
AC_LANG([C])
AM_PROG_AR
LT_INIT
AM_COND_IF([DOCS],
 [AC_CHECK_PROGS(LATEX,[latexmk rubber pdflatex],[false])
  AC_CHECK_PROGS(MAN,[man],[false])])

# Check the size of the integer types
FC_INT_TEST
FC_LONG_INT_TEST
FC_LONG_LONG_INT_TEST

# Compiler features
AC_C_INLINE
AX_CFLAGS_WARN_ALL
AX_CHECK_COMPILE_FLAG([-Wno-char-subscripts], [CFLAGS="${CFLAGS} -Wno-char-subscripts"])
AX_CHECK_COMPILE_FLAG([-Wno-dangling-else], [CFLAGS="${CFLAGS} -Wno-dangling-else"]) dnl should indent *.c and fix these
AX_CHECK_COMPILE_FLAG([-Wno-strict-aliasing], [CFLAGS="${CFLAGS} -Wno-strict-aliasing"])
AX_CHECK_COMPILE_FLAG([-Wno-maybe-uninitialized], [CFLAGS="${CFLAGS} -Wno-maybe-uninitialized"])
AX_CHECK_COMPILE_FLAG([-Wno-unused-function], [CFLAGS="${CFLAGS} -Wno-unused-function"]) dnl for s_copy, driving me buggy
AX_GCC_FUNC_ATTRIBUTE([weak])

# Checks for header files.
AC_CHECK_HEADERS([fenv.h stddef.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_STRTOD
AC_CHECK_FUNCS([atexit floor isascii memset mkdir pow rmdir sqrt strchr])
AC_CHECK_FUNCS([ftruncate mkstemp mkdtemp isatty atexit onexit tmpfile])
AC_SYS_LARGEFILE
AC_FUNC_FSEEKO

AC_OUTPUT
