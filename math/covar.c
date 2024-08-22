/* @(#)Jacobian & evaluate the inverse covariance matrix from the
 * jacobian */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

#define LOWACC 0.5
#define TARGET 1.0
#define HIGACC 2.0
#define TOL 0.000001
#define ITMAX 3

/* A numerical routine to determine the jacobian `jf' of a function
 * `func' for `n' data points with respect to `m' parameters `a' using
 * finite differencing at a scale determined by `da'. The floating
 * point accuracy is determined by TARGET as the fractional change
 * required on the evaluated function. This should give accurate
 * derivative evaluations for chi-squared evaluations at a minimum. The
 * chi-squared function is assumed to be approximately quadratic to
 * allow tuning of the step parameters if the fractional function
 * change does not fall between the specified parameters. NAT 26/2/91 */
void    jacob(double *a, double *da, Matrix * jf, double (*func) ( /* ??? */ ))
{
    int     i, j, iter;
    double  acc, chisq, chisq1, aj;
    double *f0 = NULL, *f1, *f2;

    if (jf == NULL || a == NULL || da == NULL || func == NULL)
	return;

    f1 = (double *) ralloc((unsigned) jf->m * sizeof(double));
    f2 = (double *) ralloc((unsigned) jf->m * sizeof(double));

    chisq = (*func) (f0, jf->m, a, jf->n);

    for (j = 0; j < jf->n; j++)
    {
	iter = 0;
	aj = a[j];
	if (fabs(da[j] / a[j]) < TOL)
	    da[j] = a[j] * TOL;
	acc = TARGET;
	while (iter == 0 || (iter < ITMAX && (acc < LOWACC || acc > HIGACC)))
	{
	    if (acc < TOL)
		da[j] /= TOL;
	    else
		da[j] *= sqrt(TARGET / acc);
	    a[j] = aj + da[j];
	    chisq1 = (*func) (f1, jf->m, a, jf->n);
	    acc = (fabs(chisq1 - chisq) / chisq);
	    iter++;
	}
	a[j] = aj - da[j];
	(void) (*func) (f2, jf->m, a, jf->n); 
	a[j] = aj;
	for (i = 0; i < jf->m; i++)
	    jf->el.double_v[i][j] = (f1[i] - f2[i]) / (2.0 * da[j]);
    }
    /* reset the a parameters to their starting values */
    chisq = (*func) (f0, jf->m, a, jf->n);
    rfree((void *) f1);
    rfree((void *) f2);
}

Covar  *invcov(int m, double *a, double (*func) ( /* ??? */ ), int n)




/* function to evaluate the inverse covariance matrix from the jacobian
 * NAT 27/2/91 */
{
    int     i, j, k;
    double *f, *da;
    Matrix *jf;
    Matrix *matrix_alloc();
    Covar  *incov;
    Covar  *covar_alloc(int n);
    Vector *vector_alloc();

    if (a == NULL || func == NULL)
	return (NULL);

    jf = matrix_alloc(n, m, matrix_full, double_v);
    incov = covar_alloc(m);
    incov->mat = matrix_alloc(m, m, matrix_full, double_v);
    incov->vec = vector_alloc(m, double_v);
    f = (double *) ralloc((unsigned) n * sizeof(double));
    da = (double *) ralloc((unsigned) m * sizeof(double));

    for (i = 0; i < m; i++)
	da[i] = 0.001;
    jacob(a, da, jf, func);

    for (k = 0; k < m; k++)
    {
	VECTOR_DOUBLE(incov->vec, k) = a[k];
	for (j = 0; j < m; j++)
	{
	    incov->mat->el.double_v[j][k] = 0.0;
	    for (i = 0; i < n; i++)
	    {
		incov->mat->el.double_v[j][k] += jf->el.double_v[i][j] * jf->el.double_v[i][k];
	    }
	}
    }
    rfree((void *) f);
    rfree((void *) da);
    matrix_free(jf);
    return (incov);
}

