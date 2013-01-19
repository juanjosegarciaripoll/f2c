#include <config.h>
#include "f2c.h"
#include "fio.h"

#ifdef HAVE_FTRUNCATE
#include <unistd.h>
#endif

#undef abs
#undef min
#undef max
#include "stdlib.h"
#include "string.h"

integer f_end(alist *a)
{
	unit *b;
	FILE *tf;

	if(a->aunit>=MXUNIT || a->aunit<0) err(a->aerr,101,"endfile");
	b = &f__units[a->aunit];
	if(b->ufd==NULL) {
		char nbuf[10];
		sprintf(nbuf,"fort.%ld",(long)a->aunit);
		if (tf = fopen(nbuf, f__w_mode[0]))
			fclose(tf);
		return(0);
		}
	b->uend=1;
	return(b->useek ? t_runc(a) : 0);
}

#if !defined(HAVE_FTRUNCATE)
static int
copy(FILE *from, register long len, FILE *to)
{
	int len1;
	char buf[BUFSIZ];

	while(fread(buf, len1 = len > BUFSIZ ? BUFSIZ : (int)len, 1, from)) {
		if (!fwrite(buf, len1, 1, to))
			return 1;
		if ((len -= len1) <= 0)
			break;
		}
	return 0;
}
#endif /* !HAVE_FTRUNCATE */

int
t_runc(alist *a)
{
	OFF_T loc, len;
	unit *b;
	int rc;
	FILE *bf;
#if !defined(HAVE_FTRUNCATE)
	FILE *tf;
#endif

	b = &f__units[a->aunit];
	if(b->url)
		return(0);	/*don't truncate direct files*/
	loc=FTELL(bf = b->ufd);
	FSEEK(bf,(OFF_T)0,SEEK_END);
	len=FTELL(bf);
	if (loc >= len || b->useek == 0)
		return(0);
#ifndef HAVE_FTRUNCATE
	if (b->ufnm == NULL)
		return 0;
	rc = 0;
	fclose(b->ufd);
	if (!loc) {
		if (!(bf = fopen(b->ufnm, f__w_mode[b->ufmt])))
			rc = 1;
		if (b->uwrt)
			b->uwrt = 1;
		goto done;
		}
	if (!(bf = fopen(b->ufnm, f__r_mode[0]))
	 || !(tf = tmpfile())) {
#ifdef NON_UNIX_STDIO
 bad:
#endif
		rc = 1;
		goto done;
		}
	if (copy(bf, (long)loc, tf)) {
 bad1:
		rc = 1;
		goto done1;
		}
	if (!(bf = freopen(b->ufnm, f__w_mode[0], bf)))
		goto bad1;
	rewind(tf);
	if (copy(tf, (long)loc, bf))
		goto bad1;
	b->uwrt = 1;
	b->urw = 2;
#ifdef NON_UNIX_STDIO
	if (b->ufmt) {
		fclose(bf);
		if (!(bf = fopen(b->ufnm, f__w_mode[3])))
			goto bad;
		FSEEK(bf,(OFF_T)0,SEEK_END);
		b->urw = 3;
		}
#endif
done1:
	fclose(tf);
done:
	f__cf = b->ufd = bf;
#else /* !HAVE_TRUNCATE */
	if (b->urw & 2)
		fflush(b->ufd); /* necessary on some Linux systems */
	rc = ftruncate(fileno(b->ufd), loc);
	/* The following FSEEK is unnecessary on some systems, */
	/* but should be harmless. */
	FSEEK(b->ufd, (OFF_T)0, SEEK_END);
#endif /* HAVE_TRUNCATE */
	if (rc)
		err(a->aerr,111,"endfile");
	return 0;
}
