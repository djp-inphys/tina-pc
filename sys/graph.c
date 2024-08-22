/**@(#)Graph handling.
 * @(#)Graph_node is:
 * @(#){ int type; int status; Bool bounded; float bound; float value;
 * @(#)void *to; List *cons;}
 *
 * graph.c
 *
 */

#include <stdio.h>
#include <tina/sys.h>
#include <tina/graph.h>
#include <tina/sysfuncs.h>

Graph_node *graph_node_alloc(void *ptr, int type)
/* element and set reference to ptr */

{
    Graph_node *gn;

    gn = ts_ralloc(Graph_node);
    gn->type = type;
    gn->status = 0;
    gn->bounded = false;
    gn->bound = (float)0.0;
    gn->value = (float)1.0;
    gn->to = ptr;
    gn->cons = NULL;
    return (gn);
}

void    graph_node_set(Graph_node * gn, void *ptr, int type)
{
    gn->to = ptr;
    gn->type = type;
}

List   *graph_make_list(List * list)	/* make a graph list parallel
					 * to list */
/* any old list */
{
    return (list_copy(list, (void *(*) ()) graph_node_alloc, NULL));
}

void   *graph_ref(Graph_node * gn)
{
    if (gn == NULL)
	return (NULL);

    return (gn->to);
}

List   *graph_recover_list(List * list)	/* make a list from graph list */
/* graph list */
{
    return (list_copy(list, graph_ref, NULL));
}

List   *graph_consistent_with(Graph_node * gn, List * list, Bool(*confunc) ( /* ??? */ ))
{
    List   *lptr;
    List   *cons_list = NULL;

    for (lptr = list; lptr != NULL; lptr = lptr->next)
    {
	Graph_node *gptr = (Graph_node *) lptr->to;

	if (confunc(gn->to, gptr->to) == true)
	    cons_list = ref_addtostart(cons_list, lptr->to, lptr->type);
    }
    return (cons_list);
}

void    graph_list_consistent(List * list, Bool(*confunc) ( /* ??? */ ))
{
    List   *lptr;

    for (lptr = list; lptr != NULL; lptr = lptr->next)
    {
	Graph_node *gn = (Graph_node *) lptr->to;

	list_rm_links(gn->cons);
	gn->cons = graph_consistent_with(gn, list, confunc);
    }
}

void    graph_list_set_status(List * list, int status)
{
    List   *lptr;

    for (lptr = list; lptr != NULL; lptr = lptr->next)
    {
	Graph_node *gn = (Graph_node *) lptr->to;

	gn->status = status;
    }
}
