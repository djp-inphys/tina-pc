/**@(#)Matrix invariant check
**/

#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

/* smc 2/2/93 */
#ifdef Print
#undef Print
#endif
/* smc 2/2/93 */

#define Print(x)  { if(out_text!=NULL) out_text(x); }

void    dmatrix_checkinv(void (*out_text) ( /* ??? */ ), Matrix * a, Matrix * b, char *mname)
{
    int     i, j;
    Matrix *check;
    Matrix *matrix_prod();
    double  tot = 0.0, tot2 = 0.0;
    char    temp[256];

    if (a == NULL || b == NULL)
    {
	Print(sprintf(temp, " NULL matrix passed to checkinv \n"));
	return;
    }
    check = matrix_prod(a, b);

    Print(sprintf(temp, " check inverse for %s \n", mname));
    for (i = 0; i < check->n; i++)
    {
	Print(sprintf(temp, "%4.2f ", check->el.double_v[i][i]));
	tot += fabs(check->el.double_v[i][i] - 1.0);
	for (j = 0; j < check->n; j++)
	{
	    if (i != j)
		tot2 += fabs(check->el.double_v[i][j]);
	}
    }
    Print(sprintf(temp, "\n diagonal error %8.6f off diagonal error %8.6f\n", tot, tot2));

    matrix_free((Matrix *) check);
}
