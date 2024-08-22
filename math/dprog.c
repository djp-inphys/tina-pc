/**@(#)Dynamic programming
**/
#include <tina/sys.h>
#include <tina/sysfuncs.h>

int    *dprog(int lx, int ly, int ux, int uy, double (*cost1) ( /* ??? */ ), double (*cost2) ( /* ??? */ ))
{
    float **cost = farray_alloc(lx, ly, ux + 1, uy);
    int   **match = iarray_alloc(lx, ly, ux, uy), *choice;
    int     x, y, z, zmin;	/* BUG `zmin' may be used uninitialized
				 * in this function */
    double  c = 0.0;
    double  cmin;

    for (x = ux - 1; x >= lx; x--)
    {
	for (y = ly; y < uy; y++)
	{
	    cmin = 1e10;
	    for (z = ly; z < uy; z++)
	    {
		c = cost2(x, y, x + 1, z) + cost[x + 1][z];
		if (cmin > c)
		{
		    cmin = c;
		    zmin = z;
		}
	    }
	    cost[x][y] = (float) (cost1(x, y) + cmin);
	    match[x][y] = zmin;
	}
    }

    cmin = 1e10;
    for (z = ly; z < uy; z++)
    {
	cost[lx][z];		/* BUG what does this do! */
	if (cmin > c)
	{
	    cmin = c;
	    zmin = z;
	}
    }
    farray_free((char **) cost, lx, ly, ux + 1, uy);

    choice = ivector_alloc(lx, ux);
    choice[lx] = zmin;
    for (x = lx; x < ux - 1; x++)
	choice[x + 1] = match[x][choice[x]];

    iarray_free((char **) match, lx, ly, ux, uy);
    return (choice);
}
