/**@(#)Image handling. (Getting values from an image).
 */

#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>

int     im_get_pix(Imrect * image, int i, int j)
{
    Imregion *region;
    double     pixval;

    if (image == NULL || image->vtype == ptr_v)
	return (0);

    region = image->region;
    if (i < region->ly || i >= region->uy || j < region->lx || j >= region->ux)
	return (0);

    IM_PIX_GET(image, i, j, pixval);

    return ((int)pixval);
}

void   *im_get_ptr(Imrect * image, int i, int j)
{
    Imregion *region;

    if (image == NULL || image->vtype != ptr_v)
	return (NULL);

    region = image->region;
    if (i < region->ly || i >= region->uy || j < region->lx || j >= region->ux)
	return (NULL);

    return (IM_PTR(image, i, j));
}

double  im_get_pixf(Imrect * image, int i, int j)
{
    Imregion *region;
    double  pixval;

    if (image == NULL || image->vtype == ptr_v)
	return (0);

    region = image->region;
    if (i < region->ly || i >= region->uy || j < region->lx || j >= region->ux)
	return (0);

    IM_PIX_GET(image, i, j, pixval);

    return (pixval);
}

Complex im_get_pixz(Imrect * image, int i, int j)
{
    Imregion *region;
    Complex pixval = {Complex_id};

    if (image == NULL || image->vtype == ptr_v)
	return (cmplx_zero());

    region = image->region;
    if (i < region->ly || i >= region->uy || j < region->lx || j >= region->ux)
	return (cmplx_zero());

    if (image->vtype == complex_v)
	pixval = IM_COMPLEX(image, i, j);
    else
    {
	pixval.y = 0.0;
	IM_PIX_GET(image, i, j, pixval.x);
    }
    return (pixval);
}

int     im_sub_pix(Imrect * image, double r, double c)
{
    Imregion *region;
    int     i, j;
    double  x1, x2, y1, y2;
    double  gl, pix11, pix12, pix21, pix22;
    double    pixval;

    if (image == NULL || image->vtype == ptr_v)
	return (0);

    r -= 0.5;
    c -= 0.5;

    region = image->region;
    if (r < region->ly || r + 1 >= region->uy || c < region->lx || c + 1 >= region->ux)
	return (0);

    i = (int) r;
    y1 = r - i;
    y2 = 1.0 - y1;
    j = (int) c;
    x1 = c - j;
    x2 = 1.0 - x1;

    IM_PIX_GET(image, i, j, pix11);
    IM_PIX_GET(image, i, j + 1, pix12);
    IM_PIX_GET(image, i + 1, j, pix21);
    IM_PIX_GET(image, i + 1, j + 1, pix22);

    gl = (pix11 * x2 + pix12 * x1) * y2 + (pix21 * x2 + pix22 * x1) * y1;

    pixval = (gl > 0) ? gl + 0.5 : gl - 0.5;
    return ((int)pixval);
}

double  im_sub_pixf(Imrect * image, double r, double c)
{
    Imregion *region;
    int     i, j;
    double  x1, x2, y1, y2;
    double  pix11, pix12, pix21, pix22;
    double  pixval;

    if (image == NULL || image->vtype == ptr_v)
	return (0);

    r -= 0.5;
    c -= 0.5;

    region = image->region;
    if (r < region->ly || r + 1 >= region->uy || c < region->lx || c + 1 >= region->ux)
	return (0);

    i = (int) r;
    y1 = r - i;
    y2 = 1.0 - y1;
    j = (int) c;
    x1 = c - j;
    x2 = 1.0 - x1;

    IM_PIX_GET(image, i, j, pix11);
    IM_PIX_GET(image, i, j + 1, pix12);
    IM_PIX_GET(image, i + 1, j, pix21);
    IM_PIX_GET(image, i + 1, j + 1, pix22);

    pixval = (pix11 * x2 + pix12 * x1) * y2 + (pix21 * x2 + pix22 * x1) * y1;

    return (pixval);
}

