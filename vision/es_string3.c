/**@(#)
**/
/* es_string3.c
 * 
 * build a string of 3d disparity points from an approximation to a curve
 * and a string of edges
 * 
 * the curve is a suitable approx to the edge string found by a spline or
 * conic fitter say
 * 
 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Tstring *es_par_proj_to_plane(Tstring * es, Plane * plane)
{
    Tstring *str3;
    Ddlist *ptr;
    Ddlist *end;
    Vec3    p = {Vec3_id};
    Vec3    n = {Vec3_id};

    if (es == NULL || plane == NULL)
	return (NULL);

    p = plane->p;
    n = plane->n;
    str3 = str_clone(es);
    ptr = str3->start;
    end = str3->end;

    do
    {
	Vec3    v = {Vec3_id};
	Vec3    o = {Vec3_id};
	Vec2    pos = {Vec2_id};

	DD_GET_POS2(ptr, pos);
	par_proj_ray(pos, &o, &v);
	ptr->to = vec3_make(vec3_inter_line_plane(o, v, p, n));
	ptr->type = VEC3;
	if (ptr == end)
	    break;
	ptr = ptr->next;
    } while (1);
    return (str3);
}

static Vec3 *disp_pos3(Vec2 p, Vec2 p1, Vec2 p2)
{
    Vec2    v = {Vec2_id};
    float   x;

    v = vec2_unit(vec2_diff(p2, p1));
    x = vec2_x(p1) + (vec2_y(p) - vec2_y(p1)) * vec2_x(v) / vec2_y(v);
    return (vec3_make(vec3(x, vec2_y(p), vec2_x(p) - x)));
}

static Vec3 *cv_approx3_next(Ddlist * curv, Vec2 pos, Ddlist * end)
{
    Vec2    cpos = {Vec2_id};
    Vec2    npos = {Vec2_id};
    Ddlist *ptr;

    DD_GET_POS2(curv, cpos);

    for (ptr = curv;; ptr = ptr->next)
    {
	DD_GET_POS2(ptr, npos);
	if (BETWEEN(vec2_y(pos), vec2_y(cpos), vec2_y(npos)))
	    return (disp_pos3(pos, cpos, npos));

	if (ptr == end)
	    break;
    }
    return (NULL);
}

static Vec3 *cv_approx3_last(Ddlist * curv, Vec2 pos, Ddlist * start)
{
    Vec2    cpos = {Vec2_id};
    Vec2    lpos = {Vec2_id};
    Ddlist *ptr;

    DD_GET_POS2(curv, cpos);

    for (ptr = curv;; ptr = ptr->last)
    {
	DD_GET_POS2(ptr, lpos);
	if (BETWEEN(vec2_y(pos), vec2_y(cpos), vec2_y(lpos)))
	    return (disp_pos3(pos, cpos, lpos));

	if (ptr == start)
	    break;
    }
    return (NULL);
}

Vec3   *cv_approx3(Ddlist * curv, Vec2 pos, Ddlist * start, Ddlist * end)
{
    Vec2    cpos = {Vec2_id};
    Vec2    npos = {Vec2_id};
    Vec2    lpos = {Vec2_id};

    if (curv == NULL || (curv->last == NULL && curv->next == NULL))
	return (NULL);

    if (curv == start)
	return (cv_approx3_next(curv, pos, end));
    if (curv == end)
	return (cv_approx3_last(curv, pos, start));

    DD_GET_POS2(curv, cpos);
    DD_GET_POS2(curv->last, lpos);
    DD_GET_POS2(curv->next, npos);

    if ((vec2_y(cpos) < vec2_y(lpos)) == (vec2_y(cpos) < vec2_y(npos)))	/* ambiguous */
	return (NULL);

    if ((vec2_y(cpos) < vec2_y(pos)) == (vec2_y(cpos) < vec2_y(npos)))	/* go next */
	return (cv_approx3_next(curv, pos, end));
    if ((vec2_y(cpos) < vec2_y(pos)) == (vec2_y(cpos) < vec2_y(lpos)))	/* go last */
	    return (cv_approx3_last(curv, pos, start));
    return (NULL);		/* strange occurance */
}

/* build a fast index into the string structure */
static Rindex *string_index_get(Tstring * es)
{
    Imregion *roi = es_bounding_region(es);
    Ddlist *end;
    Ddlist *ptr;
    Rindex *rx;
    List  **index;

    if (roi == NULL)
	return (NULL);

    rx = rx_alloc(roi, STRING);
    rfree((void *) roi);
    index = (List **) rx->index;
    ptr = es->start;
    end = es->end;

    do
    {
	Vec2    p = {Vec2_id};
	int     i;

	DD_GET_POS2(ptr, p);
	i = (int)floor(vec2_y(p));
	index[i] = ref_addtostart(index[i], (void *) ptr, DDLIST);
	if (ptr == end)
	    break;
	ptr = ptr->next;
    } while (1);
    return (rx);
}

