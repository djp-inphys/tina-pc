/**@(#)
**/
#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

/* Accepts either edgel or vec2 Ddlists */
Ddlist *poly_prox(Ddlist * start, Ddlist * end, double thres)
{
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    Vec2    v = {Vec2_id};
    Ddlist *dptr;
    Ddlist *dmax;
    double  length, perp, maxperp;
    Line2  *line2_between();

    if (start == NULL || end == NULL || start == end)
	return (NULL);

    DD_GET_POS2(start, p1);
    DD_GET_POS2(end, p2);
    length = vec2_mod(vec2_diff(p2,p1));
    v = vec2_unit(vec2_diff(p2, p1));

    dmax = NULL;
    maxperp = 0;
    for (dptr = start->next; dptr != end; dptr = dptr->next)
    {
	Vec2    p = {Vec2_id};

	DD_GET_POS2(dptr, p);
	perp = vec2_mod(vec2_projperp(vec2_diff(p, p1), v));
	if (perp > maxperp)
	{
	    maxperp = perp;
	    dmax = dptr;
	}
    }

    if (maxperp/length < thres)
	return (dd_link_alloc((void *) line2_between(start, end), LINE2));

    return (dd_append(poly_prox(start, dmax, thres), poly_prox(dmax, end, thres)));
}

Tstring *poly_string(Tstring * string, double thres)
{
    Ddlist *poly;

    if (string == NULL)
	return (NULL);

    poly = poly_prox(string->start, string->end, thres);

    if (poly == NULL)
	return (NULL);

    return (str_make(STRING, poly, dd_get_end(poly)));
}

List   *poly_strings(List * strings, double thres)
{
    List   *sptr;
    List   *splist = NULL;

    for (sptr = strings; sptr != NULL; sptr = sptr->next)
    {
	Tstring *string = poly_string((Tstring *) sptr->to, thres);

	splist = ref_addtostart((List *) splist, (void *) string, STRING);
    }
    return (splist);
}
