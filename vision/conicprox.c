/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

static int init_sample = 12;
static double min_aratio = 0.2;

void    conic_prox_init_sample_set(int sample)
{
    init_sample = sample;
}

/* approximate square of distance of point p to conic */
static double conic_sqrdist_check(Conic * conic, Vec2 p)
{
    double  t;
    Vec2    pc = {Vec2_id};

    t = conic_param(conic, p);
    pc = conic_point(conic, t);
    return (vec2_sqrdist(p, pc));
}

/* grow the conic along the implicit string between start and end
 * 
 * initial points are given through p1 and p2 (these are updated)
 * 
 * a form of hystersis thresholding is employed
 * 
 * lo_th (low thres) can be exeeded for upto max_div (max divergence) or
 * until hi_th (high thres) is exceeded the point of segmentation is
 * set to the last point lo_th was exceeded */
Bool    conic_grow_string(Conic * conic, Ddlist * start, Ddlist * end, Ddlist ** p1, Ddlist ** p2, double lo_th, double hi_th, int max_div)
{
    Vec2    p = {Vec2_id};
    Ddlist *ptr;
    double  sqr_dist;
    Ddlist *m1 = *p1;
    Ddlist *m2 = *p2;
    Bool    grown = false;

    /** grow backwards **/
    for (ptr = m1; ptr != start;)
    {
	int     misses = 0;

	ptr = ptr->last;
	DD_GET_POS2(ptr, p);
	sqr_dist = conic_sqrdist_check(conic, p);
	if (sqr_dist > hi_th)
	    break;
	if (sqr_dist < lo_th)
	{
	    grown = true;
	    misses = 0;
	    m1 = ptr;
	} else
	    ++misses;
	if (misses > max_div)
	    break;
    }

    /** grow forwards **/
    for (ptr = m2; ptr != end;)
    {
	int     misses = 0;

	ptr = ptr->next;
	DD_GET_POS2(ptr, p);
	sqr_dist = conic_sqrdist_check(conic, p);
	if (sqr_dist > hi_th)
	    break;
	if (sqr_dist < lo_th)
	{
	    grown = true;
	    misses = 0;
	    m2 = ptr;
	} else
	    ++misses;
	if (misses > max_div)
	    break;
    }

    *p1 = m1;
    *p2 = m2;

    if (grown || prop_get(conic->props, STRING) == NULL)
	/** replace string on proplist and reset ends **/
    {
	Vec2    e1 = {Vec2_id};
	Vec2    e2 = {Vec2_id};
	Vec2    emid = {Vec2_id};

	conic->props = proplist_rm(conic->props, STRING);
	conic->props = proplist_add(conic->props,
	  (void *) str_make(STRING, m1, m2), STRING, str_rm_only_str);
	DD_GET_POS2(m1, e1);
	DD_GET_POS2(m2, e2);
	DD_GET_POS2(ddstr_mid_point(m1, m2), emid);
	conic_set_ends(conic, e1, e2, emid);
    }
    return (grown);
}

/* grow the conic along the implicit string between start and end
 * 
 * initial points are given through p1 and p2 (these are updated)
 * 
 * actual growing is done by conic_grow_string
 * 
 * the function iterates throgh new conic fits to the string */
Conic  *conic_grow(Conic * conic, Ddlist * start, Ddlist * end, Ddlist ** p1, Ddlist ** p2, double lo_th, double hi_th, int max_div)
{
    Bool    updated;
    Ddlist *m1 = *p1;
    Ddlist *m2 = *p2;

    do
    {
	Bool    string_grown;

	/** grow start and end along conic **/
	string_grown = conic_grow_string(conic, start, end, &m1, &m2,
					 lo_th, hi_th, max_div);

	if (string_grown)	/** fit a new conic and see if still good **/
	{
	    Conic  *new_conic = ddstr_conic_ellipse_5pt(m1, m2, min_aratio);

	    conic_ellipse_filter(new_conic, m1, m2, min_aratio);

	    if (new_conic != NULL &&
		conic_check(new_conic, m1, m2, lo_th, hi_th, max_div))
	    {
		updated = true;
		conic_free(conic);
		conic = new_conic;
	    } else
	    {
		updated = false;
		if (new_conic != NULL)
		    conic_free(new_conic);
	    }
	} else
	    updated = false;
    } while (updated);

    *p1 = m1;
    *p2 = m2;

    return (conic);
}

/* check that the conic fits the implicit string start and end
 * 
 * a form of hystersis thresholding is employed
 * 
 * lo_th (low thres) can be exeeded for upto max_div (max divergence) or
 * until hi_th (high thres) is exceeded */
Bool    conic_check(Conic * conic, Ddlist * start, Ddlist * end, double lo_th, double hi_th, int max_div)
{
    Vec2    pos = {Vec2_id};
    Ddlist *dptr;
    double  sqr_dist;
    int     misses = 0;

    for (dptr = start;; dptr = dptr->next)
    {
	DD_GET_POS2(dptr, pos);
	sqr_dist = conic_sqrdist_check(conic, pos);
	if (sqr_dist > hi_th)
	    return (false);
	if (sqr_dist > lo_th)
	    ++misses;
	else
	    misses = 0;
	if (misses > max_div)
	    return (false);
	if (dptr == end)
	    break;
    }
    return (true);
}

/* check that the conic fits the list of strings
 * 
 * a form of hystersis thresholding is employed
 * 
 * lo_th (low thres) can be exeeded for upto max_div (max divergence) or
 * until hi_th (high thres) is exceeded
 * 
 * furthermore each string can deviate from the conic close to its
 * endpoints */
