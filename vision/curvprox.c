/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

static double long_length = 100.0;	/* cant be a conic */
static double short_length = 20.0;
static double ignore_length = 10.0;	/* debris of fiting */
static double conic_thres = 0.2;	/* residual threshold for conic */
static double resid_ratio = 1.0;	/* conservative threshold */
static double dot_thres_hi = 0.95;
static double dot_thres_low = 0.8;
static double len_ratio_thres = 3.0;

extern void poly_con_grow_conics(Tstring * string,
    int sample, double low_th, double up_th, int max_div);

double max_ratio(double x, double y)
{
    double ratio = fabs(x / y);
    return ((ratio < 1.0) ? 1 / ratio : ratio);
}

/* compute residual of line fit to underlying edge strings, may be subsampled */
static double line_pair_residual(Line2 * l1, Line2 * l2,
    Tstring * s1, Tstring * s2)
{
    Ddlist *end;
    Ddlist *dptr;
    int     n;
    double  p, p2_sum = 0;	/* perpendicular statistics */
    Vec2    q = {Vec2_id};

    end = s1->end;
    for (n = 2, dptr = s1->start;; dptr = dptr->next, ++n)
    {
	DD_GET_POS2(dptr, q);
	p = vec2_dist_point_line(q, l1->p1, l1->v);
	p2_sum += p * p;
	if (dptr == end)
	    break;
    }

    end = s2->end;
    for (dptr = s2->start;; dptr = dptr->next, ++n)
    {
	DD_GET_POS2(dptr, q);
	p = vec2_dist_point_line(q, l2->p1, l2->v);
	p2_sum += p * p;
	if (dptr == end)
	    break;
    }
    return ((n == 0) ? 0.0 : sqrt(p2_sum / n));
}

/* compute residual of conic fit to underlying edge string */
static double conic_residual(Conic * conic, Ddlist * start, Ddlist * end)
{
    Ddlist *dptr;
    int     n;
    double  p2_sum = 0;		/* perpendicular staistics */

    for (n = 1, dptr = start;; dptr = dptr->next, ++n)
    {
	Vec2    q = {Vec2_id};
	Vec2    r = {Vec2_id};
	double  t;

	DD_GET_POS2(dptr, q);
	t = conic_param(conic, q);
	r = conic_point(conic, t);
	p2_sum += vec2_sqrmod(vec2_diff(r, q));
	if (dptr == end)
	    break;
    }
    return ((n == 0) ? 0.0 : sqrt(p2_sum / n));
}

/* ordered line segments along string */
static int line2_pair_possible_conic(Line2 * l1, Line2 * l2)
{
    Tstring *s1, *s2;
    Conic  *conic;
    double  lresid, cresid;
    double  dp, len_ratio;

    if (l1 == NULL || l2 == NULL)
	return (0);

    /* first accept/reject gross examples */

    len_ratio = l1->length / l2->length;
    if (len_ratio < 1)
	len_ratio = 1 / len_ratio;

    if (len_ratio > 10.0)
	return (0);

    dp = fabs(vec2_dot(l1->v, l2->v));

    if (l1->length > short_length && l2->length > short_length &&
	dp < dot_thres_low)
	return (0);

    /* check residuals */

    s1 = (Tstring *) prop_get(l1->props, STRING);
    s2 = (Tstring *) prop_get(l2->props, STRING);

    if (s1 == NULL || s2 == NULL)
	return (0);

    conic = ddstr_conic_5pt(s1->start, s2->end);
    lresid = line_pair_residual(l1, l2, s1, s2);
    cresid = conic_residual(conic, s1->start, s2->end);
    conic_free(conic);

    if (cresid < conic_thres || cresid < lresid * resid_ratio)
	return (1);

    /* finally check more subtle accept/reject */

    if (dp < dot_thres_low)
	return (0);

    if (len_ratio > len_ratio_thres)
	return (0);

    if (dp > dot_thres_hi)
	return (1);

    return (0);
}

