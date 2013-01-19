f2c
===

f2c and libi77/libi77 all together in an autoconf package.

This repository contains both a Fortran77 compiler that uses C as intermediate
language, and an acommpanying library which is needed to link those programs.

The compiler and the libraries were originally in Netlib, but I have repackaged
them using autoconf and automake to make building them less painful. The ultimate
goal is to make the library and the generated code both smaller and more efficient
thanks to the use of C99 functions.

Enjoy,

Juanjo
