/**@(#)Image handling (setting values in an image)
 */

#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

void    im_put_pix(int pixval, Imrect * image, int i, int j)
{
    Imregion *region;

    if (image == NULL || image->vtype == ptr_v)
	return;

    region = image->region;
    if (i < region->ly || i >= region->uy || j < region->lx || j >= region->ux)
	return;

    IM_PIX_SET(image, i, j, pixval);
}

void    im_put_ptr(void *ptr, Imrect * image, int i, int j)
{
    Imregion *region;

    if (image == NULL || image->vtype != ptr_v)
	return;

    region = image->region;
    if (i < region->ly || i >= region->uy || j < region->lx || j >= region->ux)
	return;

    IM_PTR(image, i, j) = ptr;
}

void    im_put_pixf(double pixval, Imrect * image, int i, int j)
{
    Imregion *region;

    if (image == NULL || image->vtype == ptr_v)
	return;

    region = image->region;
    if (i < region->ly || i >= region->uy || j < region->lx || j >= region->ux)
	return;

    IM_PIX_SET(image, i, j, pixval);
}

/* Increment pixel (i, j) in image. Pixels outside image are ignored */
void    im_pixf_inc(Imrect * image, int i, int j)
{
    Imregion *region;

    if (image && (image->vtype != ptr_v) && (region = image->region))
    {
	if (region->ly <= i && i < region->uy && region->lx <= j && j < region->ux)
	{
	    double  pixval;

	    IM_PIX_GET(image, i, j, pixval);
	    IM_PIX_SET(image, i, j, ++pixval);
	}
    }
}

/* Decrement pixel (i, j) in image. Pixels outside image are ignored */
void    im_pixf_dec(Imrect * image, int i, int j)
{
    Imregion *region;

    if (image && (image->vtype != ptr_v) && (region = image->region))
    {
	if (region->ly <= i && i < region->uy && region->lx <= j && j < region->ux)
	{
	    double  pixval;

	    IM_PIX_GET(image, i, j, pixval);
	    IM_PIX_SET(image, i, j, --pixval);
	}
    }
}

void    im_put_pixz(Complex pixval, Imrect * image, int i, int j)
{
    Imregion *region;

    if (image == NULL || image->vtype == ptr_v)
	return;

    region = image->region;
    if (i < region->ly || i >= region->uy || j < region->lx || j >= region->ux)
	return;

    if (image->vtype == complex_v)
	IM_COMPLEX(image, i, j) = pixval;
    else
	IM_PIX_SET(image, i, j, pixval.x);
}

void    im_put_row(int *line, Imrect * image, int i, int from, int to)
{
    int     j;
    Imregion *region;

    if (image == NULL || image->vtype == ptr_v)
	return;

    region = image->region;
    if (i < region->ly || i >= region->uy)
	return;

    if (from >= region->ux || to < region->lx)
	return;

    if (to > region->ux)
	to = region->ux;

    if (from < region->lx)
	from = region->lx;

    for (j = from; j < to; ++j)
	IM_PIX_SET(image, i, j, line[j]);
}

void    im_put_col(int *line, Imrect * image, int i, int from, int to)
{
    int     j;
    Imregion *region;

    if (image == NULL || image->vtype == ptr_v)
	return;

    region = image->region;
    if (i < region->lx || i >= region->ux)
	return;

    if (from >= region->uy || to < region->ly)
	return;

    if (to > region->uy)
	to = region->uy;

    if (from < region->ly)
	from = region->ly;

    for (j = from; j < to; ++j)
	IM_PIX_SET(image, j, i, line[j]);
}

void    im_put_rowf(float *line, Imrect * image, int i, int from, int to)
{
    int     j;
    Imregion *region;

    if (image == NULL || image->vtype == ptr_v)
	return;

    region = image->region;
    if (i < region->ly || i >= region->uy)
	return;

    if (from >= region->ux || to < region->lx)
	return;

    if (to > region->ux)
	to = region->ux;

    if (from < region->lx)
	from = region->lx;

    for (j = from; j < to; ++j)
	IM_PIX_SET(image, i, j, line[j]);
}

