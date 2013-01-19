dnl --------------------------------------------------------------
dnl Check the size of the long and unsigned long types
AC_DEFUN([FC_LONG_INT_TEST],[
  AC_MSG_CHECKING(size of long)
  AC_RUN_IFELSE([AC_LANG_SOURCE([[#include <stdio.h>
int main() {
  const char *int_type;
  int bits;
  unsigned long x = 1;
  FILE *f=fopen("conftestval", "w");
  if (!f) exit(1);
  for (bits = 0; x; bits++) {
    x <<= 1;
  }
  fprintf(f,"F2C_LONG_BITS='%d'",bits);
  exit(0);
}
]])],[eval "`cat conftestval`"],[],[])
  AC_MSG_RESULT([$F2C_LONG_BITS])
  AC_DEFINE_UNQUOTED(F2C_LONG_BITS, $F2C_LONG_BITS, [Bit size of 'long'])])

dnl --------------------------------------------------------------
dnl Check the size of the long and unsigned long types
AC_DEFUN([FC_INT_TEST],[
  AC_MSG_CHECKING(size of int)
  AC_RUN_IFELSE([AC_LANG_SOURCE([[#include <stdio.h>
int main() {
  const char *int_type;
  int bits;
  unsigned int x = 1;
  FILE *f=fopen("conftestval", "w");
  if (!f) exit(1);
  for (bits = 0; x; bits++) {
    x <<= 1;
  }
  fprintf(f,"F2C_INT_BITS='%d'",bits);
  exit(0);
}
]])],[eval "`cat conftestval`"],[],[])
  AC_MSG_RESULT([$F2C_INT_BITS])
  AC_DEFINE_UNQUOTED(F2C_INT_BITS, $F2C_INT_BITS, [Bit size of 'int'])])

dnl --------------------------------------------------------------
dnl http://autoconf-archive.cryp.to/ac_c_long_long_.html
dnl Provides a test for the existance of the long long int type and defines HAVE_LONG_LONG if it is found.
AC_DEFUN([FC_LONG_LONG_INT_TEST],
[AC_MSG_CHECKING(size of long long)
if test "x$F2C_LONG_LONG_BITS" = "xno"; then
  AC_MSG_RESULT(not available)
  ac_cv_c_long_long=no
  F2C_LONG_LONG_BITS=""
else
  if test "$GCC" = yes; then
    ac_cv_c_long_long=yes
  else
    AC_COMPILE_IFELSE([AC_LANG_PROGRAM(,[[long long int i;]])],
    ac_cv_c_long_long=yes,
    ac_cv_c_long_long=no)
  fi
fi
if test $ac_cv_c_long_long = yes; then
  if test "x$F2C_LONG_LONG_BITS" = "x"; then
    AC_RUN_IFELSE([AC_LANG_SOURCE([[#include <stdio.h>
int main() {
  const char *int_type;
  int bits;
  unsigned long long x = 1;
  FILE *f=fopen("conftestval", "w");
  if (!f) exit(1);
  for (bits = 0; x; bits++) {
    x <<= 1;
  }
  fprintf(f,"F2C_LONG_LONG_BITS='%d'",bits);
  exit(0);
}]])],[eval "`cat conftestval`"],[],[])
  fi
fi
if test "x$F2C_LONG_LONG_BITS" = "x"; then
  AC_MSG_RESULT(not available)
else
  AC_MSG_RESULT([$F2C_LONG_LONG_BITS])
  AC_DEFINE_UNQUOTED(F2C_LONG_LONG_BITS, $F2C_LONG_LONG_BITS, [Bit sizze of long long])
fi
])

