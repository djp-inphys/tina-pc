/**@(#)Mat4 handling
**/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

static Mat4 mat4_0 = {Mat4_id};

Mat4   *mat4_alloc(void)
{
    Mat4   *m = ts_ralloc(Mat4);

    m->el[0][0] = 0.0;
    m->el[0][1] = 0.0;
    m->el[0][2] = 0.0;
    m->el[0][3] = 0.0;
    m->el[1][0] = 0.0;
    m->el[1][1] = 0.0;
    m->el[1][2] = 0.0;
    m->el[1][3] = 0.0;
    m->el[2][0] = 0.0;
    m->el[2][1] = 0.0;
    m->el[2][2] = 0.0;
    m->el[2][3] = 0.0;
    m->el[3][0] = 0.0;
    m->el[3][1] = 0.0;
    m->el[3][2] = 0.0;
    m->el[3][3] = 0.0;
    return (m);
}

Mat4   *mat4_make(Mat4 n)
{
    Mat4   *m = ts_ralloc(Mat4);

    *m = n;
    return (m);
}

void    mat4_free(Mat4 * m)
{
    rfree((void *) m);
}

/** function versions of component macros **/

double  mat4_get_xx(Mat4 m)
{
    return (mat4_xx(m));
}

double  mat4_get_xy(Mat4 m)
{
    return (mat4_xy(m));
}

double  mat4_get_xz(Mat4 m)
{
    return (mat4_xz(m));
}

double  mat4_get_xw(Mat4 m)
{
    return (mat4_xw(m));
}

double  mat4_get_yx(Mat4 m)
{
    return (mat4_yx(m));
}

double  mat4_get_yy(Mat4 m)
{
    return (mat4_yy(m));
}

double  mat4_get_yz(Mat4 m)
{
    return (mat4_yz(m));
}

double  mat4_get_yw(Mat4 m)
{
    return (mat4_yw(m));
}

double  mat4_get_zx(Mat4 m)
{
    return (mat4_zx(m));
}

double  mat4_get_zy(Mat4 m)
{
    return (mat4_zy(m));
}

double  mat4_get_zz(Mat4 m)
{
    return (mat4_zz(m));
}

double  mat4_get_zw(Mat4 m)
{
    return (mat4_zw(m));
}

double  mat4_get_wx(Mat4 m)
{
    return (mat4_wx(m));
}

double  mat4_get_wy(Mat4 m)
{
    return (mat4_wy(m));
}

double  mat4_get_wz(Mat4 m)
{
    return (mat4_wz(m));
}

double  mat4_get_ww(Mat4 m)
{
    return (mat4_ww(m));
}

Mat4    mat4(double mxx, double mxy, double mxz, double mxw, double myx, double myy, double myz, double myw, double mzx, double mzy, double mzz, double mzw, double mwx, double mwy, double mwz, double mww)
{
    Mat4    m = {Mat4_id};

    m.el[0][0] = mxx;
    m.el[0][1] = mxy;
    m.el[0][2] = mxz;
    m.el[0][3] = mxw;
    m.el[1][0] = myx;
    m.el[1][1] = myy;
    m.el[1][2] = myz;
    m.el[1][3] = myw;
    m.el[2][0] = mzx;
    m.el[2][1] = mzy;
    m.el[2][2] = mzz;
    m.el[2][3] = mzw;
    m.el[3][0] = mwx;
    m.el[3][1] = mwy;
    m.el[3][2] = mwz;
    m.el[3][3] = mww;
    return (m);
}

Mat4    mat4_unit(void)
{
    return (mat4(1.0, 0.0, 0.0, 0.0,
		 0.0, 1.0, 0.0, 0.0,
		 0.0, 0.0, 1.0, 0.0,
		 0.0, 0.0, 0.0, 1.0));
}

Mat4    mat4_zero(void)
{
    return (mat4_0);
}

