/**@(#)
**/
/**
im_create.c:
creating simple images
**/

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Imrect *imf_checquer(int width, int height, int dx, int dy)
{
    float  *row1, *row2;
    Imrect *im = im_alloc(height, width, (Imregion *) NULL, float_v);
    int     i, j;

    row1 = fvector_alloc(0, width);
    for (i = 0, j = 0; i < width; i++, j++)
    {
	if (j < dx)
	    row1[i] = (float) 0.0;
	else if (j < 2 * dx)
	    row1[i] = (float) 255.0;

	if (j == 2 * dx - 1)
	    j = -1;
    }

    row2 = fvector_alloc(0, width);
    for (i = 0, j = 0; i < width; i++, j++)
    {
	if (j < dx)
	    row2[i] = (float) 255.0;
	else if (j < 2 * dx)
	    row2[i] = (float) 0.0;

	if (j == 2 * dx - 1)
	    j = -1;
    }

    for (i = 0, j = 0; i < height; i++, j++)
    {
	if (j < dy)
	    im_put_rowf(row1, im, i, 0, width);
	else if (j < 2 * dx)
	    im_put_rowf(row2, im, i, 0, width);

	if (j == 2 * dy - 1)
	    j = -1;
    }
    fvector_free((void *) row1, 0);
    fvector_free((void *) row2, 0);
    return (im);
}

Imrect *imf_rect(int width, int height, int lx, int ly, int ux, int uy)
{
    float  *row1, *row2;
    Imrect *im = im_alloc(height, width, (Imregion *) NULL, float_v);
    int     i;

    row1 = fvector_alloc(0, width);
    for (i = 0; i < width; i++)
    {
	if (i < lx)
	    row1[i] = (float) 0.0;
	else if (i < ux)
	    row1[i] = (float) 255.0;
	else
	    row1[i] = (float) 0.0;
    }
    row2 = fvector_alloc(0, width);

    for (i = 0; i < height; i++)
    {
	if (i < ly)
	    im_put_rowf(row2, im, i, 0, width);
	else if (i < uy)
	    im_put_rowf(row1, im, i, 0, width);
	else
	    im_put_rowf(row2, im, i, 0, width);
    }
    fvector_free((void *) row1, 0);
    fvector_free((void *) row2, 0);
    return (im);
}

Imrect *imf_ellipse(int width, int height, double cx, double cy, double ax, double ay)
{
    float  *row;
    Imrect *im = im_alloc(height, width, (Imregion *) NULL, float_v);
    int     x, y;

    row = fvector_alloc(0, width);
    for (y = 0; y < height; y++)
    {
	for (x = 0; x < width; x++)
	{
	    float   x1 = (float) ((x - cx) / ax);
	    float   y1 = (float) ((y - cy) / ay);

	    if (x1 * x1 + y1 * y1 > 1.0)
		row[x] = (float) 0.0;
	    else
		row[x] = (float) 255.0;
	}
	im_put_rowf(row, im, y, 0, width);
    }

    fvector_free((void *) row, 0);
    return (im);
}

Imrect *imf_subpix_ellipse(int width, int height, double cx, double cy, double ax, double ay)
{
    float  *row;
    Imrect *im = im_alloc(height, width, (Imregion *) NULL, float_v);
    int     x, y;

    row = fvector_alloc(0, width);
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            double  x1 = (x - cx) / ax;
            double  y1 = (y - cy) / ay;
            double  x2 = (x - cx + 1) / ax;
            double  y2 = (y - cy + 1) / ay;
            double  s11, s12, s21, s22;

            s11 = x1 * x1 + y1 * y1;
            s21 = x2 * x2 + y1 * y1;
            s12 = x1 * x1 + y2 * y2;
            s22 = x2 * x2 + y2 * y2;
            if (s11 > 1.0 && s12 > 1.0 && s21 > 1.0 && s22 > 1.0)
                row[x] = (float) 0.0;
            else if (s11 < 1.0 && s12 < 1.0 && s21 < 1.0 && s22 < 1.0)
                row[x] = (float) 255.0;
            else
            {
                int     n = 32, k, l;
                double  sum = 0.0, dx, dy;

                dx = 1.0 / (n * ax);
                dy = 1.0 / (n * ay);
                for (k = 0; k < n; k++)
                {
                    double  xk = x1 + k * dx;

                    for (l = 0; l < n; l++)
                    {
                        double  yl = y1 + l * dy;

                        if (xk * xk + yl * yl < 1.0)
                            sum += 1.0;
                    }
                }
                row[x] = (float) (sum * 255.0 / (n * n));
            }
        }
        im_put_rowf(row, im, y, 0, width);
    }

    fvector_free((void *) row, 0);
    return (im);
}

