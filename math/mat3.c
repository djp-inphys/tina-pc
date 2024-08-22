/**@(#)Mat3 handling
**/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

static Mat3 mat3_0 = {Mat3_id};

Mat3   *mat3_alloc(void)
{
    Mat3   *m = ts_ralloc(Mat3);

    m->el[0][0] = 0.0;
    m->el[0][1] = 0.0;
    m->el[0][2] = 0.0;
    m->el[1][0] = 0.0;
    m->el[1][1] = 0.0;
    m->el[1][2] = 0.0;
    m->el[2][0] = 0.0;
    m->el[2][1] = 0.0;
    m->el[2][2] = 0.0;
    return (m);
}

Mat3   *mat3_make(Mat3 n)
{
    Mat3   *m = ts_ralloc(Mat3);

    *m = n;
    return (m);
}

void    mat3_free(Mat3 * m)
{
    rfree((void *) m);
}

/** function versions of component macros **/

double  mat3_get_xx(Mat3 m)
{
    return (mat3_xx(m));
}

double  mat3_get_xy(Mat3 m)
{
    return (mat3_xy(m));
}

double  mat3_get_xz(Mat3 m)
{
    return (mat3_xz(m));
}

double  mat3_get_yx(Mat3 m)
{
    return (mat3_yx(m));
}

double  mat3_get_yy(Mat3 m)
{
    return (mat3_yy(m));
}

double  mat3_get_yz(Mat3 m)
{
    return (mat3_yz(m));
}

double  mat3_get_zx(Mat3 m)
{
    return (mat3_zx(m));
}

double  mat3_get_zy(Mat3 m)
{
    return (mat3_zy(m));
}

double  mat3_get_zz(Mat3 m)
{
    return (mat3_zz(m));
}

Mat3    mat3(double mxx, double mxy, double mxz, double myx, double myy, double myz, double mzx, double mzy, double mzz)
{
    Mat3    m = {Mat3_id};

    m.el[0][0] = mxx;
    m.el[0][1] = mxy;
    m.el[0][2] = mxz;
    m.el[1][0] = myx;
    m.el[1][1] = myy;
    m.el[1][2] = myz;
    m.el[2][0] = mzx;
    m.el[2][1] = mzy;
    m.el[2][2] = mzz;
    return (m);
}

Mat3    mat3_unit(void)
{
    return (mat3(1.0, 0.0, 0.0,
		 0.0, 1.0, 0.0,
		 0.0, 0.0, 1.0));
}

Mat3    mat3_zero(void)
{
    return (mat3_0);
}

Mat3    mat3_diag(double mxx, double myy, double mzz)
{
    return (mat3(mxx, 0.0, 0.0,
		 0.0, myy, 0.0,
		 0.0, 0.0, mzz));
}

void    mat3_comps(Mat3 m, float *mxx, float *mxy, float *mxz, float *myx, float *myy, float *myz, float *mzx, float *mzy, float *mzz)
{
    *mxx = m.el[0][0];
    *mxy = m.el[0][1];
    *mxz = m.el[0][2];
    *myx = m.el[1][0];
    *myy = m.el[1][1];
    *myz = m.el[1][2];
    *mzx = m.el[2][0];
    *mzy = m.el[2][1];
    *mzz = m.el[2][2];
}

Vec3    mat3_rowx(Mat3 m)
{
    return (vec3(m.el[0][0], m.el[0][1], m.el[0][2]));
}

Vec3    mat3_rowy(Mat3 m)
{
    return (vec3(m.el[1][0], m.el[1][1], m.el[1][2]));
}

Vec3    mat3_rowz(Mat3 m)
{
    return (vec3(m.el[2][0], m.el[2][1], m.el[2][2]));
}

Vec3    mat3_colx(Mat3 m)
{
    return (vec3(m.el[0][0], m.el[1][0], m.el[2][0]));
}

Vec3    mat3_coly(Mat3 m)
{
    return (vec3(m.el[0][1], m.el[1][1], m.el[2][1]));
}

Vec3    mat3_colz(Mat3 m)
{
    return (vec3(m.el[0][2], m.el[1][2], m.el[2][2]));
}

Mat3    mat3_of_cols(Vec3 cx, Vec3 cy, Vec3 cz)
{
    Mat3    m = {Mat3_id};

    m.el[0][0] = cx.el[0];
    m.el[1][0] = cx.el[1];
    m.el[2][0] = cx.el[2];
    m.el[0][1] = cy.el[0];
    m.el[1][1] = cy.el[1];
    m.el[2][1] = cy.el[2];
    m.el[0][2] = cz.el[0];
    m.el[1][2] = cz.el[1];
    m.el[2][2] = cz.el[2];
    return (m);
}

