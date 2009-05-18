## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(SPRY_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = spry

spry_SOURCES = \
	callbacks.c \
	callbacks.h \
	main.c \
	cliopts.c \
	cliopts.h \
	spry.h \
	generators.c \
	generators.h \
	browser.c \
	browser.h \
	gui_funcs.c \
	gui_funcs.h

spry_LDFLAGS = \
	-Wl,--export-dynamic

spry_LDADD = $(SPRY_LIBS)

EXTRA_DIST = $(glade_DATA) \
	$(images_DATA)

images_DATA = \
	images/toolbar.svg\
	images/app.svg \
	images/back.svg \
	images/back_disable.svg \
	images/close.svg \
	images/context.svg \
	images/forward.svg \
	images/forward_disable.svg \
	images/fullscreen.svg \
	images/home.svg \
	images/minimize.svg

imagesdir = \
	$(pkgdatadir)

# Remove glade directory on uninstall
uninstall-local:
	-rm -r $(datadir)/spry
