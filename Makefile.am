ACLOCAL_AMFLAGS=-I m4

DISTCHECK_CONFIGURE_FLAGS= --enable-introspection --enable-gtk-doc

SUBDIRS= \
		crankbase \
		crankshape \
		crankcore \
		docs \
		tests \
		bench \
		po
if CRANK_DEMO
  SUBDIRS+= demo
endif


pkgconfigdir= $(libdir)/pkgconfig
pkgconfig_DATA= \
		crank-base-0.0.pc \
		crank-shape-0.0.pc


EXTRA_DIST= \
		po


# Benchmark
.PHONY: bench

bench: all
	$(MAKE) -C bench/ bench
