## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src 

sprydocdir = ${prefix}/doc/spry
sprydoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


EXTRA_DIST = $(sprydoc_DATA)


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(sprydocdir)
