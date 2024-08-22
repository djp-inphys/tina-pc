/*
 *
 * mat.c
 *
 * Dynamically allocated matrix of doubles.
 *
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

Mat *mat_make(int m, int n)
{
    Mat *a = talloc(Mat);
    a->m = m;
    a->n = n;
    a->el = tarray_alloc(0, 0, m, n, double);
    return(a);
}

void mat_free(Mat *a)
{
    if(a == NULL)
	return;
    tarray_free(a->el, 0, 0, a->m, a->n, double);
    rfree(a);
}

void mat_copy(Mat *a, Mat *b)
{
    if(a == NULL)
	return;
    tarray_copy_inplace(a->el, b->el, 0, 0, a->m, a->n, double);
}

void mat_zero(Mat *a)
{
    int i, j;
    if(a == NULL)
	return;
    for(i = 0; i < a->m; i++)
	for(j = 0; j < a->n; j++)
	    a->el[i][j] = 0;
}

void mat_unit(Mat *a)
{
    int i, j;
    if(a == NULL)
	return;
    for(i = 0; i < a->m; i++)
	for(j = 0; j < a->n; j++)
	    a->el[i][j] = (i == j)? 1: 0;
}

void mat_rand_unif(Mat *a, double p, double q)
{
    int i, j;
    if(a == NULL)
	return;
    for(i = 0; i < a->m; i++)
	for(j = 0; j < a->n; j++)
	    a->el[i][j] = rand_unif(p, q);
}

void mat_rand_normal(Mat *a, double m, double s)
{
    int i, j;
    if(a == NULL)
	return;
    for(i = 0; i < a->m; i++)
	for(j = 0; j < a->n; j++)
	    a->el[i][j] = rand_normal(m, s);
}

void mat_transp(Mat *at, Mat *a)
{
    int i, j;
    if(at == NULL || a == NULL)
	return;
    for(i = 0; i < a->m; i++)
	for(j = 0; j < a->n; j++)
	    at->el[j][i] = a->el[i][j];
}

void mat_stransp(Mat *a)
{
    int i, j;
    if(a == NULL)
	return;
    for(i = 0; i < a->m; i++)
	for(j = 0; j < i; j++)
	    SWAP(double, a->el[i][j], a->el[j][i]);
}

void mat_prod(Mat *ab, Mat *a, Mat *b)
{
    int i, j, k;
    if(ab == NULL || a == NULL || b == NULL)
	return;
    for(i = 0; i < a->m; i++)
	for(j = 0; j < b->n; j++)
	{
	    double sum = 0;
	    for(k = 0; k < a->n; k++)
		sum += a->el[i][k]*b->el[k][j];
	    ab->el[i][j] = sum;
	}
}

void mat_sqr(Mat *aa, Mat *a)
{
    int i, j, k;
    if(aa == NULL || a == NULL)
	return;
    for(i = 0; i < a->m; i++)
	for(j = 0; j < a->m; j++)
	{
	    double sum = 0;
	    for(k = 0; k < a->n; k++)
		sum += a->el[i][k]*a->el[j][k];
	    aa->el[i][j] = sum;
	}
}

void mat_vprod(Vec *av, Mat *a, Vec *v)
{
    int i, j;
    if(av == NULL || a == NULL || v == NULL)
	return;
    for(i = 0; i < a->m; i++)
    {
	double sum = 0;
	for(j = 0; j < a->n; j++)
	    sum += a->el[i][j]*v->el[j];
	av->el[i] = sum;
    }
}

void mat_dprod(Vec *d, Mat *a)
{
    int i, j;
    if(a == NULL || d == NULL)
	return;
    for(i = 0; i < a->m; i++)
	for(j = 0; j < a->n; j++)
	    a->el[i][j] *= d->el[i];
}

double mat_sprod(Vec *v, Mat *a, Vec *w)
{
    int i, j;
    double sum = 0;
    if(a == NULL || v == NULL)
	return(0);
    for(i = 0; i < a->m; i++)
	for(j = 0; j < a->n; j++)
	    sum += v->el[i]*a->el[i][j]*w->el[j];
    return(sum);
}

void mat_sum(Mat *a, Mat *b)
{
    int i, j;
    if(a == NULL || b == NULL)
	return;
    for(i = 0; i < a->m; i++)
	for(j = 0; j < a->n; j++)
	    a->el[i][j] += b->el[i][j];
}

void mat_diff(Mat *a, Mat *b)
{
    int i, j;
    if(a == NULL || b == NULL)
	return;
    for(i = 0; i < a->m; i++)
	for(j = 0; j < a->n; j++)
	    a->el[i][j] -= b->el[i][j];
}

void mat_times(double k, Mat *a)
{
    int i, j;
    if(a == NULL)
	return;
    for(i = 0; i < a->m; i++)
	for(j = 0; j < a->n; j++)
	    a->el[i][j] *= k;
}

void mat_minus(Mat *a)
{
    int i, j;
    if(a == NULL)
	return;
    for(i = 0; i < a->m; i++)
	for(j = 0; j < a->n; j++)
	    a->el[i][j] = -a->el[i][j];
}

void mat_accum(Mat *a, double k, Mat *b)
{
    int i, j;
    if(a == NULL || b == NULL)
	return;
    for(i = 0; i < a->m; i++)
	for(j = 0; j < a->n; j++)
	    a->el[i][j] += k*b->el[i][j];
}

void mat_sum_tensor(Mat *a, Vec *v, Vec *w)
{
    int i, j;
    if(a == NULL || v == NULL || w == NULL)
	return;
    for(i = 0; i < a->m; i++)
	for(j = 0; j < a->n; j++)
	    a->el[i][j] += v->el[i]*w->el[j];
}

void mat_accum_tensor(Mat *a, double k, Vec *v, Vec *w)
{
    int i, j;
    if(a == NULL || v == NULL || w == NULL)
	return;
    for(i = 0; i < a->m; i++)
	for(j = 0; j < a->n; j++)
	    a->el[i][j] += k*v->el[i]*w->el[j];
}

void mat_print(FILE *fp, char *fmt, Mat *a)
{
    int i, j;
    if(a == NULL)
    {
	fprintf(fp, "0 0 :\n");
	return;
    }
    fprintf(fp, "%d %d :\n", a->m, a->n);
    for(i = 0; i < a->m; i++)
    {
	for(j = 0; j < a->n; j++)
	    fprintf(fp, fmt, a->el[i][j]);
	fprintf(fp, "\n");
    }
}

Mat *mat_read(FILE *fp)
{
    Mat *a;
    int i, j, m, n;
    fscanf(fp, "%d %d %*s", &m, &n);
    a = mat_make(m, n);
    for(i = 0; i < a->m; i++)
	for(j = 0; j < a->n; j++)
	    fscanf(fp, "%lf", &a->el[i][j]);
    return(a);
}

void mat_row(Vec *row, Mat *a, int i)
{
    int j;
    if(row == NULL || a == NULL)
	return;
    for(j = 0; j < a->n; j++)
	row->el[j] = a->el[i][j];
}

void mat_row_get(Mat *a, int i, Vec *row)
{
    int j;
    if(row == NULL || a == NULL)
	return;
    for(j = 0; j < row->n; j++)
	row->el[j] = a->el[i][j];
}

void mat_row_set(Mat *a, int i, Vec *row)
{
    int j;
    if(row == NULL || a == NULL)
	return;
    for(j = 0; j < row->n; j++)
	a->el[i][j] = row->el[j];
}

void mat_col_get(Mat *a, int j, Vec *col)
{
    int i;
    if(col == NULL || a == NULL)
	return;
    for(i = 0; i < col->n; i++)
	col->el[i] = a->el[i][j];
}

void mat_col_set(Mat *a, int j, Vec *col)
{
    int i;
    if(col == NULL || a == NULL)
	return;
    for(i = 0; i < col->n; i++)
	a->el[i][j] = col->el[i];
}

void mat_block_get(Mat *a, int li, int lj, Mat *b)
{
    int i, j;
    for(i = 0; i < b->m; i++)
	for(j = 0; j < b->n; j++)
	    b->el[i][j] = a->el[i+li][j+lj];
}

void mat_block_set(Mat *a, int li, int lj, Mat *b)
{
    int i, j;
    for(i = 0; i < b->m; i++)
	for(j = 0; j < b->n; j++)
	    a->el[i+li][j+lj] = b->el[i][j];
}

void mat_index_get(Mat *a, Ivec *indi,  Ivec *indj, Mat *b)
{
    int i, j;
    for(i = 0; i < b->m; i++)
	for(j = 0; j < b->n; j++)
	    b->el[i][j] = a->el[indi->el[i]][indj->el[j]];
}

void mat_index_set(Mat *a, Ivec *indi,  Ivec *indj, Mat *b)
{
    int i, j;
    for(i = 0; i < b->m; i++)
	for(j = 0; j < b->n; j++)
	    a->el[indi->el[i]][indj->el[j]] = b->el[i][j];
}

void mat_mat3(Mat *a, Mat3 a3)
{
    a->el[0][0] = mat3_xx(a3);
    a->el[0][1] = mat3_xy(a3);
    a->el[0][2] = mat3_xz(a3);
    a->el[1][0] = mat3_yx(a3);
    a->el[1][1] = mat3_yy(a3);
    a->el[1][2] = mat3_yz(a3);
    a->el[2][0] = mat3_zx(a3);
    a->el[2][1] = mat3_zy(a3);
    a->el[2][2] = mat3_zz(a3);
}

Mat3 mat3_mat(Mat *a)
{
    Mat3 a3;
    mat3_xx(a3) = a->el[0][0];
    mat3_xy(a3) = a->el[0][1];
    mat3_xz(a3) = a->el[0][2];
    mat3_yx(a3) = a->el[1][0];
    mat3_yy(a3) = a->el[1][1];
    mat3_yz(a3) = a->el[1][2];
    mat3_zx(a3) = a->el[2][0];
    mat3_zy(a3) = a->el[2][1];
    mat3_zz(a3) = a->el[2][2];
    return(a3);
}