void    mat4_comps(Mat4 m, double *mxx, double *mxy, double *mxz, double *mxw, double *myx, double *myy, double *myz, double *myw, double *mzx, double *mzy, double *mzz, double *mzw, double *mwx, double *mwy, double *mwz, double *mww)
{
    *mxx = m.el[0][0];
    *mxy = m.el[0][1];
    *mxz = m.el[0][2];
    *mxw = m.el[0][3];
    *myx = m.el[1][0];
    *myy = m.el[1][1];
    *myz = m.el[1][2];
    *myw = m.el[1][3];
    *mzx = m.el[2][0];
    *mzy = m.el[2][1];
    *mzz = m.el[2][2];
    *mzw = m.el[2][3];
    *mwx = m.el[3][0];
    *mwy = m.el[3][1];
    *mwz = m.el[3][2];
    *mww = m.el[3][3];
}

Vec4    mat4_rowx(Mat4 m)
{
    return (vec4(m.el[0][0], m.el[0][1], m.el[0][2], m.el[0][3]));
}

Vec4    mat4_rowy(Mat4 m)
{
    return (vec4(m.el[1][0], m.el[1][1], m.el[1][2], m.el[1][3]));
}

Vec4    mat4_rowz(Mat4 m)
{
    return (vec4(m.el[2][0], m.el[2][1], m.el[2][2], m.el[2][3]));
}

Vec4    mat4_roww(Mat4 m)
{
    return (vec4(m.el[3][0], m.el[3][1], m.el[3][2], m.el[3][3]));
}

Vec4    mat4_colx(Mat4 m)
{
    return (vec4(m.el[0][0], m.el[1][0], m.el[2][0], m.el[3][0]));
}

Vec4    mat4_coly(Mat4 m)
{
    return (vec4(m.el[0][1], m.el[1][1], m.el[2][1], m.el[3][1]));
}

Vec4    mat4_colz(Mat4 m)
{
    return (vec4(m.el[0][2], m.el[1][2], m.el[2][2], m.el[3][2]));
}

Vec4    mat4_colw(Mat4 m)
{
    return (vec4(m.el[0][3], m.el[1][3], m.el[2][3], m.el[3][3]));
}

Mat4    mat4_of_cols(Vec4 cx, Vec4 cy, Vec4 cz, Vec4 cw)
{
    Mat4    m = {Mat4_id};

    m.el[0][0] = cx.el[0];
    m.el[1][0] = cx.el[1];
    m.el[2][0] = cx.el[2];
    m.el[3][0] = cx.el[3];
    m.el[0][1] = cy.el[0];
    m.el[1][1] = cy.el[1];
    m.el[2][1] = cy.el[2];
    m.el[3][1] = cy.el[3];
    m.el[0][2] = cz.el[0];
    m.el[1][2] = cz.el[1];
    m.el[2][2] = cz.el[2];
    m.el[3][2] = cz.el[3];
    m.el[0][3] = cw.el[0];
    m.el[1][3] = cw.el[1];
    m.el[2][3] = cw.el[2];
    m.el[3][3] = cw.el[3];
    return (m);
}

Mat4    mat4_of_rows(Vec4 rx, Vec4 ry, Vec4 rz, Vec4 rw)
{
    Mat4    m = {Mat4_id};

    m.el[0][0] = rx.el[0];
    m.el[0][1] = rx.el[1];
    m.el[0][2] = rx.el[2];
    m.el[0][3] = rx.el[3];
    m.el[1][0] = ry.el[0];
    m.el[1][1] = ry.el[1];
    m.el[1][2] = ry.el[2];
    m.el[1][3] = ry.el[3];
    m.el[2][0] = rz.el[0];
    m.el[2][1] = rz.el[1];
    m.el[2][2] = rz.el[2];
    m.el[2][3] = rz.el[3];
    m.el[3][0] = rw.el[0];
    m.el[3][1] = rw.el[1];
    m.el[3][2] = rw.el[2];
    m.el[3][3] = rw.el[3];
    return (m);
}

Mat4    mat4_sum(Mat4 m, Mat4 n)
{
    Mat4    sum = {Mat4_id};
    int     i, j;

    for (i = 0; i < 4; ++i)
	for (j = 0; j < 4; ++j)
	    sum.el[i][j] = m.el[i][j] + n.el[i][j];
    return (sum);
}

