/**@(#)Clique finding in generic graph structures
 * cliques.c
 */

#include <stdio.h>
#include <tina/sys.h>
#include <tina/graph.h>
#include <tina/sysfuncs.h>

static Viols_node *vn_alloc(Graph_node * gn)
{
    Viols_node *vn;

    if (gn == NULL)
	return (NULL);

    vn = ts_ralloc(Viols_node);
    vn->gn = gn;
    vn->status = vn->label = 0;
    vn->viols = NULL;
    return (vn);
}

static Viols_node *choose_viols(Viols_node * vn)
{
    return ((vn == NULL || vn->gn->status) ? NULL : vn);
}

static void set_violations(List * graph_list, List * viols_list)
{
    List   *lptr;

    if (viols_list == NULL)
	return;

    graph_list_set_status(graph_list, 0);

    for (lptr = viols_list; lptr != NULL; lptr = lptr->next)
    {
	Viols_node *vn;

	vn = (Viols_node *) lptr->to;	/* violation node */
	graph_list_set_status(vn->gn->cons, 1);
	vn->viols = list_copy(lptr->next, (void *(*) ()) choose_viols, NULL);
	graph_list_set_status(vn->gn->cons, 0);
    }
}

static int setviols(List * viols_list, int label)
{
    int     count = 0;
    List   *lptr;

    for (lptr = viols_list; lptr != NULL; lptr = lptr->next)
    {
	Viols_node *vn = (Viols_node *) lptr->to;

	if (!vn->label)
	{			/* not currently set */
	    vn->label = label;
	    ++count;
	}
    }
    return (count);
}

static void resetviols(List * viols_list, int label)
{
    List   *lptr;

    for (lptr = viols_list; lptr != NULL; lptr = lptr->next)
    {
	Viols_node *vn = (Viols_node *) lptr->to;

	if (vn->label == label)
	    vn->label = 0;
    }
}

static int check_viols(List * viols_list)
{
    List   *lptr;

    for (lptr = viols_list; lptr != NULL; lptr = lptr->next)
    {
	Viols_node *vn = (Viols_node *) lptr->to;

	if (!vn->label)
	    return (1);
    }
    return (0);
}

static Graph_node *vn_pick_gn(Viols_node * vn)
{
    return ((vn == NULL || vn->label) ? NULL : vn->gn);
}

static List *clique(List * viols_list)
{
    List   *lptr;

    for (lptr = viols_list; lptr != NULL; lptr = lptr->next)
    {
	Viols_node *vn = (Viols_node *) lptr->to;

	if (vn->status && !check_viols(vn->viols))
	    return (NULL);	/* unnecessary voluntary exclusion */
    }

    return (list_copy(viols_list, (void *(*) ()) vn_pick_gn, NULL));
}

static List *cliques(List * all, List * current, float tot, int label, float thres)
{
    Viols_node *vn;

    if (current == NULL)
    {
	List   *new_clique;

	if (tot > thres && (new_clique = clique(all)) != NULL)
	    return (link_alloc((void *) new_clique, all->type));
	else
	    return (NULL);
    }
    vn = (Viols_node *) current->to;

    if (vn->gn->bounded && tot + vn->gn->bound < thres)
	return (NULL);

    if (!vn->label)
    {				/* not excluded */
	if (setviols(vn->viols, label))
	{
	    List   *list1;
	    List   *list2;

	    list1 = cliques(all, current->next, tot + vn->gn->value, label + 1, thres);
	    resetviols(vn->viols, label);
	    vn->label = label;
	    vn->status = 1;
	    list2 = cliques(all, current->next, tot, label + 1, thres);
	    vn->label = vn->status = 0;
	    return (list_append(list1, list2));
	}
	return (cliques(all, current->next, tot + vn->gn->value, label + 1, thres));
    }
    return (cliques(all, current->next, tot, label + 1, thres));
}

static void select_clique(List * viols_list)
{
    List   *lptr;

    for (lptr = viols_list; lptr != NULL; lptr = lptr->next)
    {
	Viols_node *vn = (Viols_node *) lptr->to;

	vn->gn->status = !(vn->label);
    }
}

static float maxclique(List * all, List * current, float tot, int label, float maxc)
{
    Viols_node *vn;

    if (current == NULL)
    {
	if (tot > maxc)
	{
	    select_clique(all);
	    maxc = tot;
	}
	return (maxc);
    }
    vn = (Viols_node *) current->to;

    if (vn->gn->bounded == true && tot + vn->gn->bound < maxc)
	return (maxc);

    if (!vn->label)
    {				/* not excluded */
	if (setviols(vn->viols, label))
	{
	    maxc = maxclique(all, current->next, tot + vn->gn->value, label + 1, maxc);
	    resetviols(vn->viols, label);
	    vn->label = label;
	    maxc = maxclique(all, current->next, tot, label + 1, maxc);
	    vn->label = 0;
	} else
	    maxc = maxclique(all, current->next, tot + vn->gn->value, label + 1, maxc);
    } else
	maxc = maxclique(all, current->next, tot, label + 1, maxc);
    return (maxc);
}

List   *cliques_get(List * graph_list, int csize)	/* find all cliques >
							 * csize */
/* list of graph nodes */

{
    List   *viols_list;		/* a parallel list structure */
    List   *clique_list;

    viols_list = list_copy(graph_list, (void *(*) ()) vn_alloc, NULL);
    set_violations(graph_list, viols_list);
    clique_list = cliques(viols_list, viols_list, (float) 0.0, 1, (float) csize);
    list_rm(viols_list, rfree);
    return (clique_list);
}

float   max_clique_get(List * graph_list)
/* list of graph nodes */
{
    List   *viols_list;		/* a parallel list structure */
    float   maxc;

    viols_list = list_copy(graph_list, (void *(*) ()) vn_alloc, NULL);
    set_violations(graph_list, viols_list);
    maxc = maxclique(viols_list, viols_list, (float) 0.0, 1, (float) 0.0);
    list_rm(viols_list, rfree);
    return (maxc);
}
