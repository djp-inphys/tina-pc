/**@(#)
Input function for image file with no header
reading from file descriptor (yeuk!)
*/
#include <tina/sys.h>
#include <tina/sysfuncs.h>

Imrect *raw_fd_read_image(int fd, int width, int height, Vartype vtype)
{
    Imregion *roi_alloc(int, int, int, int);
    Imrect *image, *im_alloc(int, int, Imregion *, Vartype);
    int row_length;
    int ly, uy;
    int i;
    int read();

    image = im_alloc(height, width, (Imregion *) NULL, vtype);

    row_length = (image->region->ux - image->region->lx) * var_size(image->vtype);
    ly = image->region->ly;
    uy = image->region->uy;
    for (i = ly; i < uy; ++i)
    {
	void *row;

	IM_ROW_GET(image, i, row)
	    if (read(fd, (char *) row, row_length) != row_length)
	{
	    im_free(image);
	    error("unexpected end of file", non_fatal);
	    return (NULL);
	}
    }
    return (image);
}
