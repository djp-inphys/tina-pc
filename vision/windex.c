/**@(#)
**/
/* windex.c functions to support generic image index binning
 * 
 * typedef struct windex { int type; int m, n; struct imregion region;
 * void ***index; } Windex;
 * 
 */

#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

Windex *wx_alloc(Imregion * region, int m, int n, int type)
{
    Windex *w;
    Imregion *roi_copy();

    w = ts_ralloc(Windex);

    w->index = parray_alloc(0, 0, m, n);
    w->type = type;
    w->region = roi_copy(region);
    w->m = m;
    w->n = n;

    return (w);
}

void    wx_set(Windex * w, void *ptr, int i, int j, void (*freefunc) ( /* ??? */ ))
{
    if (i < 0 || i >= w->m || j < 0 || j >= w->n)
	return;

    if (freefunc != NULL)
	freefunc(w->index[i][j]);

    w->index[i][j] = ptr;
}

void   *wx_get(Windex * w, int i, int j)
{
    if (i < 0 || i >= w->m || j < 0 || j >= w->n)
	return (NULL);

    return (w->index[i][j]);
}

Bool    wx_in_index(Windex * w, int i, int j)
{
    return ((i < 0 || i >= w->m || j < 0 || j >= w->n) ? false : true);
}

void    wx_free(Windex * w, void (*freefunc) ( /* ??? */ ))
{
    void ***index;
    int     n, m;
    int     i, j;

    if (w == NULL)
	return;

    m = w->m;
    n = w->n;
    index = w->index;

    if (freefunc != NULL)
	for (i = 0; i < m; ++i)
	    for (j = 0; j < n; ++j)
		freefunc(index[i][j]);

    parray_free((char **) index, 0, 0, m, n);
    rfree((void *) w);
}

Ipos    wx_get_index(Windex * w, Vec2 p)
{
    Ipos    i = {Ipos_id};

    if (w == NULL)
	return (ipos(-1, -1));	/* unset dummy value */

    ipos_y(i) = (int)floor( w->m * (vec2_y(p) - w->region->ly) / (w->region->uy - w->region->ly));
    ipos_x(i) = (int)floor( w->n * (vec2_x(p) - w->region->lx) / (w->region->ux - w->region->lx));
    return (i);
}

Vec2    wx_get_pos2(Windex * w, Ipos i)
{
    Vec2    v = {Vec2_id};
    float   x, y;

    x = (float)ipos_x(i);
    y = (float)ipos_y(i);

    vec2_x(v) = w->region->lx + x * (w->region->ux - w->region->lx) / w->n;
    vec2_y(v) = w->region->ly + y * (w->region->uy - w->region->ly) / w->m;
    return (v);
}

Vec2    wx_get_mid_pos2(Windex * w, Ipos i)
{
    Vec2    v = {Vec2_id};
    float   x, y;

    x = (float)(ipos_x(i) + 0.5);
    y = (float)(ipos_y(i) + 0.5);

    vec2_x(v) = w->region->lx + x * (w->region->ux - w->region->lx) / w->n;
    vec2_y(v) = w->region->ly + y * (w->region->uy - w->region->ly) / w->m;
    return (v);
}
