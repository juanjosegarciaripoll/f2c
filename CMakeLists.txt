cmake_minimum_required(VERSION 3.10)

# Find our extra modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

# set the project name
project(F2C
  VERSION 20.10.22
  DESCRIPTION "F2C Fortran to C99 compiler"
  LANGUAGES C)

# configuration files built from checks
include(CheckSymbolExists)
check_symbol_exists(ftruncate "unistd.h" "sys/types.h" HAVE_FTRUNCATE)
check_symbol_exists(isascii "ctype.h" HAVE_ISASCII)
check_symbol_exists(isatty "unistd.h" HAVE_ISATTY)
check_symbol_exists(mkdir "sys/stat.h" "sys/types.h" HAVE_MKDIR)
check_symbol_exists(mkdtemp "stdlib.h" HAVE_MKDTEMP)
check_symbol_exists(mkstemp "stdlib.h" HAVE_MKSTEMP)
check_symbol_exists(rmdir "unistd.h" HAVE_RMDIR)

#
# Large file support on UN*X, a/k/a LFS.
#
if(NOT WIN32)
  include(FindLFS)
  #
  # Check for fseeko as well.
  #
  include(FindFseeko)
  if(FSEEKO_FOUND)
    set(HAVE_FSEEKO ON)
  endif()
else()
  set(LFS_DEFINITIONS "")
  set(FSEEKO_DEFINITIONS "")
endif()

configure_file(cmake/config.h.in ${CMAKE_BINARY_DIR}/config_aux/config.h)

##################################################
#
# Fortran support library (Former libF77+libI77)
#

set(F77_HEADER_FILES
  include/f2c.h include/f2c_inline.h include/f2c_types.h
  )

add_library(f77 STATIC
  # F77 library

  lib/f77_aloc.c lib/abort_.c lib/c_abs.c lib/c_cos.c lib/c_div.c
  lib/c_exp.c lib/c_log.c lib/c_sin.c lib/c_sqrt.c lib/d_abs.c
  lib/d_acos.c lib/d_asin.c lib/d_atan.c lib/d_atn2.c lib/d_cnjg.c
  lib/d_cos.c lib/d_cosh.c lib/d_dim.c lib/d_exp.c lib/d_imag.c
  lib/d_int.c lib/d_lg10.c lib/d_log.c lib/d_mod.c lib/d_nint.c
  lib/d_prod.c lib/d_sign.c lib/d_sin.c lib/d_sinh.c lib/d_sqrt.c
  lib/d_tan.c lib/d_tanh.c lib/derf_.c lib/derfc_.c lib/dtime_.c
  lib/ef1asc_.c lib/ef1cmc_.c lib/erf_.c lib/erfc_.c lib/etime_.c
  lib/exit_.c lib/f77vers.c lib/getarg_.c lib/getenv_.c lib/h_abs.c
  lib/h_dim.c lib/h_dnnt.c lib/h_indx.c lib/h_len.c lib/h_mod.c
  lib/h_nint.c lib/h_sign.c lib/hl_ge.c lib/hl_gt.c lib/hl_le.c
  lib/hl_lt.c lib/i_abs.c lib/i_dceiling.c lib/i_dim.c lib/i_dnnt.c
  lib/i_indx.c lib/i_len.c lib/i_len_trim.c lib/i_mod.c lib/i_nint.c
  lib/i_sceiling.c lib/i_sign.c lib/iargc_.c lib/l_ge.c lib/l_gt.c
  lib/l_le.c lib/l_lt.c lib/lbitbits.c lib/lbitshft.c lib/main.c
  lib/pow_ci.c lib/pow_dd.c lib/pow_di.c lib/pow_hh.c lib/pow_ii.c
  lib/pow_qq.c lib/pow_ri.c lib/pow_zi.c lib/pow_zz.c lib/qbitbits.c
  lib/qbitshft.c lib/r_abs.c lib/r_acos.c lib/r_asin.c lib/r_atan.c
  lib/r_atn2.c lib/r_cnjg.c lib/r_cos.c lib/r_cosh.c lib/r_dim.c
  lib/r_exp.c lib/r_imag.c lib/r_int.c lib/r_lg10.c lib/r_log.c
  lib/r_mod.c lib/r_nint.c lib/r_sign.c lib/r_sin.c lib/r_sinh.c
  lib/r_sqrt.c lib/r_tan.c lib/r_tanh.c lib/s_cat.c lib/s_cmp.c
  lib/s_copy.c lib/s_paus.c lib/s_rnge.c lib/s_stop.c lib/sig_die.c
  lib/signal_.c lib/system_.c lib/uninit.c lib/z_abs.c lib/z_cos.c
  lib/z_div.c lib/z_exp.c lib/z_log.c lib/z_sin.c lib/z_sqrt.c

  # I77 library

  lib/close.c lib/dfe.c lib/dolio.c lib/due.c lib/endfile.c lib/err.c
  lib/fmt.c lib/fmtlib.c lib/ftell64_.c lib/ftell_.c lib/i77vers.c
  lib/iio.c lib/ilnw.c lib/inquire.c lib/lread.c lib/lwrite.c
  lib/open.c lib/rdfmt.c lib/rewind.c lib/rsfe.c lib/rsli.c lib/rsne.c
  lib/sfe.c lib/sue.c lib/typesize.c lib/uio.c lib/util.c lib/wref.c
  lib/wrtfmt.c lib/wsfe.c lib/wsle.c lib/wsne.c lib/xwsne.c

  # Header files
  ${F77_HEADER_FILES}
  )

target_compile_definitions(f77 PUBLIC ${LFS_DEFINITIONS})

target_include_directories(f77
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  PRIVATE lib ${CMAKE_BINARY_DIR}/config_aux
  )

target_compile_features(f77 PUBLIC c_std_99)

##################################################
#
# Fortran to C translator
#

add_executable(f2c
  src/main.c src/init.c src/gram.c src/lex.c src/proc.c src/equiv.c
  src/data.c src/format.c src/expr.c src/exec.c src/intr.c src/io.c
  src/misc.c src/error.c src/mem.c src/names.c src/output.c
  src/p1output.c src/pread.c src/put.c src/putpcc.c src/vax.c
  src/formatdata.c src/parse_args.c src/niceprintf.c src/cds.c
  src/sysdep.c src/version.c
  )

target_include_directories(f2c
  PRIVATE ${CMAKE_BINARY_DIR}/config_aux include src
  )

target_compile_features(f2c PUBLIC c_std_99)


############################################################
#
# INSTALLATION
#
include(GNUInstallDirs)
install(TARGETS f2c f77
  EXPORT f2cConfig
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
install(FILES ${F77_HEADER_FILES}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_BINARY_DIR}/f2cConfigVersion.cmake
  VERSION ${PACKAGE_VERSION}
  COMPATIBILITY AnyNewerVersion
  )
install(EXPORT f2cConfig
  NAMESPACE f2c::
  DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/f2c"
  )
install(FILES ${CMAKE_BINARY_DIR}/f2cConfigVersion.cmake
  DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/f2c"
  )