static Ddlist *start_of_curve(Ddlist * lptr, Ddlist * end)
{
    Line2  *line = NULL;
    Line2  *last = NULL;
    int     last_was_short = 0;
    Ddlist *pos_start = NULL;

    for (;; lptr = lptr->next)
    {
	line = (Line2 *) lptr->to;

	if (line->length < ignore_length)
	{
	    if (last_was_short)	/* possible start of curve */
	    {
		if (last != NULL && !line2_pair_possible_conic(last, line))
		    pos_start = lptr->last;
		break;
	    }
	    if (pos_start == NULL)
		pos_start = lptr;
	    if (lptr == end)
	    {
		if (last != NULL)
		    pos_start = NULL;
		break;
	    }
	    last_was_short = 1;
	    continue;
	}
	if (line->length > long_length)	/* not part of conic */
	{
	    last = NULL;
	    pos_start = NULL;
	} else if (last != NULL)
	{
	    if (line2_pair_possible_conic(last, line))
		break;
	    lptr = pos_start;	/* go back */
	    pos_start = NULL;
	    last = NULL;
	} else
	{
	    last = line;
	    if (pos_start == NULL)
		pos_start = lptr;
	}

	if (lptr == end)
	{
	    if (pos_start != NULL && last_was_short && last == NULL)
	    {
		last = (Line2 *) pos_start->to;
		if (!line2_pair_possible_conic(last, line))
		    pos_start = NULL;
	    }
	    break;
	}
	last_was_short = 0;
    }
    return ((pos_start == NULL) ? lptr : pos_start);
}

Ddlist *end_of_curve(Ddlist * lptr, Ddlist * end)
{
    Line2  *line = NULL;
    Line2  *last = NULL;
    int     last_was_short = 0;
    Ddlist *pos_end = lptr;

    for (;; lptr = lptr->next)
    {
	line = (Line2 *) lptr->to;

	if (line->length < ignore_length)
	{
	    if (last_was_short)
		last = NULL;
	    pos_end = lptr;
	    last_was_short = 1;
	    if (lptr == end)
		break;
	    continue;
	}
	if (line->length > long_length)	/* not part of conic */
	    break;
	else if (last == NULL)
	    last = line;
	else if (line2_pair_possible_conic(last, line))
	{
	    pos_end = lptr;
	    last = line;
	} else
	    break;

	last_was_short = 0;

	if (lptr == end)
	    break;
    }
    return (pos_end);
}

/* take a poly strings and replace candidate sections with conics */
void poly_string_find_conics(Tstring * string,
    int sample, double low_th, double up_th, int max_div)
{
    Ddlist *lptr;
    Ddlist *start;
    Ddlist *end;
    Ddlist *conics;
    Tstring *s1, *s2;

    if (string == NULL)
	return;

    start = string->start;
    end = string->end;

    for (lptr = start;;)
    {
	Ddlist *lptr1 = NULL;
	Ddlist *lptr2 = NULL;
	Line2  *line = NULL;
	Line2  *last = NULL;

	lptr = lptr1 = start_of_curve(lptr, end);
	if (lptr == end)
	    break;
	lptr = lptr2 = end_of_curve(lptr, end);

	if (lptr != end)
	    lptr = lptr->next;

	last = (Line2 *) lptr1->to;
	line = (Line2 *) lptr2->to;
	s1 = (Tstring *) prop_get(last->props, STRING);
	s2 = (Tstring *) prop_get(line->props, STRING);
	conics = conic_prox(s1->start, s2->end, sample, low_th, up_th, max_div);

	if (conics != NULL)
	{
	    if (lptr1 == start)
	    {
		start = conics;
		start->last = lptr1->last;	/* this may be a
						 * substring */
		lptr1->last = NULL;
		if (start->last != NULL)
		    start->last->next = start;
	    } else
	    {
		lptr1->last->next = conics;
		conics->last = lptr1->last;
		lptr1->last = NULL;
	    }

	    conics = dd_get_end(conics);

	    if (lptr2 == end)
	    {
		end = conics;
		end->next = lptr2->next;	/* this may be a
						 * substring */
		if (end->next != NULL)
		    end->next->last = end;
		lptr2->next = NULL;
		ddstr_rm(lptr1, lptr2, geom_free);
		break;
	    } else
	    {
		lptr2->next->last = conics;
		conics->next = lptr2->next;
		lptr2->next = NULL;
	    }
	    ddstr_rm(lptr1, lptr2, geom_free);
	}
	if (lptr == end)
	    break;
    }

    string->start = start;
    string->end = end;
    poly_con_grow_conics(string, sample, low_th, up_th, max_div);
}

