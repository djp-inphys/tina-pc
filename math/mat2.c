/**@(#)Mat2 handling
**/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

static Mat2 mat2_0 = {Mat2_id};

void   *mat2_alloc(void)
{
    Mat2   *m = ts_ralloc(Mat2);

    m->el[0][0] = 0.0;
    m->el[0][1] = 0.0;
    m->el[1][0] = 0.0;
    m->el[1][1] = 0.0;
    return ((void *) m);
}

void   *mat2_make(Mat2 n)
{
    Mat2   *m = ts_ralloc(Mat2);

    *m = n;
    return ((void *) m);
}

void    mat2_free(void *m)
{
    rfree((void *) m);
}

Mat2    mat2(double mxx, double mxy, double myx, double myy)
{
    Mat2    m = {Mat2_id};

    m.el[0][0] = mxx;
    m.el[0][1] = mxy;
    m.el[1][0] = myx;
    m.el[1][1] = myy;
    return (m);
}

Mat2    mat2_unit(void)
{
    return (mat2(1.0, 0.0,
		 0.0, 1.0));
}

Mat2    mat2_zero(void)
{
    return (mat2_0);
}

void    mat2_comps(Mat2 m, float *mxx, float *mxy, float *myx, float *myy)
{
    *mxx = m.el[0][0];
    *mxy = m.el[0][1];
    *myx = m.el[1][0];
    *myy = m.el[1][1];
}

Vec2    mat2_rowx(Mat2 m)
{
    return (vec2(m.el[0][0], m.el[0][1]));
}

Vec2    mat2_rowy(Mat2 m)
{
    return (vec2(m.el[1][0], m.el[1][1]));
}

Vec2    mat2_colx(Mat2 m)
{
    return (vec2(m.el[0][0], m.el[1][0]));
}

Vec2    mat2_coly(Mat2 m)
{
    return (vec2(m.el[0][1], m.el[1][1]));
}

Mat2    mat2_of_rows(Vec2 rx, Vec2 ry)
{
    Mat2    m = {Mat2_id};

    m.el[0][0] = rx.el[0];
    m.el[1][0] = rx.el[1];
    m.el[0][1] = ry.el[0];
    m.el[1][1] = ry.el[1];
    return (m);
}

Mat2    mat2_of_cols(Vec2 cx, Vec2 cy)
{
    Mat2    m = {Mat2_id};

    m.el[0][0] = cx.el[0];
    m.el[0][1] = cx.el[1];
    m.el[1][0] = cy.el[0];
    m.el[1][1] = cy.el[1];
    return (m);
}

Mat2    mat2_sum(Mat2 m, Mat2 n)
{
    Mat2    sum = {Mat2_id};
    int     i, j;

    for (i = 0; i < 2; ++i)
	for (j = 0; j < 2; ++j)
	    sum.el[i][j] = m.el[i][j] + n.el[i][j];
    return (sum);
}

Mat2    mat2_diff(Mat2 m, Mat2 n)
{
    Mat2    diff = {Mat2_id};
    int     i, j;

    for (i = 0; i < 2; ++i)
	for (j = 0; j < 2; ++j)
	    diff.el[i][j] = m.el[i][j] - n.el[i][j];
    return (diff);
}

Mat2    mat2_minus(Mat2 m)
{
    Mat2    minus = {Mat2_id};
    int     i, j;

    for (i = 0; i < 2; ++i)
	for (j = 0; j < 2; ++j)
	    minus.el[i][j] = -m.el[i][j];
    return (minus);
}

Mat2    mat2_times(double k, Mat2 m)
{
    Mat2    prod = {Mat2_id};
    int     i, j;

    for (i = 0; i < 2; ++i)
	for (j = 0; j < 2; ++j)
	    prod.el[i][j] = k * m.el[i][j];
    return (prod);
}

Mat2    mat2_prod(Mat2 m, Mat2 n)
{
    Mat2    prod = {Mat2_id};
    int     i, j, k;
    double  sum;

    for (i = 0; i < 2; ++i)
	for (j = 0; j < 2; ++j)
	{
	    sum = 0.0;
	    for (k = 0; k < 2; ++k)
		sum += m.el[i][k] * n.el[k][j];
	    prod.el[i][j] = sum;
	}
    return (prod);
}

