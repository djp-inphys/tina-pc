/**@(#)
**/
/* dynamic.c
 * 
 * general routines for perfoming dynamic programming
 * 
 * the sum of weights of the matches is maximised.
 * 
 * the solution allows primitives to be skipped
 * 
 * on route to maximal solutions (missed matches score 0) */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>

#define INCLUDED(c,r) (c>=first && c<=last && r>=low[c] && r<=up[c])

/* construct a list of match data (referenced in the DP array) starts
 * from the solution and walks back through the optimal path on the
 * basis of the type fields of the DP nodes */
static List *back_track(int i, int j, Dpnode ** dp_array, int *low, int *up, int first, int last)
{
    List   *list = NULL;

    while (INCLUDED(i, j))
    {
	Dpnode *dp = &dp_array[i][j];

	switch (dp->m_type)
	{
	case DP_MATCHED:
	    if (dp->data != NULL)
		list = ref_addtostart(list, (void *) dp->data, MATCH);
	    i--;
	    j--;
	    break;
	case DP_PVTROW:
	    i--;
	    break;
	case DP_PVTCOL:
	    j--;
	    break;
	}
    }
    return (list);
}

/* find solution to DP that has been found by dp_accum
 * 
 * examine the last active row of the DP array for the highest value
 * solution and track it throgh the solution path collecting valid
 * matches along the way */
List   *dp_solution(Dpnode ** dp_array, int *low, int *up, int first, int last)
{
    int     i, j;
    float   max_sup;
    int     maxj;

    i = last;
    maxj = low[i];
    max_sup = dp_array[i][low[i]].m_tot;
    for (j = maxj + 1; j <= up[i]; ++j)
    {
	float   sup = dp_array[i][j].m_tot;

	if (sup > max_sup)
	{
	    max_sup = sup;
	    maxj = j;
	}
    }

    /* now we can back track from the solution */
    return (back_track(i, maxj, dp_array, low, up, first, last));
}

/* accumulate the DP array
 * 
 * 3 preceeding values are compared to update each node the type field is
 * set depening upon which is maximal */
void    dp_accum(Dpnode ** dp_array, int *low, int *up, int first, int last)
{
    int     i, j;

    for (i = first; i <= last; ++i)
    {
	for (j = low[i]; j <= up[i]; ++j)
	{
	    Dpnode *dp_new = &dp_array[i][j];
	    float   m_tot, r_prev = (float) 0.0, c_prev = (float) 0.0;

	    /* compute best cost to this node */

	    m_tot = dp_new->cost;
	    if (INCLUDED(i - 1, j - 1))
		m_tot += dp_array[i - 1][j - 1].m_tot;
	    if (INCLUDED(i - 1, j))
		r_prev = dp_array[i - 1][j].m_tot;
	    if (INCLUDED(i, j - 1))
		c_prev = dp_array[i][j - 1].m_tot;

	    if (m_tot > r_prev && m_tot > c_prev)
	    {
		dp_new->m_tot = m_tot;
		dp_new->m_type = DP_MATCHED;
	    } else if (c_prev > r_prev)	/* prevented along the column */
	    {
		dp_new->m_tot = c_prev;
		dp_new->m_type = DP_PVTCOL;
	    } else
	    {
		/* prevented row best */
		dp_new->m_tot = r_prev;
		dp_new->m_type = DP_PVTROW;
	    }
	}
    }
}
