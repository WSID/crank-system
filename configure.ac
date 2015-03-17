# Crank System: 게임 개발 지원을 위한 Library
############################################

# 기본 configure 설정
AC_PREREQ([2.69])
AC_INIT([crank-system], [0.0], [jongsome@gmail.com])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR(m4)

AM_SILENT_RULES
AM_INIT_AUTOMAKE([subdir-objects])

LT_INIT

IT_PROG_INTLTOOL([0.35.0])
AC_SUBST(GETTEXT_PACKAGE, crank)
# 기타 빌드 시스템 설정
# 테스트 케이스
GLIB_TESTS

# GTK-Doc
m4_ifdef([GTK_DOC_CHECK], [
GTK_DOC_CHECK([1.14],[--flavour no-tmpl])
],[
AM_CONDITIONAL([ENABLE_GTK_DOC], false)
])

# GObject Introspection
GOBJECT_INTROSPECTION_CHECK([1.30.0])


# 기본 프로그램 설정
PKG_PROG_PKG_CONFIG
AC_PROG_CC

# Crank Dummy 설정
PKG_CHECK_MODULES([CRANK_DUMMY], [glib-2.0])


# 출력합니다.
AC_OUTPUT([
		Makefile
		crankdummy/Makefile
		tests/Makefile
		docs/Makefile
		po/Makefile.in
])
