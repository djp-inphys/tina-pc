/**@(#)
**/
/* splines.c
 * 
 * functions to take strings of 2d positions and return various forms of
 * spline fit through them
 * 
 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

/* function to take a string of pos2 (referenced through the DD_GET_POS
 * macro) and return a string of Vec2 representation of the
 * interpolated conic spline */

Tstring *str_ics2(Tstring * str, int knot_sample, double str_space, double *a, double *b)
/* string of pos2 */
/* sample of underlying spline */
/* with respect to units of underlying string */
/* end point derivetive conditions: NULL for natural */
{
    Ddlist *ptr;
    Ddlist *start;
    Ddlist *end;
    int     i, nknots;
    float  *t, *x, *y, *x2, *y2;
    float   s, sum;
    Vec2    p = {Vec2_id};
    Vec2    p_last = {Vec2_id};

    if (str == NULL || str->start == str->end || str->start == NULL)
	return (NULL);

    nknots = str->count / knot_sample + 2;	/* maximum possible size */
    start = str->start;
    end = str->end;

    t = fvector_alloc(0, nknots);
    x = fvector_alloc(0, nknots);
    y = fvector_alloc(0, nknots);
    x2 = fvector_alloc(0, nknots);
    y2 = fvector_alloc(0, nknots);

    DD_GET_POS2(start, p_last);
    for (nknots=0, sum=(float)0.0, i=0, ptr=start;; ptr=ptr->next, i++)
    {
	if (i % knot_sample == 0 || ptr == end)
	{
	    DD_GET_POS2(ptr, p);
	    x[nknots] = vec2_x(p);
	    y[nknots] = vec2_y(p);
	    sum += (float) vec2_mod(vec2_diff(p, p_last));
	    t[nknots] = sum;
	    nknots++;
	    p_last = p;
	    if (ptr == end)
		break;
	}
    }

    spl_ci_sbp(t, x, nknots, a, b, x2);
    spl_ci_sbp(t, y, nknots, a, b, y2);

    start = NULL;
    for (s = t[0]; s <= sum; s += (float)str_space)
    {
	vec2_x(p) = (float) spl_ci_val(t, x, x2, nknots, s);
	vec2_y(p) = (float) spl_ci_val(t, y, y2, nknots, s);
	start = dd_ref_addtostart(start, (void *) vec2_make(p), VEC2);
    }

    if (start == NULL)
	return (NULL);

    start = dd_list_reverse(start);
    end = dd_get_end(start);

    fvector_free((void *) t, 0);
    fvector_free((void *) x, 0);
    fvector_free((void *) y, 0);
    fvector_free((void *) x2, 0);
    fvector_free((void *) y2, 0);

    return (str_make(STRING, start, end));
}