Mat4    mat4_diff(Mat4 m, Mat4 n)
{
    Mat4    diff = {Mat4_id};
    int     i, j;

    for (i = 0; i < 4; ++i)
	for (j = 0; j < 4; ++j)
	    diff.el[i][j] = m.el[i][j] - n.el[i][j];
    return (diff);
}

Mat4    mat4_minus(Mat4 m)
{
    Mat4    minus = {Mat4_id};
    int     i, j;

    for (i = 0; i < 4; ++i)
	for (j = 0; j < 4; ++j)
	    minus.el[i][j] = -m.el[i][j];
    return (minus);
}

Mat4    mat4_times(double k, Mat4 m)
{
    Mat4    prod = {Mat4_id};
    int     i, j;

    for (i = 0; i < 4; ++i)
	for (j = 0; j < 4; ++j)
	    prod.el[i][j] = k * m.el[i][j];
    return (prod);
}

Mat4    mat4_prod(Mat4 m, Mat4 n)
{
    Mat4    prod = {Mat4_id};
    double  sum;
    int     i, j, k;

    for (i = 0; i < 4; ++i)
	for (j = 0; j < 4; ++j)
	{
	    sum = 0.0;
	    for (k = 0; k < 4; ++k)
		sum += m.el[i][k] * n.el[k][j];
	    prod.el[i][j] = sum;
	}
    return (prod);
}

Mat4    mat4_inverse(Mat4 m)
{
    Mat4    inv = {Mat4_id};
    double  a[4][4];
    int     i, j, k, p[4];
    double  h, q, s, sup, pivot;

    for (i = 0; i < 4; i++)
	for (j = 0; j < 4; j++)
	    a[i][j] = m.el[i][j];

    for (k = 0; k < 4; k++)
    {
	sup = 0.0;
	p[k] = 0;
	for (i = k; i < 4; i++)
	{
	    s = 0.0;
	    for (j = k; j < 4; j++)
		s += fabs(a[i][j]);
	    q = fabs(a[i][k]) / s;
	    if (sup < q)
	    {
		sup = q;
		p[k] = i;
	    }
	}
	if (sup == 0.0)
	    return (mat4_unit());
	if (p[k] != k)
	    for (j = 0; j < 4; j++)
	    {
		h = a[k][j];
		a[k][j] = a[p[k]][j];
		a[p[k]][j] = h;
	    }
	pivot = a[k][k];
	for (j = 0; j < 4; j++)
	    if (j != k)
	    {
		a[k][j] = -a[k][j] / pivot;
		for (i = 0; i < 4; i++)
		    if (i != k)
			a[i][j] += a[i][k] * a[k][j];
	    }
	for (i = 0; i < 4; i++)
	    a[i][k] = a[i][k] / pivot;
	a[k][k] = 1.0 / pivot;
    }
    for (k = 4 - 1; k >= 0; k--)
	if (p[k] != k)
	    for (i = 0; i < 4; i++)
	    {
		h = a[i][k];
		a[i][k] = a[i][p[k]];
		a[i][p[k]] = h;
	    }

    for (i = 0; i < 4; i++)
	for (j = 0; j < 4; j++)
	    inv.el[i][j] = a[i][j];
    return (inv);
}

Mat4    mat4_transpose(Mat4 m)
{
    Mat4    trans = {Mat4_id};
    int     i, j;

    for (i = 0; i < 4; ++i)
	for (j = 0; j < 4; ++j)
	    trans.el[i][j] = m.el[j][i];
    return (trans);
}

double  mat4_trace(Mat4 m)
{
    return (m.el[0][0] + m.el[1][1] + m.el[2][2] + m.el[3][3]);
}

Vec4    mat4_vprod(Mat4 m, Vec4 v)
{
    Vec4    prod = {Vec4_id};
    double  sum;
    int     i, j;

    for (i = 0; i < 4; ++i)
    {
	sum = 0.0;
	for (j = 0; j < 4; ++j)
	    sum += m.el[i][j] * v.el[j];
	prod.el[i] = sum;
    }
    return (prod);
}

