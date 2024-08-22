/**@(#)
**/
/* linkedge.c
 * 
 * functions to connect edge strings
 * 
 * rewriten to use static variables rather than property list for data
 * manipulatin
 * 
 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sys_types.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/tina_types.h>
#include <tina/visionfuncs.h>
#include <tina/edge.h>

#define MAX_GAP 3
#define SPUR_LENGTH_THRES 5
#define TEE_ORIENTATION_THRES PIBY2

/* lists of special edge points and strings manipulated by linking
 * functions */

static List *junc_list;
static List *term_list;
static List *string_list;

static void edge_set_conn_type_on(Edgel * edge)
{
    edge->type &= EDGE_SET_CONN_MASK;
    edge->type |= EDGE_CONN;
}

#if 0
static void edge_set_conn_type_off(Edgel * edge)
{
    edge->type &= EDGE_SET_CONN_MASK;
}

#endif

static void edge_set_conn_type(Edgel * edge)
{
    Edge_conn *econn;

    if (edge == NULL || !(edge->type & EDGE_GET_CONN_MASK))
	return;

    edge->type &= EDGE_SET_CONN_MASK;
    econn = (Edge_conn *) prop_get(edge->props, EDGE_CONN);

    if (econn == NULL)
	edge->type |= EDGE_NOLINK;

    switch (econn->count)
    {
    case 0:
	edge->type |= EDGE_NOLINK;
	break;
    case 1:
	{
	    edge->type |= EDGE_TERMIN;
	    break;
	}
    case 2:
	edge->type |= EDGE_CONN;
	break;
    default:
	{
	    edge->type |= EDGE_JUNC;
	    break;
	}
    }
}

/* ARGSUSED quieten lint */
static void edge_set_conns(Edgel * edge, int type, Imrect * er, int i, int j)

/* not used */

/* edgerect location */
{
    Edgel  *eptr;
    Edgel  *er_get_edge();
    Edge_conn *econn;
    Edge_conn *econn_alloc();
    void    econn_free();
    int     n = 0, e = 0, w = 0, s = 0;

    if (er == NULL || edge == NULL || !(edge->type & EDGE_GET_CONN_MASK))
	return;

    if ((econn = (Edge_conn *) prop_get(edge->props, EDGE_CONN)) == NULL)
    {
	econn = econn_alloc();
	edge->props = proplist_add(edge->props, (void *) econn, EDGE_CONN, econn_free);
    }
    econn->c1 = NULL;
    econn->c2 = NULL;
    list_rm_links(econn->conns);
    econn->conns = NULL;
    econn->count = 0;

    if ((eptr = er_get_edge(er, i - 1, j)) != NULL &&
	eptr->type & EDGE_GET_CONN_MASK)
    {
	n = 1;
	econn->conns = link_addtostart((List *) econn->conns, link_alloc((void *) eptr, EDGE));
	econn->count++;
    }
    if ((eptr = er_get_edge(er, i + 1, j)) != NULL &&
	eptr->type & EDGE_GET_CONN_MASK)
    {
	s = 1;
	econn->conns = link_addtostart((List *) econn->conns, link_alloc((void *) eptr, EDGE));
	econn->count++;
    }
    if ((eptr = er_get_edge(er, i, j - 1)) != NULL &&
	eptr->type & EDGE_GET_CONN_MASK)
    {
	e = 1;
	econn->conns = link_addtostart((List *) econn->conns, link_alloc((void *) eptr, EDGE));
	econn->count++;
    }
    if ((eptr = er_get_edge(er, i, j + 1)) != NULL &&
	eptr->type & EDGE_GET_CONN_MASK)
    {
	w = 1;
	econn->conns = link_addtostart((List *) econn->conns, link_alloc((void *) eptr, EDGE));
	econn->count++;
    }
    if (!n && !w && (eptr = er_get_edge(er, i - 1, j + 1)) != NULL &&
	eptr->type & EDGE_GET_CONN_MASK)
    {
	econn->conns = link_addtostart((List *) econn->conns, link_alloc((void *) eptr, EDGE));
	econn->count++;
    }
    if (!n && !e && (eptr = er_get_edge(er, i - 1, j - 1)) != NULL &&
	eptr->type & EDGE_GET_CONN_MASK)
    {
	econn->conns = link_addtostart((List *) econn->conns, link_alloc((void *) eptr, EDGE));
	econn->count++;
    }
    if (!s && !w && (eptr = er_get_edge(er, i + 1, j + 1)) != NULL &&
	eptr->type & EDGE_GET_CONN_MASK)
    {
	econn->conns = link_addtostart((List *) econn->conns, link_alloc((void *) eptr, EDGE));
	econn->count++;
    }
    if (!s && !e && (eptr = er_get_edge(er, i + 1, j - 1)) != NULL &&
	eptr->type & EDGE_GET_CONN_MASK)
    {
	econn->conns = link_addtostart((List *) econn->conns, link_alloc((void *) eptr, EDGE));
	econn->count++;
    }
    switch (econn->count)
    {
    case 0:
	break;
    case 1:			/* termination point: add to
				 * termination list */
	term_list = ref_addtostart((List *) term_list, (void *) edge, EDGE);
	break;
    case 2:			/* standard connect: now finished with */
	econn->c1 = (Edgel *) econn->conns->to;
	econn->c2 = (Edgel *) econn->conns->next->to;
	list_rm_links(econn->conns);
	econn->conns = NULL;
	break;
    default:			/* potential junction: add to junction
				 * list */
	{
	    junc_list = ref_addtostart((List *) junc_list, (void *) edge, EDGE);
	    break;
	}
    }
}

