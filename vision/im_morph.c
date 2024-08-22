/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

void    morph_spere(double r, Imrect ** el_val)
/* radius about origin */
{
    int     lx, ly, ux, uy;
    int     i, j;
    double  rsq;
    Imregion *roi;

    lx = ly = (int) -r;
    ux = uy = (int) (r + 1);
    roi = roi_alloc(lx, ly, ux, uy);

    *el_val = im_alloc(uy, ux, roi, float_v);
    rfree((void *) roi);

    rsq = r * r;

    for (i = ly; i < uy; ++i)
	for (j = lx; j < ux; ++j)
	{
	    int     d = i * i + j * j;

	    if (d > rsq)
	    {
	        IM_FLOAT(*el_val, i, j) = (float) 0.0;
		continue;
	    }
	    IM_FLOAT(*el_val, i, j) = (float) sqrt(rsq - d);
	}
}

Imrect *imf_dilate(Imrect * im1, Imrect * el_val)
/* image to be dilated */
/* value of dilation mask zero value external to the mask */
{
    Imrect *im2;
    Vartype vtype;
    Imregion *roi;
    double  val;
    int     lx, ux, ly, uy;
    int     m_lx, m_ux, m_ly, m_uy;
    int     i, j;

    if (im1 == NULL || el_val == NULL)
	return (NULL);

    roi = el_val->region;
    if (roi == NULL)
	return (NULL);
    m_lx = roi->lx;
    m_ux = roi->ux;
    m_ly = roi->ly;
    m_uy = roi->uy;

    roi = im1->region;
    if (roi == NULL)
	return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    vtype = (el_val == NULL) ? im1->vtype : (Vartype) MAX((int) im1->vtype, (int) el_val->vtype);
    im2 = im_alloc(im1->height, im1->width, roi, vtype);

    for (i = ly; i < uy; ++i)
	for (j = lx; j < ux; ++j)
	{
	    double  gl, max_gl = 0;
	    int     ii, jj;
	    int     not_set = 1;

	    for (ii = m_ly; ii < m_uy; ++ii)
		for (jj = m_lx; jj < m_ux; ++jj)
		{
		    int     x = j + jj, y = i + ii;

		    if (x >= lx && x < ux && y >= ly && y < uy)	/* in image */
		    {
   	                IM_PIX_GET(el_val, ii, jj, val);
                        if (val==0.0) continue;
			IM_PIX_GET(im1, y, x, gl);

		        gl += val;
			if (not_set || gl > max_gl)
			{
			    max_gl = gl;
			    not_set = 0;
			}
		    }
		}

	    IM_PIX_SET(im2, i, j, max_gl);
	}

    return (im2);
}

Imrect *imf_erode(Imrect * im1, Imrect * el_val)
/* image to be eroded */
/* value of dilation mask non-zero for active region */
{
    Imrect *im2;
    Vartype vtype;
    Imregion *roi;
    double  val;
    int     lx, ux, ly, uy;
    int     m_lx, m_ux, m_ly, m_uy;
    int     i, j;

    if (im1 == NULL || el_val==NULL)
	return (NULL);

    roi = el_val->region;
    if (roi == NULL)
	return (NULL);
    m_lx = roi->lx;
    m_ux = roi->ux;
    m_ly = roi->ly;
    m_uy = roi->uy;

    roi = im1->region;
    if (roi == NULL)
	return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    vtype = (el_val == NULL) ? im1->vtype : (Vartype) MAX((int) im1->vtype, (int) el_val->vtype);
    im2 = im_alloc(im1->height, im1->width, roi, vtype);

    for (i = ly; i < uy; ++i)
	for (j = lx; j < ux; ++j)
	{
	    double  gl, min_gl = 0;
	    int     ii, jj;
	    int     not_set = 1;

	    for (ii = m_ly; ii < m_uy; ++ii)
		for (jj = m_lx; jj < m_ux; ++jj)
		{
		    int     x = j + jj, y = i + ii;

		    if (x >= lx && x < ux && y >= ly && y < uy)	/* in image */
		    {
			IM_PIX_GET(el_val, ii, jj, val);
                        if (val==0.0) continue;
			IM_PIX_GET(im1, y, x, gl);
			gl -= val;
			if (not_set || gl < min_gl)
			{
			    min_gl = gl;
			    not_set = 0;
			}
		    }
		}

	    IM_PIX_SET(im2, i, j, min_gl);
	}

    return (im2);
}