void    im_put_colf(float *line, Imrect * image, int i, int from, int to)
{
    int     j;
    Imregion *region;

    if (image == NULL || image->vtype == ptr_v)
	return;

    region = image->region;
    if (i < region->lx || i >= region->ux)
	return;

    if (from >= region->uy || to < region->ly)
	return;

    if (to > region->uy)
	to = region->uy;

    if (from < region->ly)
	from = region->ly;

    for (j = from; j < to; ++j)
	IM_PIX_SET(image, j, i, line[j]);
}

void    im_put_rowz(Complex * line, Imrect * image, int i, int from, int to)
{
    int     j;
    Imregion *region;

    if (image == NULL || image->vtype == ptr_v)
	return;

    region = image->region;
    if (i < region->ly || i >= region->uy)
	return;

    if (from >= region->ux || to < region->lx)
	return;

    if (to > region->ux)
	to = region->ux;

    if (from < region->lx)
	from = region->lx;

    if (image->vtype == complex_v)
    {
	for (j = from; j < to; ++j)
	    IM_COMPLEX(image, i, j) = line[j];
    } else
    {
	for (j = from; j < to; ++j)
	    IM_PIX_SET(image, i, j, line[j].x);
    }
}

void    im_put_colz(Complex * line, Imrect * image, int i, int from, int to)
{
    int     j;
    Imregion *region;

    if (image == NULL || image->vtype == ptr_v)
	return;

    region = image->region;
    if (i < region->lx || i >= region->ux)
	return;

    if (from >= region->uy || to < region->ly)
	return;

    if (to > region->uy)
	to = region->uy;

    if (from < region->ly)
	from = region->ly;

    if (image->vtype == complex_v)
    {
	for (j = from; j < to; ++j)
	    IM_COMPLEX(image, j, i) = line[j];
    } else
    {
	for (j = from; j < to; ++j)
	    IM_PIX_SET(image, j, i, line[j].x);
    }
}

void    im_put_pos_diag(int *line, Imrect * image, int x, int y, int len)
{
    int     j;
    int     minoff;
    Imregion *region;

    if (image == NULL)
	return;

    region = image->region;

    if (x >= region->ux || (x + len) < region->lx)
	return;

    if (y >= region->uy || (y + len) < region->ly)
	return;

    minoff = MIN(x - region->lx, y - region->ly);
    if (minoff < 0)
    {
	x -= minoff;
	y -= minoff;
	len += minoff;
    }
    minoff = MIN(region->ux - x - len, region->uy - y - len);
    if (minoff < 0)
	len += minoff;

    switch (image->vtype)
    {
    case char_v:
	{
	    char  **array = (char **) image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = line[j];
	}
	break;
    case uchar_v:
	{
	    unsigned char **array = (unsigned char **) image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = abs(line[j]);
	}
	break;
    case short_v:
	{
	    short **array = (short **) image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = line[j];
	}
	break;
    case ushort_v:
	{
	    unsigned short **array = (unsigned short **) image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = abs(line[j]);
	}
	break;
    case int_v:
	{
	    int   **array = (int **) image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = line[j];
	}
	break;
    case uint_v:
	{
	    unsigned int **array = (unsigned int **) image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = abs(line[j]);
	}
	break;
    case float_v:
	{
	    float **array = (float **) image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = (float)line[j];
	}
	break;
    case double_v:
	{
	    double **array = (double **) image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = line[j];
	}
	break;
    }
}