static List *bridge_small_gaps(List * terms)
/* list of termination points */
{
    List   *lptr1;
    List   *lptr2;
    List   *lmin;
    Edgel  *edge1;
    Edgel  *edge2;
    Edge_conn *conn1;
    Edge_conn *conn2;
    double  min_diff, diff;
    Vec2    v1 = {Vec2_id};
    Vec2    v2 = {Vec2_id};
    Vec2    v = {Vec2_id};

    if (terms == NULL || terms->next == NULL)
	return (terms);

    for (lptr1 = terms; lptr1->next != NULL; lptr1 = lptr1->next)
    {
	if (lptr1->type == REMOVE_ME)
	    continue;

	edge1 = (Edgel *) lptr1->to;
	conn1 = (Edge_conn *) prop_get(edge1->props, EDGE_CONN);
	v1 = vec2_diff(edge1->pos, ((Edgel *) (conn1->conns->to))->pos);
	v1 = vec2_unit(v1);
	lmin = NULL;
	min_diff = MAX_GAP;

	for (lptr2 = lptr1->next; lptr2 != NULL; lptr2 = lptr2->next)
	{
	    if (lptr2->type == REMOVE_ME)
		continue;

	    edge2 = (Edgel *) lptr2->to;

	    v = vec2_diff(edge2->pos, edge1->pos);
	    diff = vec2_mod(v);
	    if (diff > min_diff)
		continue;

	    v = vec2_unit(v);
	    if (vec2_dot(v1, v) < 0.9)
		continue;

	    conn2 = (Edge_conn *) prop_get(edge2->props, EDGE_CONN);
	    v2 = vec2_diff(edge2->pos, ((Edgel *) (conn2->conns->to))->pos);
	    v2 = vec2_unit(v2);

	    if (vec2_dot(v2, v) > -0.9)
		continue;

	    lmin = lptr2;
	    min_diff = diff;
	}

	if (lmin == NULL)
	    continue;

	edge2 = (Edgel *) lmin->to;
	conn2 = (Edge_conn *) prop_get(edge2->props, EDGE_CONN);

	conn1->c1 = conn1->conns->to;
	conn2->c1 = conn2->conns->to;
	conn1->c2 = edge2;
	conn2->c2 = edge1;
	list_rm_links(conn1->conns);
	list_rm_links(conn2->conns);
	conn1->conns = conn2->conns = NULL;
	conn1->count = conn2->count = 2;

	lptr1->type = lmin->type = REMOVE_ME;
    }
    return (list_rm_links_on_type(terms, REMOVE_ME));
}

