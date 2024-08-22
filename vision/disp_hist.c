/**@(#)
**/
/* disp_hist.c
 * 
 * Disparity histograming.
 * 
 * Used to get spatially localised approximate disparity ranges.
 * 
 * The spatial localisation leads to the construction of a 2D array of
 * histograms resulting in 3D altogether. */

#include <math.h>
#include <string.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

#define MIN_COUNT 100

/* standard binning parameters they scale with image size */
static int im_height = 256;
static int im_width = 256;
static int bin_disp = 5;
static int bin_height = 12;
static int bin_width = 16;
static int row_spacing = 2;

/* Set bining parameters for given image dimensions. */
void    disp_hist_set_params(int width, int height, int bin_h, int bin_w, int bin_d, int space)
{
    im_width = width;
    im_height = height;
    bin_height = bin_h;
    bin_width = bin_w;
    bin_disp = bin_d;
    row_spacing = space;
}

/* Update image dimensions and scale other static parameters
 * accordingly. */
void    disp_hist_set_image_dimension(int width, int height)
{
    if (width != im_width)
    {
	bin_width = bin_width * width / im_width;
	row_spacing = row_spacing * width / im_width;
	if (row_spacing == 0)
	    row_spacing = 1;
	im_width = width;
    }
    if (height != im_height)
    {
	bin_height = bin_height * height / im_height;
	im_height = height;
    }
}

/* Static histogram state parameters to simplify code. */
static Windex *histogram;
static Windex *count;
static int disp_bins;
static double lowd, upd;

/* Add to the disparity histogram array the matches between left and
 * right. Each list corresponds to a row/raster from a stereo index.
 * The match_func determines the matchable pairings (NULL is all
 * matches). */
static void raster_hist_fill(List * left, List * right, Bool(*match_func) ( /* ??? */ ))
{
    List   *lptr;
    List   *rptr;
    int   **c_index = (int **) count->index;

    for (lptr = left; right != NULL && lptr != NULL; lptr = lptr->next)
    {
	Tstring *esl, *esr;
	double  lowx, upx;
	Vec2    vl = {Vec2_id};
	Vec2    vr = {Vec2_id};
	Ipos    p = {Ipos_id};
	int    *hist;

	esl = (Tstring *) lptr->to;
	vl = str2_centroid(esl);
	lowx = vec2_x(vl) + lowd;
	upx = vec2_x(vl) + upd;

	p = wx_get_index(histogram, vl);
	hist = (int *) wx_get(histogram, ipos_y(p), ipos_x(p));
	if (hist == NULL)	/* outside histogram */
	    continue;

	c_index[ipos_y(p)][ipos_x(p)]++;

	do
	{
	    esr = (Tstring *) right->to;
	    vr = str2_centroid(esr);
	    if (vec2_x(vr) > lowx)
		break;
	    right = right->next;
	} while (right != NULL);

	for (rptr = right; rptr != NULL && vec2_x(vr) < upx;)
	{
	    if (match_func == NULL || match_func(esl, esr))
		++hist[(int) (vec2_x(vr) - vec2_x(vl) - lowd) / bin_disp];
	    rptr = rptr->next;
	    if (rptr != NULL)
	    {
		esr = (Tstring *) rptr->to;
		vr = str2_centroid(esr);
	    }
	}
    }
}

/* Fill disparity histogram array according to matches between entries
 * in the stereo indices recovered from to the left and right images.
 * 
 * Rows of the overlapping sections of the stereo indies are sampled
 * according to the static row_spacing parameter.
 * 
 * Matches from each row/raster are entered using raster_hist_fill. */
static void sindex_hist_fill(Rindex * sx_l, Rindex * sx_r, Bool(*match_func) ( /* ??? */ ))
{
    int     lrow, urow;
    int     i;

    lrow = MAX(sx_l->region->ly, sx_r->region->ly);
    urow = MIN(sx_l->region->uy, sx_r->region->uy);

    for (i = lrow; i < urow; i += row_spacing)
    {
	List   *left = (List *) sx_l->index[i];
	List   *right = (List *) sx_r->index[i];

	raster_hist_fill(left, right, match_func);
    }
}

/* Add two histograms of length n. */
static void hist_add(int *h1, int *h2, int n)
{
    int     i;

    for (i = 0; i < n; ++i)
	h1[i] += h2[i];
}

/* Accumulate disparity histograms spatially to give larger samples.
 * 
 * Each histogram and count value is replaced by the sum of histograms and
 * counts in an area around it.
 * 
 * The locality over which each individual the histogram is summed is
 * determined by the count accumulation which should exceed MIN_COUNT.
 * 
 * Hence image regions with sparse features will accumulate over larger
 * areas than those with dense features (which may not accumulate at
 * all).
 * 
 * The aim is to get a significant sample to work with. */
