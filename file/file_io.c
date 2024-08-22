/**@(#)Generic functions to handle files.
*/

#include <stdio.h>
#include <string.h>
#include <tina/file.h>
#include <tina/sys.h>
#include <tina/sys_types.h>
#include <tina/sysfuncs.h>

/* Close file. On failure, give error message and return false. */
Bool    fclose_2(FILE * stream, const char *pathname)
{
    Bool    closed_ok = true;

    if (fclose(stream) == EOF)
    {
	errorf(non_fatal, "Can't close file: %s\n", pathname);
	closed_ok = false;
    }
    return closed_ok;
}


/* Read 'count' items of size 'size' from stream into contiguous buffer
 * 'data' (alloc'd by this fn). Return buffer. On failure, give error
 * message and return NULL. */
void   *fread_2(const unsigned size, const unsigned count, FILE * stream,
		        const char *pathname)
{
    void   *data = ralloc(size * count);

    if (count != fread(data, size, count, stream))
    {
	errorf(non_fatal, "Can't read data: %s\n", pathname);
	rfree(data);
	data = NULL;
    }
    return data;
}

/* Read stream into 'nfields' fields whose sizes and addresses are
 * given in field_info. Returns number of bytes read. On failure, give
 * error message and return 0. */
unsigned fread_fields(Field_info * field_info, const unsigned nfields, FILE * stream, const char *pathname)
{
    unsigned nbytes = 0;
    unsigned i;

    for (i = 0; i < nfields; i++)
    {
	if (field_info[i].count !=
	    fread(field_info[i].address,
		  field_info[i].size,
		  field_info[i].count, stream))
	{
	    errorf(non_fatal, "Can't read fields: %s\n", pathname);
	    nbytes = 0;
	    break;
	} else
	{
	    nbytes += field_info[i].size * field_info[i].count;
	}
    }
    return nbytes;
}

/* Read image data by rows (possibly non-contiguous offset rows) from
 * stream. Imregion & vtype describe data 'data'. Returns true (read
 * ok)/false. On failure give error message.  NB Imrect data space must
 * have been alloc'd. */
Bool    fread_imrect_data(const Imrect * imrect, FILE * stream, const char *pathname)
{
    Bool    read_ok = true;

    if (imrect)
    {
	Imregion *imregion = imrect->region;
	int     lx = imregion->lx;
	int     ux = imregion->ux;
	int     ly = imregion->ly;
	int     uy = imregion->uy;
	int     y;
	unsigned ncols = ux - lx;
	unsigned size = var_size(imrect->vtype);

	for (y = ly; y < uy; ++y)
	{
	    void   *row = NULL;

	    IM_PIX_GETP(imrect, y, lx, row);
	    if (fread(row, size, ncols, stream) != ncols)
	    {
		errorf(non_fatal, "fwrite_imrect_data: Can't read data: %s\n",
		       pathname);
		read_ok = false;
		break;
	    }
	}
    } else
    {
	errorf(non_fatal, "No image to write to: %s\n", pathname);
	read_ok = false;
    }
    return read_ok;
}

/* Read padding (after data in header, to fill to standard size) and
 * discard. On failure, give error message and return false */
Bool    fread_padding(const unsigned size, FILE * stream, const char *pathname)
{
    Bool    read_ok = true;
    void   *data = ralloc(size);

    if (1 != fread(data, size, 1, stream))
    {
	errorf(non_fatal, "Can't read padding: %s\n", pathname);
	read_ok = false;
    }
    rfree(data);
    return read_ok;
}

/* Write 'count' items of 'size' from  contiguous buffer 'data' to
 * stream. On failure, give error message and return false. */
Bool    fwrite_2(const void *data, const unsigned size, const unsigned count,
		         FILE * stream, const char *pathname)
{
    Bool    write_ok = true;

    if (count != fwrite(data, size, count, stream))
    {
	errorf(non_fatal, "Can't write data: %s\n", pathname);
	write_ok = false;
    }
    return write_ok;
}

/* Write 'nfields' fields whose sizes and addresses are given in
 * field_info. Returns number of bytes read. On failure, give error
 * message and return 0. */
unsigned fwrite_fields(Field_info * field_info, const unsigned nfields, FILE * stream, const char *pathname)
{
    unsigned          i;
    unsigned nbytes = 0;

    for (i = 0; i < nfields; i++)
    {
	if (field_info[i].count !=
	    fwrite(field_info[i].address,
		   field_info[i].size,
		   field_info[i].count, stream))
	{
	    errorf(non_fatal, "Can't write fields: %s\n", pathname);
	    nbytes = 0;
	    break;
	} else
	{
	    nbytes += field_info[i].size * field_info[i].count;
	}
    }
    return nbytes;
}

/* Write image data by rows (possibly non-contiguous and offset) to
 * stream. Imregion & vtype describe data 'data'. On failure, give
 * error message and return false. */
Bool    fwrite_imrect_data(const Imrect * imrect, FILE * stream, const char *pathname)
{
    Bool    write_ok = true;

    if (imrect)
    {
	Imregion *imregion = imrect->region;
	int     lx = imregion->lx;
	int     ux = imregion->ux;
	int     ly = imregion->ly;
	int     uy = imregion->uy;
	int     y;
	unsigned size = var_size(imrect->vtype);
	unsigned ncols = ux - lx;

	for (y = ly; y < uy; y++)
	{
	    void   *row = NULL;

	    IM_PIX_GETP(imrect, y, lx, row);
	    if (fwrite((char *) row, size, ncols, stream) != ncols)
	    {
		errorf(non_fatal, "fwrite_imrect_data: Can't write data: %s\n",
		       pathname);
		write_ok = false;
		break;
	    }
	}
    } else
    {
	errorf(non_fatal, "No image to write to: %s\n", pathname);
	write_ok = false;
    }
    return write_ok;
}

/* Write padding (after data in header, to fill to standard size) On
 * failure, give error message and return false */
Bool    fwrite_padding(const unsigned size, FILE * stream, const char
		              *pathname)
{
    Bool    write_ok = true;
    void   *data = ralloc(size);

    if (1 != fwrite(data, size, 1, stream))
    {
	errorf(non_fatal, "Can't write padding: %s\n", pathname);
	write_ok = false;
    }
    rfree(data);
    return write_ok;
}

/* Open file (with error message on failure). Returns stream (NULL on
 * failure) */
FILE   *fopen_2(const char *pathname, const char *mode)
{
    FILE   *stream = fopen(pathname, mode);

    if (!stream)
    {
	errorf(non_fatal, "Can't open file: %s\n", pathname);
    }
    return stream;
}