static int shortspur(Edgel * spur, Edgel * last, int thres, int count)
{
    Edgel  *next;
    Edge_conn *conn = (Edge_conn *) prop_get(spur->props, EDGE_CONN);

    if (count > thres || conn->count > 2)	/* another junction */
	return (0);

    if (conn->count == 1)	/* a termination */
	return (count);

    next = (conn->c1 == last) ? conn->c2 : conn->c1;

    return (shortspur(next, spur, thres, count + 1));
}

static List *prunespurs(List * juncs)
{
    List   *jptr;
    int     count;

    for (jptr = juncs; jptr != NULL; jptr = jptr->next)
    {
	Edgel  *eptr = (Edgel *) jptr->to;
	Edge_conn *econn;
	List   *cptr;
	List   *short_spurs = NULL;

	econn = (Edge_conn *) prop_get(eptr->props, EDGE_CONN);

	for (cptr = econn->conns; cptr != NULL; cptr = cptr->next)
	{
	    Edgel  *spur = (Edgel *) cptr->to;
	    List   *lptr;
	    List   *link;
	    int     spur_len;

	    if ((spur_len = shortspur(spur, eptr, SPUR_LENGTH_THRES, 1)))	/* short */
	    {
		link = link_alloc((void *) cptr, spur_len);
		if (short_spurs == NULL || spur_len < short_spurs->type)
		    short_spurs = link_addtostart((List *) short_spurs, link);
		else
		{
		    for (lptr = short_spurs; lptr->next != NULL; lptr = lptr->next)
			if (spur_len < lptr->next->type)
			    break;
		    link_addafter(lptr, link);
		}
	    }
	}

	if (short_spurs == NULL)
	    continue;

	for (cptr = short_spurs, count = econn->count; cptr != NULL; cptr = cptr->next)
	{
	    Edge_conn *sconn;
	    Edgel  *spur = (Edgel *) ((List *) cptr->to)->to;

	    sconn = (Edge_conn *) prop_get(spur->props, EDGE_CONN);

	    if (sconn->count == 1)	/* terminal */
	    {
		list_rm_links(sconn->conns);
		sconn->conns = NULL;
		sconn->count = 0;
		term_list = list_rm_ref(term_list, (void *) spur, (void (*) ()) NULL);
	    } else
	    {
		/* sconn->count==2 */
		if (sconn->c1 == eptr)
		    sconn->conns = link_alloc((void *) sconn->c2, EDGE);
		else
		    sconn->conns = link_alloc((void *) sconn->c1, EDGE);
		sconn->c1 = sconn->c2 = NULL;
		sconn->count = 1;
		term_list = ref_addtostart((List *) term_list, (void *) spur, EDGE);
	    }
	    ((List *) cptr->to)->type = REMOVE_ME;
	    if (--count == 2)	/* simple connection */
		break;
	}
	list_rm_links(short_spurs);
	econn->conns = list_rm_links_on_type(econn->conns, REMOVE_ME);
    }

    for (jptr = juncs; jptr != NULL; jptr = jptr->next)
    {
	Edgel  *eptr = (Edgel *) jptr->to;
	Edge_conn *econn;
	List   *cptr;

	econn = (Edge_conn *) prop_get(eptr->props, EDGE_CONN);
	econn->count = 0;
	for (cptr = econn->conns; cptr != NULL; cptr = cptr->next)
	    ++econn->count;

	switch (econn->count)
	{
	case 0:
	    jptr->type = REMOVE_ME;
	    break;
	case 1:
	    term_list = ref_addtostart((List *) term_list, (void *) eptr, EDGE);
	    jptr->type = REMOVE_ME;
	    break;
	case 2:
	    econn->c1 = (Edgel *) econn->conns->to;
	    econn->c2 = (Edgel *) econn->conns->next->to;
	    list_rm_links(econn->conns);
	    econn->conns = NULL;
	    jptr->type = REMOVE_ME;
	    break;
	default:
	    break;
	}
    }
    return (list_rm_links_on_type(juncs, REMOVE_ME));
}

