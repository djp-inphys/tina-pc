/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

double  curv_invar_ratio(Tstring * es1, Ddlist * d1, Tstring * es2, Ddlist * d2)
{
    double  k1, k2;
    double  theta1, theta2, r;
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    Vec2    t1 = {Vec2_id};
    Vec2    t2 = {Vec2_id};

    es_diffgeom(es1, d1, 0.4, 5.0, 25.0, &p1, &t1, &k1);
    es_diffgeom(es2, d2, 0.4, 5.0, 25.0, &p2, &t2, &k2);
    theta1 = vec2_angle(t1, vec2_diff(p1, p2));
    theta2 = vec2_angle(t2, vec2_diff(p2, p1));
    r = sin(theta1) / sin(theta2);
    r = r * r * r;
    return (k1 / k2 / r);
}

void    curv_invar_ratio_range(Tstring * es1, Ddlist * d1, Tstring * es2, Ddlist * d2, int sample, float *lowp, float *upp)
{
    Ddlist *ptr1;
    Ddlist *ptr2;
    Ddlist *start1;
    Ddlist *start2;
    Ddlist *end1;
    Ddlist *end2;
    float   low, up;
    int     i;

    start1 = es1->start;
    end1 = es1->end;
    start2 = es2->start;
    end2 = es2->end;
    for (ptr1 = d1, i = 0; i < sample; i++, ptr1 = ptr1->last)
	if (ptr1 == start1)
	    break;
    start1 = ptr1;
    for (ptr1 = d1, i = 0; i < sample; i++, ptr1 = ptr1->next)
	if (ptr1 == end1)
	    break;
    end1 = ptr1;
    for (ptr2 = d2, i = 0; i < sample; i++, ptr2 = ptr2->last)
	if (ptr2 == start2)
	    break;
    start2 = ptr2;
    for (ptr2 = d2, i = 0; i < sample; i++, ptr2 = ptr2->next)
	if (ptr2 == end2)
	    break;
    end2 = ptr2;

    low = up = (float) curv_invar_ratio(es1, d1, es2, d2);
    for (ptr1 = start1;; ptr1 = ptr1->next)
    {
	for (ptr2 = start2;; ptr2 = ptr2->next)
	{
	    if (ptr1 != d1 || ptr2 != d2)
	    {
		float   invar = (float)curv_invar_ratio(es1, ptr1, es2, ptr2);

		if (invar < low)
		    low = invar;
		if (invar > up)
		    up = invar;
	    }
	    if (ptr2 == end2)
		break;
	}
	if (ptr1 == end1)
	    break;
    }
    *upp = up;
    *lowp = low;
}

Terrain_data *curv_invar_surf(Tstring * es, int sample, int buffer, double scale)
{
    Terrain_data *surf;
    Ddlist *ptr1;
    Ddlist *ptr2;
    Ddlist *start;
    Ddlist *end = (Ddlist *) NULL;
    double  invar;
    int     n, i, j;
    int     ii, jj;

    if (es == NULL || es->start == es->end)
	return (NULL);

    for (i = 0, start = es->start;; i++, start = start->next)
    {
	if (start == end)
	    return (NULL);
	if (i >= buffer)
	    break;
    }

    for (i = 0, end = es->end;; i++, end = end->last)
    {
	if (start == end)
	    return (NULL);
	if (i >= buffer)
	    break;
    }

    for (n = i = 0, ptr1 = start;; i++, ptr1 = ptr1->next)
    {
	if (i % sample == 0)
	    ++n;
	if (ptr1 == end)
	    break;
    }

    surf = terrain_alloc(TERRAIN, n, n);

    for (i = 0, ptr1 = start;; i++, ptr1 = ptr1->next)
    {
	if (i % sample == 0)
	{
	    ii = i / sample;
	    surf->data[ii][ii] = vec3((float) i, (float) i, scale);
	    if (ptr1 == end)
		break;
	    for (j = i + 1, ptr2 = ptr1->next;; j++, ptr2 = ptr2->next)
	    {
		if (j % sample == 0)
		{
		    jj = j / sample;

		    invar = curv_invar_ratio(es, ptr1, es, ptr2);
		    invar = fabs(log(fabs(invar)));
		    surf->data[ii][jj] = vec3((float) j, (float) i, invar * scale);
		    surf->data[jj][ii] = vec3((float) i, (float) j, invar * scale);
		}
		if (ptr2 == end)
		    break;
	    }
	}
	if (ptr1 == end)
	    break;
    }
    return (surf);
}

