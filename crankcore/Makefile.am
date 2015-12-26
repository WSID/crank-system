## Crank Core: Core classes foundation.

coreincludedir= $(includedir)/crank/core

lib_LTLIBRARIES = \
		libcrankcore.la

coreinclude_HEADERS = \
		crankcore.h \
		cranksession.h


# crankcore.la
libcrankcore_la_CFLAGS = \
		$(CRANK_BASE_CFLAGS) \
		$(CRANK_SHAPE_CFLAGS) \
		-I$(top_srcdir)/crankbase \
		-I$(top_srcdir)/crankshape \
		-DGETTEXT_PACKAGE=\"@GETTEXT_PACKAGE@\" \
		-DLOCALEDIR=\"$(localedir)\" \
		-lm

libcrankcore_la_LIBADD = \
		$(CRANK_BASE_LIBS) \
		$(CRANK_SHAPE_LIBS) \
		$(top_srcdir)/crankbase/libcrankbase.la \
		$(top_srcdir)/crankshape/libcrankshape.la

libcrankcore_la_SOURCES= \
		cranksession.c



# Introspection
-include $(INTROSPECTION_MAKEFILE)

if HAVE_INTROSPECTION

INTROSPECTION_GIRS=
INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir) --add-include-path=$(top_builddir)/crankbase --add-include-path=$(top_builddir)/crankshape --warn-all
INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir) --includedir=$(top_builddir)/crankbase --includedir=$(top_builddir)/crankshape

CrankCore-0.0.gir: libcrankcore.la

CrankCore_0_0_gir_SCANNERFLAGS= \
		--symbol-prefix="crank" \
		--identifier-prefix="Crank"

CrankCore_0_0_gir_INCLUDES= GObject-2.0
CrankCore_0_0_gir_CFLAGS= $(CRANK_BASE_CFLAGS) -lm -I$(top_srcdir)/crankbase -I$(top_srcdir)/crankshape
CrankCore_0_0_gir_LIBS= libcrankcore.la
CrankCore_0_0_gir_FILES= $(libcrankcore_la_SOURCES) $(coreinclude_HEADERS)

INTROSPECTION_GIRS+= CrankCore-0.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir= $(libdir)/girepository-1.0
typelib_DATA= $(INTROSPECTION_GIRS:.gir=.typelib)



# Vapigen
EXTRA_DIST=CrankCore-0.0.metadata CrankCore-0.0-custom.vala

if ENABLE_VAPIGEN
-include $(VAPIGEN_MAKEFILE)

crank-core-0.0.vapi: CrankCore-0.0.gir

VAPIGEN_VAPIS= crank-core-0.0.vapi

crank_core_0_0_vapi_DEPS=crank-base-0.0
crank_core_0_0_vapi_GIRDIRS= $(top_builddir)/crankbase
crank_core_0_0_vapi_VAPIDIRS= $(top_builddir)/crankbase
crank_core_0_0_vapi_METADATADIRS= $(srcdir)
crank_core_0_0_vapi_FILES= CrankCore-0.0.gir

vapidir= $(datadir)/vala/vapi
vapi_DATA= $(VAPIGEN_VAPIS)
endif

CLEANFILES = $(gir_DATA) $(typelib_DATA) $(vapi_DATA)

endif