Mat3    mat3_of_rows(Vec3 rx, Vec3 ry, Vec3 rz)
{
    Mat3    m = {Mat3_id};

    m.el[0][0] = rx.el[0];
    m.el[0][1] = rx.el[1];
    m.el[0][2] = rx.el[2];
    m.el[1][0] = ry.el[0];
    m.el[1][1] = ry.el[1];
    m.el[1][2] = ry.el[2];
    m.el[2][0] = rz.el[0];
    m.el[2][1] = rz.el[1];
    m.el[2][2] = rz.el[2];
    return (m);
}

Mat3    mat3_sum(Mat3 m, Mat3 n)
{
    Mat3    sum = {Mat3_id};
    int     i, j;

    for (i = 0; i < 3; ++i)
	for (j = 0; j < 3; ++j)
	    sum.el[i][j] = m.el[i][j] + n.el[i][j];
    return (sum);
}

Mat3    mat3_sum3(Mat3 l, Mat3 m, Mat3 n)
{
    Mat3    sum = {Mat3_id};
    int     i, j;

    for (i = 0; i < 3; ++i)
	for (j = 0; j < 3; ++j)
	    sum.el[i][j] = l.el[i][j] + m.el[i][j] + n.el[i][j];
    return (sum);
}

Mat3    mat3_diff(Mat3 m, Mat3 n)
{
    Mat3    diff = {Mat3_id};
    int     i, j;

    for (i = 0; i < 3; ++i)
	for (j = 0; j < 3; ++j)
	    diff.el[i][j] = m.el[i][j] - n.el[i][j];
    return (diff);
}

Mat3    mat3_minus(Mat3 m)
{
    Mat3    minus = {Mat3_id};
    int     i, j;

    for (i = 0; i < 3; ++i)
	for (j = 0; j < 3; ++j)
	    minus.el[i][j] = -m.el[i][j];
    return (minus);
}

Mat3    mat3_times(double k, Mat3 m)
{
    Mat3    prod = {Mat3_id};
    int     i, j;

    for (i = 0; i < 3; ++i)
	for (j = 0; j < 3; ++j)
	    prod.el[i][j] = k * m.el[i][j];
    return (prod);
}

Mat3    mat3_prod(Mat3 m, Mat3 n)
{
    Mat3    prod = {Mat3_id};
    double  sum;
    int     i, j, k;

    for (i = 0; i < 3; ++i)
	for (j = 0; j < 3; ++j)
	{
	    sum = 0.0;
	    for (k = 0; k < 3; ++k)
		sum += m.el[i][k] * n.el[k][j];
	    prod.el[i][j] = sum;
	}
    return (prod);
}

Mat3    mat3_inverse(Mat3 m)
{
    Mat3    inv = {Mat3_id};
    double  a[3][3];
    int     i, j, k, p[3];
    double  h, q, s, sup, pivot;

    for (i = 0; i < 3; i++)
	for (j = 0; j < 3; j++)
	    a[i][j] = m.el[i][j];

    for (k = 0; k < 3; k++)
    {
	sup = 0.0;
	p[k] = 0;
	for (i = k; i < 3; i++)
	{
	    s = 0.0;
	    for (j = k; j < 3; j++)
		s += fabs(a[i][j]);
	    q = fabs(a[i][k]) / s;
	    if (sup < q)
	    {
		sup = q;
		p[k] = i;
	    }
	}
	if (sup == 0.0)
	    return (mat3_unit());
	if (p[k] != k)
	    for (j = 0; j < 3; j++)
	    {
		h = a[k][j];
		a[k][j] = a[p[k]][j];
		a[p[k]][j] = h;
	    }
	pivot = a[k][k];
	for (j = 0; j < 3; j++)
	    if (j != k)
	    {
		a[k][j] = -a[k][j] / pivot;
		for (i = 0; i < 3; i++)
		    if (i != k)
			a[i][j] += a[i][k] * a[k][j];
	    }
	for (i = 0; i < 3; i++)
	    a[i][k] = a[i][k] / pivot;
	a[k][k] = 1.0 / pivot;
    }
    for (k = 3 - 1; k >= 0; k--)
	if (p[k] != k)
	    for (i = 0; i < 3; i++)
	    {
		h = a[i][k];
		a[i][k] = a[i][p[k]];
		a[i][p[k]] = h;
	    }

    for (i = 0; i < 3; i++)
	for (j = 0; j < 3; j++)
	    inv.el[i][j] = a[i][j];
    return (inv);
}