Vec4    mat4_transpose_vprod(Mat4 m, Vec4 v)
{
    Vec4    prod = {Vec4_id};
    double  sum;
    int     i, j;

    for (i = 0; i < 4; ++i)
    {
	sum = 0.0;
	for (j = 0; j < 4; ++j)
	    sum += m.el[j][i] * v.el[j];
	prod.el[i] = sum;
    }
    return (prod);
}

double  mat4_sprod(Vec4 v, Mat4 m, Vec4 w)
{
    double  sum = 0.0;
    int     i, j;

    for (i = 0; i < 4; ++i)
	for (j = 0; j < 4; ++j)
	    sum += v.el[i] * m.el[i][j] * w.el[j];
    return (sum);
}

Mat4    mat4_tensor(Vec4 v, Vec4 w)
{
    Mat4    prod = {Mat4_id};
    int     i, j;

    for (i = 0; i < 4; ++i)
	for (j = 0; j < 4; ++j)
	    prod.el[i][j] = v.el[i] * w.el[j];
    return (prod);
}

Mat4    mat4_read(FILE * fp)
{
    Mat4    temp = {Mat4_id};
    int     i;

    for (i = 0; i < 4; ++i)
	(void) fscanf(fp, "%f %f %f %f",
		      &temp.el[i][0], &temp.el[i][1], &temp.el[i][2], &temp.el[i][3]);
    return (temp);
}

void    mat4_print(FILE * fp, Mat4 m)
{
    int     i;

    for (i = 0; i < 4; ++i)
	(void) fprintf(fp, "%f %f %f %f\n", m.el[i][0], m.el[i][1], m.el[i][2], m.el[i][3]);
}

void    mat4_pprint(FILE * fp, char *msg, Mat4 m)
{
    int     i, n;

    n = strlen(msg);
    (void) fprintf(fp, "%s", msg);
    (void) fprintf(fp, "|%15.6f%15.6f%15.6f%15.6f|\n",
		   m.el[0][0], m.el[0][1], m.el[0][2], m.el[0][3]);
    for (i = 0; i < n; ++i)
	(void) fputc(' ', stderr);
    (void) fprintf(fp, "|%15.6f%15.6f%15.6f%15.6f|\n",
		   m.el[1][0], m.el[1][1], m.el[1][2], m.el[1][3]);
    for (i = 0; i < n; ++i)
	(void) fputc(' ', stderr);
    (void) fprintf(fp, "|%15.6f%15.6f%15.6f%15.6f|\n",
		   m.el[2][0], m.el[2][1], m.el[2][2], m.el[2][3]);
    for (i = 0; i < n; ++i)
	(void) fputc(' ', stderr);
    (void) fprintf(fp, "|%15.6f%15.6f%15.6f%15.6f|\n",
		   m.el[3][0], m.el[3][1], m.el[3][2], m.el[3][3]);
}

void    mat4_format(Mat4 m)
{
    int     i;

    for (i = 0; i < 4; ++i)
	format("%f %f %f %f\n", m.el[i][0], m.el[i][1], m.el[i][2], m.el[i][3]);
}

void    mat4_eigen(Mat4 m, double *eval, Vec4 * evec)
{
    int     i, j;
    Matrix *a = matrix_alloc(4, 4, matrix_full, double_v);
    Matrix *b = matrix_alloc(4, 4, matrix_full, double_v);
    Vector *v = vector_alloc(4, double_v);

    /** copy mat4 into matrix **/
    for (i = 0; i < 4; i++)
	for (j = 0; j < 4; j++)
	    matrix_putf(m.el[i][j], a, i, j);

    /** get vector of eigenvals and matrix of column eigenvecs **/
    (void) matrix_eigen_sym(a, v, b);

    /** copy into eval and evec **/
    for (i = 0; i < 4; i++)
	eval[i] = vector_getf(v, i);
    for (i = 0; i < 4; i++)
	for (j = 0; j < 4; j++)
	    evec[i].el[j] = matrix_getf(b, j, i);
    matrix_free(a);
    matrix_free(b);
    vector_free(v);
}
