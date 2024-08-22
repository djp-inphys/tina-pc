/**@(#)Functions to read/write AIFF (Aivru Image File Format) image files
*/

#include <stdlib.h>
#include <string.h>
#include <tina/file.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <time.h>

extern Bool fclose_2(FILE * stream, const char *pathname);
extern Bool fread_imrect_data(const Imrect * imrect, FILE * stream, const char *pathname);
extern Bool fread_padding(const unsigned size, FILE * stream, const char *pathname);
extern Bool fwrite_imrect_data(const Imrect * imrect, FILE * stream, const char *pathname);
extern Bool fwrite_padding(const unsigned size, FILE * stream, const char *pathname);
extern FILE *fopen_2(const char *pathname, const char *mode);
extern unsigned fread_fields(Field_info * field_info, const unsigned nfields, FILE * stream, const char *pathname);
extern unsigned fwrite_fields(Field_info * field_info, const unsigned nfields, FILE * stream, const char *pathname);

static Aiffhdr aiffhdr;
static Field_info field_info[] =
{
    {Field_info_id, &aiffhdr.magic, sizeof(aiffhdr.magic), 1},
    {Field_info_id, &aiffhdr.length, sizeof(aiffhdr.length), 1},
    {Field_info_id, &aiffhdr.type, sizeof(aiffhdr.type), 1},
    {Field_info_id, &aiffhdr.height, sizeof(aiffhdr.height), 1},
    {Field_info_id, &aiffhdr.width, sizeof(aiffhdr.width), 1},
    {Field_info_id, &aiffhdr.lx, sizeof(aiffhdr.lx), 4},
    {Field_info_id, &aiffhdr.source_id, sizeof(aiffhdr.source_id), 1},
    {Field_info_id, &aiffhdr.process_id, sizeof(aiffhdr.process_id), 1},
    {Field_info_id, &aiffhdr.date, sizeof(aiffhdr.date), 1},
    {Field_info_id, &aiffhdr.time, sizeof(aiffhdr.time), 1},
    {Field_info_id, &aiffhdr.title, sizeof(aiffhdr.title), 1},
};
static unsigned const nfields = sizeof field_info / sizeof(Field_info);

/* Read aiff header from stream into (static global) aiffhdr. Return
 * aiffhdrp (static global)(on error NULL). Handles byte reversal
 * problems. Leaves file descriptor at start of image data. NB DON'T
 * free aiffhdrp (it points to global static). */
Aiffhdr *aiff_read_head(FILE * stream, const char *pathname)
{
    Aiffhdr *aiffhdrp = NULL;

    unsigned nbytes = fread_fields(field_info, nfields, stream, pathname);

    if (nbytes)
    {
	int     padding = AIFF_HD_LEN - nbytes;

	aiffhdrp = &aiffhdr;
	/* Handle possible byte reversal */
	if (aiffhdr.magic == AIFF_AMIGC)
	{			/* Header (but not image) byte reversed */
	    /* swab should be defined in stdlib */
/*	    extern void swab(const char *from, char *to, int nbytes);
NAT 1/5/95 changed for compatability with PC compiler 1/5/95 */
	    extern void swab(char *from, char *to, int nbytes);

	    swab((char *) &aiffhdr.magic, (char *) &aiffhdr.magic, nbytes);
	}
	if (aiffhdr.magic != AIFF_MAGIC)
	{
	    aiffhdrp = NULL;
	}
	(void) fread_padding(padding, stream, pathname);
    }
    return aiffhdrp;
}

/* Create an imrect and read an image file called 'pathname' into it.
 * Open file, read header, padding and data, close file. On failure,
 * give error message and return NULL. */
Imrect *aiff_read_image_stream(FILE * stream, const char *pathname)
{
    Imrect *imrect = NULL;

    Aiffhdr *aiffhdr = aiff_read_head(stream, pathname);

    if (aiffhdr)
    {
	Imregion *imregion = roi_alloc(aiffhdr->lx, aiffhdr->ly,
				       aiffhdr->ux, aiffhdr->uy);

	imrect = im_alloc(aiffhdr->height, aiffhdr->width, imregion,
			  (Vartype) aiffhdr->type);
	rfree((void *) imregion);
	if (!fread_imrect_data(imrect, stream, pathname))
	{
	    im_free(imrect);
	    imrect = NULL;
	}
    }
    return imrect;
}

