/**@(#)
**/
/* windex.c functions to support generic list based image index binning
 * 
 * typedef struct windex { int type; int m, n; struct imregion region;
 * void ***index;          treat as List ***index; } Windex;
 * 
 */

#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void    wx_add_entry(Windex * w, void *ptr, int type, int i, int j)
{
    if (i < 0 || i >= w->m || j < 0 || j >= w->n)
	return;

    if (link_get_by_ref((List *) w->index[i][j], ptr) != NULL)
	return;			/* already referenced */
    w->index[i][j] = ref_addtostart((List *) w->index[i][j], (void *) ptr, type);
}

void    wx_rm_entry(Windex * w, void *ptr, int i, int j)
{
    if (i < 0 || i >= w->m || j < 0 || j >= w->n)
	return;

    w->index[i][j] = list_rm_ref((List *) w->index[i][j], ptr, (void (*) ()) NULL);
}

void    wx_delete_entry(Windex * w, void *entry)
{
    void ***index;
    int     n, m;
    int     i, j;

    if (w == NULL)
	return;

    m = w->m;
    n = w->n;
    index = w->index;

    for (i = 0; i < m; ++i)
	for (j = 0; j < n; ++j)
	    index[i][j] = list_rm_ref((List *) index[i][j], entry, (void (*) ()) NULL);
}

void    wx_replace_entry(Windex * w, void *entry, List * entry_list)
{
    List ***index;
    List   *copy;
    int     n, m;
    int     i, j;

    if (w == NULL)
	return;

    m = w->m;
    n = w->n;
    index = (List ***) w->index;

    for (i = 0; i < m; ++i)
	for (j = 0; j < n; ++j)
	{
	    if (link_get_by_ref(index[i][j], entry) != NULL)
	    {
		index[i][j] = list_rm_ref(index[i][j], entry, (void (*) ()) NULL);
		copy = list_copy(entry_list, (void *(*) ()) NULL, NULL);
		index[i][j] = list_append(copy, index[i][j]);
	    }
	}
}

void    wx_duplicate_entry(Windex * w, void *entry1, void *entry2, int type)
{
    List ***index;
    int     n, m;
    int     i, j;

    if (w == NULL)
	return;

    m = w->m;
    n = w->n;
    index = (List ***) w->index;

    for (i = 0; i < m; ++i)
	for (j = 0; j < n; ++j)
	    if (link_get_by_ref(index[i][j], entry1) != NULL)
		index[i][j] = ref_addtostart((List *) index[i][j], (void *) entry2, type);
}

static double wx_inth(Windex * w, Vec2 p, Vec2 v, int y)
{
    if (w == NULL)
	return (0.0);

    y *= (w->region->uy - w->region->ly) / w->m;
    y += (int)floor(w->region->ly - vec2_y(p));

    return (vec2_x(p) + vec2_x(v) * y / vec2_y(v));
}

static double wx_intv(Windex * w, Vec2 p, Vec2 v, int x)
{
    if (w == NULL)
	return (0.0);

    x *= (w->region->ux - w->region->lx) / w->n;
    x += (int)floor(w->region->lx - vec2_x(p));

    return (vec2_y(p) + vec2_y(v) * x / vec2_x(v));
}

void    wx_add_str2(Tstring * str, int type, Windex * w)
/* string of 2d positions */

/* a suitable window index */
{
    Ddlist *ptr;
    Ddlist *start;
    Ddlist *end;
    Vec2    v = {Vec2_id};
    Ipos    p = {Ipos_id};
    Ipos    pnew = {Ipos_id};

    if (str == NULL)
	return;

    start = str->start;
    end = str->end;

    ptr = start;
    DD_GET_POS2(ptr, v);
    p = wx_get_index(w, v);
    wx_add_entry(w, (void *) str, type, ipos_y(p), ipos_x(p));
    do
    {
	ptr = ptr->next;
	DD_GET_POS2(ptr, v);
	pnew = wx_get_index(w, v);
	if (ipos_equal(pnew, p) == false)
	{
	    p = pnew;
	    wx_add_entry(w, (void *) str, type, ipos_y(p), ipos_x(p));
	}
    }
    while (ptr != end);
}

void    wx_add_line(Windex * w, void *ptr, int type, Vec2 p1, Vec2 p2)
{
    Vec2    v = {Vec2_id};
    Ipos    i1 = {Ipos_id};
    Ipos    i2 = {Ipos_id};
    int     m, n;

    if (w == NULL)
	return;

    m = w->m;
    n = w->n;
    v = vec2_diff(p2, p1);

    if (fabs(vec2_x(v)) > fabs(vec2_y(v)))	/* horizontal */
    {
	int     fi, li, fj, lj;
	int     i, j, inc;

	if (vec2_y(v) < 0)
	{
	    SWAP(Vec2, p1, p2)
	    /* BUG passing  double AND Vec2 to vec2 */
	    /* v = vec2(-1.0, v); */
		v = vec2(-1.0, 0.0);
	}
	i1 = wx_get_index(w, p1);
	i2 = wx_get_index(w, p2);

	if (i2.y < 0 || i1.y >= m)
	    return;

	inc = (vec2_x(v) > 0) ? 1 : -1;

	if (i1.y < 0)
	{
	    fi = 0;
	    fj = (int)floor(wx_inth(w, p1, v, 0));
	} else
	{
	    fi = i1.y;
	    fj = i1.x;
	}

	if (i2.y >= m)
	{
	    li = m;
	    lj = (int)floor(wx_inth(w, p1, v, m));
	} else
	{
	    li = i2.y;
	    lj = i2.x;
	}

	j = fj;
	for (i = fi; i < li; ++i, j -= inc)	/* --j to include above
						 * and below raster */
	{
	    int     nj = (int)floor(wx_inth(w, p1, v, i + 1));

	    if (nj > lj)	/* only true on last iteration */
		nj = lj;

	    for (; j <= nj; j += inc)
		wx_add_entry(w, ptr, type, i, j);
	}
    } else
    {
	int     fi, li, fj, lj;
	int     i, j, inc;

	if (vec2_x(v) < 0)
	{
	    SWAP(Vec2, p1, p2)
	    /* BUG passing  double AND Vec2 to vec2 */
	    /* v = vec2(-1.0, v); */
		v = vec2(-1.0, 0.0);
	}
	i1 = wx_get_index(w, p1);
	i2 = wx_get_index(w, p2);

	if (i2.x < 0 || i1.x >= n)
	    return;

	inc = (vec2_y(v) > 0) ? 1 : -1;

	if (i1.x < 0)
	{
	    fj = 0;
	    fi = (int)floor(wx_intv(w, p1, v, 0));
	} else
	{
	    fj = i1.x;
	    fi = i1.y;
	}

	if (i2.x >= m)
	{
	    lj = m;
	    li = (int)floor(wx_intv(w, p1, v, n));
	} else
	{
	    lj = i2.x;
	    li = i2.y;
	}

	i = fi;
	for (j = fj; j < lj; ++j, i -= inc)	/* --j to include above
						 * and below raster */
	{
	    int     ni = (int)floor(wx_intv(w, p1, v, j + 1));

	    if (ni > li)	/* only true on last iteration */
		ni = li;

	    for (; i <= ni; i += inc)
		wx_add_entry(w, ptr, type, i, j);
	}
    }
}
