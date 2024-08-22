/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* get exactly n knots along string that references POS2 data */

void    str2_get_knots(Tstring * es, int n, double *x, double *y)
{
    Ddlist *ptr;
    int     i, j;
    double  l, dl;

    l = es->count;
    switch (es->type)
    {
    case STRING:
	dl = (l - 1.0) / (n - 1);
	break;
    case LOOP:
	dl = (l - 1.0) / n;
	break;
    }

    for (i = 0, j = 0, ptr = es->start; j < n; i++, ptr = ptr->next)
    {
	if (i >= j * dl || (es->type == STRING && ptr == es->end))
	{
	    Vec2    v = {Vec2_id};

	    DD_GET_POS2(ptr, v);
	    x[j] = vec2_x(v);
	    y[j] = vec2_y(v);
	    j++;
	}
    }
}


/* get exactly n knots along string that references Vec3 data */

void    str3_get_knots(Tstring * es, int n, double *x, double *y, double *z)
{
    Ddlist *ptr;
    int     i, j;
    double  l, dl;

    l = es->count;
    switch (es->type)
    {
    case STRING:
	dl = (l - 1.0) / (n - 1);
	break;
    case LOOP:
	dl = (l - 1.0) / n;
	break;
    }

    for (i = 0, j = 0, ptr = es->start; j < n; i++, ptr = ptr->next)
    {
	if (i >= j * dl || (es->type == STRING && ptr == es->end))
	{
	    Vec3   *v = (Vec3 *) ptr->to;

	    x[j] = vec3_x(*v);
	    y[j] = vec3_y(*v);
	    z[j] = vec3_z(*v);
	    j++;
	}
    }
}
