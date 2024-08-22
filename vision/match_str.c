/**@(#)
**/
/* match_str.c
 * 
 * generic stereo functions for computing support between complete edge
 * strings
 * 
 * the strings must already be referenced through the property list of
 * each edge using the key STRING
 * 
 * this approach is used to compute the strict figural continuity support.
 * That is, the sum of support from valid matches that exist between a
 * pair of uniquely labled sub-strings. */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* make an example of a string match */
String_match *sm_make(Tstring * s1, Tstring * s2, int s1_id, int s2_id)
{
    String_match *sm = ts_ralloc(String_match);

    sm->s1 = s1;
    sm->s2 = s2;
    sm->s1_id = s1_id;
    sm->s2_id = s2_id;
    sm->support = 0;
    sm->r_low = sm->r_up = 0;

    return (sm);
}

/* free a list of string matches */
void    sm_list_rm(List * sm_list)
{
    list_rm(sm_list, rfree);
}

/* initialise values in a string match */
static void sm_init_sup(String_match * sm)
{
    if (sm == NULL)
	return;

    sm->support = 0;
}


/* search list of string matches for one with given pair of edge
 * sub-string identifiers
 * 
 * if no such string match exists return NULL */
String_match *str_mat_from_list(List * mlist, int s1_id, int s2_id)
{
    List   *ptr;

    for (ptr = mlist; ptr != NULL; ptr = ptr->next)
	if (s1_id == ptr->type && s2_id == ((String_match *) ptr->to)->s2_id)
	    return ((String_match *) ptr->to);
    return (NULL);
}

/* initialise edge string match string lists */
void    es_match_string_init(Tstring * es)
{
    if (es == NULL)
	return;
    es->props = proplist_addifnp(es->props, NULL, MLIST,
				 (void (*) ()) NULL, true);
}

/* accumulate matches and support for an individual edge contour string
 * into list of string matches of uniquely labled sub-parts add it to
 * the property list of the global string
 * 
 * uniquely labled sub-strings correspond to those string parts that cross
 * a set of epipolars/rasters only once (eg strings are implicitly
 * broken at turning points in the y direction). These labels are
 * indexed through the property luists of the epipolar sub-strings
 * using the key STRING.
 * 
 * examines the matches of the component epipolar sub-strings */
/* ARGSUSED quieten lint */
void    es_match_string(Tstring * es, int type, double (*cost_func) ( /* ??? */ ))

/* unused */

{
    List   *matches;		/* list of string matches */
    Tstring *ses;		/* string of sub strings */
    Ddlist *sptr;
    Ddlist *start;
    Ddlist *end;
    int     s1_id, s2_id;

    ses = string_of_sindex_strings(es);

    if (ses == NULL)
	return;

    start = ses->start;
    end = ses->end;

    matches = (List *) prop_get(es->props, MLIST);
    list_apply_func(matches, sm_init_sup, NULL);

    for (sptr = start; sptr != end; sptr = sptr->next)
    {
	Tstring *s1;
	List   *mlist;
	List   *mptr;
	int     r;
	Vec2    v = {Vec2_id};


	s1 = (Tstring *) sptr->to;
	mlist = (List *) prop_get(s1->props, MLIST);
	s1_id = (int) prop_get(s1->props, STRING);

	v = str2_centroid(s1);
	r = (int)floor(vec2_y(v));

	for (mptr = mlist; mptr != NULL; mptr = mptr->next)
	{
	    Match  *m = (Match *) mptr->to;
	    Tstring *s2;
	    String_match *sm;

	    s2 = (Tstring *) m->to2;
	    s2_id = (int) prop_get(s2->props, STRING);
	    if ((sm = str_mat_from_list(matches, s1_id, s2_id)) == NULL)
	    {
		Edgel  *edge = (Edgel *) s2->start->to;

		sm = sm_make(es, (Tstring *) prop_get(edge->props, STRING), s1_id, s2_id);
		matches = ref_addtostart((List *) matches, (void *) sm, s1_id);
		sm->r_low = sm->r_up = r;
	    }
	    if (r < sm->r_low)
		sm->r_low = r;
	    if (r > sm->r_up)
		sm->r_up = r;

	    if (cost_func == NULL)
	    {
		Support *s = (Support *) prop_get(m->props, MATCH_SUPPORT);

		if (s == NULL || s->type <= BAD_MATCH)
		    continue;
		sm->support += ((Match *) mptr->to)->weight;
	    } else
		sm->support += cost_func(m);
	}
	if (sptr == end)
	    break;
    }
    es->props = proplist_addifnp(es->props, (void *) matches, MLIST, sm_list_rm, false);
    str_rm_links(ses);
}

