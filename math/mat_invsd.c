/**@(#)Inverse SVD
**/

#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

Matrix *matrix_invsvd(Matrix * a, double condition)
{
    Matrix *matinv;
    Matrix *v = NULL;
    Matrix *d;
    Matrix *vd;
    Matrix *ut;
    Matrix *u = NULL;
    double *w = NULL;
    int     i;

    if (a == NULL)
	return (NULL);

    matrix_svd(a, &u, &v, &w, condition);
    d = matrix_alloc(a->n, a->n, matrix_full, double_v);
    for (i = 0; i < a->n; i++)
	if (w[i])
	    d->el.double_v[i][i] = 1.0 / w[i];
    ut = matrix_transp(u);
    vd = matrix_prod(v,d);
    matinv = matrix_prod(vd, ut);

    matrix_free((Matrix *) v);
    matrix_free((Matrix *) d);
    matrix_free((Matrix *) vd);
    matrix_free((Matrix *) u);
    matrix_free((Matrix *) ut);
    return (matinv);
}
