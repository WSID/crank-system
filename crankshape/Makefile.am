## crank shape: Utilities for shape processing.

shapeincludedir=$(includedir)/crank/shape

lib_LTLIBRARIES = \
		libcrankshape.la

shapeinclude_HEADERS = \
		crankshape.h \
		crankshapemisc.h \
		crankplane.h \
		crankbox.h \
		crankeuler.h \
		crankrotation.h \
		cranktrans.h \
		crankoctreeset.h \
		crankpolystruct3.h \
		\
		crankshape2.h \
		crankshape2finite.h \
		crankshape2vertexed.h \
		crankshape2polygon.h \
		crankshape2iround.h \
		\
		crankshape2point.h \
		crankshape2segment.h \
		crankshape2triangle.h \
		crankshape2circle.h \
		crankshape2rect.h \
		crankshape2cpolygon.h \
		\
		crankshape3.h \
		crankshape3finite.h \
		crankshape3vertexed.h \
		crankshape3polygon.h \
		crankshape3polyhedron.h \
		crankshape3tpolyhedron.h \
		crankshape3iround.h \
		\
		crankshape3sphere.h \
		crankshape3point.h \
		crankshape3segment.h \
		crankshape3triangle.h \
		crankshape3tetrahedron.h \
		crankshape3cuboid.h \
		crankshape3cpolyhedron.h \
		\
		crankgjk.h



# crankbase.la
libcrankshape_la_CFLAGS = \
		$(CRANK_SHAPE_CFLAGS) \
		-I$(top_srcdir)/crankbase \
		-DGETTEXT_PACKAGE=\"@GETTEXT_PACKAGE@\" \
		-DLOCALEDIR=\"$(localedir)\" \
		-lm

libcrankshape_la_LIBADD = \
		$(CRANK_SHAPE_LIBS) \
		$(top_srcdir)/crankbase/libcrankbase.la

libcrankshape_la_SOURCES= \
		crankshapemisc.c \
		crankplane.c \
		crankbox.c \
		crankeuler.c \
		crankrotation.c \
		cranktrans.c \
		crankoctreeset.c \
		crankpolystruct3.c \
		crankshape2.c \
		crankshape2finite.c \
		crankshape2vertexed.c \
		crankshape2polygon.c \
		crankshape2iround.c \
		crankshape2point.c \
		crankshape2segment.c \
		crankshape2triangle.c \
		crankshape2circle.c \
		crankshape2rect.c \
		crankshape2cpolygon.c \
		crankshape3.c \
		crankshape3finite.c \
		crankshape3vertexed.c \
		crankshape3polygon.c \
		crankshape3polyhedron.c \
		crankshape3tpolyhedron.c \
		crankshape3iround.c \
		crankshape3sphere.c \
		crankshape3point.c \
		crankshape3segment.c \
		crankshape3triangle.c \
		crankshape3tetrahedron.c \
		crankshape3cuboid.c \
		crankshape3cpolyhedron.c \
		crankgjk.c



# Introspection 파일
-include $(INTROSPECTION_MAKEFILE)

if HAVE_INTROSPECTION

INTROSPECTION_GIRS=
INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir) --add-include-path=$(top_builddir)/crankbase --warn-all
INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir) --includedir=$(top_builddir)/crankbase

CrankShape-0.0.gir: libcrankshape.la

CrankShape_0_0_gir_SCANNERFLAGS= \
		--symbol-prefix="crank" \
		--identifier-prefix="Crank"

CrankShape_0_0_gir_INCLUDES= GObject-2.0 CrankBase-0.0
CrankShape_0_0_gir_CFLAGS= $(CRANK_SHAPE_CFLAGS) -lm -I$(top_srcdir)/crankbase
CrankShape_0_0_gir_LIBS= libcrankshape.la
CrankShape_0_0_gir_FILES= $(libcrankshape_la_SOURCES) $(shapeinclude_HEADERS)

INTROSPECTION_GIRS+= CrankShape-0.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir= $(libdir)/girepository-1.0
typelib_DATA= $(INTROSPECTION_GIRS:.gir=.typelib)



# Vapigen
EXTRA_DIST=CrankShape-0.0.metadata CrankShape-0.0-custom.vala

if ENABLE_VAPIGEN
-include $(VAPIGEN_MAKEFILE)

VAPIGEN_VAPIS= crank-shape-0.0.vapi

crank_shape_0_0_vapi_DEPS=crank-base-0.0
crank_shape_0_0_vapi_GIRDIRS= $(top_builddir)/crankbase
crank_shape_0_0_vapi_VAPIDIRS= $(top_builddir)/crankbase
crank_shape_0_0_vapi_METADATADIRS= $(srcdir)
crank_shape_0_0_vapi_FILES= CrankShape-0.0.gir CrankShape-0.0-custom.vala

vapidir= $(datadir)/vala/vapi
vapi_DATA= $(VAPIGEN_VAPIS)
endif

CLEANFILES = $(gir_DATA) $(typelib_DATA) $(vapi_DATA)

# Extra dependency to regenerate crank-shape-0.0.vapi
crank-shape-0.0.vapi: CrankShape-0.0.gir CrankShape-0.0-custom.vala

endif
