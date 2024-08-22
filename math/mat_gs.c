/*
 *
 * mat_gs.c
 *
 * Routines using Gram-Schmidt orthogonalisation process.
 *
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

void vec_gram_schmidt(int p, Vec ** basis)
{
    int i, j;
    for (i = 0; i < p; i++)
    {
	for (j = 0; j < i; j++)
	{
	    double d = vec_dot(basis[i], basis[j]);
	    vec_accum(basis[i], -d, basis[j]);
	}
	vec_unit(basis[i]);
    }
}

void vec_basis_complete(int p, Vec **basis)
{
    int i, j, n = basis[0]->n;
    for(i = p; i < n; i++)
	vec_rand_unif(basis[i], -1, 1);
    for (i = p; i < n; i++)
    {
	for (j = 0; j < i; j++)
	{
	    double d = vec_dot(basis[i], basis[j]);
	    vec_accum(basis[i], -d, basis[j]);
	}
	vec_unit(basis[i]);
    }
}

void mat_rand_orthonormal(Mat *r)
{
    int i, n = r->n;
    Vec **basis = tvector_alloc(0, n, Vec *);
    for(i = 0; i < n; i++)
    {
	basis[i] = vec_make(n);
	vec_rand_normal(basis[i], 0, 1);
    }
    vec_gram_schmidt(n, basis);
    for(i = 0; i < n; i++)
	mat_col_set(r, i, basis[i]);
    for(i = 0; i < n; i++)
	vec_free(basis[0]);
    tvector_free(basis, 0, Vec *);
}