/* ARGSUSED quieten lint */
void poly_con_grow_conics(Tstring * string,
    int sample, double low_th, double up_th, int max_div)
{
    Ddlist *start;
    Ddlist *end;
    Ddlist *cptr;

    if (string == NULL)
	return;

    low_th *= low_th;		/* conic check uses sq thresholds */
    up_th *= up_th;

    start = string->start;
    end = string->end;

    for (cptr = start;;)
    {
	Conic  *conic;
	Conic  *tot_conic = NULL;
	Ddlist *lptr1 = cptr;
	Ddlist *lptr2 = cptr;
	Ddlist *conics;
	Tstring *s1, *s2;

	if (cptr->type != CONIC2)
	{
	    if (cptr == end)
		break;
	    cptr = cptr->next;
	    continue;
	}
	s1 = s2 = (Tstring *) geom_prop_get(cptr->to, cptr->type, STRING);

	if (cptr != start)	/* grow back */
	{
	    for (lptr1 = cptr->last;; lptr1 = lptr1->last)
	    {
		double  dummy = 0.0;

		s1 = (Tstring *) geom_prop_get(lptr1->to, lptr1->type, STRING);

		/* BUG ddstr_conic_ellipse_5pt requires 3rd arg: double
		 * min_aratio */
		conic = ddstr_conic_ellipse_5pt(s1->start, s2->end, dummy);

		if (conic == NULL ||
		    conic_check(conic, s1->start, s2->end,
				low_th, up_th, max_div) == false)
		{
		    conic_free(conic);
		    lptr1 = lptr1->next;
		    break;
		}
		conic_free(tot_conic);
		tot_conic = conic;
		if (lptr1 == start)
		    break;
	    }
	}
	if (cptr != end)	/* grow back */
	{
	    for (lptr2 = cptr->next;; lptr2 = lptr2->next)
	    {
		double  dummy = 0.0;

		s2 = (Tstring *) geom_prop_get(lptr2->to, lptr2->type, STRING);

		/* BUG ddstr_conic_ellipse_5pt requires 3rd arg: double
		 * min_aratio */
		conic = ddstr_conic_ellipse_5pt(s1->start, s2->end, dummy);
		if (conic == NULL ||
		    conic_check(conic, s1->start, s2->end,
				low_th, up_th, max_div) == false)
		{
		    conic_free(conic);
		    lptr2 = lptr2->last;
		    break;
		}
		conic_free(tot_conic);
		tot_conic = conic;
		if (lptr2 == end)
		    break;
	    }
	}
	cptr = (lptr2 == end) ? end : lptr2->next;
	if (lptr1 == lptr2)
	{
	    if (cptr == end)
		break;
	    continue;
	}
	s1 = (Tstring *) geom_prop_get(lptr1->to, lptr1->type, STRING);
	s2 = (Tstring *) geom_prop_get(lptr2->to, lptr2->type, STRING);
	conic_ellipse_filter(tot_conic, s1->start, s2->end, 0.2);

	tot_conic->props =
	    proplist_add(tot_conic->props,
		(void *) str_make(STRING, s1->start, s2->end), STRING,
		str_rm_only_str);
	conics = dd_link_alloc((void *) tot_conic, CONIC2);
	if (lptr1 == start)
	{
	    start = conics;
	    start->last = lptr1->last;	/* this may be a substring */
	    if (start->last != NULL)
		start->last->next = start;
	} else
	{
	    lptr1->last->next = conics;
	    conics->last = lptr1->last;
	}

	if (lptr2 == end)
	{
	    end = conics;
	    end->next = lptr2->next;	/* this may be a substring */
	    if (end->next != NULL)
		end->next->last = end;
	    lptr1->last = lptr2->next = NULL;
	    ddstr_rm(lptr1, lptr2, geom_free);
	    break;
	} else
	{
	    lptr2->next->last = conics;
	    conics->next = lptr2->next;
	}
	lptr1->last = lptr2->next = NULL;
	ddstr_rm(lptr1, lptr2, geom_free);

	if (cptr == end)
	    break;
    }
    string->start = start;
    string->end = end;
}

void    poly_strings_find_conics(List * strings,
    int sample, double low_th, double up_th, int max_div)
{
    List   *sptr;

    for (sptr = strings; sptr != NULL; sptr = sptr->next)
	poly_string_find_conics((Tstring *) sptr->to,
	    sample, low_th, up_th, max_div);
}
