/**@(#)
**/
/* matchable.c
 * 
 * generic stereo functions for determining matchability of edge
 * sub-strings based upon local properties
 * 
 * provides an initial prune on ambiguity
 * 
 * 2 aspects are considered orientation and contrast
 * 
 * edge orientation varies between -PI and +PI but this depends upon the
 * sign of intensity contrast across the edge
 * 
 * hence 3 factors are dealt with
 * 
 * similar orientation, same contrast sign, similar contrast value
 * 
 * for the case where only the orientation is important (ie the sign of
 * contrast is allowed to change to allow for accidental viewpoint
 * alignments) absolute orientation values which do not include the
 * contrast component are computed.
 * 
 * absolute orientation varies between -PI/2 to PI/2 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

/* stereo module static parameter values and set functions
 * 
 * provides data hiding and limits number of external variables */

static float low_orient_thres = (float)0.3;
static float hi_orient_thres = (float)1.0;
static float disparity_gradient = (float)0.5;
static float low_con_ratio = (float)0.2;
static float hi_con_ratio = (float)5.0;

void    es_match_set_low_or_thres(double thres)
{
    low_orient_thres = (float)thres;
}

void    es_match_set_hi_or_thres(double thres)
{
    hi_orient_thres = (float)thres;
}

void    es_match_set_grad_thres(double thres)
{
    disparity_gradient = (float)thres;
}

void    es_match_set_con_ratio(double ratio)
{
    low_con_ratio = (float)ratio;
    hi_con_ratio = (float)(1.0 / ratio);
    ORDER(float, low_con_ratio, hi_con_ratio);
}

/* calculate the average orientation value of the egels that constitute
 * this edge string contour
 * 
 * the contor will usually be one of the sub strings from the stereo index */
double  es_mean_or(Tstring * es)
{
    Ddlist *dptr;
    Ddlist *end;
    double  or;

    if (es == NULL)
	return (0);

    dptr = es->start;
    end = es->end;
    or = DD_EDGE(dptr)->orient;
    for (; dptr != end;)
    {
	dptr = dptr->next;
	or += DD_EDGE(dptr)->orient;
    }
    return (or / es->count);
}

/* calculate the average contrast value of the egels that constitute
 * this edge string contour
 * 
 * the contor will usually be one of the sub strings from the stereo index */
double  es_mean_con(Tstring * es)
{
    Ddlist *dptr;
    Ddlist *end;
    double  con;

    if (es == NULL)
	return (0);

    dptr = es->start;
    end = es->end;
    con = DD_EDGE(dptr)->contrast;
    for (; dptr != end;)
    {
	dptr = dptr->next;
	con += DD_EDGE(dptr)->contrast;
    }
    return (con / es->count);
}

/* test whether the orientation is winthin threshold
 * 
 * takes into acount the cyclic nature of orientation using the range
 * argument
 * 
 * in radians 2 choices of range exist: PI    orientation independent of
 * edge contrast 2PI   orientation dependent upon edge contrast */
Bool    orient_less_than_thres(double or, double thres, double range)
{
    return ((or < thres || range - or < thres) ? true : false);
}

/* test whether orientaions agree within the disparity gradient limit */
Bool    orients_within_gradient_limit(double or1, double or2, double dgl)

/* disparity gradient limit */
{
    double  cot1, cot2;

    cot1 = 1.0 / tan(or1);
    cot2 = 1.0 / tan(or2);

    if (4 * sqr(cot1 - cot2) <= dgl * (sqr(cot1 + cot2) + 4))
	return (true);
    return (false);
}

/* test whether edge strings orientation values match
 * 
 * 
 * orientation is dependent upon contrast and has range 2PI (-PI to PI) */
Bool    es_match_orient(Tstring * es1, Tstring * es2)
{
    double  or1, or2, ordiff;

    if (es1 == NULL || es2 == NULL)
	return (false);

    or1 = es_mean_or(es1);
    or2 = es_mean_or(es2);

    ordiff = fabs(or1 - or2);
    if (orient_less_than_thres(ordiff, low_orient_thres, TWOPI) == true)
	return (true);
    if (orient_less_than_thres(ordiff, hi_orient_thres, TWOPI) == false)
	return (false);
    return (orients_within_gradient_limit(or1, or2, disparity_gradient));
}

/* compute absolute orientation
 * 
 * this orientation is independent of contrast and has range -PI/2 to PI/2 */
double  orient_abs(double or)
{
    int     n;

    if (or > PIBY2)
    {
	n = (int)(or / PI + 1);
	return (or - n * PI);
    }
    if (or < -PIBY2)
    {
	n = (int)((-or) / PI + 1);
	return (or + n * PI);
    }
    return (or);
}

/* test whether edge strings absolute orientation values match
 * 
 * this allows contrast reversal to occur between images
 * 
 * 
 * absolute orientation has a range of PI (-PI/2 to PI/2) */
Bool    es_match_abs_orient(Tstring * es1, Tstring * es2)
{
    double  or1, or2, ordiff;

    if (es1 == NULL || es2 == NULL)
	return (false);

    or1 = orient_abs(es_mean_or(es1));
    or2 = orient_abs(es_mean_or(es2));

    ordiff = fabs(or1 - or2);
    if (orient_less_than_thres(ordiff, low_orient_thres, PI) == true)
	return (true);
    if (orient_less_than_thres(ordiff, hi_orient_thres, PI) == false)
	return (false);
    return (orients_within_gradient_limit(or1, or2, disparity_gradient));
}

/* test whether edge strings contrast values match */
Bool    es_match_contrast(Tstring * es1, Tstring * es2)
{
    double  con1, con2;
    double  con_ratio;

    if (es1 == NULL || es2 == NULL)
	return (false);

    con1 = es_mean_con(es1);
    con2 = es_mean_con(es2);

    con_ratio = con1 / con2;

    return (con_ratio > low_con_ratio && con_ratio < hi_con_ratio) ? true : false;
}

/* test whether edge strings orientation and contrast values match */
Bool    es_match_orandcon(Tstring * es1, Tstring * es2)
{
    if (es_match_contrast(es1, es2) == false)
	return (false);
    return (es_match_orient(es1, es2));
}
