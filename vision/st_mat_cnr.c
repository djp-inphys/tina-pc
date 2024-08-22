/**@(#)
**/
#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/sys_types.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/tina_types.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

static FILE *fp = NULL;

void    set_st_corner_matches(Imrect * er)
{
    void   *data = NULL;
    Rindex *fx;

    if ((fx = prop_get(er->props, ER_TINDEX)) == NULL)
	return;

    fp = fopen("temp.dump", "w");
    apply_func_to_windex(fx, (void *(*) ())set_st_corner_match, data);
    (void) fclose(fp);
}

/* Starting from the current left hand edgel can we go back to any
 * previous stereo matching and check that the current stereo match is
 * consistent */
/* ARGSUSED quieten lint */
/* BUGFIX JB 22/11/93 was: void   *set_st_corner_match(Edgel * ledge,
 * void *data) */

void    set_st_corner_match(Edgel * ledge, void *data /* unused */ )
{
    List   *left_matches;
    Match  *best_left_match;
    Edgel  *redge;
    List   *back_matches_left;
    List   *back_matches_right;
    List   *for_matches_left;
    List   *for_matches_right;
    Match  *back_match_left;
    Match  *back_match_right;
    Edgel  *back_edge_left;
    Edgel  *back_edge_right;
    List   *sold_matches_left;
    Match  *sold_match_left;
    Edgel  *sold_edge_right;

    /* current stereo match is redge */
    if ((left_matches = (List *) prop_get(ledge->props, MLIST)) == NULL
	|| (left_matches->type < GOOD_MATCH)
	|| (best_left_match = (Match *) left_matches->to) == NULL
	|| (redge = (Edgel *) best_left_match->to2) == NULL)
	return;

    if ((back_matches_left = (List *) prop_get(ledge->props, BACKTEMP)) == NULL

    /* if the temporal match type is already better than GOOD_MATCH
     * then the FORTEMP and BACKTEMP matches are already known to be
     * identical */
	|| (back_matches_left->type < GOOD_MATCH)
	|| (back_match_left = (Match *) back_matches_left->to) == NULL
	|| (back_edge_left = (Edgel *) back_match_left->to2) == NULL)
	return;

    if ((back_matches_right = (List *) prop_get(redge->props, BACKTEMP)) == NULL

    /* if the temporal match type is already better than GOOD_MATCH
     * then the FORTEMP and BACKTEMP matches are already known to be
     * identical */
	|| (back_matches_right->type < GOOD_MATCH)
      || (back_match_right = (Match *) back_matches_right->to) == NULL
	|| (back_edge_right = (Edgel *) back_match_right->to2) == NULL)
	return;

    /* old stereo match is sold_edge_right */
    if ((sold_matches_left = (List *) prop_get(back_edge_left->props, MLIST)) == NULL
	|| (sold_match_left = (Match *) sold_matches_left->to) == NULL)
	return;
    sold_edge_right = sold_match_left->to2;

    if (sold_edge_right == back_edge_right)
    {
	back_matches_left->type = FIXED_MATCH;
	back_matches_right->type = FIXED_MATCH;
	for_matches_left = (List *) prop_get(back_edge_left->props, FORTEMP);
	for_matches_right = (List *) prop_get(back_edge_right->props, FORTEMP);
	if (for_matches_left != NULL)
	    for_matches_left->type = FIXED_MATCH;
	if (for_matches_right != NULL)
	    for_matches_right->type = FIXED_MATCH;
	if (fp != NULL)
	    (void) fprintf(fp, "%3.2f %3.2f %3.2f %3.2f %3.2f %3.2f %3.2f %3.2f\n",
		 back_edge_left->pos.el[0], back_edge_left->pos.el[1],
	       back_edge_right->pos.el[0], back_edge_right->pos.el[1],
			   ledge->pos.el[0], ledge->pos.el[1],
			   redge->pos.el[0], redge->pos.el[1]);
    }
}

Match  *find_temporal_match(Match * match)
{
    void   *get_fixed_match();
    Edgel  *ledge;
    Edgel  *foredge;
    Match  *formatch;
    int     data = FORTEMP;

    ledge = (Edgel *) match->to1;
    if ((formatch = (Match *) get_fixed_match(ledge, &data)) != NULL)
    {
	foredge = (Edgel *) formatch->to1;
	data = MLIST;
	return ((Match *) get_fixed_match(foredge, &data));
    } else
	return (NULL);
}