double          im_sub_pixqf(Imrect *image, double y, double x)
/* fits simple quadratic function to image and returns interpolated value
                                                                NAT 10/10/90 */
{
    Imregion       *region = image->region;
    double          pixval[3][3];
    float           a, b, c, d, e, f;
    double          inter;
    short           i, j, n, m;
    float           xs, ys;

    i = tina_int(x-1);
    j = tina_int(y-1);

    xs = (float)( x -  i - 1.5 );
    ys = (float)(y -  j - 1.5 );

    if (j < region->ly || j > region->uy - 3
        || i < region->lx || i > region->ux - 3)
        return (0);
    for (n = 0; n < 3; n++)
    {
        for (m = 0; m < 3; m++)
        {
            IM_PIX_GET(image, j + n, i + m, pixval[n][m]);
        }
    }

    a = (float)pixval[1][1];
    b = (float)((pixval[0][2] - pixval[0][0]
        + pixval[1][2] - pixval[1][0]
        + pixval[2][2] - pixval[2][0]) / 6.0);
    c = (float)((pixval[2][0] - pixval[0][0]
        + pixval[2][1] - pixval[0][1]
        + pixval[2][2] - pixval[0][2]) / 6.0);
    d = (float)((pixval[0][0] - 2.0 * pixval[0][1] + pixval[0][2]
        + 3.0 * pixval[1][0] - 6.0 * pixval[1][1] + 3.0 * pixval[1][2]
        + pixval[2][0] - 2.0 * pixval[2][1] + pixval[2][2]) / 10.0);
    e = (float)((pixval[0][0] - pixval[2][0]
        + pixval[2][2] - pixval[0][2]) / 4.0);
    f = (float)((pixval[0][0] + 3.0 * pixval[0][1] + pixval[0][2]
        - 2.0 * pixval[1][0] - 6.0 * pixval[1][1] - 2.0 * pixval[1][2]
        + pixval[2][0] + 3.0 * pixval[2][1] + pixval[2][2]) / 10.0);

    xs *=(float)2.0;
    ys *=(float)2.0;
    inter = a + 0.5*(b * xs + c * ys + d * xs * xs + e * xs * ys + f * ys * ys);

    return (inter);
}

Complex im_sub_pixz(Imrect * im, double y, double x)
{
    int     i, j;
    double  x1, x2, y1, y2;
    Complex z00 = {Complex_id};
    Complex z10 = {Complex_id};
    Complex z01 = {Complex_id};
    Complex z11 = {Complex_id};
    double  re00, re01, re10, re11, re0;
    double  im00, im01, im10, im11, im0;

    y -= 0.5;
    i = (int) y;
    y1 = y - i;
    y2 = 1.0 - y1;
    x -= 0.5;
    j = (int) x;
    x1 = x - j;
    x2 = 1.0 - x1;

    z00 = im_get_pixz(im, i, j);
    z01 = im_get_pixz(im, i, j + 1);
    z10 = im_get_pixz(im, i + 1, j);
    z11 = im_get_pixz(im, i + 1, j + 1);

    re00 = cmplx_re(z00);
    re10 = cmplx_re(z10);
    re01 = cmplx_re(z01);
    re11 = cmplx_re(z11);
    re0 = y2 * (x2 * re00 + x1 * re01) + y1 * (x2 * re10 + x1 * re11);

    im00 = cmplx_im(z00);
    im10 = cmplx_im(z10);
    im01 = cmplx_im(z01);
    im11 = cmplx_im(z11);
    im0 = y2 * (x2 * im00 + x1 * im01) + y1 * (x2 * im10 + x1 * im11);

    return (cmplx(re0, im0));
}

void    im_get_row(int *line, Imrect * image, int i, int from, int to)
{
    int     j;
    Imregion *region;
    double pixval;

    for (j = from; j < to; ++j)
	line[j] = 0;

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
    {
	IM_PIX_GET(image, i, j, pixval);
        line[j] = (int)pixval;
    }
}

void    im_get_col(int *line, Imrect * image, int i, int from, int to)
{
    int     j;
    Imregion *region;
    double pixval;

    for (j = from; j < to; ++j)
	line[j] = 0;

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
    {
	IM_PIX_GET(image, j, i, pixval);
        line[j] = (int) pixval;
    }
}

void    im_get_rowf(float *line, Imrect * image, int i, int from, int to)
{
    int     j;
    Imregion *region;
    double pixval;

    for (j = from; j < to; ++j)
	line[j] = (float) 0.0;

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
    {
	IM_PIX_GET(image, i, j, pixval);
        line[j] = (float) pixval;
    }
}

