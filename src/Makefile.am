
vmoddir = $(VMOD_DIR)
vmod_LTLIBRARIES = libvmod_utf8.la

libvmod_utf8_la_CFLAGS = $(VMOD_INCLUDES)
libvmod_utf8_la_LDFLAGS = -module -export-dynamic -avoid-version -shared \
	$(LIBS)

libvmod_utf8_la_SOURCES = \
	vmod_utf8.c
nodist_libvmod_utf8_la_SOURCES = \
	vcc_if.c \
	vcc_if.h

dist_man_MANS = vmod_utf8.3

VMOD_utf8S = tests/*.vtc

$(libvmod_utf8_la_OBJECTS): vcc_if.h

vcc_if.c vcc_if.h vmod_utf8.man.rst: $(VMODTOOL) $(top_srcdir)/src/vmod.vcc
	$(PYTHON) $(VMODTOOL) $(top_srcdir)/src/vmod.vcc

vmod_utf8.3: vmod_utf8.man.rst
	${RST2MAN} $? $@

check:
	$(VARNISHTEST) -Dvarnishd=$(VARNISHD) \
	    -Dvmod_topbuild=$(abs_top_builddir) $(VMOD_utf8S)

EXTRA_DIST = vmod.vcc \
	$(VMOD_utf8S)

CLEANFILES = $(builddir)/vcc_if.c \
	$(builddir)/vcc_if.h \
	$(builddir)/vmod_utf8.man.rst \
	$(builddir)/vmod_utf8.rst \
	$(builddir)/$(dist_man_MANS)