static void rmjuncs(List * juncs)
{
    List   *jptr;

    for (jptr = juncs; jptr != NULL; jptr = jptr->next)
    {
	Edgel  *eptr = (Edgel *) jptr->to;
	Edge_conn *econn;
	List   *cptr;

	econn = (Edge_conn *) prop_get(eptr->props, EDGE_CONN);

	for (cptr = econn->conns; cptr != NULL; cptr = cptr->next)
	{
	    Edgel  *nptr = (Edgel *) cptr->to;
	    Edge_conn *nconn;

	    nconn = (Edge_conn *) prop_get(nptr->props, EDGE_CONN);
	    switch (nconn->count)
	    {
	    case 1:
		rfree((void *) nconn->conns);
		nconn->conns = NULL;
		nconn->count = 0;
		term_list = list_rm_ref(term_list, (void *) nptr, (void (*) ()) NULL);
		break;
	    case 2:
		{
		    Edgel  *keep = (nconn->c1 == eptr) ? nconn->c2 : nconn->c1;

		    nconn->conns = link_alloc((void *) keep, EDGE);
		    nconn->count = 1;
		    term_list = ref_addtostart((List *) term_list, (void *) nptr, EDGE);
		    break;
		}
	    default:
		break;		/* junctions take care of themselves */
	    }
	}
	list_rm_links(econn->conns);
	econn->conns = NULL;
	econn->count = 0;
	edge_set_type_remove_me(eptr);
    }
}

static List *prunejuncs(List * juncs)
{
    List   *jptr;

    for (jptr = juncs; jptr != NULL; jptr = jptr->next)
    {
	Edgel  *eptr = (Edgel *) jptr->to;
	Edge_conn *econn;
	List   *cptr;

	econn = (Edge_conn *) prop_get(eptr->props, EDGE_CONN);

	for (cptr = econn->conns; cptr != NULL; cptr = cptr->next)
	{
	    Edgel  *nptr = (Edgel *) cptr->to;
	    Edge_conn *nconn;

	    nconn = (Edge_conn *) prop_get(nptr->props, EDGE_CONN);
	    if (nconn->count > 2)	/* a neighbouring junction */
		cptr->type = REMOVE_ME;
	}
	econn->conns = list_rm_links_on_type(econn->conns, REMOVE_ME);
    }

    for (jptr = juncs; jptr != NULL; jptr = jptr->next)
    {
	Edgel  *eptr = (Edgel *) jptr->to;
	Edge_conn *econn;
	List   *cptr;

	econn = (Edge_conn *) prop_get(eptr->props, EDGE_CONN);

	econn->count = 0;
	for (cptr = econn->conns; cptr != NULL; cptr = cptr->next)
	    ++econn->count;

	switch (econn->count)
	{
	case 0:
	    jptr->type = REMOVE_ME;
	    break;
	case 1:
	    term_list = ref_addtostart((List *) term_list, (void *) eptr, EDGE);
	    jptr->type = REMOVE_ME;
	    break;
	case 2:
	    econn->c1 = (Edgel *) econn->conns->to;
	    econn->c2 = (Edgel *) econn->conns->next->to;
	    list_rm_links(econn->conns);
	    econn->conns = NULL;
	    jptr->type = REMOVE_ME;
	default:
	    break;
	}
    }
    return (list_rm_links_on_type(juncs, REMOVE_ME));
}

