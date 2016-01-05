## Crank Core: Core classes foundation.

visualincludedir= $(includedir)/crank/visual

lib_LTLIBRARIES = \
		libcrankvisual.la

visualinclude_HEADERS = \
		crankvisual.h \
		crankfilm.h \
		crankrenderable.h \
		crankrendermodule.h

# crankvisual.la
libcrankvisual_la_CFLAGS = \
		$(CRANK_BASE_CFLAGS) \
		$(CRANK_SHAPE_CFLAGS) \
		$(CRANK_VISUAL_CFLAGS) \
		-I$(top_srcdir)/crankbase \
		-I$(top_srcdir)/crankshape \
		-I$(top_srcdir)/crankcore \
		-DGETTEXT_PACKAGE=\"@GETTEXT_PACKAGE@\" \
		-DLOCALEDIR=\"$(localedir)\" \
		-lm

libcrankvisual_la_LIBADD = \
		$(CRANK_BASE_LIBS) \
		$(CRANK_SHAPE_LIBS) \
		$(CRANK_VISUAL_LIBS) \
		$(top_srcdir)/crankbase/libcrankbase.la \
		$(top_srcdir)/crankshape/libcrankshape.la \
		$(top_srcdir)/crankcore/libcrankcore.la

libcrankvisual_la_SOURCES= \
		crankfilm.c \
		crankrenderable.c \
		crankrendermodule.c



# Introspection
-include $(INTROSPECTION_MAKEFILE)

if HAVE_INTROSPECTION

INTROSPECTION_GIRS=
INTROSPECTION_SCANNER_ARGS= \
		--add-include-path=$(srcdir) \
		--add-include-path=$(top_builddir)/crankbase \
		--add-include-path=$(top_builddir)/crankshape \
		--add-include-path=$(top_builddir)/crankcore \
		--warn-all

INTROSPECTION_COMPILER_ARGS= \
		--includedir=$(srcdir) \
		--includedir=$(top_builddir)/crankbase \
		--includedir=$(top_builddir)/crankshape \
		--includedir=$(top_builddir)/crankcore

CrankVisual-0.0.gir: libcrankvisual.la

CrankVisual_0_0_gir_SCANNERFLAGS= \
		--symbol-prefix="crank" \
		--identifier-prefix="Crank"

CrankVisual_0_0_gir_INCLUDES= GObject-2.0 Cogl-2.0 CrankBase-0.0 CrankShape-0.0 CrankCore-0.0
CrankVisual_0_0_gir_CFLAGS= $(CRANK_BASE_CFLAGS) $(CRANK_VISUAL_CFLAGS) -lm -I$(top_srcdir)/crankbase -I$(top_srcdir)/crankshape -I$(top_srcdir)/crankcore
CrankVisual_0_0_gir_LIBS= libcrankvisual.la
CrankVisual_0_0_gir_FILES= $(libcrankvisual_la_SOURCES) $(visualinclude_HEADERS)

INTROSPECTION_GIRS+= CrankVisual-0.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir= $(libdir)/girepository-1.0
typelib_DATA= $(INTROSPECTION_GIRS:.gir=.typelib)



# Vapigen
EXTRA_DIST=CrankVisual-0.0.metadata CrankVisual-0.0-custom.vala

if ENABLE_VAPIGEN
-include $(VAPIGEN_MAKEFILE)

crank-visual-0.0.vapi: CrankVisual-0.0.gir

# VAPIGEN_VAPIS= crank-visual-0.0.vapi

crank_visual_0_0_vapi_DEPS=crank-base-0.0 crank-shape-0.0 crank-core-0.0
crank_visual_0_0_vapi_GIRDIRS= $(top_builddir)/crankbase $(top_builddir)/crankshape $(top_builddir)/crankcore
crank_visual_0_0_vapi_VAPIDIRS= $(top_builddir)/crankbase $(top_builddir)/crankshape $(top_builddir)/crankcore
crank_visual_0_0_vapi_METADATADIRS= $(srcdir)
crank_visual_0_0_vapi_FILES= CrankVisual-0.0.gir

vapidir= $(datadir)/vala/vapi
vapi_DATA= $(VAPIGEN_VAPIS)
endif

CLEANFILES = $(gir_DATA) $(typelib_DATA) $(vapi_DATA)

endif
