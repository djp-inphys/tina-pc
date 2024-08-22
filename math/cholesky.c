/**@(#)Cholesky
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

#define TINY 1.0e-20

static int cholesky1(double **A, int n)
{
    int     i, j, k;

    for (i = 0; i < n; ++i)
    {
	for (j = 0; j <= i; ++j)
	{
	    double  sum = A[i][j];

	    A[j][i] = 0;

	    for (k = 0; k < j; ++k)
		sum -= A[i][k] * A[j][k];	/* computed previously */

	    if (i == j)
	    {
		if (sum < 0)
		    return (0);
		sum = sqrt(sum);
		if (fabs(sum) < TINY)
		    return (0);
		A[i][j] = sum;
	    } else
		A[i][j] = sum / A[j][j];
	}
    }
    return (1);
}

#undef TINY

static void cholbksb(double **A, int n, double *x, double *b)
{
    int     i, j;
    double  sum;

    for (i = 0; i < n; i++)
    {
	sum = b[i];
	for (j = 0; j < i; ++j)
	    sum -= x[j] * A[i][j];
	x[i] = sum / A[i][i];
    }

    for (i = n - 1; i >= 0; i--)
    {
	sum = x[i];
	for (j = i + 1; j < n; j++)
	    sum -= x[j] * A[j][i];
	x[i] = sum / A[i][i];
    }
}

Matrix *matrix_cholesky_decomp(Matrix * A)
{
    if (A == NULL || A->n != A->m)
	return (NULL);

    A = matrix_cast_fill(A, double_v);
    if (!cholesky1(A->el.double_v, A->n))
    {
	matrix_free((Matrix *) A);
	return (NULL);
    }
    return (A);
}

Vector *matrix_cholesky_back_sub(Matrix * A, Vector * b)
{
    int     n;
    Vector *x = NULL;
    Vector *c = NULL;

    if (A == NULL || A->n != A->m)
	return (NULL);

    n = A->n;
    if (b == NULL || b->n != n)
	return (NULL);

    A = matrix_cast_fill(A, double_v);
    c = vector_cast(b, double_v);
    x = vector_alloc(n, double_v);
    cholbksb(A->el.double_v, n, (double *) x->data, (double *) c->data);
    vector_free(c);
    matrix_free((Matrix *) A);

    return (x);
}

Vector *matrix_cholesky_sol(Matrix * A, Vector * b)
{
    int     n;
    int     sucess;
    Vector *x = NULL;
    Vector *c = NULL;

    if (A == NULL || A->n != A->m)
	return (NULL);

    n = A->n;
    if (b == NULL || b->n != n)
	return (NULL);

    A = matrix_cast_fill(A, double_v);
    sucess = cholesky1(A->el.double_v, n);

    if (sucess)
    {
	c = vector_cast(b, double_v);
	x = vector_alloc(n, double_v);
	cholbksb(A->el.double_v, n, (double *) x->data, (double *) c->data);
	vector_free(c);
    }
    matrix_free((Matrix *) A);
    return (x);
}

Vector *matrix_cholesky_weighted_least_square(Matrix * A, Matrix * W, Vector * b)
{
    Matrix *At;
    Matrix *M;
    Matrix *temp;
    Vector *x;

    if (A == NULL || A->m != b->n || W == NULL || W->n != W->m || W->m != A->m)
	return (NULL);

    A = matrix_cast_fill(A, double_v);	/* to maintain precision */
    At = matrix_transp(A);
    x = matrix_vprod(W, b);
    b = matrix_vprod(At, x);
    vector_free(x);
    temp = matrix_prod(W, A);
    M = matrix_prod(At, temp);
    matrix_free((Matrix *) temp);
    x = matrix_cholesky_sol(M, b);
    vector_free(b);
    matrix_free((Matrix *) A);
    matrix_free((Matrix *) At);
    matrix_free((Matrix *) M);
    return (x);
}

Vector *matrix_cholesky_least_square(Matrix * A, Vector * b)
{
    Matrix *At;
    Matrix *M;
    Vector *x;

    if (A == NULL || b == NULL || A->m != b->n)
	return (NULL);

    A = matrix_cast_fill(A, double_v);	/* to keep precision */
    At = matrix_transp(A);
    b = matrix_vprod(At, b);
    M = matrix_prod(At, A);
    x = matrix_cholesky_sol(M, b);
    vector_free(b);
    matrix_free((Matrix *) A);
    matrix_free((Matrix *) At);
    matrix_free((Matrix *) M);
    return (x);
}
