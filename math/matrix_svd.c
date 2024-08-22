/**@(#)Matrix SVD
**/

#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>

void    matrix_svd(Matrix * a, Matrix ** u, Matrix ** v, double **w, double condition)
{
    int     j;
    void    SVDcmp();
    double  wmax, thresh;
    Matrix *dmatrix_copy();
    Matrix *matrix_alloc();

    if (*u == (Matrix *) NULL)
	*u = dmatrix_copy(a);
    if (*w == (double *) NULL)
	*w = (double *) ralloc((unsigned) a->n * sizeof(double));
    if (*v == (Matrix *) NULL)
	*v = matrix_alloc(a->n, a->n, matrix_full, double_v);
    /* singular value decomposition */

    SVDcmp((*u)->el.double_v, (*u)->m, (*u)->n, *w, (*v)->el.double_v);
    /* Editing the sigular values given condition */
    wmax = 0.0;
    for (j = 0; j < ((*u)->n); j++)
	if ((*w)[j] > wmax)
	    wmax = (*w)[j];
    thresh = condition * wmax;
    for (j = 0; j < ((*u)->n); j++)
	if ((*w)[j] < thresh)
	    (*w)[j] = 0.0;
}
