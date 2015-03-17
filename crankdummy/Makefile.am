## crank dummy 모듈: 빌드 시스템을 세우는 동안 빌드 시스템을 돌려 볼 수 있는 더미


# 대상 목록
lib_LTLIBRARIES = \
		libcrankdummy.la

include_HEADERS = \
		crankdummy.h

# crankdummy.la
libcrankdummy_la_LDFLAGS = \
		-static

libcrankdummy_la_CFLAGS = \
		$(CRANK_DUMMY_CFLAGS)

libcrankdummy_la_LIBADD = \
		$(CRANK_DUMMY_LIBS)

libcrankdummy_la_SOURCES = \
		crankdummy.c