Mat2    mat2_inverse(Mat2 m)
{
    double  det, k;
    float   mxx, mxy, myx, myy;

    mat2_comps(m, &mxx, &mxy, &myx, &myy);
    det = mxx * myy - mxy * myx;
    if (det == 0.0)
	return (mat2_unit());
    k = 1.0 / det;
    return (mat2(k * myy, -k * mxy,
		 -k * myx, k * mxx));
}

Mat2    mat2_transpose(Mat2 m)
{
    Mat2    trans = {Mat2_id};
    int     i, j;

    for (i = 0; i < 2; ++i)
	for (j = 0; j < 2; ++j)
	    trans.el[i][j] = m.el[j][i];
    return (trans);
}

Mat2    mat2_sym(Mat2 m)
{
    double  mxx = mat2_xx(m);
    double  mxy = mat2_xy(m);
    double  myx = mat2_yx(m);
    double  myy = mat2_yy(m);

    mxy = 0.5 * (mxy + myx);
    return (mat2(mxx, mxy, mxy, myy));
}

double  mat2_trace(Mat2 m)
{
    return (m.el[0][0] + m.el[1][1]);
}

double  mat2_det(Mat2 m)
{
    return (mat2_xx(m) * mat2_yy(m) - mat2_xy(m) * mat2_yx(m));
}

Bool    mat2_posdef(Mat2 m)
{
    if (mat2_xx(m) <= 0.0)
	return (false);
    else if (mat2_det(m) <= 0.0)
	return (false);
    else
	return (true);
}

Vec2    mat2_vprod(Mat2 m, Vec2 v)
{
    Vec2    prod = {Vec2_id};
    int     i, j;
    double  sum;

    for (i = 0; i < 2; ++i)
    {
	sum = 0.0;
	for (j = 0; j < 2; ++j)
	    sum += m.el[i][j] * v.el[j];
	prod.el[i] = sum;
    }
    return (prod);
}

double  mat2_sprod(Vec2 v, Mat2 m, Vec2 w)
{
    double  sum = 0.0;
    int     i, j;

    for (i = 0; i < 2; ++i)
	for (j = 0; j < 2; ++j)
	    sum += v.el[i] * m.el[i][j] * w.el[j];
    return (sum);
}

Mat2    mat2_tensor(Vec2 v, Vec2 w)
{
    Mat2    prod = {Mat2_id};
    int     i, j;

    for (i = 0; i < 2; ++i)
	for (j = 0; j < 2; ++j)
	    prod.el[i][j] = v.el[i] * w.el[j];
    return (prod);
}

Mat2    mat2_read(FILE * fp)
{
    Mat2    temp = {Mat2_id};
    int     i;

    for (i = 0; i < 2; ++i)
	(void) fscanf(fp, "%f %f", &temp.el[i][0], &temp.el[i][1]);
    return (temp);
}

void    mat2_print(FILE * fp, Mat2 m)
{
    int     i;

    for (i = 0; i < 2; ++i)
	(void) fprintf(fp, "%f %f\n", m.el[i][0], m.el[i][1]);
}

void    mat2_pprint(FILE * fp, char *msg, Mat2 m)
{
    int     i, n;

    n = strlen(msg);
    (void) fprintf(fp, "%s", msg);
    (void) fprintf(fp, "|%15.6f%15.6f|\n", m.el[0][0], m.el[0][1]);
    for (i = 0; i < n; ++i)
	(void) fputc(' ', stderr);
    (void) fprintf(fp, "|%15.6f%15.6f|\n", m.el[1][0], m.el[1][1]);
}

void    mat2_format(Mat2 m)
{
    int     i;

    for (i = 0; i < 2; ++i)
	format("%f %f \n", m.el[i][0], m.el[i][1]);
}

/**
eigendirection and eigenvalues of symmetric 2by2 matrix
|a b|
|b c|
**/

void    mat2_sym_eigen(Mat2 m, double *theta, double *lambda1, double *lambda2)
{
    double  a, b, c, p, q, r;

    a = mat2_xx(m);
    b = 0.5 * (mat2_xy(m) + mat2_yx(m));
    c = mat2_yy(m);
    p = (a + c) / 2.0;
    q = (a - c) / 2.0;
    r = sqrt(q * q + b * b);
    if (b == 0.0 && q == 0.0)
	*theta = 0.0;
    else
	*theta = 0.5 * atan2(b, q);
    *lambda1 = p + r;
    *lambda2 = p - r;
}