void    im_put_neg_diag(int *line, Imrect * image, int x, int y, int len)
{
    int     j;
    int     minoff;
    Imregion *region;

    if (image == NULL)
	return;

    region = image->region;

    if ((x - len) >= region->ux || x < region->lx)
	return;

    if (y >= region->uy || (y + len) < region->ly)
	return;

    minoff = MIN(region->ux - x, y - region->ly);
    if (minoff < 0)
    {
	x += minoff;
	y -= minoff;
	len += minoff;
    }
    minoff = MIN(x - len - region->lx, region->uy - y - len);
    if (minoff < 0)
	len += minoff;

    switch (image->vtype)
    {
    case char_v:
	{
	    char  **array = (char **) image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = line[j];
	}
	break;
    case uchar_v:
	{
	    unsigned char **array = (unsigned char **) image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = abs(line[j]);
	}
	break;
    case short_v:
	{
	    short **array = (short **) image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = line[j];
	}
	break;
    case ushort_v:
	{
	    unsigned short **array = (unsigned short **) image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = abs(line[j]);
	}
	break;
    case int_v:
	{
	    int   **array = (int **) image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = line[j];
	}
	break;
    case uint_v:
	{
	    unsigned int **array = (unsigned int **) image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = abs(line[j]);
	}
	break;
    case float_v:
	{
	    float **array = (float **) image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = (float)line[j];
	}
	break;
    case double_v:
	{
	    double **array = (double **) image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = line[j];
	}
	break;
    }
}

void    im_put_pos_diagf(float *line, Imrect * image, int x, int y, int len)
{
    int     j;
    int     minoff;
    Imregion *region;

    if (image == NULL)
	return;

    region = image->region;

    if (x >= region->ux || (x + len) < region->lx)
	return;

    if (y >= region->uy || (y + len) < region->ly)
	return;

    minoff = MIN(x - region->lx, y - region->ly);
    if (minoff < 0)
    {
	x -= minoff;
	y -= minoff;
	len += minoff;
    }
    minoff = MIN(region->ux - x - len, region->uy - y - len);
    if (minoff < 0)
	len += minoff;

    switch (image->vtype)
    {
    case char_v:
	{
	    char  **array = (char **) image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = (char)line[j];
	}
	break;
    case uchar_v:
	{
	    unsigned char **array = (unsigned char **) image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = (unsigned char)(fabs(line[j]));
	}
	break;
    case short_v:
	{
	    short **array = (short **) image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = (short)line[j];
	}
	break;
    case ushort_v:
	{
	    unsigned short **array = image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = (unsigned short)fabs(line[j]);
	}
	break;
    case int_v:
	{
	    int   **array = image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = (int)line[j];
	}
	break;
    case uint_v:
	{
	    unsigned int **array = image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = (unsigned int)fabs(line[j]);
	}
	break;
    case float_v:
	{
	    float **array = image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = line[j];
	}
	break;
    case double_v:
	{
	    double **array = image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = line[j];
	}
	break;
    }
}

void    im_put_neg_diagf(float *line, Imrect * image, int x, int y, int len)
{
    int     j;
    int     minoff;
    Imregion *region;

    if (image == NULL)
	return;

    region = image->region;

    if ((x - len) >= region->ux || x < region->lx)
	return;

    if (y >= region->uy || (y + len) < region->ly)
	return;

    minoff = MIN(region->ux - x, y - region->ly);
    if (minoff < 0)
    {
	x += minoff;
	y -= minoff;
	len += minoff;
    }
    minoff = MIN(x - len - region->lx, region->uy - y - len);
    if (minoff < 0)
	len += minoff;

    switch (image->vtype)
    {
    case char_v:
	{
	    char  **array = image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = (char)line[j];
	}
	break;
    case uchar_v:
	{
	    unsigned char **array = image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = (unsigned char)fabs(line[j]);
	}
	break;
    case short_v:
	{
	    short **array = image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = (short)line[j];
	}
	break;
    case ushort_v:
	{
	    unsigned short **array = image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = (unsigned short)fabs(line[j]);
	}
	break;
    case int_v:
	{
	    int   **array = image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = (int)line[j];
	}
	break;
    case uint_v:
	{
	    unsigned int **array = image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = (unsigned int)fabs(line[j]);
	}
	break;
    case float_v:
	{
	    float **array = image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = line[j];
	}
	break;
    case double_v:
	{
	    double **array = image->data;

	    for (j = 0; j < len; j++)
		array[y + j][x + j] = line[j];
	}
	break;
    }
}