double  curv_invar_ratio_dds(Ddlist * d1, Ddlist * d2, int n)
{
    double  k1, k2;
    double  theta1, theta2, r;
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    Vec2    t1 = {Vec2_id};
    Vec2    t2 = {Vec2_id};

    dds_diffgeom(d1, &p1, &t1, &k1, n);
    dds_diffgeom(d2, &p2, &t2, &k2, n);
    theta1 = vec2_angle(t1, vec2_diff(p1, p2));
    theta2 = vec2_angle(t2, vec2_diff(p2, p1));
    r = sin(theta1) / sin(theta2);
    r = r * r * r;
    return (k1 / k2 / r);
}

void    curv_invar_ratio_range_dds(Tstring * es1, Ddlist * d1, Tstring * es2, Ddlist * d2, int sample, float *lowp, float *upp)
{
    Ddlist *ptr1;
    Ddlist *ptr2;
    Ddlist *start1;
    Ddlist *start2;
    Ddlist *end1;
    Ddlist *end2;
    float   low, up;
    int     i;

    start1 = es1->start;
    end1 = es1->end;
    start2 = es2->start;
    end2 = es2->end;
    for (ptr1 = d1, i = 0; i < sample; i++, ptr1 = ptr1->last)
	if (ptr1 == start1)
	    break;
    start1 = ptr1;
    for (ptr1 = d1, i = 0; i < sample; i++, ptr1 = ptr1->next)
	if (ptr1 == end1)
	    break;
    end1 = ptr1;
    for (ptr2 = d2, i = 0; i < sample; i++, ptr2 = ptr2->last)
	if (ptr2 == start2)
	    break;
    start2 = ptr2;
    for (ptr2 = d2, i = 0; i < sample; i++, ptr2 = ptr2->next)
	if (ptr2 == end2)
	    break;
    end2 = ptr2;

    low = up = (float)curv_invar_ratio_dds(d1, d2, 1);
    for (ptr1 = start1;; ptr1 = ptr1->next)
    {
	for (ptr2 = start2;; ptr2 = ptr2->next)
	{
	    if (ptr1 != d1 || ptr2 != d2)
	    {
		float   invar = (float)curv_invar_ratio_dds(ptr1, ptr2, 1);

		if (invar < low)
		    low = invar;
		if (invar > up)
		    up = invar;
	    }
	    if (ptr2 == end2)
		break;
	}
	if (ptr1 == end1)
	    break;
    }
    *upp = up;
    *lowp = low;
}

