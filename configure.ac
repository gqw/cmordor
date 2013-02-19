#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT([cmordor], [0.0.1], [gqwmail@gmail.com])
AM_INIT_AUTOMAKE
LT_INIT
AC_CONFIG_SRCDIR([cmordor/main.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AX_BOOST_BASE([1.40],, [AC_ERROR([Missing boost headers (1.40+)])])
AX_BOOST_PROGRAM_OPTIONS
AX_BOOST_REGEX
AX_BOOST_THREAD
AX_BOOST_DATE_TIME

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([cmordor/Makefile])
AC_CONFIG_FILES([test/Makefile])
AC_OUTPUT
