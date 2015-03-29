ACLOCAL_AMFLAGS=-I m4

DISTCHECK_CONFIGURE_FLAGS= --enable-introspection --enable-gtk-doc

SUBDIRS= \
		crankbase \
		tests \
		docs \
		po

if TEST_PYTHON
SUBDIRS+= tests_python
endif



EXTRA_DIST= \
		glib-tap.mk \
		tap-driver.sh \
		tap-test \
		test-driver \
		po