Bool    conic_check_list(Conic * conic, List * strings, double lo_th, double hi_th, int max_div)
{
    Vec2    pos = {Vec2_id};
    Ddlist *dptr;
    double  sqr_dist;
    int     misses = 0;
    List   *ptr;

    for (ptr = strings; ptr != NULL; ptr = ptr->next)
    {
	Tstring *str = (Tstring *) ptr->to;
	int     start_div, end_div, i;

	start_div = str->count / 5;
	end_div = str->count - start_div;

	for (i = 0, dptr = str->start; i < start_div; ++i)
	    dptr = dptr->next;

	for (; i < end_div; i++, dptr = dptr->next)
	{
	    DD_GET_POS2(dptr, pos);
	    sqr_dist = conic_sqrdist_check(conic, pos);

	    if (sqr_dist > hi_th)
		return (false);

	    if (sqr_dist > lo_th)
		++misses;
	    else
		misses = 0;

	    if (misses > max_div)
		return (false);
	}
    }

    return (true);
}

/* count the number of points (at the sample frequency) that are close
 * to the conic */
int     conic_count(Conic * conic, Ddlist * start, Ddlist * end, int sample, double thres_sqr)
{
    Vec2    p = {Vec2_id};
    int     count = 0;
    Ddlist *dptr;
    int     i;

    for (dptr = start;;)
    {
	DD_GET_POS2(dptr, p);
	if (conic_sqrdist_check(conic, p) < thres_sqr)
	    ++count;

	if (dptr == end)
	    break;

	for (i = 0; i < sample; ++i, dptr = dptr->next)
	    if (dptr == end)
		break;
    }
    return (count);
}

#if 0
static Bool is_straight(Ddlist * dd1, Ddlist * dd2, Ddlist * dd3, double thres)
{
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    Vec2    p3 = {Vec2_id};
    Vec2    v = {Vec2_id};

    DD_GET_POS2(dd1, p1);
    DD_GET_POS2(dd2, p2);
    DD_GET_POS2(dd3, p3);
    v = vec2_unit(vec2_diff(p3, p1));
    return (fit2_point_on_line(p2, v, p1, thres));
}

#endif

Ddlist *conic_prox(Ddlist * start, Ddlist * end, int sample, double lo_th, double hi_th, int max_div)
{
    Ddlist *p1;
    Ddlist *p2;
    Ddlist *m1;
    Ddlist *m2;
    Ddlist *list1 = NULL;
    Ddlist *list2 = NULL;
    Conic  *conic = NULL;
    double  lo_sqth = lo_th * lo_th;
    double  hi_sqth = hi_th * hi_th;
    int     i, maxcount = 0;

    if (start == NULL || end == NULL || start == end)
	return (NULL);

    p1 = start;
    p2 = ddstr_nth_point(start, end, 4 * sample + 1);
    if (p2 == NULL)
	p2 = end;

    while (1)
    {

	/* if (is_straight(p1, ddstr_mid_point(p1, p2), p2, lo_th)) {
	 * if (p2 == end) break; for (i = 0; i < sample; ++i) { p1 =
	 * p1->next; p2 = p2->next; if (p2 == end) break; } continue; } */
	conic = ddstr_conic_ellipse_5pt(p1, p2, min_aratio);
	if (conic != NULL &&
	    conic_check(conic, p1, p2, lo_sqth, hi_sqth, max_div))
	{
	    int     count = conic_count(conic, start, end, sample / 2, lo_sqth);

	    if (count > maxcount)
	    {
		maxcount = count;
		m1 = p1;
		m2 = p2;
	    }
	}
	conic_free(conic);
	conic = NULL;

	if (p2 == end)
	    break;

	for (i = 0; i < sample; ++i)
	{
	    p1 = p1->next;
	    p2 = p2->next;
	    if (p2 == end)
		break;
	}
    }

    if (maxcount >= 5)
    {
	conic = ddstr_conic_ellipse_5pt(m1, m2, min_aratio);
	conic = conic_grow(conic, start, end, &m1, &m2,
			   lo_sqth, hi_sqth, max_div);

	if (conic != NULL && conic->type != ELLIPSE)
	{
	    if (fabs(conic->t1) > 2 || fabs(conic->t2) > 2)
	    {
		conic_free(conic);
		conic = NULL;
	    }
	}
    }
    if (conic == NULL)		/* failed */
    {
	sample = (int)(sample*0.75);		/* increase sample frequency */
	if (sample >= 3)
	    return (conic_prox(start, end, sample, lo_th, hi_th, max_div));
	return (linear_prox(start, end, (float)lo_th, init_sample));
    }
    if (m1 != start)
	list1 = conic_prox(start, m1, sample,
			   lo_th, hi_th, max_div);
    if (m2 != end)
	list2 = conic_prox(m2, end, sample,
			   lo_th, hi_th, max_div);

    return (dd_append(list1, dd_append(dd_link_alloc((void *) conic, CONIC2), list2)));
}

Tstring *conic_string(Tstring * string, int init_smpl, double lo_th, double hi_th, int max_div)
{
    Ddlist *conic;

    if (string == NULL)
	return (NULL);

    init_sample = init_smpl;

    conic = conic_prox(string->start, string->end, init_sample,
		       lo_th, hi_th, max_div);

    if (conic == NULL)
	return (NULL);

    return (str_make(STRING, conic, dd_get_end(conic)));
}

List   *conic_strings(List * strings, int init_smpl, double lo_th, double hi_th, int max_div)
{
    List   *sptr;
    List   *splist = NULL;

    for (sptr = strings; sptr != NULL; sptr = sptr->next)
    {
	Tstring *string = (Tstring *) sptr->to;

	string = conic_string(string, init_smpl, lo_th, hi_th, max_div);
	splist = ref_addtostart(splist, (void *) string, STRING);
    }
    return (splist);
}
