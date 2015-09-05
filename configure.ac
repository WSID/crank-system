# Crank System: A Library for gaming
################################################################################

######## Basic configure #######################################################
AC_PREREQ([2.69])
AC_INIT([crank-system], [0.0], [jongsome@gmail.com])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR(m4)

AM_SILENT_RULES
AM_INIT_AUTOMAKE([subdir-objects])

LT_INIT

IT_PROG_INTLTOOL([0.35.0])
AC_SUBST(GETTEXT_PACKAGE, crank)


######## Basic program check. ##################################################
PKG_PROG_PKG_CONFIG
AC_PROG_CC


######## Module configure ######################################################
PKG_CHECK_MODULES([CRANK_BASE], [glib-2.0 gobject-2.0 gtk+-3.0])



######## Testing ###############################################################
GLIB_TESTS


######## GTK-Doc ###############################################################
m4_ifdef([GTK_DOC_CHECK], [
GTK_DOC_CHECK([1.14],[--flavour no-tmpl])
],[
AM_CONDITIONAL([ENABLE_GTK_DOC], false)
])

######## GObject Introspection #################################################
GOBJECT_INTROSPECTION_CHECK([1.30.0])


######## Introspection Test for Python #########################################
AC_ARG_ENABLE(test-python,
		  AS_HELP_STRING([--enable-test-python[=@<:@no/auto/yes@:>@]],
		                 [Enable tests on gir with python]),
		  , 
		  [enable_test_python=auto])

AC_MSG_CHECKING([Checking for test-python])

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
		 
	[AC_MSG_ERROR([only yes/no/auto option for enable-test-python])	]	)

AC_MSG_RESULT([$test_python])
AM_CONDITIONAL([TEST_PYTHON], [test S$test_python == S"yes"])



######## Test for vapigen to build .vapi file ##################################
VAPIGEN_CHECK()
AS_IF([test S"$enable_vala" = S"yes"],
		[AM_PROG_VALAC])

######## Benchmark recursive targets. ##########################################
AM_EXTRA_RECURSIVE_TARGETS([bench])


######## Prints configuration results ##########################################
AC_OUTPUT([
		Makefile
		crankbase/Makefile
		tests/Makefile
		tests/c/Makefile
		tests/python/Makefile
		tests/vala/Makefile
		docs/Makefile
		bench/Makefile
		bench/c/Makefile
		po/Makefile.in
		
		demo/Makefile
		demo/matrix/Makefile
		
		crank-base-0.0.pc
])