static List *prunetees(List * juncs)
{
    List   *jptr;

    for (jptr = juncs; jptr != NULL; jptr = jptr->next)
    {
	Edgel  *eptr = (Edgel *) jptr->to;
	Edgel  *links[3];
	Edge_conn *econn;
	Edge_conn *lconn[3];
	int     i, j;
	int     c1 = 0, c2 = 0, c3;
	float   mindif = (float)TWOPI;

	econn = (Edge_conn *) prop_get(eptr->props, EDGE_CONN);

	if (econn->count != 3)	/* not a three way junction */
	    continue;

	links[0] = (Edgel *) econn->conns->to;
	links[1] = (Edgel *) econn->conns->next->to;
	links[2] = (Edgel *) econn->conns->next->next->to;

	for (i = 0; i < 3; ++i)
	{
	    lconn[i] = (Edge_conn *) prop_get(links[i]->props, EDGE_CONN);
	    if (lconn[i]->count != 2)	/* not a simple continue */
		break;
	}
	if (i < 3)
	    continue;

	for (i = 0; i < 2; ++i)
	    for (j = i + 1; j < 3; ++j)
	    {
		float   absordif = (float)fabs(links[i]->orient - links[j]->orient);

		absordif = (float)MIN(absordif, TWOPI - absordif);

		if (absordif < mindif)
		{
		    c1 = i;
		    c2 = j;
		    mindif = absordif;
		}
	    }

	if (mindif > TEE_ORIENTATION_THRES)
	    continue;

	econn->c1 = links[c1];
	econn->c2 = links[c2];

	list_rm_links(econn->conns);
	econn->conns = NULL;
	econn->count = 2;

	jptr->type = REMOVE_ME;

	c3 = 3 - c1 - c2;
	econn = lconn[c3];	/* Edge_conn of the remaining edge */
	econn->conns = link_alloc((void *)
		 ((econn->c1 == eptr) ? econn->c2 : econn->c1), EDGE);
	econn->c1 = econn->c2 = NULL;
	econn->count = 1;
	term_list = ref_addtostart((List *) term_list, (void *) links[c3], EDGE);	/* new term */
    }
    return (list_rm_links_on_type(juncs, REMOVE_ME));
}

static Tstring *edge_getloop(Edgel * edge)
{
    Ddlist *start = NULL;
    Ddlist *end = NULL;
    Edge_conn *cptr;
    Edgel  *eptr;
    Edgel  *from;

    if (edge == NULL || !(edge->type & EDGE_GET_CONN_MASK))
	return (NULL);

    cptr = (Edge_conn *) prop_get(edge->props, EDGE_CONN);
    if (cptr->count != 2)
	return (NULL);
    start = end = dd_link_alloc((void *) edge, EDGE);
    from = edge;
    edge->type |= EDGE_LOOP;

    for (eptr = cptr->c1; eptr != edge; eptr = cptr->c1)
    {
	end = dd_link_addtoend(end, dd_link_alloc((void *) eptr, EDGE));
	cptr = (Edge_conn *) prop_get(eptr->props, EDGE_CONN);
	eptr->type |= EDGE_LOOP;
	if (cptr->c2 != from)
	    SWAP(Edgel *, cptr->c1, cptr->c2)
		from = eptr;
    }

    start->last = end;		/* to complete the loop */
    end->next = start;

    return (str_make(LOOP, start, end));
}

static void edge_find_loops(Edgel * edge)
{
    Tstring *string;

    if (edge == NULL || edge->type & EDGE_GET_LOOP_MASK ||
	(edge->type & EDGE_GET_CONN_MASK) != EDGE_CONN)
	return;

    string = edge_getloop(edge);
    if (string != NULL)
	string_list = ref_addtostart((List *) string_list, (void *) string, STRING);
}

