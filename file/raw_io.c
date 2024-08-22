/**@(#)Functions to read/write RAW image files
*/

#include <stdio.h>
#include <string.h>
#include <tina/file.h>
#include <tina/sys.h>
#include <tina/sys_types.h>
#include <tina/sysfuncs.h>

extern Bool fclose_2(FILE * stream, const char *pathname);
extern FILE *fopen_2(const char *pathname, const char *mode);
extern Bool fread_imrect_data(const Imrect * imrect, FILE * stream, const char *pathname);
extern Bool fwrite_imrect_data(const Imrect * imrect, FILE * stream, const char *pathname);

/* Create an imrect and read an image file called 'pathname' into it.
 * Open file, read data and close file. On failure, give error message
 * and return NULL. */
Imrect *raw_read_image(const char *pathname, const int width, const int height,
		               const Vartype vtype)
{
    FILE   *stream = fopen_2(pathname, "rb");
    Imrect *imrect = NULL;

    if (stream)
    {
	Imregion *imregion = NULL;

	imrect = im_alloc(height, width, imregion, (Vartype) vtype);
	if (!fread_imrect_data(imrect, stream, pathname))
	{
	    im_free(imrect);
	    imrect = NULL;
	}
	fclose_2(stream, pathname);
    }
    return imrect;
}

/* Write an imrect to  an image file called 'pathname'. Open file, read
 * data and close file. On failure, give error message and return
 * false. */
Bool    raw_write_image(const Imrect * imrect, const char *pathname)
{
    Bool    write_ok = false;

    if (imrect)
    {
	FILE   *stream = fopen_2(pathname, "wb");

	if (stream)
	{
	    write_ok = fwrite_imrect_data(imrect, stream, pathname);
	    (void) fclose_2(stream, pathname);
	}
    } else
    {
	errorf(non_fatal, "No image to write to: %s\n", pathname);
    }
    return write_ok;
}
