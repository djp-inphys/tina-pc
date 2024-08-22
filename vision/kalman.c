/**@(#)
**/
/**
kalman.c:
stationary scalar kalman filter for constraints
**/

#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

static Bool verbose = false;

Bool    kalman_verbose_get(void)
{
    return (verbose);
}

void    kalman_verbose_set(Bool new)
{
    verbose = new;
}

void    vector2_free(Vector * v)
{
    int     i;

    if (v == NULL)
	return;
    for (i = 0; i < v->n; i++)
	vector_free((Vector *) vector_getp(v, i));
    vector_free(v);
}

void    vector2_format(Vector * v)
{
    int     i;

    vector_format(v);
    format("\n");
    for (i = 0; i < v->n; i++)
    {
	Vector *vi = (Vector *) vector_getp(v, i);

	if (vi != NULL)
	{
	    format("%10d: ", i);
	    vector_format(vi);
	    format("\n");
	}
    }
}

static Vector *accum_vprod_1(Vector * x, Matrix * a, Vector * v)
{
    int     i, j, m, n;
    double *xe, **ae, *ve;

    if (a == NULL || v == NULL)
	return (x);

    m = a->m;
    n = a->n;
    if (x == NULL)
	x = vector_alloc(m, double_v);

    xe = x->data;
    ae = a->el.double_v;
    ve = v->data;

    for (i = 0; i < m; i++)
	for (j = 0; j < n; j++)
	    xe[i] += ae[i][j] * ve[j];

    return (x);
}

static Vector *accum_vprod_2(Vector * x, Matrix * a, Vector * v)
{
    int     i, j, m;
    double *xe, **ae, *ve;

    if (a == NULL || v == NULL)
	return (x);

    m = a->m;
    if (x == NULL)
	x = vector_alloc(m, double_v);

    xe = x->data;
    ae = a->el.double_v;
    ve = v->data;

    for (i = 0; i < m; i++)
    {
	for (j = 0; j < i; j++)
	    xe[i] += ae[i][j] * ve[j];
	for (j = i; j < m; j++)
	    xe[i] += ae[j][i] * ve[j];
    }

    return (x);
}

static Vector *accum_vprod_3(Vector * x, Matrix * a, Vector * v)
{
    int     i, j, m, n;
    double *xe, **ae, *ve;

    if (a == NULL || v == NULL)
	return (x);

    m = a->m;
    n = a->n;
    if (x == NULL)
	x = vector_alloc(n, double_v);

    xe = x->data;
    ae = a->el.double_v;
    ve = v->data;

    for (i = 0; i < n; i++)
	for (j = 0; j < m; j++)
	    xe[i] += ae[j][i] * ve[j];

    return (x);
}

static Vector *smatrix2_vprod(Matrix * a, Vector * v)
{
    int     i, j;
    int     m, n;
    Vector *av;

    m = n = MIN(a->n, v->n);

    av = vector_alloc(m, ptr_v);
    for (i = 0; i < m; i++)
    {
	Vector *avi = (Vector *) vector_getp(av, i);

	for (j = 0; j < i; j++)
	{
	    Matrix *aij = (Matrix *) matrix_getp(a, i, j);
	    Vector *vj = (Vector *) vector_getp(v, j);

	    avi = accum_vprod_1(avi, aij, vj);
	}

	{
	    Matrix *aii = (Matrix *) matrix_getp(a, i, i);
	    Vector *vi = (Vector *) vector_getp(v, i);

	    avi = accum_vprod_2(avi, aii, vi);
	}

	for (j = i + 1; j < n; j++)
	{
	    Matrix *aij = (Matrix *) matrix_getp(a, j, i);
	    Vector *vj = (Vector *) vector_getp(v, j);

	    avi = accum_vprod_3(avi, aij, vj);
	}
	vector_putp((void *) avi, av, i);
    }
    return (av);
}

static double vector2_dot(Vector * v1, Vector * v2)
{
    int     i;
    int     n;
    double  v12 = 0.0;

    n = MIN(v1->n, v2->n);
    for (i = 0; i < n; i++)
	v12 += vector_dot((Vector *) vector_getp(v1, i),
			  (Vector *) vector_getp(v2, i));
    return (v12);
}