Mat3    mat3_transpose(Mat3 m)
{
    Mat3    trans = {Mat3_id};
    int     i, j;

    for (i = 0; i < 3; ++i)
	for (j = 0; j < 3; ++j)
	    trans.el[i][j] = m.el[j][i];
    return (trans);
}

double  mat3_trace(Mat3 m)
{
    return (m.el[0][0] + m.el[1][1] + m.el[2][2]);
}

double  mat3_det(Mat3 m)
{
    float   mxx, mxy, mxz, myx, myy, myz, mzx, mzy, mzz;

    mat3_comps(m, &mxx, &mxy, &mxz, &myx, &myy, &myz, &mzx, &mzy, &mzz);
    return (mxx * myy * mzz + mxy * myz * mzx + mxz * myx * mzy
	    - mxx * myz * mzy - mxy * myx * mzz - mxz * myy * mzx);
}

Bool    mat3_posdef(Mat3 m)
{
    if (m.el[0][0] <= 0.0)
	return (false);
    else if (m.el[0][0] * m.el[1][1] - m.el[0][1] * m.el[1][0] <= 0.0)
	return (false);
    else if (mat3_det(m) <= 0.0)
	return (false);
    else
	return (true);
}

Vec3    mat3_vprod(Mat3 m, Vec3 v)
{
    Vec3    prod = {Vec3_id};
    double  sum;
    int     i, j;

    for (i = 0; i < 3; ++i)
    {
	sum = 0.0;
	for (j = 0; j < 3; ++j)
	    sum += m.el[i][j] * v.el[j];
	prod.el[i] = sum;
    }
    return (prod);
}

Vec3    mat3_transpose_vprod(Mat3 m, Vec3 v)
{
    Vec3    prod = {Vec3_id};
    double  sum;
    int     i, j;

    for (i = 0; i < 3; ++i)
    {
	sum = 0.0;
	for (j = 0; j < 3; ++j)
	    sum += m.el[j][i] * v.el[j];
	prod.el[i] = sum;
    }
    return (prod);
}

double  mat3_sprod(Vec3 v, Mat3 m, Vec3 w)
{
    double  sum = 0.0;
    int     i, j;

    for (i = 0; i < 3; ++i)
	for (j = 0; j < 3; ++j)
	    sum += v.el[i] * m.el[i][j] * w.el[j];
    return (sum);
}

Mat3    mat3_tensor(Vec3 v, Vec3 w)
{
    Mat3    prod = {Mat3_id};
    int     i, j;

    for (i = 0; i < 3; ++i)
	for (j = 0; j < 3; ++j)
	    prod.el[i][j] = v.el[i] * w.el[j];
    return (prod);
}

Mat3    mat3_sum_tensor(Mat3 m, Vec3 v, Vec3 w)
{
    Mat3    sum = {Mat3_id};
    int     i, j;

    for (i = 0; i < 3; ++i)
	for (j = 0; j < 3; ++j)
	    sum.el[i][j] = m.el[i][j]+v.el[i] * w.el[j];
    return (sum);
}

Mat3    mat3_read(FILE * fp)
{
    Mat3    temp = {Mat3_id};
    int     i;

    for (i = 0; i < 3; ++i)
	(void) fscanf(fp, "%f %f %f",
		      &temp.el[i][0], &temp.el[i][1], &temp.el[i][2]);
    return (temp);
}

void    mat3_print(FILE * fp, Mat3 m)
{
    int     i;

    for (i = 0; i < 3; ++i)
	(void) fprintf(fp, "%f %f %f\n", m.el[i][0], m.el[i][1], m.el[i][2]);
}

void    mat3_pprint(FILE * fp, char *msg, Mat3 m)
{
    int     i, n;

    n = strlen(msg);
    (void) fprintf(fp, "%s", msg);
    (void) fprintf(fp, "|%15.6f%15.6f%15.6f|\n",
		   m.el[0][0], m.el[0][1], m.el[0][2]);
    for (i = 0; i < n; ++i)
	(void) fprintf(fp, " ");
    (void) fprintf(fp, "|%15.6f%15.6f%15.6f|\n",
		   m.el[1][0], m.el[1][1], m.el[1][2]);
    for (i = 0; i < n; ++i)
	(void) fprintf(fp, " ");
    (void) fprintf(fp, "|%15.6f%15.6f%15.6f|\n",
		   m.el[2][0], m.el[2][1], m.el[2][2]);
}

