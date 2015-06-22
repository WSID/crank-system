ACLOCAL_AMFLAGS=-I m4

DISTCHECK_CONFIGURE_FLAGS= --enable-introspection --enable-gtk-doc

SUBDIRS= \
		crankbase \
		tests \
		docs \
		po

pkgconfigdir= $(libdir)/pkgconfig
pkgconfig_DATA= \
		crank-base-0.0.pc


EXTRA_DIST= \
		glib-tap.mk \
		tap-driver.sh \
		tap-test \
		test-driver \
		po
