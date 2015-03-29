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

# 모듈 설정
PKG_CHECK_MODULES([CRANK_BASE], [glib-2.0 gobject-2.0])



# Introspection Test for Python
AC_ARG_ENABLE(test-python,
		  AS_HELP_STRING([--enable-test-python[=@<:@no/auto/yes@:>@]],
		                 [gir에 대해 python 검사를 수행합니다.]),
		  , 
		  [enable_test_python=auto])

AC_MSG_CHECKING([test-python 확인 진행중])

AS_CASE([$enable_test_python],
	[no],
		[test_python="no"],
		
	[yes],
		[if test S$found_introspection != S"yes"
			then AC_MSG_ERROR([Introspection feature is required for python test])
		 fi
		 AM_PATH_PYTHON([],[test_python="yes"], [AC_MSG_ERROR([Python is not found!])])	],
		 
	[auto],
		[if test S$found_introspection == S"yes"
			then AM_PATH_PYTHON([],[test_python="yes"], [test_python="no"])
		 fi	],
		 
	[AC_MSG_ERROR([--enable-test-python은 yes/no/auto 옵션으로만 주세요.])	]	)

AC_MSG_RESULT([$test_python])
AM_CONDITIONAL([TEST_PYTHON], [test S$test_python == S"yes"])




# 출력합니다.
AC_OUTPUT([
		Makefile
		crankbase/Makefile
		tests/Makefile
		tests_python/Makefile
		docs/Makefile
		po/Makefile.in
])
