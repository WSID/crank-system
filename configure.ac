# Crank System: 게임 개발 지원을 위한 Library
############################################

# 기본 configure 설정
AC_PREREQ([2.69])
AC_INIT([crank-system], [0.0], [jongsome@gmail.com])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR(m4)

AM_INIT_AUTOMAKE([subdir-objects])

LT_INIT

# 기본 프로그램 설정
PKG_PROG_PKG_CONFIG
AC_PROG_CC

# Crank Dummy 설정
PKG_CHECK_MODULES([CRANK_DUMMY], [glib-2.0])


# tests 설정
GLIB_TESTS


# 출력합니다.
AC_OUTPUT([
		Makefile
		crankdummy/Makefile
		tests/Makefile
])
