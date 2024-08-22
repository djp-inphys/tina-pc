/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void    state_format_one(State * state, int i)
{
    unsigned int type = VECTOR_INT(state->type, i);
    void   *geom = VECTOR_PTR(state->geom, i);

    if (type)
	geom_format(geom, type);
}

void    state_format(State * state)
{
    int     i;
    int     maxindex = state->maxindex;
    unsigned int *type = state->type->data;
    void  **geom = state->geom->data;

    for (i = 0; i < maxindex; i++)
	if (type[i])
	    geom_format(geom[i], type[i]);
}

void    state_cov_format(State * state)
{
    int     i, j;

    for (i = 0; i < state->maxindex; i++)
    {
	for (j = 0; j <= i; j++)
	{
	    if (matrix_getp(state->s, i, j) != NULL)
		format("* ");
	    else
		format("0 ");
	}
	format("\n");
    }
    format("\n");
}

void    state_cov_format_one(State * state, int i)
{
    matrix_format((Matrix *) matrix_getp(state->s, i, i));
    format("\n");
}

void    state_cov_format_two(State * state, int i, int j)
{
    matrix_format((Matrix *) matrix_getp(state->s, i, j));
    format("\n");
}

void    state_corr_format_one(State * state, int i)
{
    int     j, k;
    Matrix *m = (Matrix *) matrix_getp(state->s, i, i);
    Matrix *c;

    if (m == NULL)
	format("(nil)\n");

    c = matrix_alloc(m->m, m->n, m->shape, m->vtype);
    for (j = 0; j < m->m; j++)
    {
	double  mjj = matrix_getf(m, j, j);

	matrix_putf(sqrt(mjj), c, j, j);
	for (k = 0; k < j; k++)
	{
	    double  corr;
	    double  mkk = matrix_getf(m, k, k);

	    corr = matrix_getf(m, j, k) / sqrt(mjj * mkk);
	    matrix_putf(corr, c, j, k);
	}
    }
    matrix_format(c);
    matrix_free(c);
}

void    state_corr_format_two(State * state, int i, int j)
{
    int     k, l;
    Matrix *mij = (Matrix *) matrix_getp(state->s, i, j);
    Matrix *mii = (Matrix *) matrix_getp(state->s, i, i);
    Matrix *mjj = (Matrix *) matrix_getp(state->s, j, j);
    Matrix *c;

    if (mij == NULL)
	format("(nil)\n");

    c = matrix_alloc(mij->m, mij->n, mij->shape, mij->vtype);
    for (k = 0; k < mij->m; k++)
    {
	double  mikik = matrix_getf(mii, k, k);

	for (l = 0; l < mij->n; l++)
	{
	    double  corr;
	    double  mjljl = matrix_getf(mjj, l, l);

	    corr = matrix_getf(mij, k, l) / sqrt(mikik * mjljl);
	    matrix_putf(corr, c, k, l);
	}
    }
    matrix_format(c);
    matrix_free(c);
}

void    state_basis_format(State * state)
{
    format("state->basis\n");
    vector_format(state->basis);
}

void    state_basis_format_one(State * state, int i)
{
    void   *basis = vector_getp(state->basis, i);
    int     type = vector_get(state->type, i);

    format("state->basis: %d\n", i);
    basis_format(basis, type);
}
