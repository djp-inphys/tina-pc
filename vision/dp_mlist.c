/**@(#)
**/
/* dp_mlist.c
 * 
 * general routines for perfoming dynamic programming over a list of
 * matches
 * 
 * match indices are held in the DP_INDEX property of the match
 * 
 * the indices (ints) indicate the monoticity of the underlying problem */

#include <string.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* static variables to maitain DP array
 * 
 * prevents repeted allocation and freeing of these data structures
 * 
 * a large array is allocated prior to dynamic programming over match
 * lists. */

static int dp_size;
static Dpnode **dp_array;	/* the DP array */
static int *low, *up;		/* lower and upper indices into DP
				 * array */

void    dp_mlist_build(int s)
{
    if (s <= dp_size)
	return;
    narray_free((char **) dp_array, 0, dp_size, 0, dp_size, sizeof(Dpnode));
    rfree((void *) low);
    rfree((void *) up);
    dp_size = s;
    dp_array = ts_narray_alloc(0, 0, dp_size, dp_size, Dpnode);
    low = (int *) ralloc((unsigned) (sizeof(int *) * dp_size));
    up = (int *) ralloc((unsigned) (sizeof(int *) * dp_size));
}

/* adjust low and up values between first and last to represent a
 * minimally valid and fully connected DP array. */
void    form_valid_dp_array(int *low, int *up, int firsti, int lasti, int minj)
{
    int     i, m;

    /* make DP array a strict envelope */

    for (i = firsti; i <= lasti; ++i)
	if (low[i] > minj)
	    --low[i];

    for (i = firsti; i < lasti; ++i)
    {
	if (up[i + 1] > up[i])
	    up[i] = up[i + 1] - 1;
    }

    m = up[firsti];
    for (i = firsti + 1; i <= lasti; ++i)
    {
	if (up[i] > m)
	    m = up[i];
	else
	    up[i] = m;
    }

    m = low[lasti];
    for (i = lasti - 1; i >= firsti; --i)
    {
	if (low[i] != -1 && low[i] < m)
	    m = low[i];
	else
	    low[i] = m;
    }

    /* ensure fully connected envelope */
    for (i = firsti; i < lasti; ++i)
    {
	if (up[i] < low[i])
	    up[i] = low[i];
	if (up[i] < low[i + 1])
	    up[i] = low[i + 1];
    }
}

void    mlist_set_dp_indices(List * mlist, int (*index_func) ( /* ??? */ ), void *data)
{
    List   *lptr;

    for (lptr = mlist; lptr != NULL; lptr = lptr->next)
    {
	int     to1, to2;
	Match  *m = (Match *) lptr->to;
	Pair   *p;

	to1 = index_func(m->to1, m->type, data);
	to2 = index_func(m->to2, m->type, data);
	p = pair_make((void *) to1, (int) NULL, (void *) to2, (int) NULL);
	m->props = proplist_addifnp(m->props, (void *) p, DP_INDEX, rfree, true);
    }
}

List   *dp_mlist(List * list, double (*cost_func) ( /* ??? */ ))
/* list of list of matches in assending order */

{
    List   *ptr;
    Match  *match;
    Pair   *indices;
    int     firsti, lasti, maxj, minj;
    int     i, j, n;

    if (list == NULL)
	return (NULL);

    for (n = 0, ptr = list; ptr != NULL; ptr = ptr->next)
    {
	match = (Match *) ptr->to;
	indices = (Pair *) prop_get(match->props, DP_INDEX);
	if (indices == NULL)
	    return (NULL);
	i = (int) indices->to1;
	if (i > n)
	    n = i;
    }
    n++;

    if (n > dp_size)
    {
	error("dp_mlist: dynamic programming table limit exeeded", warning);
	return (NULL);
    }
    for (i = 0; i < n; ++i)
	low[i] = up[i] = -1;

    maxj = 0;
    minj = dp_size - 1;
    for (ptr = list; ptr != NULL; ptr = ptr->next)
    {
	match = (Match *) ptr->to;
	indices = (Pair *) prop_get(match->props, DP_INDEX);
	i = (int) indices->to1;
	j = (int) indices->to2;

	if (low[i] == -1 || j < low[i])
	    low[i] = j;
	if (up[i] == -1 || j > up[i])
	    up[i] = j;
	if (j > maxj)
	    maxj = j;
	if (j < minj)
	    minj = j;
    }

    if (maxj > dp_size)
    {
	error("dp_mlist: dynamic programming table limit exeeded", warning);
	return (NULL);
    }
    /* find range of used values */
    for (i = 0; i < n; ++i)
	if (low[i] != -1)
	    break;
    firsti = i;
    lasti = n - 1;

    if (firsti > lasti)
	return (NULL);

    form_valid_dp_array(low, up, firsti, lasti, minj);

    /* initialise DP array elements */

    for (i = firsti; i <= lasti; ++i)
	(void) memset((char *) &dp_array[i][low[i]], 0, (up[i] - low[i] + 1) * sizeof(Dpnode));

    /* fill in values from match list */

    for (ptr = list; ptr != NULL; ptr = ptr->next)
    {
	match = (Match *) ptr->to;
	indices = (Pair *) prop_get(match->props, DP_INDEX);
	i = (int) indices->to1;
	j = (int) indices->to2;

	dp_array[i][j].data = (void *) match;
	if (cost_func == NULL)
	    dp_array[i][j].cost = match->weight;
	else
	    dp_array[i][j].cost = (float)cost_func(match);
    }

    dp_accum(dp_array, low, up, firsti, lasti);
    list = dp_solution(dp_array, low, up, firsti, lasti);

    return (list);
}