static void accum_hist(void)
{
    Windex *accum;
    Windex *total;
    int  ***index1, ***index2;
    int   **c1, **c2;
    int     i, j, m, n, bins, r, maxr;

    if (histogram == NULL)
	return;

    m = histogram->m;
    n = histogram->n;
    bins = disp_bins * sizeof(int);
    maxr = MAX(m, n);

    accum = wx_alloc(histogram->region, m, n, (int) NULL);
    total = wx_alloc(count->region, m, n, (int) NULL);

    index1 = (int ***) accum->index;
    index2 = (int ***) histogram->index;
    for (i = 0; i < m; ++i)
	for (j = 0; j < n; ++j)
	{
	    index1[i][j] = (int *) ralloc((unsigned) bins);
	    (void) memcpy((char *) index1[i][j], (char *) index2[i][j], bins);
	}

    c1 = (int **) total->index;
    c2 = (int **) count->index;

    for (i = 0; i < m; ++i)
	for (j = 0; j < n; ++j)
	{
	    int     tot = c2[i][j];

	    for (r = 1; r < maxr && tot < MIN_COUNT; ++r)
	    {
		int     ii, jj;

		ii = i - r;
		for (jj = j - r; ii >= 0 && jj <= j + r && jj < n; ++jj)
		{
		    if (jj < 0)
			continue;
		    tot += c2[ii][jj];
		    hist_add(index1[i][j], index2[ii][jj], disp_bins);
		}
		ii = i + r;
		for (jj = j - r; ii < m && jj <= j + r && jj < n; ++jj)
		{
		    if (jj < 0)
			continue;
		    tot += c2[ii][jj];
		    hist_add(index1[i][j], index2[ii][jj], disp_bins);
		}
		jj = j - r;
		for (ii = i - r + 1; jj >= 0 && ii < i + r && ii < m; ++ii)
		{
		    if (ii < 0)
			continue;
		    tot += c2[ii][jj];
		    hist_add(index1[i][j], index2[ii][jj], disp_bins);
		}
		jj = j + r;
		for (ii = i - r + 1; jj < n && ii < i + r && ii < m; ++ii)
		{
		    if (ii < 0)
			continue;
		    tot += c2[ii][jj];
		    hist_add(index1[i][j], index2[ii][jj], disp_bins);
		}
	    }
	    c1[i][j] = tot;
	}
    wx_free(histogram, rfree);
    histogram = accum;
    wx_free(count, (void (*) ()) NULL);
    count = total;
}

/* The final stage in disparity range estimation using histograms is to
 * interpret each individual local histogram in the context of its
 * sample size.
 * 
 * A threshold based upon sample size is used to identify lower and upper
 * disparity limits which are returned as range vectors (Vec2s). */
static void hist_set_range(Windex * range)
{
    int  ***index;
    int   **c;
    Vec2 ***disp;
    int     i, j, k, m, n;
    int     dbm1 = disp_bins - 1;

    if (range == NULL || histogram == NULL)
	return;

    m = range->m;
    n = range->n;

    if (m != histogram->m || n != histogram->n)
	return;

    index = (int ***) histogram->index;
    c = (int **) count->index;
    disp = (Vec2 ***) range->index;

    for (i = 0; i < m; ++i)
	for (j = 0; j < n; ++j)
	{
	    int     thres = c[i][j] / 5;
	    int    *hist = index[i][j];

	    for (k = 0; k < dbm1; ++k)
		if (hist[k] + hist[k + 1] > thres)
		    break;
	    if (k < dbm1)
		vec2_x(*disp[i][j]) = (float)(lowd + (k - 1) * bin_disp);
	    else
		vec2_x(*disp[i][j]) = (float)lowd;

	    for (k = dbm1; k > 0; --k)
		if (hist[k] + hist[k - 1] > thres)
		    break;
	    if (k > 0)
		vec2_y(*disp[i][j]) = (float)(lowd + (k + 1) * bin_disp);
	    else
		vec2_y(*disp[i][j]) = (float)upd;
	}
}

/* Primary external function for disparity histogram construction.
 * 
 * Requires appropriate image dimension parameters to be set prior to call
 * using either disp_hist_set_image_dimension or disp_hist_set_params.
 * 
 * Sets static overall disparity range parameters.
 * 
 * Allocates 3D histogram and 2D count arrays for the left image stereo
 * index. */
Windex *sindex_disp_hist(Rindex * sx_left, Rindex * sx_right, double lowdisp, double updisp, Bool(*match_func) ( /* ??? */ ))

/* max disp range */

/* edge string match test (NULL for all matches) */
{
    Windex *disp_range;
    Imregion *region;
    int     i, j, m, n, bins;
    int  ***index;

    if (sx_left == NULL || sx_right == NULL)
	return (NULL);

    region = sx_left->region;
    m = (region->uy - region->ly) / bin_height + 1;
    n = (region->ux - region->lx) / bin_width + 1;

    lowd = lowdisp;
    upd = updisp;
    disp_bins = (int)((upd - lowd) / bin_disp + 1);
    bins = disp_bins * sizeof(int);

    histogram = wx_alloc(region, m, n, (int) NULL);
    count = wx_alloc(region, m, n, (int) NULL);
    index = (int ***) histogram->index;
    for (i = 0; i < m; ++i)
	for (j = 0; j < n; ++j)
	{
	    index[i][j] = (int *) ralloc((unsigned) bins);
	    (void) memset((char *) index[i][j], 0, bins);
	}

    sindex_hist_fill(sx_left, sx_right, match_func);
    accum_hist();
    disp_range = disp_range_build(region, m, n);
    hist_set_range(disp_range);
    wx_free(histogram, rfree);
    wx_free(count, (void (*) ()) NULL);
    return (disp_range);
}

/* Edgerect level wrapper around sindex_disp_hist.
 * 
 * Sets the appropriate image dimension parameters and recovers left and
 * right stereo index data structures from the respective property
 * lists of the edgerects. */
Windex *er_disp_hist(Imrect * er_left, Imrect * er_right, double lowdisp, double updisp, Bool(*match_func) ( /* ??? */ ))
/* imrects containing left and right edges */
/* max disp range */

/* edge string match test (NULL for all matches) */
{
    Rindex *sx_left;
    Rindex *sx_right;

    if (er_left == NULL || er_right == NULL)
	return (NULL);

    disp_hist_set_image_dimension(er_left->width, er_left->height);
    sx_left = (Rindex *) prop_get(er_left->props, SINDEX);
    sx_right = (Rindex *) prop_get(er_right->props, SINDEX);

    if (sx_left == NULL || sx_right == NULL)
	return (NULL);
    return (sindex_disp_hist(sx_left, sx_right, lowdisp, updisp, match_func));
}
