## crank base: Crank System의 기저면 지원을 당담합니다.

# 대상 목록
lib_LTLIBRARIES = \
		libcrankbase.la

include_HEADERS = \
		crankbase.h \
		crankbasemacro.h \
		crankfunction.h \
		crankvala.h \
		crankvalue.h \
		crank128.h \
		crankstring.h \
		\
		crankrange.h \
		crankiter.h \
		\
		crankcomplex.h \
		crankquaternion.h \
		crankpermutation.h \
		\
		crankveccommon.h \
		crankvecbool.h \
		crankvecint.h \
		crankvecfloat.h \
		crankveccplxfloat.h \
		\
		crankmatcommon.h \
		crankmatfloat.h \
		crankmatcplxfloat.h \
		\
		crankadvmat.h \
		\
		crankdigraph.h \
		crankadvgraph.h \
		\
		crankbasetest.h



# crankbase.la
libcrankbase_la_CFLAGS = \
		$(CRANK_BASE_CFLAGS) \
		-DGETTEXT_PACKAGE=\"@GETTEXT_PACKAGE@\" \
		-DLOCALEDIR=\"$(localedir)\" \
		-lm

libcrankbase_la_LIBADD = \
		$(CRANK_BASE_LIBS)

libcrankbase_la_SOURCES= \
		crankfunction.c \
		crankvala.c \
		crankvalue.c \
		crankstring.c \
		crank128.c \
		\
		crankrange.c \
		crankiter.c \
		\
		crankcomplex.c \
		crankquaternion.c \
		crankdigraph.c \
		crankpermutation.c \
		crankvecbool.c \
		crankvecint.c \
		crankvecfloat.c \
		crankveccplxfloat.c \
		crankmatfloat.c \
		crankmatcplxfloat.c \
		\
		crankadvgraph.c \
		crankadvmat.c\
		\
		crankbasetest.c



# Introspection 파일
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
CrankBase_0_0_gir_FILES= $(libcrankbase_la_SOURCES) $(include_HEADERS)

INTROSPECTION_GIRS+= CrankBase-0.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir= $(libdir)/girepository-1.0
typelib_DATA= $(INTROSPECTION_GIRS:.gir=.typelib)



# Vapigen 파일
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

CLEANFILES = $(gir_DATA) $(typelib_DATA)

endif