/* Create an imrect and read an image file called 'pathname' into it.
 * Open file, read header, padding and data, close file. On failure,
 * give error message and return NULL. */
Imrect *aiff_read_image(const char *pathname)
{
    FILE   *stream = fopen_2(pathname, "rb");
    Imrect *imrect = NULL;

    if (stream)
    {
	imrect = aiff_read_image_stream(stream, pathname);
	fclose_2(stream, pathname);
    }
    return imrect;
}

/* Write aiff header to file on stream from (static global) aiffhdr.
 * Return write_ok (true or false). Handles byte reversal problems.
 * Leaves file descriptor at start of image data. NB DON'T free
 * aiffhdrp (it points to global static). */
Bool    aiff_write_head(Imrect * imrect, FILE * stream, const char *pathname)
{
    Bool    write_ok = false;
    Imregion *imregion = imrect->region;
    char    times[10];
    char    dates[10];
    static const Aiffhdr aiffhdr_default =
    {
	aiffhdr_id,
	AIFF_MAGIC,		/* magic */
	AIFF_HD_LEN,		/* length: std header length */
	0,			/* type */
	0,			/* height */
	0,			/* width */
	0,			/* lx */
	0,			/* ux */
	0,			/* ly */
	0,			/* uy */
	AIFF_UNKNOWN,		/* source_id */
	AIFF_UNKNOWN,		/* process_id */
	"",			/* date */
	"",			/* time */
	"No title",		/* title */
    };
    unsigned nbytes = 0;

    time_t  tm;
    struct tm *tp;

    (void) time(&tm);
    tp = localtime(&tm);

    sprintf(times, "%02d:%02d:%02d", tp->tm_hour, tp->tm_min, tp->tm_sec);
    sprintf(dates, "%02d/%02d/%02d", tp->tm_mday, tp->tm_mon + 1, tp->tm_year);
    aiffhdr = aiffhdr_default;

    strncpy(aiffhdr.time, times, 8);
    strncpy(aiffhdr.date, dates, 8);

    aiffhdr.type = imrect->vtype;
    aiffhdr.height = imrect->height;
    aiffhdr.width = imrect->width;
    aiffhdr.lx = imregion->lx;
    aiffhdr.ly = imregion->ly;
    aiffhdr.ux = imregion->ux;
    aiffhdr.uy = imregion->uy;

    nbytes = fwrite_fields(field_info, nfields, stream, pathname);
    if (nbytes)
    {
	int     padding_size = aiffhdr.length - nbytes;

	if (fwrite_padding(padding_size, stream, pathname))
	{
	    write_ok = true;
	}
    }
    return write_ok;
}

/* Write an imrect to  an image file called 'pathname'. Open file,
 * write header, padding and data, close file. On failure, give error
 * message and return false. NB stream must be valid. */
Bool    aiff_write_image_stream(Imrect * imrect, FILE * stream, const char *pathname)
{
    Bool    write_ok = false;
    extern Bool fwrite_imrect_data(const Imrect * imrect, FILE * stream, const char *pathname);

    if (imrect)
    {
	if (aiff_write_head(imrect, stream, pathname))
	{
	    write_ok = fwrite_imrect_data(imrect, stream, pathname);
	}
    } else
    {
	errorf(non_fatal, "No image to write to: %s\n", pathname);
    }
    return write_ok;
}

/* Write an imrect to  an image file called 'pathname'. Open file,
 * write header, padding and data, close file. On failure, give error
 * message and return false. */
Bool    aiff_write_image(Imrect * imrect, const char *pathname)
{
    Bool    write_ok = false;
    FILE   *stream = fopen_2(pathname, "wb");

    if (stream)
    {
	write_ok = aiff_write_image_stream(imrect, stream, pathname);
	(void) fclose_2(stream, pathname);
    }
    return write_ok;
}
