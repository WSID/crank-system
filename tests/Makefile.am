SUBDIRS=c

EXTRA_DIST= \
		glib-tap.mk \
		tap-driver.sh \
		tap-test \
		test-driver

if TEST_PYTHON
SUBDIRS+= python
endif

if ENABLE_VAPIGEN
SUBDIRS+= vala
endif
