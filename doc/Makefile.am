dist_man_MANS = f2c.1

.tex.pdf:
	$(LATEX) --pdf $<

EXTRA_DIST = f2c.tex
doc_DATA = f2c.pdf
CLEANFILES = f2c.pdf f2c-man.pdf

f2c.pdf: f2c-man.pdf

# The -n25 has the man page (Appendix B) numbers start on page 25.

f2c-man.pdf: f2c.1
	env MANROFFOPT='-n25 -P-pa4' $(MAN) -Tpdf ./$< > $@

f2c-orig.pdf:
	curl --output $@ http://www.netlib.org/f2c/f2c.pdf
