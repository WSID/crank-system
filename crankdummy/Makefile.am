## crank dummy 모듈: 빌드 시스템을 세우는 동안 빌드 시스템을 돌려 볼 수 있는 더미


# 대상 목록
lib_LTLIBRARIES = \
		libcrankdummy.la

include_HEADERS = \
		crankdummy.h

# crankdummy.la
libcrankdummy_la_CFLAGS = \
		$(CRANK_DUMMY_CFLAGS)

libcrankdummy_la_LIBADD = \
		$(CRANK_DUMMY_LIBS)

libcrankdummy_la_SOURCES = \
		crankdummy.c


# Introspection 파일
-include $(INTROSPECTION_MAKEFILE)

if HAVE_INTROSPECTION

INTROSPECTION_GIRS=
INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir) --warn-all
INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir)

CrankDummy-0.0.gir: libcrankdummy.la

CrankDummy_0_0_gir_CFLAGS= $(CRANK_DUMMY_CFLAGS)
CrankDummy_0_0_gir_LIBS= libcrankdummy.la
CrankDummy_0_0_gir_FILES= $(libcrankdummy_la_SOURCES) crankdummy.h
INTROSPECTION_GIRS+= CrankDummy-0.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir= $(libdir)/girepository-1.0
typelib_DATA= $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES = $(gir_DATA) $(typelib_DATA)

endif
