/**@(#)
**/
/**
*
* edge.c
*
* edge handling functions
*
*
* typedef struct edgel
* {
*     int type;
*     int label;
*     struct vec2 pos;
*     float orient;
*     float contrast;
*     struct list *props;
* } Edgel;
*
*/

#include <stdio.h>
#include <tina/sys.h>
#include <tina/sys_types.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/tina_types.h>
#include <tina/edge.h>
#ifdef _PCC
#include <memory.h>
#endif

static int label;

Edgel  *edge_alloc(int type)
{
    Edgel  *edge = ts_ralloc(Edgel);

    edge->type = type;
    edge->label = label++;
    edge->pos = vec2_zero();
    edge->orient = edge->contrast = (float) 0.0;
    edge->props = NULL;
    return (edge);
}

Edge_conn *econn_alloc(void)
{
    Edge_conn *econn = ts_ralloc(Edge_conn);

    econn->conns = NULL;
    econn->c1 = econn->c2 = NULL;
    econn->count = 0;
    return (econn);
}

void    edge_free(Edgel * edge)
{
    if (edge == NULL)
	return;
    proplist_freelist(edge->props);
    rfree((void *) edge);
}

void    econn_free(Edge_conn * econn)
{
    list_rm_links(econn->conns);
    rfree((void *) econn);
}

Edgel  *edge_copy(Edgel * edge)
{
    Edgel  *copy;
    List   *proplist_copy();

    if (edge == NULL)
	return (NULL);

    copy = ts_ralloc(Edgel);
    (void) memcpy((char *) copy, (char *) edge, sizeof(Edgel));
    copy->props = proplist_copy(edge->props);
    return (copy);
}

void   *edge_sindex_prop_get(Edgel * e, int ptype)

/* type of prop required */
{
    Tstring *es;

    if (e == NULL)
	return (NULL);

    es = (Tstring *) prop_get(e->props, SINDEX);
    return ((es == NULL) ? NULL : prop_get(es->props, ptype));
}

void   *edge_prop_get(Edgel * e, int ptype)

/* type of prop required */
{
    return ((e == NULL) ? NULL : prop_get(e->props, ptype));
}

/* Get position of edge in image if possible */
Vec2    edge_image_pos(Edgel * edge)
{
    Vec2   *pos = NULL;

    if (edge->type & EDGE_GET_RECT_MASK)	/* rectified in some way */
	pos = prop_get(edge->props, IMPOS);

    return ((pos == NULL) ? edge->pos : *pos);
}

void    edge_set_type_remove_me(Edgel * edge)
{
    edge->type = REMOVE_ME;
}

/* ARGSUSED quieten lint */
void    edge_rm_on_remove_me(Edgel * edge, int type, Imrect * edgerect, int i, int j)
{
    if (edge->type == REMOVE_ME)
    {
	edge_free(edge);
	IM_PTR(edgerect, i, j) = NULL;
    }
}

void    edge_save_pos_prop(Edgel * edge, int type, int prop_type)
{
    Vec2   *p;

    if (type != EDGE || edge == NULL)
	return;

    p = vec2_alloc();
    *p = edge->pos;
    edge->props = proplist_addifnp(edge->props, (void *) p, prop_type, vec2_free, true);
}

void    edge_get_pos_prop(Edgel * edge, int type, int prop_type)
{
    Vec2   *p;

    if (type != EDGE || edge == NULL)
	return;

    p = prop_get(edge->props, prop_type);
    if (p != NULL)
	edge->pos = *p;
}

void    edge_print(FILE * fp, Edgel * edge)
{
    (void) fprintf(fp, "Edge type %d label %d ", edge->type, edge->label);
    vec2_print(fp, edge->pos);
    (void) fprintf(fp, "or %f con %f\n", edge->orient, edge->contrast);
}

void    edge_format(Edgel * edge)
{
    format("Edge type %d label %d ", edge->type, edge->label);
    vec2_format(edge->pos);
    format("or %f con %f\n", edge->orient, edge->contrast);
}
