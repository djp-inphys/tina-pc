/**@(#)
**/
/* smooth_1d.c
 * 
 * one dimensional smoothing function
 * 
 * smoothing is a special form of convolution in which edge effects can be
 * approximated using sub-total ratios.
 * 
 * functions accept only  floating point covolution profiles
 * 
 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>

static Prof1 *prof1_subtot_ratio(Prof1 * profile)
{
    Prof1  *subtot;
    Prof1  *prof1_alloc();
    int     i, n1, n2;
    float   tot = (float)0.0;

    n1 = profile->n1;
    n2 = profile->n2;
    subtot = prof1_alloc(n1, n2, float_v);

    for (i = n1; i < n2; ++i)
    {
	subtot->el.float_v[i] = tot;
	tot += profile->el.float_v[i];
    }
    for (i = n1; i < n2; ++i)
	subtot->el.float_v[i] /= tot;
    return (subtot);
}

void    smooth_1d(float *line, int n1, int n2, Prof1 * profile)	/* use profile forwards */



{
    float   sum;
    int     i, j;
    int     p1, p2, firstfull, lastfull;
    float  *prof, *subtot;
    Prof1  *subtot_p;
    void    prof1_free();
    float  *temp;

    if (profile == NULL || profile->vtype != float_v)
	return;

    p1 = profile->n1;
    p2 = profile->n2;
    firstfull = MAX(n1 - p1, n1);
    lastfull = MIN(n2 - p2, n2);
    prof = profile->el.float_v;
    subtot_p = prof1_subtot_ratio(profile);
    subtot = subtot_p->el.float_v;
    temp = fvector_alloc(n1, n2);

    for (i = n1; i < firstfull; ++i)
    {
	for (sum = (float)0.0, j = n1 - i; j < p2; ++j)
	    sum += prof[j] * line[i + j];
	temp[i] = (float) (sum / (1.0 - subtot[n1 - i]));
    }

    for (; i <= lastfull; ++i)	/* most work */
    {
	for (sum = (float)0.0, j = p1; j < p2; ++j)
	    sum += (float) (prof[j] * line[i + j]);
	temp[i] = sum;
    }

    for (; i < n2; ++i)
    {
	for (sum = (float)0.0, j = p1; j < n2 - i; ++j)
	    sum += prof[j] * line[i + j];
	temp[i] = sum / subtot[n2 - i];
    }

    for (i = n1; i < n2; ++i)
	line[i] = temp[i];

    fvector_free((void *) temp, n1);
    prof1_free(subtot_p);
}

void    smooth_1d_sym(float *line, int n1, int n2, Prof1 * profile)	/* use profile
									 * symetrically */



{
    float   sum;
    int     i, j;
    int     p1, p2, firstfull, lastfull;
    int     offset, pm, odd;
    float  *prof, *subtot;
    Prof1  *subtot_p;
    void    prof1_free();
    float  *temp;

    if (profile == NULL || profile->vtype != float_v)
	return;

    p1 = profile->n1;
    p2 = profile->n2;
    firstfull = MAX(n1 - p1, n1);
    lastfull = MIN(n2 - p2, n2);
    prof = profile->el.float_v;
    subtot_p = prof1_subtot_ratio(profile);
    subtot = subtot_p->el.float_v;
    temp = fvector_alloc(n1, n2);

    odd = (p2 - p1) % 2;	/* is the profile odd or even */
    pm = p1 + (p2 - p1) / 2;	/* mid point of profile */
    offset = p1 + p2 - 1;

    for (i = n1; i < firstfull; ++i)
    {
	for (sum = (float)0.0, j = n1 - i; j < p2; ++j)
	    sum += (float) (prof[j] * line[i + j]);
	temp[i] = (float) (sum / (1.0 - subtot[n1 - i]));
    }

    for (; i <= lastfull; ++i)	/* most work so exploit symetry */
    {
	sum = (odd) ? prof[pm] * line[i + pm] : 0;
	for (j = p1; j < pm; ++j)
	    sum += prof[j] * (line[i + j] + line[i + offset - j]);
	temp[i] = sum;
    }

    for (; i < n2; ++i)
    {
	for (sum = (float)0.0, j = p1; j < n2 - i; ++j)
	    sum += prof[j] * line[i + j];
	temp[i] = sum / subtot[n2 - i];
    }

    for (i = n1; i < n2; ++i)
	line[i] = temp[i];

    fvector_free((void *) temp, n1);
    prof1_free(subtot_p);
}

void    conv_1d(float *line, int n1, int n2, Prof1 * profile)	/* use profile backwards */



{
    float   sum;
    int     i, j;
    int     p1, p2;
    int     lower, upper;
    float  *prof;
    float  *temp;

    if (profile == NULL || profile->vtype != float_v)
	return;

    p1 = profile->n1;
    p2 = profile->n2;
    lower = MAX(n1 - p2 + 1, 0);
    upper = MIN(n2 - p1, n2);
    prof = profile->el.float_v;
    temp = fvector_alloc(n1, n2);

    for (i = n1; i < lower; ++i)
	temp[i] = (float)0.0;

    for (; i <= upper; ++i)	/* most work */
    {
	for (sum = (float)0.0, j = p1; j < p2; ++j)
	    sum += prof[j] * line[i - j];
	temp[i] = sum;
    }

    for (; i < n2; ++i)
	temp[i] = (float)0.0;

    for (i = n1; i < n2; ++i)
	line[i] = temp[i];

    fvector_free((void *) temp, n1);
}