void    im_get_colf(float *line, Imrect * image, int i, int from, int to)
{
    int     j;
    Imregion *region;
    double pixval;

    for (j = from; j < to; ++j)
	line[j] = (float) 0.0;

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
    {
	IM_PIX_GET(image, j, i, pixval);
        line[j] = (float) pixval;
    }
}

void    im_get_rowz(Complex * line, Imrect * image, int i, int from, int to)
{
    int     j;
    Imregion *region;

    for (j = from; j < to; ++j)
	line[j] = cmplx_zero();

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
	    line[j] = IM_COMPLEX(image, i, j);
    } else
    {
	for (j = from; j < to; ++j)
	    IM_PIX_GET(image, i, j, line[j].x);
    }
}

void    im_get_colz(Complex * line, Imrect * image, int i, int from, int to)
{
    int     j;
    Imregion *region;

    for (j = from; j < to; ++j)
	line[j] = cmplx_zero();

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
	    line[j] = IM_COMPLEX(image, j, i);
    } else
    {
	for (j = from; j < to; ++j)
	    IM_PIX_GET(image, j, i, line[j].x);
    }
}

void    im_get_pos_diag(int *line, Imrect * image, int x, int y, int len)
{
    int     j;
    int     minoff;
    Imregion *region;

    for (j = 0; j < len; ++j)
	line[j] = 0;

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
		line[j] = array[y + j][x + j];
	}
	break;
    case uchar_v:
	{
	    unsigned char **array = (unsigned char **) image->data;

	    for (j = 0; j < len; j++)
		line[j] = array[y + j][x + j];
	}
	break;
    case short_v:
	{
	    short **array = (short **) image->data;

	    for (j = 0; j < len; j++)
		line[j] = array[y + j][x + j];
	}
	break;
    case ushort_v:
	{
	    unsigned short **array = (unsigned short **) image->data;

	    for (j = 0; j < len; j++)
		line[j] = array[y + j][x + j];
	}
	break;
    case int_v:
	{
	    int   **array = (int **) image->data;

	    for (j = 0; j < len; j++)
		line[j] = array[y + j][x + j];
	}
	break;
    case uint_v:
	{
	    unsigned int **array = (unsigned int **) image->data;

	    for (j = 0; j < len; j++)
		line[j] = array[y + j][x + j];
	}
	break;
    case float_v:
	{
	    float **array = (float **) image->data;

	    for (j = 0; j < len; j++)
	    {
		float   gl = array[y + j][x + j];

		line[j] = (int) ((gl > 0) ? gl + 0.5 : gl - 0.5);
	    }
	}
	break;
    case double_v:
	{
	    double **array = (double **) image->data;

	    for (j = 0; j < len; j++)
	    {
		double  gl = array[y + j][x + j];

		line[j] = (int)((gl > 0) ? gl + 0.5 : gl - 0.5);
	    }
	}
	break;
    }
}

void    im_get_neg_diag(int *line, Imrect * image, int x, int y, int len)
{
    int     j;
    int     minoff;
    Imregion *region;

    for (j = 0; j < len; ++j)
	line[j] = 0;

    if (image == NULL)
	return;

    region = image->region;
    if (x < region->lx || (x - len) >= region->ux)
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
		line[j] = array[y + j][x - j];
	}
	break;
    case uchar_v:
	{
	    unsigned char **array = (unsigned char **) image->data;

	    for (j = 0; j < len; j++)
		line[j] = array[y + j][x - j];
	}
	break;
    case short_v:
	{
	    short **array = (short **) image->data;

	    for (j = 0; j < len; j++)
		line[j] = array[y + j][x - j];
	}
	break;
    case ushort_v:
	{
	    unsigned short **array = (unsigned short **) image->data;

	    for (j = 0; j < len; j++)
		line[j] = array[y + j][x - j];
	}
	break;
    case int_v:
	{
	    int   **array = (int **) image->data;

	    for (j = 0; j < len; j++)
		line[j] = array[y + j][x - j];
	}
	break;
    case uint_v:
	{
	    unsigned int **array = (unsigned int **) image->data;

	    for (j = 0; j < len; j++)
		line[j] = array[y + j][x - j];
	}
	break;
    case float_v:
	{
	    float **array = (float **) image->data;

	    for (j = 0; j < len; j++)
	    {
		float   gl = array[y + j][x - j];

		line[j] = (int)((gl > 0) ? gl + 0.5 : gl - 0.5);
	    }
	}
	break;
    case double_v:
	{
	    double **array = (double **) image->data;

	    for (j = 0; j < len; j++)
	    {
		double  gl = array[y + j][x - j];

		line[j] = (int)((gl > 0) ? gl + 0.5 : gl - 0.5);
	    }
	}
	break;
    }
}

