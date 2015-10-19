## crank shape: Utilities for shape processing.

shapeincludedir=$(includedir)/crank/shape

lib_LTLIBRARIES = \
		libcrankshape.la

shapeinclude_HEADERS = \
		crankshape.h \
		crankshape2.h \
		crankcpolygon.h



# crankbase.la
libcrankshape_la_CFLAGS = \
		$(CRANK_SHAPE_CFLAGS) \
		-DGETTEXT_PACKAGE=\"@GETTEXT_PACKAGE@\" \
		-DLOCALEDIR=\"$(localedir)\" \
		-lm

libcrankshape_la_LIBADD = \
		$(CRANK_SHAPE_LIBS)

libcrankshape_la_SOURCES= \
		crankshape2.c \
		crankcpolygon.c



# Introspection 파일
-include $(INTROSPECTION_MAKEFILE)

if HAVE_INTROSPECTION

INTROSPECTION_GIRS=
INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir) --warn-all
INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir)

CrankShape-0.0.gir: libcrankshape.la

CrankShape_0_0_gir_SCANNERFLAGS= \
		--symbol-prefix="crank" \
		--identifier-prefix="Crank"

CrankShape_0_0_gir_INCLUDES= GObject-2.0
CrankShape_0_0_gir_CFLAGS= $(CRANK_SHAPE_CFLAGS) -lm
CrankShape_0_0_gir_LIBS= libcrankshape.la
CrankShape_0_0_gir_FILES= $(libcrankshape_la_SOURCES) $(shapeinclude_HEADERS)

INTROSPECTION_GIRS+= CrankShape-0.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir= $(libdir)/girepository-1.0
typelib_DATA= $(INTROSPECTION_GIRS:.gir=.typelib)



# Vapigen
#EXTRA_DIST=CrankShape-0.0.metadata crankshape-custom.vala

if ENABLE_VAPIGEN
-include $(VAPIGEN_MAKEFILE)

VAPIGEN_VAPIS= crank-shape-0.0.vapi

crank_shape_0_0_vapi_METADATADIRS= $(srcdir)
crank_shape_0_0_vapi_FILES= CrankShape-0.0.gir

vapidir= $(datadir)/vala/vapi
vapi_DATA= $(VAPIGEN_VAPIS)
endif

CLEANFILES = $(gir_DATA) $(typelib_DATA) $(vapi_DATA)

endif