Covar  *covar(int m, double *a, double (*func) ( /* ??? */ ), int n, double condition)
{
    Matrix *matrix_alloc();
    Matrix *jf;
    Matrix *v = NULL;
    Matrix *u = NULL;
    double *w = NULL, *da, *f;
    double  sum;
    Covar  *cov;
    Covar  *covar_alloc(int n);
    int     i, j, k;
    void    matrix_svd();
    Vector *vector_alloc();

    if (a == NULL || func == NULL)
	return (NULL);

    da = (double *) ralloc((unsigned) m * sizeof(double));
    f = (double *) ralloc((unsigned) n * sizeof(double));
    jf = matrix_alloc(n, m, matrix_full, double_v);
    cov = covar_alloc(m);
    cov->mat = matrix_alloc(m, m, matrix_full, double_v);
    cov->vec = vector_alloc(m, double_v);

    for (i = 0; i < m; i++)
	da[i] = 0.001;
    jacob(a, da, jf, func);
    matrix_svd(jf, &u, &v, &w, condition);

    /* Sum contributions to the covariance matrix */
    for (i = 0; i < m; i++)
    {
	VECTOR_DOUBLE(cov->vec, i) = a[i];
	for (j = 0; j <= i; j++)
	{
	    for (sum = 0.0, k = 0; k < m; k++)
		if (w[k])
		    sum += v->el.double_v[i][k] * v->el.double_v[j][k] / (w[k] * w[k]);
	    cov->mat->el.double_v[j][i] = cov->mat->el.double_v[i][j] = sum;
	}
    }

    rfree((void *) w);
    rfree((void *) da);
    rfree((void *) f);
    matrix_free(jf);
    matrix_free(v);
    matrix_free(u);

    return (cov);
}

Covar  *covar_update(Covar * inv_acov, Covar * inv_bcov, double condition)
{
    int     i;
    Matrix *matrix_prod();
    Matrix *matrix_invsvd();
    Matrix *matrix_alloc();
    Matrix *matrix_add();
    Matrix *delta;
    Matrix *new_delta;
    Matrix *comb;
    Covar  *tot_invc;
    Covar  *covar_alloc(int n);
    Matrix *tot_cov;

    if (inv_acov == NULL)
	return (NULL);
    if (inv_bcov == NULL)
	return (inv_acov);

    delta = matrix_alloc(1, inv_acov->n, matrix_full, double_v);
    for (i = 0; i < inv_acov->n; i++)
	delta->el.double_v[0][i] = VECTOR_DOUBLE(inv_acov->vec, i)
	    - VECTOR_DOUBLE(inv_bcov->vec, i);

    tot_invc = covar_alloc(inv_acov->n);
    tot_invc->n = inv_acov->n;
    tot_invc->label = inv_acov->label;
    tot_invc->vec = vector_alloc(inv_acov->n, double_v);
    tot_invc->mat = matrix_add(inv_acov->mat, inv_bcov->mat);

    tot_cov = matrix_invsvd(tot_invc->mat, condition);
    comb = matrix_prod(delta, inv_acov->mat);
    new_delta = matrix_prod(comb, tot_cov);

    for (i = 0; i < inv_acov->n; i++)
    {
	VECTOR_DOUBLE(tot_invc->vec, i) = VECTOR_DOUBLE(inv_bcov->vec, i)
	    + new_delta->el.double_v[0][i];
    }

    matrix_free(delta);
    matrix_free(comb);
    matrix_free(tot_cov);
    matrix_free(new_delta);

    return (tot_invc);
}

Covar  *covar_add(Covar * inv_acov, Covar * inv_bcov)
{
    Covar  *tot_invc;
    Covar  *covar_alloc(int n);
    Vector *vector_alloc();
    Matrix *matrix_add();
    Matrix *matrix_copy();
    int     i;

    if (inv_acov == NULL && inv_bcov == NULL)
	return (NULL);
    if (inv_acov == NULL && inv_bcov != NULL)
    {
	inv_acov = inv_bcov;
	inv_bcov = NULL;
    }
    if (inv_acov != NULL && inv_bcov != NULL && (inv_acov->label != inv_bcov->label))
	return (NULL);

    tot_invc = covar_alloc(inv_acov->n);
    tot_invc->n = inv_acov->n;
    tot_invc->label = inv_acov->label;
    tot_invc->vec = vector_alloc(inv_acov->n, double_v);
    if (inv_bcov != NULL)
	tot_invc->mat = matrix_add(inv_acov->mat, inv_bcov->mat);
    else
	tot_invc->mat = matrix_copy(inv_acov->mat);

    for (i = 0; i < inv_acov->n; i++)
    {
	VECTOR_DOUBLE(tot_invc->vec, i) = VECTOR_DOUBLE(inv_acov->vec, i);
    }

    return (tot_invc);
}

Covar  *covar_alloc(int n)
{
    Covar  *cov = ts_ralloc(Covar);

    if (cov == NULL)
	return (NULL);
    cov->n = n;
    cov->mat = NULL;
    cov->vec = NULL;
    return (cov);
}

void    covar_free(Covar * cov)
{
    if (cov == NULL)
	return;
    if (cov->mat)
	matrix_free(cov->mat);
    if (cov->vec)
	vector_free(cov->vec);
    rfree((void *) cov);
}
