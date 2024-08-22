/* @(#)Concave polygon scan conversion. apply_inside_poly(): scan
 * convert nvert-sided concave non-simple polygon with vertices at p[i]
 * for i = [0..nvert-1] by calling func() for each visible span of
 * pixels; the polygon can be clockwise or counterclockwise. Algorithm
 * does uniform point sampling at pixel centres. Inside-outside test is
 * done by Jordan's rule: a point is considered to be inside if an
 * emanating ray intersects the polygon an odd number of times. func()
 * processes the data on line y from lx to ux inclusive.
 * 
 * Concave Polygon Scan Conversion, by Paul Heckbert; modified by Jim
 * Ivins. See Glassner (editor) 1990 "Graphics Gems" p 681 (Academic
 * Press) */
#include <tina/math.h>
#include <tina/sysfuncs.h>

typedef struct
{
    double  x;			/* x coordinate of intersection with
				 * current scanline. */
    double  dx;			/* change in x WRT y. */
    int     i;			/* Edge number: edge i goes from pt[i]
				 * to pt[i+1] */
}

        Poly_edge;

static Vec2 *pt = NULL;		/* Array of vertices. */
static Poly_edge *active = NULL;/* Active edge list: edges crossing
				 * scanline y. */

static int compare_ind(const void *u, const void *v)
{
    /* Changed by Julian Briggs 2/11/93 to match qsort */
    /**
      int     ind_u = vec2_y (pt[*(int*)u]);
      int     ind_v = vec2_y (pt[*(int*)v]);
      **/
    int     ind_u = (int) vec2_y(pt[*(int *) u]);
    int     ind_v = (int) vec2_y(pt[*(int *) v]);

    return (ind_u == ind_v) ? 0 : (ind_u < ind_v ? -1 : +1);
}

static int compare_active(const void *u, const void *v)
{
    /* Changed by Julian Briggs 2/11/93 to match qsort */
    /* return (u->x <= v->x) ? -1 : +1; */
    return (((Poly_edge *) u)->x <= ((Poly_edge *) v)->x) ? -1 : +1;
}

static void delete(int i, int *nact)
{
    int     j;

    for (j = 0; active[j].i != i; j++)
	if (j >= *nact)
	    return;
    (*nact)--;
    memcpy(&active[j], &active[j + 1], (*nact - j) * sizeof(active[0]));
}

static void insert(int i, int y, int n, int *nact)
{
    int     j;
    double  dx;
    Vec2   *p;
    Vec2   *q;

    j = i < n - 1 ? i + 1 : 0;
    if (vec2_x(pt[i]) < vec2_x(pt[j]))
    {
	p = &pt[i];
	q = &pt[j];
    } else
    {
	p = &pt[j];
	q = &pt[i];
    }

    active[*nact].dx = dx = (vec2_x(*q) - vec2_x(*p))
	/ (vec2_y(*q) - vec2_y(*p));
    active[*nact].x = dx * (y + 0.5 - vec2_y(*p)) + vec2_x(*p);
    active[*nact].i = i;
    (*nact)++;
}

void    apply_inside_poly(int nvert, Vec2 * p, int max_x, int max_y,
			          void (*func) (), void *data)
{
    int     nact;		/* Number of active edges. */
    int     k, ly, uy, y, i, j, lx, ux;
    int    *ind;		/* Sorted list of vertex indices */

    pt = p;

    if ((nvert <= 0) || !p)
	return;

    ind = tvector_alloc(0, nvert, int);
    active = tvector_alloc(0, nvert, Poly_edge);

    /* Create a y-sorted array of indices ind[k] into ertex list */
    for (k = 0; k < nvert; k++)
	ind[k] = k;

    qsort(ind, nvert, sizeof(ind[0]), compare_ind);

    nact = 0;
    k = 0;
    /* BUGFIX Julian Briggs 1/11/93: ceil & floor take & return double */
    ly = MAX(0, (int) ceil((double) vec2_y(pt[ind[0]]) - 0.5));	/* Polygon y min */
    uy = MIN(max_y - 1,
	     (int) floor((double) vec2_y(pt[ind[nvert - 1]]) - 0.5));	/* Polygon y max */

    for (y = ly; y <= uy; y++)
    {
	for (; k < nvert && vec2_y(pt[ind[k]]) <= y + 0.5; k++)
	{
	    i = ind[k];

	    j = i > 0 ? i - 1 : nvert - 1;	/* Vertex before i */
	    if (vec2_y(pt[j]) <= y - 0.5)
		delete(j, &nact);
	    else if (vec2_y(pt[j]) > y + 0.5)
		insert(j, y, nvert, &nact);

	    j = i < nvert - 1 ? i + 1 : 0;	/* Vertex after i */
	    if (vec2_y(pt[j]) <= y - 0.5)
		delete(i, &nact);
	    else if (vec2_y(pt[j]) > y + 0.5)
		insert(i, y, nvert, &nact);
	}

	qsort(active, nact, sizeof(active[0]), compare_active);

	/* Draw horizontal segments for scanline y. Span between j and
	 * j+1 is inside polygon. Span between j+1 and j+2 is outside
	 * polygon. */
	for (j = 0; j < nact; j += 2)
	{
	    lx = (int) ceil(active[j].x - 0.5);	/* Left end of span */
	    if (lx < 0)
		lx = 0;

	    ux = (int) floor(active[j + 1].x - 0.5);	/* Right end of span */
	    if (ux >= max_x)
		ux = max_x - 1;

	    (*func) (y, lx, ux, data);

	    active[j].x += active[j].dx;
	    active[j + 1].x += active[j + 1].dx;
	}
    }
    tvector_free(ind, 0, int);
    tvector_free(active, 0, Poly_edge);
}