Imrect *imf_subpix_ellipsoid(int width, int height, double cx, double cy, double ax, double ay)
{
    float  *row;
    Imrect *im = im_alloc(height, width, (Imregion *) NULL, float_v);
    int     x, y;

    row = fvector_alloc(0, width);
    for (y = 0; y < height; y++)
    {
	for (x = 0; x < width; x++)
	{
	    double  x1 = (x - cx) / ax;
	    double  y1 = (y - cy) / ay;
	    double  x2 = (x - cx + 1) / ax;
	    double  y2 = (y - cy + 1) / ay;
	    double  s11, s12, s21, s22;

	    s11 = x1 * x1 + y1 * y1;
	    s21 = x2 * x2 + y1 * y1;
	    s12 = x1 * x1 + y2 * y2;
	    s22 = x2 * x2 + y2 * y2;
	    if (s11 > 1.0 && s12 > 1.0 && s21 > 1.0 && s22 > 1.0)
		row[x] = (float) 0.0;
	    else if (s11 < 1.0 && s12 < 1.0 && s21 < 1.0 && s22 < 1.0)
		row[x] = (float) (255.0*(1.0-(y1 +0.5/ay)*(y1 +0.5/ay)-(x1 +0.5/ax)*(x1 +0.5/ax)));
	    else
	    {
		int     n = 32, k, l;
		double  sum = 0.0, dx, dy;

		dx = 1.0 / (n * ax);
		dy = 1.0 / (n * ay);
		for (k = 0; k < n; k++)
		{
		    double  xk = x1 + k * dx;

		    for (l = 0; l < n; l++)
		    {
			double  yl = y1 + l * dy;

			if (xk * xk + yl * yl < 1.0)
			    sum += (1.0-xk * xk - yl * yl);
		    }
		}
		row[x] = (float) (sum * 255.0 / (n * n));
	    }
	}
	im_put_rowf(row, im, y, 0, width);
    }

    fvector_free((void *) row, 0);
    return (im);
}

Imrect *imf_subpix_algebraic(int width, int height, double (*f) ( /* ??? */ ), void *data)
{
    float  *row;
    Imrect *im = im_alloc(height, width, (Imregion *) NULL, float_v);
    Imrect *im1 = im_alloc(height + 1, width + 1, (Imregion *) NULL, float_v);
    int     x, y;

    row = fvector_alloc(0, width + 1);
    for (y = 0; y < height + 1; y++)
    {
	for (x = 0; x < width + 1; x++)
	    row[x] = (float) f((double) x, (double) y, data);;
	im_put_rowf(row, im1, y, 0, width + 1);
    }

    for (y = 0; y < height; y++)
    {
	for (x = 0; x < width; x++)
	{
	    double  s11 = IM_FLOAT(im1, y, x);
	    double  s12 = IM_FLOAT(im1, y + 1, x);
	    double  s21 = IM_FLOAT(im1, y, x + 1);
	    double  s22 = IM_FLOAT(im1, y + 1, x + 1);

	    if (s11 > 0.0 && s12 > 0.0 && s21 > 0.0 && s22 > 0.0)
		row[x] = (float) 0.0;
	    else if (s11 < 0.0 && s12 < 0.0 && s21 < 0.0 && s22 < 0.0)
		row[x] = (float) 255.0;
	    else
	    {
		int     n = 16, k, l;
		double  sum = 0.0, dx, dy;

		dx = 1.0 / n;
		dy = 1.0 / n;
		for (k = 0; k < n; k++)
		{
		    double  xk = x + k * dx;

		    for (l = 0; l < n; l++)
		    {
			double  yl = y + l * dy;

			if (f(xk, yl, data) < 0.0)
			    sum += 1.0;
		    }
		}
		row[x] = (float) (sum * 255.0 / (n * n));
	    }
	}
	im_put_rowf(row, im, y, 0, width);
    }

    im_free(im1);
    fvector_free((void *) row, 0);
    return (im);
}

static double cx0, cy0, cos0, sin0, ax0, ay0, ex0, ey0;

static double sellipse(double x, double y)
{
    double  x0, y0;

    x -= cx0;
    y -= cy0;
    x0 = x * cos0 + y * sin0;
    y0 = -x * sin0 + y * cos0;
    x0 /= ax0;
    y0 /= ay0;
    x0 = fabs(x0);
    y0 = fabs(y0);
    return (pow(x0, ex0) + pow(y0, ey0) - 1.0);
}

Imrect *imf_subpix_sellipse(int width, int height, double cx, double cy, double theta, double ax, double ay, double ex, double ey)
{
    cx0 = cx;
    cy0 = cy;
    ax0 = ax;
    ay0 = ay;
    ex0 = ex;
    ey0 = ey;
    cos0 = cos(theta);
    sin0 = sin(theta);
    return (imf_subpix_algebraic(width, height, sellipse, NULL));
}

Imrect *imf_delta(int width, int height, double cx, double cy)
{
    Imrect *im = im_alloc(height, width, (Imregion *) NULL, float_v);
    int     x = (int) (cx + 0.5);
    int     y = (int) (cy + 0.5);

    im_put_pixf(255.0, im, y, x);
    return (im);
}

Imrect *imf_unif_noise(int width, int height, int dx, int dy, double a, double b)
{
    float  *row;
    Imrect *im = im_alloc(height, width, (Imregion *) NULL, float_v);
    int     i, x, y;

    row = fvector_alloc(0, width);
    for (y = 0; y < height; y += dy)
    {
	for (x = 0; x < width; x += dx)
	{
	    float   g = (float) rand_unif(a, b);

	    for (i = 0; i < dx && x + i < width; i++)
		row[x + i] = g;
	}
	for (i = 0; i < dy && y + i < height; i++)
	    im_put_rowf(row, im, y + i, 0, width);
    }

    fvector_free((void *) row, 0);
    return (im);
}

Imrect *im_corrupt(Imrect * im, int dx, int dy, double a, double b)
{
    Imrect *noise = imf_unif_noise(im->width, im->height, dx, dy,
				   a, b);
    Imrect *im1;

    im1 = im_sum(im, noise);
    im_free(noise);
    return (im1);
}
