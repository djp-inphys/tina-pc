/**@(#)Functions to read/write IFF (Image File Format) image files
*/

#include <stdio.h>
#include <string.h>
#include <tina/file.h>
#include <tina/sys.h>
#include <tina/sys_types.h>
#include <tina/sysfuncs.h>

extern Bool fclose_2(FILE * stream, const char *pathname);
extern Bool fread_imrect_data(const Imrect * imrect, FILE * stream, const char *pathname);
extern Bool fread_padding(const unsigned size, FILE * stream, const char *pathname);
extern Bool fwrite_imrect_data(const Imrect * imrect, FILE * stream, const char *pathname);
extern Bool fwrite_padding(const unsigned size, FILE * stream, const char *pathname);
extern FILE *fopen_2(const char *pathname, const char *mode);
extern unsigned fread_fields(Field_info * field_info, const unsigned nfields, FILE * stream, const char *pathname);
extern unsigned fwrite_fields(Field_info * field_info, const unsigned nfields, FILE * stream, const char *pathname);

static Iffhdr iffhdr;
static Field_info field_info[] =
{
    {Field_info_id, &iffhdr.length, sizeof(iffhdr.length), 1},
    {Field_info_id, &iffhdr.type, sizeof(iffhdr.type), 1},
    {Field_info_id, &iffhdr.height, sizeof(iffhdr.height), 1},
    {Field_info_id, &iffhdr.width, sizeof(iffhdr.width), 1},
};
static unsigned const nfields = sizeof field_info / sizeof(Field_info);

/* Read iff header from stream into (static global) iffhdr. Return
 * iffhdrp (static global)(on error NULL) . Leaves file descriptor at
 * start of image data. NB DON'T free iffhdrp (it points to global
 * static). */
Iffhdr *iff_read_head(FILE * stream, const char *pathname)
{
    unsigned nbytes = fread_fields(field_info, nfields, stream, pathname);

    if (nbytes)
    {
	int     padding = IFF_HD_LEN - nbytes;

	(void) fread_padding(padding, stream, pathname);
    }
    return &iffhdr;
}

/* Create an imrect and read an image file called 'pathname' into it.
 * Open file, read header, padding and data, close file. On failure,
 * give error message and return NULL. */
Imrect *iff_read_image(const char *pathname)
{
    FILE   *stream = fopen_2(pathname, "rb");
    Imrect *imrect = NULL;

    if (stream)
    {
	Iffhdr *iffhdr = iff_read_head(stream, pathname);

	if (iffhdr)
	{
	    Imregion *imregion = NULL;

	    imrect = im_alloc(iffhdr->height, iffhdr->width, imregion,
			      (Vartype) iffhdr->type);
	    if (!fread_imrect_data(imrect, stream, pathname))
	    {
		im_free(imrect);
		imrect = NULL;
	    }
	}
	fclose_2(stream, pathname);
    }
    return imrect;
}

/* Write iff header to file on stream from (static global) iffhdr.
 * Return write_ok (true or false). Handles byte reversal problems.
 * Leaves file descriptor at start of image data. NB DON'T free iffhdrp
 * (it points to global static). */
Bool    iff_write_head(Imrect * imrect, FILE * stream, const char *pathname)
{
    Bool    write_ok = false;
    static const Iffhdr iffhdr_default =
    {
	iffhdr_id,
	IFF_HD_LEN,		/* length: std header length */
	0,			/* type */
	0,			/* height */
	0,			/* width */
    };
    unsigned nbytes = 0;

    iffhdr = iffhdr_default;
    iffhdr.type = imrect->vtype;
    iffhdr.height = imrect->height;
    iffhdr.width = imrect->width;

    nbytes = fwrite_fields(field_info, nfields, stream, pathname);
    if (nbytes)
    {
	int     padding_size = iffhdr.length - nbytes;

	if (fwrite_padding(padding_size, stream, pathname))
	{
	    write_ok = true;
	}
    }
    return write_ok;
}

/* Write an imrect to  an image file called 'pathname'. Open file,
 * write header, padding and data, close file. On failure, give error
 * message and return false. */
Bool    iff_write_image(Imrect * imrect, const char *pathname)
{
    Bool    write_ok = false;

    if (imrect)
    {
	FILE   *stream = fopen_2(pathname, "wb");

	if (stream)
	{
	    if (iff_write_head(imrect, stream, pathname))
	    {
		write_ok = fwrite_imrect_data(imrect, stream, pathname);
	    }
	    (void) fclose_2(stream, pathname);
	}
    } else
    {
	errorf(non_fatal, "No image to write to: %s\n", pathname);
    }
    return write_ok;
}
