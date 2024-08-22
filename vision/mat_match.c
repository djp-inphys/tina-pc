/**@(#)
**/
/* mat_match.c
 * 
 * matchability module and functions
 * 
 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

static Bool use_transf_thres = false;
static float rotthres = (float)PI;
static float dotthres = (float)1.0;
static float posthres = (float)1000.0;
static float low_lenratio = (float)0.75;
static float up_lenratio = (float)1.33;
static float low_conratio = (float)0.75;
static float up_conratio = (float)1.33;

void    matcher_set_length_ratio(double lenratio)
{
    low_lenratio = (float)lenratio;
    up_lenratio = (float)(1.0 / lenratio);
    ORDER(float, low_lenratio, up_lenratio);
    low_conratio = low_lenratio;/* tempory measure */
    up_conratio = up_lenratio;
}

double  matcher_get_length_ratio(void)
{
    return (low_lenratio);
}

void    matcher_set_max_rot(double rot)
{
    rotthres = (float)rot;
    dotthres = (float)cos(rotthres);
}

double  matcher_get_max_rot(void)
{
    return (rotthres);
}

void    matcher_set_max_trans(double pos)
{
    posthres = (float)pos;
}

double  matcher_get_max_trans(void)
{
    return (posthres);
}

void    matcher_set_use_transf_thres(Bool use)
{
    use_transf_thres = use;
}

static Bool line3_good_match(Line3 * l1, Line3 * l2)
{
    float   lenratio;

    if (l1 == NULL || l2 == NULL)
	return (false);

    if (use_transf_thres == true)
    {
	if (vec3_dot(l1->v, l2->v) < dotthres)
	    return (false);
    }
    lenratio = l1->length / l2->length;
    if (lenratio < low_lenratio || lenratio > up_lenratio)
	return (false);

    return (true);
}

static Bool conic3_matchable(Conic3 * c1, Conic3 * c2)
{
    double  conratio;

    if (c1 == NULL || c2 == NULL)
	return (false);

    if (use_transf_thres == true)
    {
	if (vec3_dot(c1->ez, c2->ez) < dotthres)
	    return (false);
    }
    conratio = c1->conic->alpha / c2->conic->alpha;
    if (conratio < low_conratio || conratio > up_conratio)
	return (false);
    conratio = c1->conic->beta / c2->conic->beta;
    if (conratio < low_conratio || conratio > up_conratio)
	return (false);
    return (true);
}

Bool    smm_good_match(void *p1, void *p2, int type)
{
    Bool    bool = false;

    switch (type)
    {
    case POINT3:
	bool = (true);		/* always matchable */
	break;
    case LINE3:
	bool = (line3_good_match((Line3 *) p1, (Line3 *) p2));
	break;
    case CONIC3:
	bool = (conic3_matchable((Conic3 *) p1, (Conic3 *) p2));
	break;
    default:
	bool = (false);
	break;
    }
    return (bool);
}

static Bool line3_reasonable_match(Line3 * l1, Line3 * l2)
{
    if (l1 == NULL || l2 == NULL)
	return (false);

    if (use_transf_thres == true)
    {
	if (vec3_dot(l1->v, l2->v) < dotthres)
	    return (false);
    }
    return (true);
}

Bool    smm_reasonable_match(void *p1, void *p2, int type)
{
    Bool    bool = false;

    switch (type)
    {
    case POINT3:
	bool = (true);		/* always matchable */
	break;
    case LINE3:
	bool = (line3_reasonable_match((Line3 *) p1, (Line3 *) p2));
	break;
    case CONIC3:
	bool = (conic3_matchable((Conic3 *) p1, (Conic3 *) p2));
	break;
    default:
	bool = (false);
	break;
    }
    return (bool);
}


List   *smm_good_matches(void *p, int ptype, List * list)
{
    List   *lptr;
    List   *match_list = NULL;
    Match  *match_make();
    double  smm_match_strength(Match * match);

    for (lptr = list; lptr != NULL; lptr = lptr->next)
	if (lptr->type == ptype && smm_good_match(p, lptr->to, ptype))
	{
	    Match  *match = match_make(p, lptr->to, ptype);

	    match->weight = (float)smm_match_strength(match);
	    match_list = ref_addtostart(match_list, (void *) match, MATCH);
	}
    return (list_reverse(match_list));
}

double  smm_match_strength(Match * match)
{
    if (match == NULL)
	return (0.0);

    switch (match->type)
    {
    case LINE3:
	{
	    Line3  *l1 = (Line3 *) match->to1;
	    Line3  *l2 = (Line3 *) match->to2;

	    if (l1->length < l2->length)
		return (l1->length * l1->length / l2->length);
	    else
		return (l2->length * l2->length / l1->length);
	}
    case CONIC3:
	{
	    Conic  *c1 = ((Conic3 *) match->to1)->conic;
	    Conic  *c2 = ((Conic3 *) match->to2)->conic;
	    double  len1, len2;

	    len1 = conic_approx_length(c1, 3);
	    len2 = conic_approx_length(c2, 3);
	    if (len1 < len2)
		return (fabs(c1->t2 - c1->t1) * len1 / TWOPI);
	    else
		return (fabs(c2->t2 - c2->t1) * len2 / TWOPI);
	}
    case POINT3:
	return (1.0);
    default:
	return (0.0);
    }
}

double  smm_mlist_goodness(List * mlist)
/* list of matches  */
{
    float   goodness = (float) 0.0;
    List   *con_list = NULL;
    List   *lptr;
    List   *cptr;

    for (lptr = mlist; lptr != NULL; lptr = lptr->next)
    {
	Match  *m = (Match *) lptr->to;
	float   con;
	int     label;

	con = m->weight;
	label = geom_label_get(m->to1, m->type);
	cptr = link_get_by_type(con_list, label);

	if (cptr == NULL)
	{
	    con_list = ref_addtostart(con_list, (void *) ralloc(sizeof(float)), label);
	    cptr = con_list;
	} else if (*((float *) cptr->to) > con)
	    continue;

	*((float *) cptr->to) = con;
    }

    for (cptr = con_list; cptr != NULL; cptr = cptr->next)
	goodness += *((float *) cptr->to);
    list_rm(con_list, (void (*) ()) NULL);
    return (goodness);
}