static Tstring *edge_getstring(Edgel * term)
{
    Ddlist *start = NULL;
    Ddlist *end = NULL;
    Edge_conn *cptr;
    Edgel  *eptr;
    Edgel  *from;

    if (term == NULL)
	return (NULL);

    cptr = (Edge_conn *) prop_get(term->props, EDGE_CONN);
    if (cptr->count != 1)
	return (NULL);
    start = end = dd_link_alloc((void *) term, EDGE);
    from = term;
    term->type |= EDGE_NOT_LOOP;

    for (eptr = (Edgel *) cptr->conns->to;; eptr = cptr->c1)
    {
	end = dd_link_addtoend(end, dd_link_alloc((void *) eptr, EDGE));
	cptr = (Edge_conn *) prop_get(eptr->props, EDGE_CONN);
	eptr->type |= EDGE_NOT_LOOP;
	if (cptr->count != 2)
	    break;

	if (cptr->c2 != from)
	    SWAP(Edgel *, cptr->c1, cptr->c2)
		from = eptr;
    }

    return (str_make(STRING, start, end));
}

static List *findstrings(List * terms)
{
    List   *tptr;
    List   *strings = NULL;

    terms = list_copy(terms, (void *(*) ()) NULL, NULL);

    tptr = terms;
    while (tptr != NULL)
    {
	Tstring *sptr = edge_getstring((Edgel *) tptr->to);

	strings = link_addtostart((List *) strings, link_alloc((void *) sptr, STRING));
	(void) list_rm_ref(tptr, sptr->end->to, (void (*) ()) NULL);
	tptr = link_rm_el(tptr);
    }

    return (strings);
}

void    er_find_edge_strings(Imrect * er)
/* edge rect */
{
    void    er_apply_to_all_edges();

    if (er == NULL)
	return;

    /* first set conn field of edge type to allow all possible
     * connections */
    er_apply_to_all_edges(er, edge_set_conn_type_on, NULL);
    er_apply_to_all_edges(er, edge_set_conns, (void *) er);

    junc_list = prunespurs(junc_list);
    junc_list = prunetees(junc_list);
    junc_list = prunejuncs(junc_list);
    rmjuncs(junc_list);
    list_rm_links(junc_list);

    term_list = bridge_small_gaps(term_list);
    string_list = findstrings(term_list);
    list_rm_links(term_list);
    junc_list = term_list = NULL;

    er_apply_to_all_edges(er, edge_set_conn_type, NULL);
    er_apply_to_all_edges(er, edge_find_loops, NULL);	/* adds to string_list */

    er->props = proplist_addifnp(er->props, (void *) string_list, STRING, str_rm_list, false);
}

void    er_find_simple_edge_strings(Imrect * er)
/* edge rect */
{
    void    er_apply_to_all_edges();

    if (er == NULL)
	return;

    /* first set conn field of edge type to allow all possible
     * connections */
    er_apply_to_all_edges(er, edge_set_conn_type_on, NULL);
    er_apply_to_all_edges(er, edge_set_conns, (void *) er);

    junc_list = prunespurs(junc_list);
    rmjuncs(junc_list);
    list_rm_links(junc_list);

    string_list = findstrings(term_list);
    list_rm_links(term_list);
    junc_list = term_list = NULL;

    er_apply_to_all_edges(er, edge_set_conn_type, NULL);
    er_apply_to_all_edges(er, edge_find_loops, NULL);	/* adds to string_list */

    er->props = proplist_addifnp(er->props, (void *) string_list, STRING, str_rm_list, false);
}

List   *er_specific_edge_strings(Imrect * er, void (*func) ( /* ??? */ ), void *data)
/* edge rect */


{
    void    er_apply_to_all_edges();

    if (er == NULL)
	return ((List *) NULL);

    /* first set conn field using function */
    er_apply_to_all_edges(er, func, (void *) data);
    er_apply_to_all_edges(er, edge_set_conns, (void *) er);

    junc_list = prunespurs(junc_list);
    rmjuncs(junc_list);
    list_rm_links(junc_list);

    string_list = findstrings(term_list);
    list_rm_links(term_list);
    junc_list = term_list = NULL;

    er_apply_to_all_edges(er, edge_set_conn_type, NULL);
    er_apply_to_all_edges(er, edge_find_loops, NULL);	/* adds to string_list */

    return (string_list);
}