void    im_get_pos_diagf(float *line, Imrect * image, int x, int y, int len)
{
    int     j;
    int     minoff;
    Imregion *region;

    for (j = 0; j < len; ++j)
	line[j] = (float) 0.0;

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
		line[j] = array[y + j][x + j];
	}
	break;
    case uchar_v:
	{
	    unsigned char **array = (unsigned char **) image->data;

	    for (j = 0; j < len; j++)
		line[j] = array[y + j][x + j];
	}
	break;
    case short_v:
	{
	    short **array = (short **) image->data;

	    for (j = 0; j < len; j++)
		line[j] = array[y + j][x + j];
	}
	break;
    case ushort_v:
	{
	    unsigned short **array = (unsigned short **) image->data;

	    for (j = 0; j < len; j++)
		line[j] = array[y + j][x + j];
	}
	break;
    case int_v:
	{
	    int   **array = (int **) image->data;

	    for (j = 0; j < len; j++)
		line[j] = (float) array[y + j][x + j];
	}
	break;
    case uint_v:
	{
	    unsigned int **array = (unsigned int **) image->data;

	    for (j = 0; j < len; j++)
		line[j] = (float) array[y + j][x + j];
	}
	break;
    case float_v:
	{
	    float **array = (float **) image->data;

	    for (j = 0; j < len; j++)
	    {
		float   gl = array[y + j][x + j];

		line[j] = (float)((gl > 0) ? gl + 0.5 : gl - 0.5);
	    }
	}
	break;
    case double_v:
	{
	    double **array = (double **) image->data;

	    for (j = 0; j < len; j++)
	    {
		double  gl = array[y + j][x + j];

		line[j] = (float)((gl > 0) ? gl + 0.5 : gl - 0.5);
	    }
	}
	break;
    }
}

void    im_get_neg_diagf(float *line, Imrect * image, int x, int y, int len)
{
    int     j;
    int     minoff;
    Imregion *region;

    for (j = 0; j < len; ++j)
	line[j] = (float) 0.0;

    if (image == NULL)
	return;

    region = image->region;
    if (x < region->lx || (x - len) >= region->ux)
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
		line[j] = array[y + j][x - j];
	}
	break;
    case uchar_v:
	{
	    unsigned char **array = (unsigned char **) image->data;

	    for (j = 0; j < len; j++)
		line[j] = array[y + j][x - j];
	}
	break;
    case short_v:
	{
	    short **array = (short **) image->data;

	    for (j = 0; j < len; j++)
		line[j] = array[y + j][x - j];
	}
	break;
    case ushort_v:
	{
	    unsigned short **array = (unsigned short **) image->data;

	    for (j = 0; j < len; j++)
		line[j] = array[y + j][x - j];
	}
	break;
    case int_v:
	{
	    int   **array = (int **) image->data;

	    for (j = 0; j < len; j++)
		line[j] = (float) array[y + j][x - j];
	}
	break;
    case uint_v:
	{
	    unsigned int **array = (unsigned int **) image->data;

	    for (j = 0; j < len; j++)
		line[j] = (float) array[y + j][x - j];
	}
	break;
    case float_v:
	{
	    float **array = (float **) image->data;

	    for (j = 0; j < len; j++)
	    {
		float   gl = array[y + j][x - j];

		line[j] = (float)((gl > 0) ? gl + 0.5 : gl - 0.5);
	    }
	}
	break;
    case double_v:
	{
	    double **array = (double **) image->data;

	    for (j = 0; j < len; j++)
	    {
		double  gl = array[y + j][x - j];

		line[j] = (float)((gl > 0) ? gl + 0.5 : gl - 0.5);
	    }
	}
	break;
    }
}
