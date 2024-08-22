/**@(#)Avoids too many parameters in conic_filter & calling functions
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>



static double (*filter) () = NULL;	/* Filter to be applied */

double  (*conic_filter_get()) ( void /* ??? */ )
{
    return (filter);
}

void    conic_filter_set(double (*newfilter) ( /* ??? */ ))
{
    filter = newfilter;
}

/**
sampling frequency on fitted curve
**/

static int sample = 4;

int     conic_sample_get(void)
{
    return (sample);
}

void    conic_sample_set(int newsample)
{
    sample = newsample;
}

/**
nominal variance of fitted points
**/

static double var = 1.0;

double  conic_var_get(void)
{
    return (var);
}

void    conic_var_set(double newvar)
{
    var = newvar;
}

/**
number of filter iterations
**/

static int iter = 3;

int     conic_iter_get(void)
{
    return (iter);
}

void    conic_iter_set(int newiter)
{
    iter = newiter;
}

/* Apply chosen filter to point string */
void    conic_filter(Conic * conic, Ddlist * start, Ddlist * end)
{
    Conic_stat stats = {Conic_stat_id};
    double  scale;
    Ddlist *dptr;
    Vec2    p = {Vec2_id};
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    int     i, j, len;

    if (conic == NULL || filter == NULL)
	return;

    /** store copy of unfiltered conic **/
    /* BUGFIX conic0 unused */
    /* Conic   conic0; conic0 = *conic; */

    conic_normalise(conic);
    scale = MAX(fabs(conic->alpha), fabs(conic->beta));

    /** filter at least 5 points **/
    len = ddstr_length(start, end);
    if (len / sample < 4)
	sample = len / 4;

    for (i = 0; i < iter; ++i)
    {
	conic_stat_init(&stats, scale, 100.0);
	for (dptr = start;;)
	{
	    DD_GET_POS2(dptr, p);
	    filter(conic, &stats, p, var);
	    if (dptr == end)
		break;
	    for (j = 0; dptr != end && j < sample; ++j)
		dptr = dptr->next;
	}
	conic_correct(conic, stats.x);
    }
    conic_setup(conic);

    DD_GET_POS2(start, p1);
    DD_GET_POS2(end, p2);
    DD_GET_POS2(ddstr_mid_point(start, end), p);
    conic_set_ends(conic, p1, p2, p);
    conic->props = proplist_add(conic->props,
				(void *) conic_stat_copy(&stats),
				STATS,
				rfree);
}

/**
apply chosen filter to point string but limit result to an ellipse
**/
void    conic_ellipse_filter(Conic * conic, Ddlist * start, Ddlist * end, double min_aratio)
{
    Conic_stat stats = {Conic_stat_id};
    double  scale;
    Ddlist *dptr;
    Vec2    p = {Vec2_id};
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    int     i, j, len;
    Conic   conic0 = {Conic_id};

    if (conic == NULL || filter == NULL)
	return;

    /** store copy of unfiltered conic **/
    conic0 = *conic;

    conic_normalise(conic);
    scale = MAX(fabs(conic->alpha), fabs(conic->beta));

    /** filter at least 5 points **/
    len = ddstr_length(start, end);
    if (len / sample < 4)
	sample = len / 4;

    for (i = 0; i < iter; ++i)
    {
	conic_stat_init(&stats, scale, 100.0);
	for (dptr = start;;)
	{
	    DD_GET_POS2(dptr, p);
	    filter(conic, &stats, p, var);
	    if (dptr == end)
		break;
	    for (j = 0; dptr != end && j < sample; ++j)
		dptr = dptr->next;
	}
	conic_correct(conic, stats.x);
    }
    conic_setup(conic);

    if (conic->type == HYPERBOLA || conic_aratio(conic) < min_aratio)
    {
	/** have made things worse, use saved copy **/
	double  t1 = conic0.t1;
	double  dt = conic0.t2 - conic0.t1;

	*conic = conic0;

	/** set up 5pt stats without changing conic **/
	conic_stat_init(&stats, scale, 100.0);
	filter(conic, &stats, conic_point(conic, t1), var);
	filter(conic, &stats, conic_point(conic, t1 + 0.25 * dt), var);
	filter(conic, &stats, conic_point(conic, t1 + 0.50 * dt), var);
	filter(conic, &stats, conic_point(conic, t1 + 0.75 * dt), var);
	filter(conic, &stats, conic_point(conic, t1 + 1.00 * dt), var);
    }
    DD_GET_POS2(start, p1);
    DD_GET_POS2(end, p2);
    DD_GET_POS2(ddstr_mid_point(start, end), p);
    conic_set_ends(conic, p1, p2, p);
    conic->props = proplist_add(conic->props,
				(void *) conic_stat_copy(&stats),
				STATS,
				rfree);
}

Conic  *conic_fit(Ddlist * start, Ddlist * end)
{
    Conic  *conic = ddstr_conic_5pt(start, end);

    conic_filter(conic, start, end);
    return (conic);
}

Conic  *conic_ellipse_fit(Ddlist * start, Ddlist * end, double min_aratio)
{
    Conic  *conic = ddstr_conic_ellipse_5pt(start, end, min_aratio);

    conic_ellipse_filter(conic, start, end, min_aratio);
    return (conic);
}
