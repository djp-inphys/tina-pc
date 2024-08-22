/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sys_types.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/tina_types.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void    get_corner_matches(Rindex * fx1, Rindex * fx2, int pos_type, Imregion(*search_func) ( /* ??? */ ), void* (*make_match) ( /* ??? */ ))
{
    int     ly, uy;
    int     i;
    Imregion *index_region;

    if (fx1 == NULL || fx2 == NULL)
	return;

    if ((index_region = fx1->region) == NULL)
	return;

    ly = index_region->ly;
    uy = index_region->uy;

    for (i = ly; i < uy; ++i)
    {
	List   *ledge = fx1->index[i];

	while (ledge != NULL)
	{
	    Edgel  *edge = (Edgel *) ledge->to;

	    if (edge != NULL)
		get_corner_match(edge, fx2, pos_type, search_func(edge), make_match);
	    ledge = ledge->next;
	}
    }
}

void    apply_func_to_windex(Rindex * fx, void *(*func) ( /* ??? */ ), void *data)
{
    int     ly, uy;
    int     i;
    Imregion *index_region;

    if (fx == NULL)
	return;

    if ((index_region = fx->region) == NULL)
	return;

    ly = index_region->ly;
    uy = index_region->uy;

    for (i = ly; i < uy; ++i)
    {
	List   *ledge = fx->index[i];

	while (ledge != NULL)
	{
	    Edgel  *edge = (Edgel *) ledge->to;

	    if (edge != NULL)
		func(edge, data);
	    ledge = ledge->next;
	}
    }
}

void    get_corner_match(Edgel * edge1, Rindex * fx2, int pos_type, Imregion search_region, void *(*make_match) ( /* ??? */ ))
{
    int     lx, ly, ux, uy;
    int     i;
    Imregion *index_region;

    if (edge1 == NULL || fx2 == NULL)
	return;

    if ((index_region = fx2->region) == NULL)
	return;

    lx = search_region.lx;
    ly = search_region.ly;
    ux = search_region.ux;
    uy = search_region.uy;

    if (lx < index_region->lx)
	lx = index_region->lx;
    if (ux > index_region->ux)
	ux = index_region->ux;
    if (lx > ux)
	return;
    if (ly < index_region->ly)
	ly = index_region->ly;
    if (uy > index_region->uy)
	uy = index_region->uy;
    if (ly > uy)
	return;

    for (i = ly; i < uy; ++i)
    {
	List   *ledge = fx2->index[i];

	while (ledge != NULL)
	{
	    Edgel  *edge2 = (Edgel *) ledge->to;
	    Vec2   *rect;

	    if (edge2 != NULL)
	    {
		rect = (Vec2 *) prop_get(edge2->props, pos_type);
		if (rect == NULL)
		    rect = &edge2->pos;
		if ((int) rect->el[0] >= lx && (int) rect->el[0] <= ux)
		    make_match(edge1, edge2);
	    }
	    ledge = ledge->next;
	}
    }
}

static double match_weight(Match * match)
{
    return (match->weight);
}

static void rm_match_list(List * list)
{
    list_rm(list, match_free);
}

void    add_match_to_props(Edgel * edge, void *match, int type)
{
    List   *list;

    if (edge == NULL || match == NULL)
	return;

    list = prop_get(edge->props, type);
    list = list_add_sorted(list, link_alloc((void *) match, POT_MATCH), match_weight);
    edge->props = proplist_addifnp(edge->props, (void *) list, type, rm_match_list, false);
}

void    rm_match_from_props(Edgel * edge, int *type)
{
    edge->props = proplist_free(edge->props, *type);
}

void    rm_corner_matches(Rindex * fx, int *type)
{
    apply_func_to_windex(fx, (void *(*) ()) rm_match_from_props, (void *) type);
}

void   *get_matches_list(Edgel * edgel, int *type)
{
    List   *matches;

    matches = prop_get(edgel->props, *type);
    return ((void *) matches);
}

