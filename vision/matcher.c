/**@(#)
**/
/* matcher.c
 * 
 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

static List *model;
static Matrix *model_tbl;
static List *scene;
static Matrix *scene_tbl;

static List *pot_cliques;
static List *pw_cliques;

double  smm_mlist_goodness();

static Match_clique *clique_make(List * mlist, double strength, int csize)
{
    Match_clique *c = ts_ralloc(Match_clique);

    c->strength = (float)strength;
    c->mlist = mlist;
    c->csize = csize;
    return (c);
}

static void clique_free(Match_clique * c)
{
    if (c == NULL)
	return;

    list_rm(c->mlist, match_free);
    rfree((void *) c);
}

static double clique_neg_strength(Match_clique * c)
{
    if (c == NULL)
	return (0.0);
    return (-(c->strength));
}

void    smm_set(List * list1, List * list2, Matrix * table1, Matrix * table2)
{
    model = list1;
    scene = list2;
    model_tbl = table1;
    scene_tbl = table2;
    list_rm(pot_cliques, clique_free);
    pot_cliques = NULL;
    list_rm(pw_cliques, clique_free);
    pw_cliques = NULL;
}

Bool    smm_consistent_matches(Match * m1, Match * m2)
{
    int     p11, p12, p21, p22;
    Pwrte  *pwrte1, *pwrte2;

    if (m1 == NULL || m2 == NULL)
	return (false);

    if (m1->to1 == m2->to1 || m1->to2 == m2->to2)
	return (false);

    p11 = (int) geom_prop_get(m1->to1, m1->type, PWR);
    p21 = (int) geom_prop_get(m1->to2, m1->type, PWR);
    p12 = (int) geom_prop_get(m2->to1, m2->type, PWR);
    p22 = (int) geom_prop_get(m2->to2, m2->type, PWR);

    pwrte1 = model_tbl->el.ptr_v[p11][p12];
    pwrte2 = scene_tbl->el.ptr_v[p21][p22];

    return (pwrte_compatible(pwrte1, pwrte2));
}

static List *clique_to_mlist(Match_clique * c)
{
    return (c->mlist);
}

#if 0
static List *smm_pot_clique_mlists(void)
{
    return (list_copy(pot_cliques, (void *(*) ()) clique_to_mlist, NULL));
}

#endif

static List *smm_pw_clique_mlists(void)
{
    return (list_copy(pw_cliques, (void *(*) ()) clique_to_mlist, NULL));
}

static List *mutual_cliques(List * mlist, int csize)
{
    List   *graph;
    List   *gcliques;
    List   *cliques = NULL;
    List   *lptr;

    graph = graph_make_list(mlist);
    graph_list_consistent(graph, smm_consistent_matches);
    gcliques = cliques_get(graph, csize - 1);
    for (lptr = gcliques; lptr != NULL; lptr = lptr->next)
    {
	List   *mlist = graph_recover_list((List *) lptr->to);
	Match_clique *c;

	c = clique_make(mlist, smm_mlist_goodness(mlist), csize);
	cliques = ref_addtostart(cliques, (void *) c, LIST);
	list_rm_links((List *) lptr->to);
    }
    list_rm(graph, rfree);
    return (cliques);
}

static void smm_cliches_to_pot_cliques(List * match_cliches)
/* Match cliche list */
{
    List   *cptr;

    for (cptr = match_cliches; cptr != NULL; cptr = cptr->next)
    {
	Match_cliche *mc = (Match_cliche *) cptr->to;
	List   *mlist = NULL;
	List   *group;
	List   *clist;
	List   *ptr;
	int     fthres, gthres;	/* focus and global clique sizes */

	fthres = mc->fthres;
	gthres = mc->gthres;
	group = mc->group;

	for (ptr = mc->focus; ptr != NULL; ptr = ptr->next)
	{
	    List   *flist = smm_good_matches(ptr->to, ptr->type, scene);

	    mlist = list_append(flist, mlist);
	}

	clist = mutual_cliques(mlist, fthres);	/* a set of initial
						 * cliques */

	for (ptr = clist; ptr != NULL; ptr = ptr->next)
	{
	    Match_clique *clique = (Match_clique *) ptr->to;

	    clique->mlist = smm_mats_con_with_mlist(group, scene, clique->mlist);

	    clique->strength = (float)smm_mlist_goodness(clique->mlist);
	    clique->csize = gthres;
	}
	pot_cliques = list_append(clist, pot_cliques);
    }
    pot_cliques = sort_list(pot_cliques, clique_neg_strength, NULL);
}

static void smm_mutual_cliques(void)
{
    List   *lptr;

    for (lptr = pot_cliques; lptr != NULL; lptr = lptr->next)
    {
	Match_clique *mc = (Match_clique *) lptr->to;

	if (list_length(mc->mlist) > mc->csize)
	{
	    List   *cliques = mutual_cliques(mc->mlist, mc->csize);

	    pw_cliques = list_append(cliques, pw_cliques);
	}
    }
    pw_cliques = sort_list(pw_cliques, clique_neg_strength, NULL);
}

List   *smm_run(List * cliches)
{
    List   *mlists;

    smm_cliches_to_pot_cliques(cliches);
    smm_mutual_cliques();
    mlists = smm_pw_clique_mlists();
    return (mlists);
}
