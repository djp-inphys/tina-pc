/**@(#)
  */
#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/math.h>

Matrix *dmatrix_read_fp(FILE * fp, int n, int m)
{
    int     i, j;
    Matrix *a;
    Matrix *matrix_alloc();

    if ((a = matrix_alloc(m, n, matrix_full, double_v)) == NULL)
	return (NULL);
    for (i = 0; i < a->m; i++)
	for (j = 0; j < a->n; j++)
	    (void) fscanf(fp, "%lf ", &(a->el.double_v[i][j]));
    return (a);
}
