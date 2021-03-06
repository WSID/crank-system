# Crank System: A Library for gaming
################################################################################

######## Basic configure #######################################################
AC_PREREQ([2.69])
AC_INIT([crank-system],[0.3],[jongsome@gmail.com])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR(m4)

AM_SILENT_RULES([yes])
AM_INIT_AUTOMAKE([subdir-objects])

LT_INIT

IT_PROG_INTLTOOL([0.35.0])
AC_SUBST(GETTEXT_PACKAGE, crank)


######## Basic program check. ##################################################
PKG_PROG_PKG_CONFIG
AC_PROG_CC



######## Module configure ######################################################
PKG_CHECK_MODULES([CRANK_BASE], [glib-2.0 gobject-2.0])
PKG_CHECK_MODULES([CRANK_SHAPE], [glib-2.0 gobject-2.0])
PKG_CHECK_MODULES([CRANK_VISUAL], [glib-2.0 gobject-2.0 cogl-2.0-experimental clutter-1.0])


######## Build demo ############################################################
AC_ARG_ENABLE(demo,
  AS_HELP_STRING([--enable-demo[=@<:@no/yes@:>@]],
                 [Enable build of demos to show functions of Crank System]),
  [AS_IF([test s$enableval == s"yes"],
         [PKG_CHECK_MODULES([CRANK_BASE_DEMO],
                            [glib-2.0 gobject-2.0 gtk+-3.0])
          PKG_CHECK_MODULES([CRANK_VISUAL_DEMO],
                            [glib-2.0 gobject-2.0 gtk+-3.0 cogl-2.0-experimental clutter-1.0 clutter-gtk-1.0])] ) ] )
AM_CONDITIONAL([CRANK_DEMO], [test s$enable_demo == s"yes"])

######## Testing ###############################################################
GLIB_TESTS




######## GTK-Doc ###############################################################
m4_ifdef([GTK_DOC_CHECK],
  [
GTK_DOC_CHECK([1.20], [--flavour no-tmpl])
  ],
  [
AM_CONDITIONAL([ENABLE_GTK_DOC], false)
  ]
)

######## GObject Introspection #################################################
GOBJECT_INTROSPECTION_CHECK([1.30.0])


######## Introspection Test for Python #########################################
AC_ARG_ENABLE(test-python,
  AS_HELP_STRING([--enable-test-python[=@<:@no/auto/yes@:>@]],
                 [Enable tests on gir with python]),
  ,
  [enable_test_python=auto] )

AS_IF([test s$enable_test_python != s"no"],
      [AM_PATH_PYTHON([], [have_python="yes"], [have_python="no"])] )

AC_MSG_CHECKING([for test-python])

AS_CASE([$enable_test_python],
	[no],
	[],

	[yes],
	[if test S$enable_introspection != S"yes"
	   then AC_MSG_ERROR([Introspection feature is required for python test])
	 fi
	 if test s$have_python != s"yes"
	   then AC_MSG_ERROR([Python interpreter is required for python test])
	 fi	],

	[auto],
	[if test S$enable_introspection == S"yes" ; then
	   enable_test_python=$have_python
	 else
	   enable_test_python="no"
	 fi	],
		 
	[AC_MSG_ERROR([only yes/no/auto option for enable-test-python])	]	)

AC_MSG_RESULT([$enable_test_python])
AM_CONDITIONAL([TEST_PYTHON], [test S$enable_test_python == S"yes"])



######## Test for vapigen to build .vapi file ##################################
# VAPIGEN_CHECK() will check for Introspection check.
VAPIGEN_CHECK()
AS_IF([test S"$enable_vala" = S"yes"],
      [AM_PROG_VALAC])





######## Prints configuration results ##########################################
AC_CONFIG_FILES([
		Makefile
		crankbase/Makefile
		crankshape/Makefile
		crankcore/Makefile
		crankvisual/Makefile

		tests/Makefile
		tests/c/Makefile
		tests/c/base/Makefile
		tests/c/shape/Makefile
		tests/python/Makefile
		tests/python/base/Makefile
		tests/python/shape/Makefile
		tests/vala/Makefile
		tests/vala/base/Makefile
		tests/vala/shape/Makefile

		docs/Makefile
		bench/Makefile
		bench/c/Makefile
		po/Makefile.in
		
		demo/Makefile
		demo/matrix/Makefile
		demo/triangles/Makefile
		
		crank-base-0.0.pc
		crank-shape-0.0.pc
		crank-core-0.0.pc
		crank-visual-0.0.pc
])
AC_OUTPUT
