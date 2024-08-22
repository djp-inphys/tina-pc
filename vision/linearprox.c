/**@(#)
**/
#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

#define INIT_SAMPLE 12

static double line_sqrdist(Vec2 q, Vec2 p, Vec2 v)	/* point q to line (p v) */

{
    Vec2    dq = {Vec2_id};

    dq = vec2_projperp(vec2_diff(q, p), v);
    return (vec2_sqrmod(dq));
}

static Bool line_check(Vec2 p, Vec2 v, Ddlist * start, Ddlist * end, int max_diverge, double thres)
{
    Vec2    pos = {Vec2_id};
    Ddlist *dptr;
    int     misses = 0;
    double  thres2 = 2 * thres;

    for (dptr = start;; dptr = dptr->next)
    {
	double  sep;

	DD_GET_POS2(dptr, pos);
	sep = line_sqrdist(pos, p, v);
	if (sep > thres2)
	    break;
	if (sep > thres)
	    ++misses;
	else
	    misses = 0;
	if (misses > max_diverge)
	    return (false);
	if (dptr == end)
	    break;
    }
    return (true);
}

static int line_count(Vec2 p, Vec2 v, Ddlist * start, Ddlist * end, int sample, double thres)
{
    Vec2    q = {Vec2_id};
    int     i, count = 0;
    Ddlist *dptr;

    for (dptr = start;;)
    {
	DD_GET_POS2(dptr, q);
	if (line_sqrdist(q, p, v) < thres)
	    ++count;

	if (dptr == end)
	    break;

	for (i = 0; i < sample; ++i, dptr = dptr->next)
	    if (dptr == end)
		break;
    }
    return (count);
}

static void line_grow(Vec2 p, Vec2 v, Ddlist * start, Ddlist * end, Ddlist ** p1, Ddlist ** p2, int max_diverge, double thres)
{
    Ddlist *m1 = *p1;
    Ddlist *m2 = *p2;
    Ddlist *ptr;
    Vec2    pos = {Vec2_id};
    int     misses;

    misses = 0;
    for (ptr = m1; ptr != start;)
    {
	ptr = ptr->last;
	DD_GET_POS2(ptr, pos);
	if (line_sqrdist(pos, p, v) < thres)
	{
	    misses = 0;
	    m1 = ptr;
	} else
	    ++misses;
	if (misses > max_diverge)
	    break;
    }

    misses = 0;
    for (ptr = m2; ptr != end;)
    {
	ptr = ptr->next;
	DD_GET_POS2(ptr, pos);
	if (line_sqrdist(pos, p, v) < thres)
	{
	    misses = 0;
	    m2 = ptr;
	} else
	    ++misses;
	if (misses > max_diverge)
	    break;
    }

    *p1 = m1;
    *p2 = m2;
}

Ddlist *linear_prox(Ddlist * start, Ddlist * end, float thres, int sample)
{
    Ddlist *p1;
    Ddlist *p2;
    Ddlist *pm;
    Ddlist *m1;
    Ddlist *m2;
    Ddlist *list1 = NULL;
    Ddlist *list2 = NULL;
    Line2  *line = NULL;
    double  thres_sqr = thres * thres;
    Vec2    q = {Vec2_id};
    Vec2    p = {Vec2_id};
    Vec2    v = {Vec2_id};
    int     i, max_diverge, maxcount = 0;

    if (start == NULL || end == NULL || start == end)
	return (NULL);

    if (ddstr_count(start, end) < 5)
	return (poly_prox(start, end, thres));

    p1 = start;
    p2 = ddstr_nth_point(start, end, 2 * sample + 1);
    if (p2 == NULL)
	p2 = end;
    pm = ddstr_mid_point(p1, p2);
    max_diverge = sample / 3;
    if (max_diverge == 0)
	max_diverge = 1;

    while (1)
    {
	DD_GET_POS2(p1, p);
	DD_GET_POS2(p2, q);
	v = vec2_unit(vec2_diff(q, p));
	DD_GET_POS2(pm, q);

	if (line_sqrdist(q, p, v) < thres_sqr &&
	    line_check(p, v, p1, p2, max_diverge, thres_sqr))
	{
	    int     count = line_count(p, v, start, end, sample / 2, thres_sqr);

	    if (count > maxcount)
	    {
		maxcount = count;
		m1 = p1;
		m2 = p2;
	    }
	}
	if (p2 == end)
	    break;

	for (i = 0; i < sample; ++i)
	{
	    p1 = p1->next;
	    pm = pm->next;
	    p2 = p2->next;
	    if (p2 == end)
		break;
	}
    }

    if (maxcount > 2)
    {
	DD_GET_POS2(m1, p);
	DD_GET_POS2(m2, q);
	v = vec2_unit(vec2_diff(q, p));
	line_grow(p, v, start, end, &m1, &m2, max_diverge, thres_sqr);
	line = line2_fit_and_grow(&m1, &m2, start, end, thres);
    }
    if (line == NULL)		/* failed */
    {
	sample /= 2;
	if (sample >= 3)
	    return (linear_prox(start, end, thres, sample));
	return (poly_prox(start, end, thres));
    }
    if (start->last == end && end->next == start)	/* A LOOP */
    {
	line2_free(line);	/* ignore this line and start again */
	if (ddstr_length(start, m1) < ddstr_length(m2, end))
	    return (linear_prox(m2->next, m2->last, thres, sample));
	else
	    return (linear_prox(m1->next, m1->last, thres, sample));
    }
    if (m1 != start)
	list1 = linear_prox(start, m1, thres, sample);

    if (m2 != end)
	list2 = linear_prox(m2, end, thres, sample);

    return (dd_append(list1, dd_append(dd_link_alloc((void *) line, LINE2), list2)));
}

Tstring *linear_string(Tstring * string, double thres)
{
    Ddlist *linear;

    if (string == NULL)
	return (NULL);

    linear = linear_prox(string->start, string->end, (float)thres, INIT_SAMPLE);

    if (linear == NULL)
	return (NULL);

    return (str_make(STRING, linear, dd_get_end(linear)));
}

List   *linear_strings(List * strings, double thres)
{
    List   *sptr;
    List   *splist = NULL;

    for (sptr = strings; sptr != NULL; sptr = sptr->next)
    {
	Tstring *string = linear_string((Tstring *) sptr->to, thres);

	splist = ref_addtostart((List *) splist, (void *) string, STRING);
    }
    return (splist);
}
