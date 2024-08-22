/**@(#)Imrect handling. (Imrect is Tina's generic image structure)
 * @(#)Imrect is:
 * @(#){ Vartype vtype; int imtype; int width, height; Imregion *region; List *props; }
 */

#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/image.h>

/* Image allocation.  Allocate memory for Imrect data structure and for
 * region of interest (roi).  Ie Imrect (image rectangle) and imregion.
 * Set roi co-ordinates (top-left bottom-right). Allocate memory for
 * image data. */
Imrect *im_alloc(int height, int width, Imregion * region, Vartype vtype)
{
    Imrect *image;
    Imregion *roi_alloc();
    Imregion *roi_copy();
    void  **narray_alloc();

    int     lx, ly, ux, uy;

    if (region == NULL)		/* alloc whole image */
	region = roi_alloc(0, 0, width, height);
    else			/* use copy of given region */
	region = roi_copy(region);

    if (region == NULL)
	return (NULL);

    lx = region->lx;
    ly = region->ly;
    ux = region->ux;
    uy = region->uy;

    image = ts_ralloc(Imrect);

    image->height = height;
    image->width = width;
    image->vtype = vtype;
    image->region = region;
    image->props = NULL;
    if (vtype == complex_v)
    {
	image->data = (void *) ts_narray_alloc(ly, lx, uy, ux, Complex);
    } else
    {
	image->data = (void *) narray_alloc(ly, lx, uy, ux, var_size(vtype));
    }

    return image;
}

/* Wrap an imrect data structure around the contiguous block of memory
 * specified by the region and vtype arguments. */
Imrect *im_wrap_contig(void *mem_ptr, int height, int width, Imregion * region, Vartype vtype)
{
    Imrect *image;
    Imregion *roi_alloc();
    Imregion *roi_copy();
    int     i;
    int     lx, ly, ux, uy;
    int     roi_width;
    unsigned int vsize;
    void   *nvector_alloc();
    void  **data;

    if (region == NULL)		/* alloc whole image */
	region = roi_alloc(0, 0, width, height);
    else			/* use copy of given region */
	region = roi_copy(region);

    if (region == NULL)
	return (NULL);

    lx = region->lx;
    ly = region->ly;
    ux = region->ux;
    uy = region->uy;
    roi_width = ux - lx;

    image = ts_ralloc(Imrect);

    image->height = height;
    image->width = width;
    image->vtype = vtype;
    image->region = region;
    image->props = NULL;

    data = (void **) nvector_alloc(ly, uy, sizeof(void *));
    image->data = (void *) data;

    vsize = var_size(vtype);

    for (i = ly; i < uy; ++i)
	data[i] = (void *) ((int) mem_ptr + (roi_width * (i - ly) - lx) * vsize);

    return image;
}

/* Copy specified roi of image1 to image2 throgh a double Storage must
 * already be allocated for image2. */
static void write_thro_double(Imrect * image1, Imrect * image2, Imregion * roi)
{
    int     lx, ly, ux, uy;
    int     i, j;
    double  gl;


    lx = roi->lx;
    ly = roi->ly;
    ux = roi->ux;
    uy = roi->uy;

    for (i = ly; i < uy; ++i)
	for (j = lx; j < ux; ++j)
	{
	    IM_PIX_GET(image1, i, j, gl);
	    IM_PIX_SET(image2, i, j, gl);
	}
}

/* Copy specified roi of image1 to image2 through type int (ok for
 * ptr).  Storage must already be allocated for image2. */
static void write_thro_int(Imrect * image1, Imrect * image2, Imregion * roi)
{
    int     lx, ly, ux, uy;
    int     i, j;
    double     gl;

    lx = roi->lx;
    ly = roi->ly;
    ux = roi->ux;
    uy = roi->uy;

    for (i = ly; i < uy; ++i)
	for (j = lx; j < ux; ++j)
	{
	    IM_PIX_GET(image1, i, j, gl);
	    IM_PIX_SET(image2, i, j, (int)gl);
	}
}

/* Copy specified roi of image1 to image2 through type complex. Storage
 * must already be allocated for image2. */
static void write_thro_complex(Imrect * image1, Imrect * image2, Imregion * roi)
{
    int     lx, ly, ux, uy;
    int     i, j;
    Complex gl =
    {Complex_id};

    lx = roi->lx;
    ly = roi->ly;
    ux = roi->ux;
    uy = roi->uy;

    for (i = ly; i < uy; ++i)
	for (j = lx; j < ux; ++j)
	{
	    IM_PIX_GETZ(image1, i, j, gl);
	    IM_PIX_SETZ(image2, i, j, gl);
	}
}

