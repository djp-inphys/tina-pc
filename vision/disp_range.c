/**@(#)
**/
/* disp_range.c
 * 
 * Module for managing current disparity range information.
 * 
 * Must be revised as appropriate before other stereo matching.
 * 
 * Can be used in conjuntion with disparity histogram to obtain spatial
 * map of disparity ranges directly from the edge data.
 * 
 * Subsequently provides an local index for disparity range estimates. */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* Static structure and functions to manage index of allowable
 * disparity its size should mirror dimensions of stereo index of the
 * left image. */
static Windex *disp_range;

void    disp_range_set(Windex * range)
{
    wx_free(disp_range, rfree);
    disp_range = range;
}

Windex *disp_range_get(void)
{
    return (disp_range);
}

/* Enquire about the disparity range corresponding to image location
 * (wrt stereo index image region). */
Bool    disp_range_at_pos2(Vec2 v, double *low_d, double *up_d)
{
    Ipos    p = {Ipos_id};
    Vec2   *vp;

    if (disp_range == NULL)
	return (false);

    p = wx_get_index(disp_range, v);
    vp = (Vec2 *) wx_get(disp_range, ipos_y(p), ipos_x(p));

    if (vp == NULL)
	return (false);

    *low_d = vec2_x(*vp);
    *up_d = vec2_y(*vp);
    return (true);
}

/* Fix the disparity range of the disparity range index. */
void    disp_range_fix_disparity(Windex * w, double low_d, double up_d)
{
    Vec2 ***index;
    int     i, j;
    int     n, m;

    if (w == NULL)
	return;

    m = w->m;
    n = w->n;
    index = (Vec2 ***) w->index;

    for (i = 0; i < m; ++i)
	for (j = 0; j < n; ++j)
	    *index[i][j] = vec2(low_d, up_d);
}

/* Make a disparity range index corresponding to given region and
 * dimensions. */
Windex *disp_range_build(Imregion * region, int m, int n)
{
    Windex *w;
    Vec2 ***index;
    int     i, j;

    if (region == NULL)
	return (NULL);

    w = wx_alloc(region, m, n, DISPARITY);
    m = w->m;
    n = w->n;
    index = (Vec2 ***) w->index;

    for (i = 0; i < m; ++i)
	for (j = 0; j < n; ++j)
	    index[i][j] = vec2_make(vec2_zero());
    return (w);
}

/* Build a disparity range window for the edgerect uses the region of
 * the associated stereo index. */
Windex *er_disp_range_build(Imrect * er, int m, int n)
{
    Rindex *sx;

    if (er == NULL)
	return (NULL);

    sx = (Rindex *) prop_get(er->props, SINDEX);
    if (sx == NULL)
	return (NULL);

    return (disp_range_build(sx->region, m, n));
}
