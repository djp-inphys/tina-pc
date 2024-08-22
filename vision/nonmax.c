/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>


/* nonmax.c
 * 
 * locate directional peak in gradsq image of type float using non maximal
 * suppresion and form appropriate edge rect
 * 
 * fit is performed to sub pixel acuity using quadratic fit across peak in
 * quantised direction
 * 
 * if sub pix falls outside pixel ignore it
 * 
 */

Imrect *nonmaxsup(Imrect * gradx, Imrect * grady, Imrect * gradsq, double thres)
{
    Imrect *edge_image;
    Imregion *region;
    int     i, j;
    int     lx, ux, ly, uy;
    int     uxm1, uym1;
    float   sqthres = (float)(thres * thres);
    float  *rowx, *rowy;
    float  *grad, *grad_m1, *grad_p1;

    if (gradx == NULL || grady == NULL || gradsq == NULL)
	return (NULL);

    region = gradsq->region;

    edge_image = im_alloc(gradsq->height, gradsq->width, region, ptr_v);
    region = edge_image->region;

    lx = region->lx;
    ux = region->ux;
    ly = region->ly;
    uy = region->uy;

    uxm1 = ux - 1;
    uym1 = uy - 1;

    rowx = fvector_alloc(lx, ux);
    rowy = fvector_alloc(lx, ux);
    grad = fvector_alloc(lx, ux);
    grad_m1 = fvector_alloc(lx, ux);
    grad_p1 = fvector_alloc(lx, ux);

    for (i = ly + 1; i < uym1; ++i)
    {
	im_get_rowf(rowy, grady, i, lx, ux);
	im_get_rowf(rowx, gradx, i, lx, ux);
	im_get_rowf(grad, gradsq, i, lx, ux);
	im_get_rowf(grad_p1, gradsq, i + 1, lx, ux);
	im_get_rowf(grad_m1, gradsq, i - 1, lx, ux);

	for (j = lx + 1; j < uxm1; ++j)
	{
	    float   a, b;
	    float   st;
	    float   del;
	    float   dr, dc;
	    float   gradratio, fabsgradratio;
	    Edgel  *eptr;
	    Edgel  *edge_alloc();
	    Vec2    pos = {Vec2_id};

	    if (grad[j] < sqthres)
		continue;

	    st = grad[j];
	    gradratio = rowx[j] / rowy[j];
	    fabsgradratio = (float)fabs(gradratio);
	    if (fabsgradratio < 1.5 && fabsgradratio > 0.67)	/* diagonal */
	    {
		if ((st < grad[j - 1] || st <= grad[j + 1]) &&
		    (st < grad_m1[j] || st <= grad_p1[j]))
		    continue;
		if (gradratio > 0)	/* right diagonal */
		{
		    if (st < grad_m1[j - 1] || st <= grad_p1[j + 1])
			continue;
		    st = (float)sqrt(st);
		    a = (float)sqrt(grad_m1[j - 1]);
		    b = (float)sqrt(grad_p1[j + 1]);
		    del = (a - b) / ((a + b - st * 2) * 2);
		    dr = (float)(del + 0.5);
		    dc = (float)(del + 0.5);
		} else
		{
		    if (st < grad_p1[j - 1] || st <= grad_m1[j + 1])
			continue;
		    st = (float)sqrt(st);
		    a = (float)sqrt(grad_p1[j - 1]);
		    b = (float)sqrt(grad_m1[j + 1]);
		    del = (a - b) / ((a + b - st * 2) * 2);
		    dr = (float)(0.5 - del);
		    dc = (float)(del + 0.5);
		}
	    } else if (fabs(rowx[j]) > fabs(rowy[j]))
	    {
		if (st < grad[j - 1] || st <= grad[j + 1])
		    continue;
		st = (float)sqrt(st);
		a = (float)sqrt(grad[j - 1]);
		b = (float)sqrt(grad[j + 1]);
		del = (a - b) / ((a + b - st * 2) * 2);
		dr = (float)0.5;
		dc = (float)(del + 0.5);
	    } else
	    {
		if (st < grad_m1[j] || st <= grad_p1[j])
		    continue;
		st = (float)sqrt(st);
		a = (float)sqrt(grad_m1[j]);
		b = (float)sqrt(grad_p1[j]);
		del = (a - b) / ((a + b - st * 2) * 2);
		dr = (float)(del + 0.5);
		dc = (float)0.5;	/* pixel centre */
	    }

	    {
		int     ii, jj;	/* actual storage location */

		pos = vec2(j + dc, i + dr);
		jj = (int)floor(vec2_x(pos));
		ii = (int)floor(vec2_y(pos));
		if (ii < ly || ii >= uy || jj < lx || jj >= ux ||
		    IM_PTR(edge_image, ii, jj) != NULL)
		    continue;

		eptr = edge_alloc(EDGE_RAW);
		eptr->pos = pos;
		eptr->orient = (float)atan2(rowx[j], rowy[j]);
		eptr->contrast = st;
		IM_PTR(edge_image, ii, jj) = (void *) eptr;
	    }
	}
    }
    fvector_free((void *) rowx, lx);
    fvector_free((void *) rowy, lx);
    fvector_free((void *) grad, lx);
    fvector_free((void *) grad_m1, lx);
    fvector_free((void *) grad_p1, lx);
    return (edge_image);
}