/* Overwrite region of image2 by region of image1. The region used is
 * the intersection of the roi's of image1 and image2.  Storage must
 * already be allocated for image2. */
void    im_copy_inplace(Imrect * image2, Imrect * image1)
{
    Imregion *roi;
    Imregion *roi_inter();
    Vartype vtype;
    void * memcpy();

    if (image1 == NULL || image2 == NULL)
	return;

    roi = roi_inter(image1->region, image2->region);
    if(!roi) 
      {
	errorf(warning,"im_copy_inplace() regions do not overlap\n");
	return;
      }
    vtype = (Vartype) MAX((int) image1->vtype, (int) image2->vtype);

    if (image1->vtype != image2->vtype || (int) image1->vtype > (int) complex_v)
    {
	switch (vtype)
	{
	case char_v:
	case uchar_v:
	case short_v:
	case ushort_v:
	case int_v:
	case uint_v:
	case ptr_v:
	    write_thro_int(image1, image2, roi);
	    break;
	case float_v:
	case double_v:
	    write_thro_double(image1, image2, roi);
	    break;
	case complex_v:
	    write_thro_complex(image1, image2, roi);
	    break;
	  case vram0_v:
	  case vram1_v:
	  case vram2_v:
	  case vram3_v:
	    write_thro_int(image1, image2, roi);
	    break;
	  default:
	    error("Cannot copy this image type",fatal);
	    break;
	}
    } else
    {
	/* same type */
	int     lx, ly, ux, uy;
	int     nchars;
	unsigned int vsize;
	int     i;
	char  **array1 = (char **) image1->data;
	char  **array2 = (char **) image2->data;

	vsize = var_size(image1->vtype);

	lx = roi->lx;
	ly = roi->ly;
	ux = roi->ux;
	uy = roi->uy;
	lx *= vsize;
	ux *= vsize;
	nchars = ux - lx;

	for (i = ly; i < uy; ++i)
	    (void) memcpy(array2[i] + lx, array1[i] + lx, nchars);
    }

    rfree((void *) (char *) roi);
}

/* Make new copy of specified roi of image.  Allocate storage for new
 * copy.  Copy specified roi of image into it. Return pointer to it. */
Imrect *im_subim(Imrect * image, Imregion * region)
{
    Imregion *subregion;
    Imregion *roi_inter();
    Imrect *subimage;

    if (image == NULL)
	return (NULL);

    subregion = roi_inter(region, image->region);
    if (subregion == NULL)
	return (NULL);

    subimage = im_alloc(image->height, image->width, subregion, image->vtype);
    rfree((void *) (char *) subregion);
    im_copy_inplace(subimage, image);
    return (subimage);
}

/* Make new copy of image of given type.  Allocate storage for new
 * copy. Copy whole image into it. Return pointer to it. */
Imrect *im_cast(Imrect * image, Vartype vtype)
{
    Imrect *copy;

    if (image == NULL)
	return (NULL);

    copy = im_alloc(image->height, image->width, image->region, vtype);
    im_copy_inplace(copy, image);

    return (copy);
}

/* Make new copy of image.  Allocate storage for new copy. Copy whole
 * image into it. Return pointer to it. */
Imrect *im_copy(Imrect * image)
{
    Imrect *copy;

    if (image == NULL)
	return (NULL);

    copy = im_alloc(image->height, image->width, image->region, image->vtype);
    im_copy_inplace(copy, image);

    return (copy);
}

/* Destroy image.  Free an image's storage. */
void    im_free(Imrect * image)
{
    int     lx, ly, ux, uy;
    unsigned int vsize;

    if (image == NULL)
	return;

    proplist_freelist(image->props);

    lx = image->region->lx;
    ly = image->region->ly;
    ux = image->region->ux;
    uy = image->region->uy;

    vsize = var_size(image->vtype);
    narray_free((char **) image->data, ly, lx, uy, ux, vsize);
    rfree((void *) image->region);
    rfree((void *) image);
}

/**
Shifts data and roi of an image by
 dy rows
 dx cols
cheaply, in place
**/

void    im_shift(Imrect * im, int dy, int dx)
{
    Imregion *roi;
    int     y, ly, uy;
    unsigned int vsize;
    void   *row;

    if (im == NULL)
	return;

    roi = im->region;
    ly = roi->ly;
    uy = roi->uy;
    vsize = var_size(im->vtype);

    for (y = ly; y < uy; y++)
    {
	IM_ROW_GET(im, y, row);
	row = (void *) ((int) row - vsize * dx);
	IM_ROW_SET(im, y, row);
    }
    im->data = (void **) im->data - dy;

    roi->lx += dx;
    roi->ux += dx;
    roi->ly += dy;
    roi->uy += dy;
}
