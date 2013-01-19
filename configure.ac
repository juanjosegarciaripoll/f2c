dnl -*- Autoconf -*-
AC_INIT([F2C Fortran to C99 compiler],
	[0.0.0],
	[jjgarcia@users.sourceforge.net],
	[f2c])

#
# Initialize Autoconf. Note that all files in config_aux are created by
# the automatic tools.
#
AC_PREREQ(2.59)
AC_CONFIG_SRCDIR([./README])		dnl Unique file where sources are
AC_CONFIG_MACRO_DIR([m4])		dnl Additional macro directories
AC_CONFIG_AUX_DIR([config_aux])		dnl Where to put autoconf files
AC_CONFIG_HEADERS([config_aux/config.h])	dnl Automatically generated
AC_CONFIG_FILES([Makefile src/Makefile lib/Makefile include/Makefile scripts/Makefile])
AC_CONFIG_FILES([scripts/f77], [chmod +x scripts/f77])
AC_CONFIG_HEADERS([include/f2c.h])

#
# Initialize Automake, minimal version 1.9, with options to make it less
# pedantic, various distribution targets and placing object files together
# inside source dirs.
#
AM_INIT_AUTOMAKE([1.9 foreign dist-bzip2 dist-zip subdir-objects])

# Programs used to build the library
AC_PROG_CC
AC_LANG([C])
AC_PROG_LIBTOOL

# Check the size of the integer types
FC_INT_TEST
FC_LONG_INT_TEST
FC_LONG_LONG_INT_TEST

# Compiler features
AC_C_INLINE

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