static Vector *accum_vector_times(Vector * x, double k, Vector * v)
{
    int     i;
    int     n;
    double *xe, *ve;

    if (k == 0.0 || v == NULL)
	return (x);

    n = v->n;
    if (x == NULL)
	x = vector_alloc(n, double_v);

    xe = x->data;
    ve = v->data;
    for (i = 0; i < n; i++)
	xe[i] += k * ve[i];

    return (x);
}


static void accum_vector2_times(Vector * x, double k, Vector * v)
{
    int     i;
    int     n;

    n = MIN(x->n, v->n);
    for (i = 0; i < n; i++)
    {
	Vector *xi = (Vector *) vector_getp(x, i);
	Vector *vi = (Vector *) vector_getp(v, i);

	xi = accum_vector_times(xi, k, vi);
	vector_putp((void *) xi, x, i);
    }
}

static Matrix *accum_matrix_tensor(Matrix * a, double k, Vector * v, Vector * w)
{
    int     i, j, m, n;
    double **ae, *ve, *we;

    if (k == 0.0 || v == NULL || w == NULL)
	return (a);

    m = v->n;
    n = w->n;
    if (a == NULL)
	a = matrix_alloc(m, n, matrix_full, double_v);

    ae = a->el.double_v;
    ve = v->data;
    we = w->data;
    for (i = 0; i < m; i++)
	for (j = 0; j < n; j++)
	    ae[i][j] += k * ve[i] * we[j];
    return (a);
}

static Matrix *accum_matrix_symtensor(Matrix * a, double k, Vector * v)
{
    int     i, j, n;
    double **ae, *ve;

    if (k == 0.0 || v == NULL)
	return (a);

    n = v->n;
    if (a == NULL)
	a = matrix_alloc(n, n, matrix_lower, double_v);

    ae = a->el.double_v;
    ve = v->data;
    for (i = 0; i < n; i++)
	for (j = 0; j <= i; j++)
	    ae[i][j] += k * ve[i] * ve[j];
    return (a);
}

void    accum_smatrix2_symtensor(Matrix * a, double k, Vector * v)
{
    int     i, j;
    int     n;

    n = MIN(a->n, v->n);
    for (i = 0; i < n; i++)
    {
	Vector *vi = (Vector *) vector_getp(v, i);

	for (j = 0; j < i; j++)
	{
	    Matrix *aij = (Matrix *) matrix_getp(a, i, j);
	    Vector *vj = (Vector *) vector_getp(v, j);

	    aij = accum_matrix_tensor(aij, k, vi, vj);
	    matrix_putp((void *) aij, a, i, j);
	}

	{
	    Matrix *aii = (Matrix *) matrix_getp(a, i, i);

	    aii = accum_matrix_symtensor(aii, k, vi);
	    matrix_putp((void *) aii, a, i, i);
	}
    }
}

/**
imposes constraint with n active primitives as:
z+h[i0].x[i0]+...+h[i(n-1)].x[i(n-1)] = 0
**/

static Bool kalman_error(double z, double hsh, double eps, int *pdf, double *res)
{
    if (hsh < -eps * eps)
    {
	error("kalman: not positive indefinite", non_fatal);
	*res = 1e10;
	return (true);
    } else if (fabs(hsh) < eps * eps)
    {
	if (fabs(z) > 2.0 * eps)
	{
	    error("kalman: inconsistent", non_fatal);
	    *res = 1e10;
	} else
	{
	    error("kalman: dependent", warning);
	    *res = 0.0;
	    (*pdf)--;
	}
	return (true);
    } else
	return (false);
}

double  kalman(State * state, double z, Vector * h, double eps, int *pdf)
{
    Vector *sh;
    double  hsh, res;

    sh = smatrix2_vprod(state->s, h);
    hsh = vector2_dot(h, sh);
    z += vector2_dot(state->x, h);

    if (kalman_verbose_get())
	format("z = %e hsh = %e sigma = %e\n", z, hsh, sqrt(fabs(hsh)));

    if (kalman_error(z, hsh, eps, pdf, &res))
    {
	vector2_free(sh);
	return (res);
    }
    accum_vector2_times(state->x, -z / hsh, sh);
    accum_smatrix2_symtensor(state->s, -1.0 / hsh, sh);

    vector2_free(sh);
    return (z * z / hsh);
}
