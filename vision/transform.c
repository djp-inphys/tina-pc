/** @(#)Least squares transform functions for matched 3D geometry
 * position (pos) and vector (vec) treated seperately
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* Compute approx (rot first) least square transformation on the basis
 * of vector data obtained from appropriate geometrical primitives
 * transform from match->t1 to match->t2 for each member of the list */
Transform3 mlist_comp_transform_vec3(List * match_list, int *terror)
{
    Transform3 trans = {Transform3_id};

    trans.type = 0;
    trans.R = mlist_comp_rot_all(match_list, terror);	/* uses all */
    if (*terror)
	trans.t = vec3_zero();
    else
	trans.t = mlist_comp_translate_all(match_list, trans.R);

    if (*terror)
	error("there is a transform error", warning);

    return (trans);
}

/* Compute approx (rot first) least square transformation on the basis
 * of position data obtained from appropriate geometrical primitives
 * centroid can be weighted (on basis of match strength) if required
 * transform from match->t1 to match->t2 for each member of the list */
Transform3 mlist_comp_transform_pos3(List * match_list, Bool weighted, int *terror)

/* if true use a weighted centroid */

{
    Transform3 trans = {Transform3_id};
    float   tot_weight = (float)0.0;
    List   *lptr;
    Vec3    c1 = {Vec3_id};
    Vec3    c2 = {Vec3_id};

    c1 = c2 = vec3_zero();
    trans.type = 0;

    for (lptr = match_list; lptr != NULL; lptr = lptr->next)
    {
	Match  *mptr = (Match *) lptr->to;
	Point3 *p1;
	Point3 *p2;
	float   weight;

	if (mptr->type != POINT3)
	    continue;

	p1 = (Point3 *) mptr->to1;
	p2 = (Point3 *) mptr->to2;
	weight = (float)((weighted == true) ? mptr->weight : 1.0);

	c1 = vec3_times(weight, vec3_sum(c1, p1->p));
	c2 = vec3_sum(c2, p2->p);
	tot_weight += weight;
    }

    c1 = vec3_times(1 / tot_weight, c1);
    c2 = vec3_times(1 / tot_weight, c2);

    trans.R = mlist_comp_rot_pos3(match_list, c1, c2, terror);
    trans.t = (terror) ? vec3_zero() : vec3_diff(c2, mat3_vprod(trans.R, c1));

    if (*terror)
	error("there is a transform error", warning);

    return (trans);
}

/* Test if particular match is consitent with transformation trans
 * should take geometry in match->t1 to match->t2 */
Bool    transform_match_ok(Match * match, Transform3 trans)
{
    Bool    within_error;
    void   *geom;

    if (match == NULL)
	return (false);

    geom = geom_copy(match->to1, match->type);
    geom_transform(geom, match->type, &trans);
    within_error = geom_within_error(geom, match->to2, match->type);
    geom_free(geom, match->type);
    return (within_error);
}

/* Remove elements of match list (list) that are not consistent with
 * transformation (trans) use freematch to determine whether to free up
 * Match structure or only the List element */
List   *transform_prune_mlist(List * list, Transform3 trans, Bool freematch)
{
    List   *pruned = NULL;
    List   *lptr;
    List   *next;

    for (lptr = list; lptr != NULL; lptr = next)
    {
	next = lptr->next;
	if (transform_match_ok((Match *) lptr->to, trans) == false)
	{
	    if (freematch == true)
		(void) link_rm(lptr, rfree);	/* delete this match */
	    else
		(void) link_rm_el(lptr);
	    continue;
	}
	pruned = link_addtostart((List *) pruned, lptr);
    }
    return (list_reverse(pruned));
}

/* Starting from the pair of matches {m1, m2} compute transformation
 * recruit additional matches from match list (list) if possible */
Transform3 match_pair_transform_vec3(Match * m1, Match * m2, List * list, int *match_count)

/* full list of matches */

{
    List   *tlist = NULL;
    Transform3 trans = {Transform3_id};
    Transform3 oldtrans = {Transform3_id};
    int     old_count, count = 0;
    int     terror;

    *match_count = 0;

    trans.R = mat3_unit();
    trans.t = vec3_zero();

    if (m1 == NULL || m2 == NULL)
	return (trans);
    tlist = ref_addtostart(tlist, (void *) m1, MATCH);
    tlist = ref_addtostart(tlist, (void *) m2, MATCH);

    do
    {
	old_count = count;
	oldtrans = trans;
	trans = mlist_comp_transform_vec3(tlist, &terror);
	list_rm(tlist, (void (*) ()) NULL);
	if (!terror)
	{
	    tlist = transform_prune_mlist(
	    list_copy(list, (void *(*) ()) NULL, NULL), trans, false);
	    count = list_length(tlist);
	}
    }
    while (count >= 2 && count > old_count);

    list_rm(tlist, (void (*) ()) NULL);
    *match_count = old_count;

    return (oldtrans);
}

/* Find the best (highest cardinality) transformation from the match
 * list try each pair of matches in turn as the basis of the
 * transformation */
Transform3 mlist_best_transform_vec3(List * list, int *match_count)
{
    Transform3 trans = {Transform3_id};
    Transform3 best_trans = {Transform3_id};
    int     count, maxcount = -1;
    List   *l1;
    List   *l2;

    best_trans.R = mat3_unit();
    best_trans.t = vec3_zero();

    for (l1 = list; l1 != NULL; l1 = l1->next)
	for (l2 = l1->next; l2 != NULL; l2 = l2->next)
	{
	    Match  *m1 = (Match *) l1->to;
	    Match  *m2 = (Match *) l2->to;

	    trans = match_pair_transform_vec3(m1, m2, list, &count);
	    if (count > maxcount)
	    {
		maxcount = count;
		best_trans = trans;
	    }
	}

    *match_count = maxcount;
    return (best_trans);
}

/* Compute transromation from match list (list) iteratively prune and
 * grow transformation until stable */
Transform3 mlist_transform_vec3(List * list, int *match_count)
{
    List   *tlist;
    Transform3 trans = {Transform3_id};
    Transform3 oldtrans = {Transform3_id};
    int     old_count, count = 0;
    int     terror;

    trans.R = mat3_unit();
    trans.t = vec3_zero();
    tlist = list_copy(list, (void *(*) ()) NULL, NULL);

    do
    {
	old_count = count;
	oldtrans = trans;
	trans = mlist_comp_transform_vec3(tlist, &terror);
	list_rm(tlist, (void (*) ()) NULL);
	if (!terror)
	{
	    tlist = transform_prune_mlist(list_copy(list,
			    (void *(*) ()) NULL, NULL), trans, false);
	    count = list_length(tlist);
	}
    }
    while (count >= 2 && count > old_count);

    list_rm(tlist, (void (*) ()) NULL);
    *match_count = old_count;

    return (oldtrans);
}
