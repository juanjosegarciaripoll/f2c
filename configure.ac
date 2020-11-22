dnl -*- Autoconf -*-
AC_INIT([F2C Fortran to C99 compiler],
	[20.11.30],
	[jjgarcia@users.sourceforge.net],
	[f2c])

#
# Initialize Autoconf. Note that all files in config_aux are created by
# the automatic tools.
#
AC_PREREQ(2.59)
AC_CONFIG_SRCDIR([./README.md])		dnl Unique file where sources are
AC_CONFIG_MACRO_DIR([m4])		dnl Additional macro directories
AC_CONFIG_AUX_DIR([config_aux])		dnl Where to put autoconf files
AC_CONFIG_HEADERS([config_aux/config.h])	dnl Automatically generated
AC_CONFIG_FILES([Makefile src/Makefile lib/Makefile include/Makefile scripts/Makefile])
AC_CONFIG_FILES([scripts/f77], [chmod +x scripts/f77])

#
# Initialize Automake, minimal version 1.9, with options to make it less
# pedantic, various distribution targets and placing object files together
# inside source dirs.
#
AM_INIT_AUTOMAKE([1.9 foreign dist-bzip2 dist-zip subdir-objects])

# Programs used to build the library
AC_LANG([C])
AC_PROG_CC_C99
AM_PROG_CC_C_O # needed to build in subdirs
AC_PROG_LIBTOOL

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])

# Checks for library functions.
AC_FUNC_FORK
AC_CHECK_FUNCS([isascii mkdir rmdir])
AC_CHECK_FUNCS([ftruncate mkstemp mkdtemp isatty tmpfile])
AC_SYS_LARGEFILE
AC_FUNC_FSEEKO

AC_OUTPUT
