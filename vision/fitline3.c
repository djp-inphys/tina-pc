/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

#define DISP_THRES 1.0
#define DISP_GRAD 1.0
#define RASTER_THRES 1.0
#define HORIZ_THRES 0.995

static Tstring *form_disp_str(Line2 * line2)
{
    Tstring *es;
    Ddlist *dispstr = NULL;
    List   *mlist;
    List   *mptr;
    Vec2    v = {Vec2_id};
    Vec2    p = {Vec2_id};

    if (line2 == NULL)
	return (NULL);

    v = line2->v;
    p = line2->p1;
    es = (Tstring *) prop_get(line2->props, STRING);
    if (es == NULL)
	return (NULL);

    mlist = es_get_list_of_matches(es);
    for (mptr = mlist; mptr != NULL; mptr = mptr->next)
    {
	Ddlist *dptr;
	Ddlist *end;

	es = (Tstring *) ((Match *) mptr->to)->to2;
	end = es->end;
	for (dptr = es->start;; dptr = dptr->next)
	{
	    Vec2    pm = {Vec2_id};
	    Vec2   *pdisp = ts_ralloc(Vec2);
	    float   x, y, d;

	    pm = DD_EDGE_POS(dptr);
	    y = vec2_y(pm) - vec2_y(p);
	    x = vec2_x(v) * y / vec2_y(v);
	    d = vec2_x(pm) - vec2_x(p) - x;
	    *pdisp = vec2(sqrt(x * x + y * y), d);
	    dispstr = dd_ref_addtostart(dispstr, (void *) pdisp, VEC2);
	    if (dptr == end)
		break;
	}
    }

    dispstr = sort_ddlist(dispstr, vec2_get_x, NULL);
    return (str_make(STRING, dispstr, dd_get_end(dispstr)));
}

Line3  *line3_disp_from2d(Line2 * line2)
{
    Tstring *dispstr;
    Line2  *lined;
    Vec3    p1 = {Vec3_id};
    Vec3    p2 = {Vec3_id};
    Vec2    p = {Vec2_id};

    if (line2 == NULL)
	return (NULL);

    /* test for horizontal 2D line */
    if (fabs(vec2_x(line2->v)) > HORIZ_THRES ||
	fabs(vec2_y(line2->p1) - vec2_y(line2->p2)) < RASTER_THRES)
	return (NULL);

    dispstr = form_disp_str(line2);
    if (dispstr == NULL || dispstr->count < 5)
    {
	str_rm(dispstr, rfree);
	return (NULL);
    }
    lined = line2_best_fit(dispstr->start, dispstr->end, DISP_THRES);
    if (lined == NULL || fabs(vec2_y(lined->v) / vec2_x(lined->v)) > DISP_GRAD)
    {
	line2_free(lined);
	return (NULL);
    }
    p1 = p2 = vec3_of_vec2(line2->p1);
    p = vec2_times(vec2_x(lined->p1), line2->v);	/* 2d offset of p1 */
    p1 = vec3_sum(p1, vec3_of_vec2(p));
    vec3_z(p1) = vec2_y(lined->p1);	/* add disparity */
    p = vec2_times(vec2_x(lined->p2), line2->v);	/* 2d offset of p2 */
    p2 = vec3_sum(p2, vec3_of_vec2(p));
    vec3_z(p2) = vec2_y(lined->p2);	/* add disparity */
    line2_free(lined);
    return (line3_make(p1, p2, DISPARITY));	/* has no string
						 * property */
}

Line3  *line3_from_line2(Line2 * line2)
{
    Line3  *line3;

    if (line2 == NULL)
	return (NULL);

    line3 = line3_disp_from2d(line2);
    line3_par_proj_3d(line3);

    if (line3 == NULL)
	return (NULL);

    line3->props = proplist_add(line3->props, (void *) line2, LINE2,
				(void (*) ()) NULL);
    line2->props = proplist_add(line2->props, (void *) line3, LINE3,
				(void (*) ()) NULL);

    return (line3);
}