/* set the total string support for matches associated with epipolar
 * sub-strings of an edge contour from the string matches of the edge
 * string as a whole */
void    es_mlist_set_total_string_sup(Tstring * es)
{
    List   *matches;		/* list of string matches */
    Tstring *ses;		/* string of sub strings */
    Ddlist *sptr;
    Ddlist *start;
    Ddlist *end;
    int     s1_id, s2_id;

    ses = string_of_sindex_strings(es);

    if (ses == NULL)
	return;

    start = ses->start;
    end = ses->end;

    matches = (List *) prop_get(es->props, MLIST);

    for (sptr = start; sptr != end; sptr = sptr->next)
    {
	Tstring *s1;
	List   *mlist;
	List   *mptr;

	s1 = (Tstring *) sptr->to;
	mlist = (List *) prop_get(s1->props, MLIST);
	s1_id = (int) prop_get(s1->props, STRING);

	for (mptr = mlist; mptr != NULL; mptr = mptr->next)
	{
	    Match  *m = (Match *) mptr->to;
	    Support *sup;
	    Tstring *s2;
	    String_match *sm;

	    s2 = (Tstring *) m->to2;
	    sup = (Support *) prop_get(m->props, MATCH_SUPPORT);
	    s2_id = (int) prop_get(s2->props, STRING);
	    sm = str_mat_from_list(matches, s1_id, s2_id);

	    if (sm == NULL)
		continue;

	    sup->total_string = (float)sm->support;
	}
	if (sptr == end)
	    break;
    }
    str_rm_links(ses);
}

/* match string support value */
static double sm_support_neg(String_match * sm)
{
    return (sm == NULL) ? 0.0 : -sm->support;
}

/* choose matches that are consitent with the given string match */
static void sm_choose_matches(Tstring * ses, String_match * sm)
{
    Ddlist *sptr;
    Ddlist *start;
    Ddlist *end;

    if (ses == NULL || sm == NULL)
	return;

    start = ses->start;
    end = ses->end;

    for (sptr = start; sptr != end; sptr = sptr->next)
    {
	Tstring *s1, *s2;
	int     s1_id, s2_id;
	List   *mlist;
	List   *mptr;
	Match  *match;
	Support *msup = NULL;

	s1 = (Tstring *) sptr->to;
	s1_id = (int) prop_get(s1->props, STRING);

	if (s1_id != sm->s1_id)
	    continue;

	mlist = (List *) prop_get(s1->props, MLIST);

	for (mptr = mlist; mptr != NULL; mptr = mptr->next)
	{
	    match = (Match *) mptr->to;

	    s2 = (Tstring *) ((Match *) mptr->to)->to2;
	    s2_id = (int) prop_get(s2->props, STRING);

	    if (s2_id != sm->s2_id)
		continue;

	    msup = (Support *) prop_get(match->props, MATCH_SUPPORT);
	    if (msup->type <= BAD_MATCH)	/* already rejected */
		mptr = NULL;

	    break;
	}

	if (mptr == NULL)
	    continue;		/* no appropriate match */

	mlist_set_supp_type(mlist, BAD_MATCH);
	msup->type = GOOD_MATCH;
    }
}

/* choose matches at the string level */
void    es_choose_string_matches(Tstring * es, int type, double (*cost_func) ( /* ??? */ ))

/* not used */

{
    List   *matches;
    List   *mptr;
    Tstring *ses;		/* string of sub-strings */

    ses = string_of_sindex_strings(es);

    es_match_string(es, type, cost_func);	/* first call to string
						 * matcher */
    matches = (List *) prop_get(es->props, MLIST);
    matches = sort_list(matches, sm_support_neg, NULL);
    for (mptr = matches; mptr != NULL; mptr = mptr->next)
    {
	String_match *sm = (String_match *) mptr->to;

	if (sm->support == 0.0)
	    break;

	sm_choose_matches(ses, sm);
	/* es_match_string does not effect order of matches */
	es_match_string(es, type, cost_func);
	mptr->next = sort_list(mptr->next, sm_support_neg, NULL);
    }
    str_rm_links(ses);
}