void    mat3_format(Mat3 m)
{
    int     i;

    for (i = 0; i < 3; ++i)
	format("%f %f %f\n", m.el[i][0], m.el[i][1], m.el[i][2]);
}

#if 0
/* ICCBUG static function: order never called */
static void order(x1, x2, x3)
double *x1, *x2, *x3;
{
    double  y1 = *x1;
    double  y2 = *x2;
    double  y3 = *x3;

    if (y1 <= y2)
    {
	if (y3 <= y1)
	{
	    *x1 = y3;
	    *x2 = y1;
	    *x3 = y2;
	} else if (y3 <= y2)
	{
	    *x1 = y1;
	    *x2 = y3;
	    *x3 = y2;
	} else
	{
	    *x1 = y1;
	    *x2 = y2;
	    *x3 = y3;
	}
    } else
    {
	if (y3 <= y2)
	{
	    *x1 = y3;
	    *x2 = y2;
	    *x3 = y1;
	} else if (y3 <= y1)
	{
	    *x1 = y2;
	    *x2 = y3;
	    *x3 = y1;
	} else
	{
	    *x1 = y2;
	    *x2 = y1;
	    *x3 = y3;
	}
    }
}

#endif

/************

Vec3            mat3_eigenvec(m, l)
Mat3            m = {Mat3_id};
double          l;
{
    Vec3            rx = {Vec3_id};
Vec3 ry = {Vec3_id};
Vec3 rz = {Vec3_id};
    Vec3            ex = {Vec3_id};
Vec3 ey = {Vec3_id};
Vec3 ez = {Vec3_id};
    double          nx, ny, nz, n;

    rx = vec3_unit(vec3_diff(mat3_rowx(m), vec3(l, 0.0, 0.0)));
    ry = vec3_unit(vec3_diff(mat3_rowy(m), vec3(0.0, l, 0.0)));
    rz = vec3_unit(vec3_diff(mat3_rowz(m), vec3(0.0, 0.0, l)));

    ex = vec3_cross(ry, rz);
    nx = vec3_mod(ex);
    ey = vec3_cross(rz, rx);
    ny = vec3_mod(ey);
    ez = vec3_cross(rx, ry);
    nz = vec3_mod(ez);
    n = MAX3(nx, ny, nz);
    if (n == nx)
	return (vec3_unit(ex));
    else if (n == ny)
	return (vec3_unit(ey));
    else
	return (vec3_unit(ez));
}

Bool            mat3_eigen(m, l1, l2, l3, e1, e2, e3)
Mat3            m = {Mat3_id};
double         *l1, *l2, *l3;
Vec3           *e1;
Vec3 *e2;
Vec3 *e3;
{
    double          mxx = mat3_xx(m);
    double          mxy = mat3_xy(m);
    double          mxz = mat3_xz(m);
    double          myx = mat3_yx(m);
    double          myy = mat3_yy(m);
    double          myz = mat3_yz(m);
    double          mzx = mat3_zx(m);
    double          mzy = mat3_zy(m);
    double          mzz = mat3_zz(m);
    double          a, b, c, d;
    Bool            rl;

    a = -1.0;
    b = mxx + myy + mzz;
    c = -(myy * mzz - myz * mzy) - (mxx * mzz - mxz * mzx) - (mxx * myy - mxy * myx);
    d = mat3_det(m);

    if (!cubic_roots(a, b, c, d, l1, l2, l3))
	return (false);

    order(l1, l2, l3);
    *e1 = mat3_eigenvec(m, *l1);
    *e2 = mat3_eigenvec(m, *l2);
    *e3 = mat3_eigenvec(m, *l3);
}

*************/

void    mat3_eigen(Mat3 m, double *eval, Vec3 * evec)
{
    int     i, j;
    Matrix *a = matrix_alloc(3, 3, matrix_full, double_v);
    Matrix *b = matrix_alloc(3, 3, matrix_full, double_v);
    Vector *v = vector_alloc(3, double_v);

    /** copy mat3 into matrix **/
    for (i = 0; i < 3; i++)
	for (j = 0; j < 3; j++)
	    matrix_putf(m.el[i][j], a, i, j);

    /** get vector of eigenvals and matrix of column eigenvecs **/
    (void) matrix_eigen_sym(a, v, b);

    /** copy into eval and evec **/
    for (i = 0; i < 3; i++)
	eval[i] = vector_getf(v, i);
    for (i = 0; i < 3; i++)
	for (j = 0; j < 3; j++)
	    evec[i].el[j] = matrix_getf(b, j, i);
    matrix_free(a);
    matrix_free(b);
    vector_free(v);
}
