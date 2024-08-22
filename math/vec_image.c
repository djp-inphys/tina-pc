/**@(#)Extracting data from image row or col in vector format
 */

#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

/* return vector of data in row y from lx to ux, cast to vtype */
Vector *im_row_vector(Imrect * im, int y, int lx, int ux, Vartype vtype)
{
    int     x, xmin, xmax;
    Vector *v = vector_alloc(ux - lx, vtype);

    if (v == NULL)
	return (NULL);
    if (im == NULL || y < im->region->ly || y >= im->region->uy)
	return (v);

    xmin = MAX(lx, im->region->lx);
    xmax = MIN(ux, im->region->ux);
    switch (vtype)
    {
    case char_v:
    case uchar_v:
    case short_v:
    case ushort_v:
    case int_v:
    case uint_v:
	{
	    for (x = xmin; x < xmax; x++)
	    {
		double     gl;

		IM_PIX_GET(im, y, x, gl);
		VECTOR_SET(v, x - lx, gl);
	    }
	    break;
	}
    case float_v:
    case double_v:
	{
	    for (x = xmin; x < xmax; x++)
	    {
		double  gl;

		IM_PIX_GET(im, y, x, gl);
		VECTOR_SET(v, x - lx, gl);
	    }
	    break;
	}
    case complex_v:
	{
	    for (x = xmin; x < xmax; x++)
	    {
		Complex gl = {Complex_id};

		IM_PIX_GETZ(im, y, x, gl);
		VECTOR_SETZ(v, x - lx, gl);
	    }
	    break;
	}
    default:
	vector_free(v);
	return (NULL);
    }

    return (v);
}

/* return vector of data in column x from ly to uy, cast to vtype */
Vector *im_col_vector(Imrect * im, int x, int ly, int uy, Vartype vtype)
{
    int     y, ymin, ymax;
    Vector *v = vector_alloc(uy - ly, vtype);

    if (v == NULL)
	return (NULL);
    if (im == NULL || x < im->region->lx || x >= im->region->ux)
	return (v);

    ymin = MAX(ly, im->region->ly);
    ymax = MIN(uy, im->region->uy);
    switch (vtype)
    {
    case char_v:
    case uchar_v:
    case short_v:
    case ushort_v:
    case int_v:
    case uint_v:
	{
	    for (y = ymin; y < ymax; y++)
	    {
		double     gl;

		IM_PIX_GET(im, y, x, gl);
		VECTOR_SET(v, y - ly, gl);
	    }
	    break;
	}
    case float_v:
    case double_v:
	{
	    for (y = ymin; y < ymax; y++)
	    {
		double  gl;

		IM_PIX_GET(im, y, x, gl);
		VECTOR_SET(v, y - ly, gl);
	    }
	    break;
	}
    case complex_v:
	{
	    for (y = ymin; y < ymax; y++)
	    {
		Complex gl = {Complex_id};

		IM_PIX_GETZ(im, y, x, gl);
		VECTOR_SETZ(v, y - ly, gl);
	    }
	    break;
	}
    default:
	vector_free(v);
	return (NULL);
    }

    return (v);
}
