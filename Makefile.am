## Makefile.am

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = scripts src lib include doc

dist_doc_DATA = README.md COPYRIGHT ChangeLog

ChangeLog:
	wget --output-document=$@ http://www.netlib.org/f2c/changes
