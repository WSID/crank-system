## crank base: Crank System의 기저면 지원을 당담합니다.

# 대상 목록
lib_LTLIBRARIES = \
		libcrankbase.la

include_HEADERS = \
		crankbase.h \
		crankbasemacro.h \
		crankfuncholder.h



# crankbase.la
libcrankbase_la_CFLAGS = \
		$(CRANK_BASE_CFLAGS) \
		-DGETTEXT_PACKAGE=\"@GETTEXT_PACKAGE@\" \
		-DLOCALEDIR=\"$(localedir)\"

libcrankbase_la_LIBADD = \
		$(CRANK_BASE_LIBS)

libcrankbase_la_SOURCES= \
		crankfuncholder.c



# Introspection 파일
-include $(INTROSPECTION_MAKEFILE)

if HAVE_INTROSPECTION

INTROSPECTION_GIRS=
INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir) --warn-all
INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir)

CrankBase-0.0.gir: libcrankbase.la

CrankBase_0_0_gir_PACKAGES= glib-2.0 gobject-2.0
CrankBase_0_0_gir_SCANNERFLAGS= --symbol-prefix="crank"
CrankBase_0_0_gir_CFLAGS= $(CRANK_BASE_CFLAGS)
CrankBase_0_0_gir_LIBS= libcrankbase.la
CrankBase_0_0_gir_FILES= $(libcrankbase_la_SOURCES) $(include_HEADERS)

INTROSPECTION_GIRS+= CrankBase-0.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir= $(libdir)/girepository-1.0
typelib_DATA= $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES = $(gir_DATA) $(typelib_DATA)

endif
