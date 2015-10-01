ACLOCAL_AMFLAGS=-I m4

DISTCHECK_CONFIGURE_FLAGS= --enable-introspection --enable-gtk-doc

SUBDIRS= \
		crankbase \
		docs \
		tests \
		bench \
		po \
		demo

pkgconfigdir= $(libdir)/pkgconfig
pkgconfig_DATA= \
		crank-base-0.0.pc


EXTRA_DIST= \
		po


# Benchmark
.PHONY: bench

bench: all
	$(MAKE) -C bench/ bench