#define SEARCH_WINDOW  3
#define MAX_ALLOW_DIFF 5.0

static Ddlist *closest_in_index(Rindex * rx, Vec2 pos)
{
    int     r, i;
    Ddlist *closest = NULL;
    Imregion *roi;
    List   *ptr;
    Vec2    p = {Vec2_id};
    float   dist;
    float   min_dist = (float)0.0;

    if (rx == NULL)
	return (NULL);

    roi = rx->region;

    r = (int)floor(vec2_y(p));
    i = r - SEARCH_WINDOW;
    if (i < roi->ly)
	i = roi->ly;
    r += SEARCH_WINDOW;
    if (r > roi->uy)
	r = roi->uy;

    while (i < r)
    {
	for (ptr = rx->index[i]; ptr != NULL; ptr = ptr->next)
	{
	    Ddlist *dd = (Ddlist *) ptr->to;

	    DD_GET_POS2(dd, p);

	    dist = (float)vec2_mod(vec2_diff(pos, p));
	    if (dist < MAX_ALLOW_DIFF && (closest == NULL || dist < min_dist))
	    {
		min_dist = dist;
		closest = dd;
	    }
	}
	++i;
    }
    return (closest);
}

Tstring *es_build_string3(Tstring * curv, Tstring * es)
/* approximated geometrical string (not always edge) */
/* associated edge string */
{
    List   *mlist;
    List   *mptr;
    Ddlist *dispstr = NULL;
    Ddlist *start;
    Ddlist *end;
    Rindex *rx;

    if (curv == NULL || es == NULL)
	return (NULL);

    /* get list of matches unique in ->to2  ordered along list */
    mlist = es_get_list_of_matches(es);
    rx = string_index_get(curv);/* index string */

    start = curv->start;
    end = curv->end;

    for (mptr = mlist; mptr != NULL; mptr = mptr->next)
    {
	Ddlist *dptr;
	Ddlist *closest;
	Tstring *s1, *s2;
	Vec2    p = {Vec2_id};

	s1 = (Tstring *) ((Match *) mptr->to)->to1;
	s2 = (Tstring *) ((Match *) mptr->to)->to2;

	p = DD_EDGE_POS(s1->start);
	closest = closest_in_index(rx, p);
	if (closest == NULL)
	    closest = str_get_min(curv, dist_to_pos2, (void *) &p);	/* slow */

	for (dptr = s2->start;; dptr = dptr->next)
	{
	    Vec3   *p;

	    p = cv_approx3(closest, DD_EDGE_POS(dptr), start, end);
	    if (p != NULL)
		dispstr = dd_ref_addtostart(dispstr, (void *) p, VEC3);
	    if (dptr == s2->end)
		break;
	}
    }
    rx_free_links(rx);		/* free sting index */
    if (dispstr == NULL)
	return (NULL);
    return (str_make(STRING, dispstr, dd_get_end(dispstr)));
}

Tstring *es_build_string4(Tstring * curv, Tstring * es)
/* approximated geometrical string (not always edge) */
/* associated edge string */
{
    List   *mlist;
    List   *mptr;
    Ddlist *dispstr = NULL;
    Ddlist *start;
    Ddlist *end;
    Rindex *rx;

    if (curv == NULL || es == NULL)
	return (NULL);

    /* get list of matches unique in ->to2  ordered along list */
    mlist = es_get_list_of_matches(es);
    rx = string_index_get(curv);/* index string */

    start = curv->start;
    end = curv->end;

    for (mptr = mlist; mptr != NULL; mptr = mptr->next)
    {
	Ddlist *dptr;
	Ddlist *closest;
	Tstring *s1, *s2;
	Vec2    p = {Vec2_id};

	s1 = (Tstring *) ((Match *) mptr->to)->to1;
	s2 = (Tstring *) ((Match *) mptr->to)->to2;

	p = DD_EDGE_POS(s1->start);
	closest = closest_in_index(rx, p);
	if (closest == NULL)
	    closest = str_get_min(curv, dist_to_pos2, (void *) &p);	/* slow */

	for (dptr = s2->start;; dptr = dptr->next)
	{
	    Edgel  *edge = DD_EDGE(dptr);
	    Vec3   *p3;
	    Vec4   *p4;

	    p3 = cv_approx3(closest, edge->pos, start, end);
	    if (p3 != NULL)
	    {
		p4 = vec4_alloc();
		*(Vec3 *) p4 = *p3;
		vec4_w(*p4) = edge->orient;
		dispstr = dd_ref_addtostart(dispstr, (void *) p4, VEC4);
		rfree((void *) p3);
	    }
	    if (dptr == s2->end)
		break;
	}
    }
    rx_free_links(rx);		/* free string index */
    if (dispstr == NULL)
	return (NULL);
    return (str_make(STRING, dispstr, dd_get_end(dispstr)));
}
