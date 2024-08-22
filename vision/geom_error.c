/**@(#)
**/
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Bool    geom_within_error(void *geom1, void *geom2, int type)
{
    switch (type)
    {
	case POINT3:
	return (point3_within_error((Point3 *) geom1, (Point3 *) geom2));
	break;
    case LINE3:
	return (line3_within_error((Line3 *) geom1, (Line3 *) geom2));
	break;
    case CONIC3:
	return (conic3_within_error((Conic3 *) geom1, (Conic3 *) geom2));
	break;
    }
    return (false);
}

/* for use with reclist_update of reclist_flat */
void   *geom_within_error_update(void *geom1, int *type, void *geom2)
{
    if (geom_within_error(geom1, geom2, *type))
	return (geom1);
    return (NULL);
}

static Match *geom_make_match(void *geom2, int *type, void *geom1)
{
    Match  *match = match_make(geom1, geom2, *type);

    *type = MATCH;
    return (match);
}

static void *all_matches(void *geom, int *type, Pair * pair)


/* transform and geom_list */
{
    List   *geom_list;
    List   *mat_list;
    Transform3 *trans;
    Match  *match = NULL;
    void   *copy;

    geom_list = (List *) pair->to1;
    trans = (Transform3 *) pair->to2;

    copy = geom_copy(geom, *type);
    geom_transform(copy, *type, trans);
    geom_list = reclist_list_flat(geom_list, geom_within_error_update, *type, copy);
    geom_free(copy, *type);

    if (geom_list == NULL)
	return (NULL);

    if (list_length(geom_list) == 1)	/* a unique match */
    {
	match = match_make(geom, geom_list->to, *type);
	list_rm_links(geom_list);
	*type = MATCH;
	return ((void *) match);
    }
    mat_list = reclist_list_update(geom_list, (void *(*) ()) geom_make_match, (int) NULL,
				   geom);
    list_rm_links(geom_list);
    *type = LIST;
    return ((void *) mat_list);
}

List   *geom3_all_matches_under_trans(List * g1, List * g2, Transform3 trans)
{
    Pair   *pair = pair_make((void *) g2, LIST, (void *) &trans, TRANSFORM3);
    List   *all_mats;

    all_mats = reclist_list_flat(g1, all_matches, (int) NULL, (void *) pair);	/* not flat */
    return (geom_list_make_flat(all_mats));
}
