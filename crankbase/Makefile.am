## Crank Base: Base support.

baseincludedir= $(includedir)/crank/base

lib_LTLIBRARIES = \
		libcrankbase.la

baseinclude_HEADERS = \
		crankbase.h \
		crankbasemacro.h \
		crankbasemisc.h \
		crankfunction.h \
		crankvalue.h \
		crankbits.h \
		crank128.h \
		crankstring.h \
		\
		crankrange.h \
		crankiter.h \
		crankpair.h \
		\
		crankcomplex.h \
		crankquaternion.h \
		crankpermutation.h \
		\
		crankveccommon.h \
		crankvecbool.h \
		crankvecuint.h \
		crankvecint.h \
		crankvecfloat.h \
		crankveccplxfloat.h \
		\
		crankmatcommon.h \
		crankmatfloat.h \
		crankmatcplxfloat.h \
		\
		crankcellspace2.h \
		crankcellspace3.h \
		\
		crankadvmat.h \
		\
		crankdigraph.h \
		crankadvgraph.h \
		\
		crankcomposite.h \
		crankcompositable.h \
		crankcompositable1n.h \
		\
		crankbasetest.h \
		crankbench.h \
		crankbenchrun.h \
		crankbenchresult.h


# crankbase.la
libcrankbase_la_CFLAGS = \
		$(CRANK_BASE_CFLAGS) \
		-DGETTEXT_PACKAGE=\"@GETTEXT_PACKAGE@\" \
		-DLOCALEDIR=\"$(localedir)\" \
		-lm

libcrankbase_la_LIBADD = \
		$(CRANK_BASE_LIBS)

libcrankbase_la_SOURCES= \
		crankbasemisc.c \
		crankfunction.c \
		crankvalue.c \
		crankstring.c \
		crankbits.c \
		crank128.c \
		\
		crankrange.c \
		crankiter.c \
		crankpair.c \
		\
		crankcomplex.c \
		crankquaternion.c \
		crankdigraph.c \
		crankpermutation.c \
		crankvecbool.c \
		crankvecuint.c \
		crankvecint.c \
		crankvecfloat.c \
		crankveccplxfloat.c \
		crankmatfloat.c \
		crankmatcplxfloat.c \
		\
		crankcellspace2.c \
		crankcellspace3.c \
		\
		crankadvgraph.c \
		crankadvmat.c \
		\
		crankcomposite.c \
		crankcompositable.c \
		crankcompositable1n.c \
		\
		crankbasetest.c \
		crankbench.c \
		crankbenchrun.c \
		crankbenchresult.c



# Introspection
-include $(INTROSPECTION_MAKEFILE)

if HAVE_INTROSPECTION

INTROSPECTION_GIRS=
INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir) --warn-all
INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir)

CrankBase-0.0.gir: libcrankbase.la

CrankBase_0_0_gir_SCANNERFLAGS= \
		--symbol-prefix="crank" \
		--identifier-prefix="Crank"
		
CrankBase_0_0_gir_INCLUDES= GObject-2.0
CrankBase_0_0_gir_CFLAGS= $(CRANK_BASE_CFLAGS) -lm
CrankBase_0_0_gir_LIBS= libcrankbase.la
CrankBase_0_0_gir_FILES= $(libcrankbase_la_SOURCES) $(baseinclude_HEADERS)

INTROSPECTION_GIRS+= CrankBase-0.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir= $(libdir)/girepository-1.0
typelib_DATA= $(INTROSPECTION_GIRS:.gir=.typelib)



# Vapigen
EXTRA_DIST=CrankBase-0.0.metadata crankbase-custom.vala

if ENABLE_VAPIGEN
-include $(VAPIGEN_MAKEFILE)

crank-base-0.0.vapi: CrankBase-0.0.gir CrankBase-0.0.metadata crankbase-custom.vala

VAPIGEN_VAPIS= crank-base-0.0.vapi

crank_base_0_0_vapi_METADATADIRS= $(srcdir)
crank_base_0_0_vapi_FILES= CrankBase-0.0.gir $(srcdir)/crankbase-custom.vala

vapidir= $(datadir)/vala/vapi
vapi_DATA= $(VAPIGEN_VAPIS)
endif

CLEANFILES = $(gir_DATA) $(typelib_DATA) $(vapi_DATA)

endif