Terrain_data *curv_invar_surf_dds(Tstring * es, int sample, int buffer, double scale)
{
    Terrain_data *surf;
    Ddlist *ptr1;
    Ddlist *ptr2;
    Ddlist *start;
    Ddlist *end = (Ddlist *) NULL;
    double  invar;
    int     n, i, j;
    int     ii, jj;

    if (es == NULL || es->start == es->end)
	return (NULL);

    for (i = 0, start = es->start;; i++, start = start->next)
    {
	if (start == end)
	    return (NULL);
	if (i >= buffer)
	    break;
    }

    for (i = 0, end = es->end;; i++, end = end->last)
    {
	if (start == end)
	    return (NULL);
	if (i >= buffer)
	    break;
    }

    for (n = i = 0, ptr1 = start;; i++, ptr1 = ptr1->next)
    {
	if (i % sample == 0)
	    ++n;
	if (ptr1 == end)
	    break;
    }

    surf = terrain_alloc(TERRAIN, n, n);

    for (i = 0, ptr1 = start;; i++, ptr1 = ptr1->next)
    {
	if (i % sample == 0)
	{
	    ii = i / sample;
	    surf->data[ii][ii] = vec3((float) i, (float) i, scale);
	    if (ptr1 == end)
		break;
	    for (j = i + 1, ptr2 = ptr1->next;; j++, ptr2 = ptr2->next)
	    {
		if (j % sample == 0)
		{
		    jj = j / sample;

		    invar = curv_invar_ratio_dds(ptr1, ptr2, 1);
		    invar = fabs(log(fabs(invar)));
		    surf->data[ii][jj] = vec3((float) j, (float) i, invar * scale);
		    surf->data[jj][ii] = vec3((float) i, (float) j, invar * scale);
		}
		if (ptr2 == end)
		    break;
	    }
	}
	if (ptr1 == end)
	    break;
    }
    return (surf);
}

Pair   *curv_invar_closest(Tstring * es, double ratio)
/* pos2 string */
/* invar ratio to obtain */
{
    Ddlist *ptr1;
    Ddlist *ptr2;
    Ddlist *start;
    Ddlist *end;
    double  rdiff = 0.0;
    double  mindiff = 0.0;
    Ddlist *minptr1 = NULL;
    Ddlist *minptr2 = NULL;

    if (es == NULL || es->start == es->end)
	return (NULL);

    start = es->start;
    end = es->end;
    for (ptr1 = start; ptr1->next != end; ptr1 = ptr1->next)
	for (ptr2 = ptr1->next; ptr2 != end; ptr2 = ptr2->next)
	{
	    rdiff = fabs(curv_invar_ratio(es, ptr1, es, ptr2) - ratio);

	    if (minptr1 == NULL || rdiff < mindiff)
	    {
		minptr1 = ptr1;
		minptr2 = ptr2;
		mindiff = rdiff;
	    }
	}
    return (pair_alloc((void *) minptr1, (int) DDLIST, (void *) minptr2, (int) DDLIST));
}

List   *curv_invar_matches(Tstring * es, double ratio)
/* pos2 string */
/* invar ratio to obtain */
{
    Ddlist *ptr1;
    Ddlist *ptr2;
    Ddlist *start;
    Ddlist *end;
    double  last_ratio = 0.0;
    double  this_ratio = 0.0;
    List   *matches = NULL;

    if (es == NULL || es->start == es->end)
	return (NULL);

    start = es->start;
    end = es->end;
    for (ptr1 = start;; ptr1 = ptr1->next)
    {
	for (ptr2 = start;; ptr2 = ptr2->next, last_ratio = this_ratio)
	{
	    if (ptr1 == ptr2)
	    {
		if (ptr2 == end)
		    break;
		continue;
	    }
	    this_ratio = curv_invar_ratio(es, ptr1, es, ptr2);

	    if (ptr2 == start)
		continue;

	    if (BETWEEN(ratio, last_ratio, this_ratio))
	    {
		Pair   *pair;
		double  lastrdiff = fabs(last_ratio - ratio);
		double  thisrdiff = fabs(this_ratio - ratio);
		Ddlist *ptr;
		double  diff;

		diff = MIN(lastrdiff, thisrdiff);
		if (fabs(diff / ratio) > 0.05)
		    continue;
		ptr = (lastrdiff < thisrdiff) ? ptr2->last : ptr2;
		pair = pair_alloc((void *) ptr1, (int) DDLIST, (void *) ptr, (int) DDLIST);
		matches = ref_addtostart((List *) matches, (void *) pair, PAIRS);
	    }
	    if (ptr2 == end)
		break;
	}
	if (ptr1 == end)
	    break;
    }
    return (matches);
}