Matrix *add_patch_to_props(Edgel * edge, Imrect * image, float sigma)
{
    static Matrix *weight = NULL;
    Matrix *patch;
    float   x0, y0;
    float   x, y;
    float   dx, dy;
    float   norm = (float)0.0;
    int     i, j;

    if (edge == NULL || image == NULL)
	return (NULL);
    if (weight == NULL)
    {
	weight = matrix_alloc(5, 5, matrix_full, float_v);
	for (x = (float)-2.0 * sigma, i = 0; x <= 2.0 * sigma; x += sigma, i++)
	    for (y = (float)-2.0 * sigma, j = 0; y <= 2.0 * sigma; y += sigma, j++)
		weight->el.float_v[i][j] = (float)(exp(-(x * x + y * y) / (4.0 * sigma * sigma)));
    }
    if ((patch = matrix_alloc(5, 5, matrix_full, float_v)) == NULL)
	return (NULL);
    x0 = edge->pos.el[0];
    y0 = edge->pos.el[1];
    for (x = (float)-2.0 * sigma, i = 0; x <= 2.0 * sigma; x += sigma, i++)
	for (y = (float)-2.0 * sigma, j = 0; y <= 2.0 * sigma; y += sigma, j++)
	{
	    patch->el.float_v[i][j] = (float)(weight->el.float_v[i][j] *
		im_get_quadinterpf(image, x0 + x, y0 + y, &dx, &dy));
	    norm += patch->el.float_v[i][j] * patch->el.float_v[i][j];
	}
    if (norm != 0.0)
	norm = (float)(1.0 / sqrt(norm));
    else
	norm = (float)0.0;
    for (i = 0; i < 5; i++)
	for (j = 0; j < 5; j++)
	    patch->el.float_v[i][j] *= norm;

    edge->props = proplist_add(edge->props, (void *) patch, PATCH, matrix_free);
    return (patch);
}

float   corner_correlation(Imrect * image1, Imrect * image2, Edgel * edge1, Edgel * edge2, float sigma)
{
    float   total = (float)0.0;
    int     i, j;
    Matrix *patch1;
    Matrix *patch2;

    if (edge1 == NULL || edge2 == NULL)
	return ((float)0.0);

    if ((patch1 = prop_get(edge1->props, PATCH)) == NULL)
	if ((patch1 = add_patch_to_props(edge1, image1, sigma)) == NULL)
	    return ((float)0.0);

    if ((patch2 = prop_get(edge2->props, PATCH)) == NULL)
	if ((patch2 = add_patch_to_props(edge2, image2, sigma)) == NULL)
	    return ((float)0.0);

    for (i = 0; i < 5; i++)
	for (j = 0; j < 5; j++)
	    total += patch1->el.float_v[i][j] * patch2->el.float_v[i][j];

    return (total);
}

float   good_corner(Edgel * edge1, Edgel * edge2, float region, float asymetry, Imrect * image1, Imrect * image2)
{
    float   corr, asym;

    if (edge1 == NULL || edge2 == NULL)
	return ((float)0.0);

    /* weak constraint on relative value of corner strength */
    asym = (edge1->contrast - edge2->contrast)
	/ (edge1->contrast + edge2->contrast);
    if (fabs(asym) > asymetry)
	return ((float)0.0);
    corr = corner_correlation(image1, image2, edge1, edge2, region);

    return (corr);
}

float   correlation(Imrect * image1, Imrect * image2, float x1, float y1, float x2, float y2, float sigma)
{
    float   total = (float)0.0;
    float   norm1 = (float)0.0;
    float   norm2 = (float)0.0;
    float   grey1, grey2, dx, dy;
    float   x, y;
    static Matrix *weight = NULL;
    int     i, j;

    if (weight == NULL)
    {
	weight = matrix_alloc(5, 5, matrix_full, float_v);
	for (x = (float)-2.0 * sigma, i = 0; x <= 2.0 * sigma; x += sigma, i++)
	    for (y = (float)-2.0 * sigma, j = 0; y <= 2.0 * sigma; y += sigma, j++)
		weight->el.float_v[i][j] = (float)(exp(-(x * x + y * y) / (2.0 * sigma * sigma)));
    }
    for (x = (float)-2.0 * sigma, i = 0; x <= 2.0 * sigma; x += sigma, i++)
    {
	for (y = (float)-2.0 * sigma, j = 0; y <= 2.0 * sigma; y += sigma, j++)
	{
	    grey1 = (float)im_get_quadinterpf(image1, x1 + x, y1 + y, &dx, &dy);
	    grey2 = (float)im_get_quadinterpf(image2, x2 + x, y2 + y, &dx, &dy);
	    total += weight->el.float_v[i][j] * grey1 * grey2;
	    norm1 += weight->el.float_v[i][j] * grey1 * grey1;
	    norm2 += weight->el.float_v[i][j] * grey2 * grey2;
	}
    }
    total /= (float)sqrt(norm1 * norm2);
    return (total);
}

void   *get_fixed_match(Edgel * edgel, int *type)
{
    List   *matches;

    matches = prop_get(edgel->props, *type);
    if (matches != NULL && matches->type == FIXED_MATCH)
	return (matches->to);
    else
	return (NULL);
}

void   *get_good_match(Edgel * edgel, int *type)
{
    List   *matches;

    matches = prop_get(edgel->props, *type);
    if (matches != NULL && matches->type == GOOD_MATCH)
	return (matches->to);
    else
	return (NULL);
}
