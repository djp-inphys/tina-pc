/**@(#)Image point corresponding to projective point etc
**/

#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

/** image point corresponding to projective point **/
Vec2    vec2_of_proj2(Vec3 v)
{
    double  z = vec3_z(v);

    return (vec2(vec3_x(v) / z, vec3_y(v) / z));
}

/** (unit) projective point corresponding to image point **/
Vec3    proj2_of_vec2(Vec2 v)
{
    return (vec3(vec2_x(v), vec2_y(v), 1.0));
}

/** result of applying projective transform to projective point **/
Vec3    proj2_rectify(Mat3 m, Vec3 v)
{
    return (vec3_unit(mat3_vprod(m, v)));
}

/** result of applying projective transform to image point **/
Vec2    vec2_rectify(Mat3 m, Vec2 v)
{
    Vec3    w = {Vec3_id};

    w = mat3_vprod(m, vec3(vec2_x(v), vec2_y(v), 1.0));
    return (vec2(vec3_x(w) / vec3_z(w), vec3_y(w) / vec3_z(w)));
}

/** projective coordinates of projective line joining two points **/
Vec3    proj2_join(Vec3 p, Vec3 q)
{
    return (vec3_unitcross(p, q));
}

/** projective coordinates of intersection of two lines **/
Vec3    proj2_intersect(Vec3 p, Vec3 q)
{
    return (vec3_unitcross(p, q));
}

/** temporary (not so stable) **/
static Vec3 solve(Mat3 m, Vec3 y)
{
    return (mat3_vprod(mat3_inverse(m), y));
}

Mat3    proj2_to_frame(Vec3 p00, Vec3 p10, Vec3 p01, Vec3 p11)
{
    Mat3    m = {Mat3_id};
    Vec3    px = {Vec3_id};
    Vec3    py = {Vec3_id};
    Vec3    pz = {Vec3_id};
    Vec3    v = {Vec3_id};

    /** for stability **/
    p00 = vec3_unit(p00);
    p01 = vec3_unit(p01);
    p10 = vec3_unit(p10);
    p11 = vec3_unit(p11);

    /** images of (1 0 0), (0 1 0), and (0 0 1) **/
    px = proj2_intersect(proj2_join(p00, p10), proj2_join(p01, p11));
    py = proj2_intersect(proj2_join(p00, p01), proj2_join(p10, p11));
    pz = vec3_unit(p00);

    /** found m up to scale factor on each column **/
    m = mat3_of_cols(px, py, pz);

    /** now make (1 1 1) go to p11 **/
    v = vec3_unit(solve(m, p11));
    m = mat3_of_cols(vec3_times(vec3_x(v), px),
		     vec3_times(vec3_y(v), py),
		     vec3_times(vec3_z(v), pz));

    return (m);
}

Mat3    proj2_between(Vec2 p00, Vec2 p10, Vec2 p01, Vec2 p11, Vec2 q00, Vec2 q10, Vec2 q01, Vec2 q11)
{
    Mat3    mr = {Mat3_id};
    Mat3    ms = {Mat3_id};
    Mat3    mrs = {Mat3_id};
    Vec3    r00 = {Vec3_id};
    Vec3    r10 = {Vec3_id};
    Vec3    r01 = {Vec3_id};
    Vec3    r11 = {Vec3_id};
    Vec3    s00 = {Vec3_id};
    Vec3    s10 = {Vec3_id};
    Vec3    s01 = {Vec3_id};
    Vec3    s11 = {Vec3_id};

    r00 = proj2_of_vec2(p00);
    r10 = proj2_of_vec2(p10);
    r01 = proj2_of_vec2(p01);
    r11 = proj2_of_vec2(p11);

    s00 = proj2_of_vec2(q00);
    s10 = proj2_of_vec2(q10);
    s01 = proj2_of_vec2(q01);
    s11 = proj2_of_vec2(q11);

    mr = proj2_to_frame(r00, r10, r01, r11);
    ms = proj2_to_frame(s00, s10, s01, s11);
    mrs = mat3_prod(ms, mat3_inverse(mr));
    return (mrs);
}

Mat3    proj2_between_proj2(Vec3 p00, Vec3 p10, Vec3 p01, Vec3 p11, Vec3 q00, Vec3 q10, Vec3 q01, Vec3 q11)
{
    Mat3    mp = {Mat3_id};
    Mat3    mq = {Mat3_id};

    mp = proj2_to_frame(p00, p10, p01, p11);
    mq = proj2_to_frame(q00, q10, q01, q11);
    return (mat3_prod(mq, mat3_inverse(mp)));
}

/**
least squares replacement for geometrical method above
**/

/**
proj_between_x1 is unstable if zx compoment of
projection is small
use proj_between_ls below which does all three and gets best
**/

Mat3    proj_x1(int n, Vec3 * p, Vec3 * q, double *badness)
{
    Mat3    m = {Mat3_id};
    Matrix *a = matrix_alloc(2 * n, 8, matrix_full, double_v);
    Vector *b = vector_alloc(2 * n, double_v);
    Vector *c;
    int     i;

    for (i = 0; i < n; i++)
    {
	double  xp = vec3_x(p[i]), xq = vec3_x(q[i]);
	double  yp = vec3_y(p[i]), yq = vec3_y(q[i]);
	double  zp = vec3_z(p[i]), zq = vec3_z(q[i]);

	matrix_putf(zq * yp, a, 2 * i, 0);
	matrix_putf(zq * zp, a, 2 * i, 1);
	matrix_putf(zq * xp, a, 2 * i, 2);
	matrix_putf(-xq * yp, a, 2 * i, 6);
	matrix_putf(-xq * zp, a, 2 * i, 7);
	vector_putf(xq * xp, b, 2 * i);

	matrix_putf(zq * yp, a, 2 * i + 1, 3);
	matrix_putf(zq * zp, a, 2 * i + 1, 4);
	matrix_putf(zq * xp, a, 2 * i + 1, 5);
	matrix_putf(-yq * yp, a, 2 * i + 1, 6);
	matrix_putf(-yq * zp, a, 2 * i + 1, 7);
	vector_putf(yq * xp, b, 2 * i + 1);
    }

    if ((c = matrix_cholesky_least_square(a, b)) == NULL)
    {
	*badness = 1e10;
	return (mat3_zero());
    }
    mat3_xy(m) = vector_getf(c, 0);
    mat3_xz(m) = vector_getf(c, 1);
    mat3_xx(m) = vector_getf(c, 2);
    mat3_yy(m) = vector_getf(c, 3);
    mat3_yz(m) = vector_getf(c, 4);
    mat3_yx(m) = vector_getf(c, 5);
    mat3_zy(m) = vector_getf(c, 6);
    mat3_zz(m) = vector_getf(c, 7);
    mat3_zx(m) = 1.0;

    matrix_free(a);
    vector_free(b);
    vector_free(c);

    *badness = MAX(fabs(mat3_zy(m)), fabs(mat3_zz(m)));
    return (m);
}

Mat3    proj_y1(int n, Vec3 * p, Vec3 * q, double *badness)
{
    Mat3    m = {Mat3_id};
    Matrix *a = matrix_alloc(2 * n, 8, matrix_full, double_v);
    Vector *b = vector_alloc(2 * n, double_v);
    Vector *c;
    int     i;

    for (i = 0; i < n; i++)
    {
	double  xp = vec3_x(p[i]), xq = vec3_x(q[i]);
	double  yp = vec3_y(p[i]), yq = vec3_y(q[i]);
	double  zp = vec3_z(p[i]), zq = vec3_z(q[i]);

	matrix_putf(zq * zp, a, 2 * i, 0);
	matrix_putf(zq * xp, a, 2 * i, 1);
	matrix_putf(zq * yp, a, 2 * i, 2);
	matrix_putf(-xq * zp, a, 2 * i, 6);
	matrix_putf(-xq * xp, a, 2 * i, 7);
	vector_putf(xq * yp, b, 2 * i);

	matrix_putf(zq * zp, a, 2 * i + 1, 3);
	matrix_putf(zq * xp, a, 2 * i + 1, 4);
	matrix_putf(zq * yp, a, 2 * i + 1, 5);
	matrix_putf(-yq * zp, a, 2 * i + 1, 6);
	matrix_putf(-yq * xp, a, 2 * i + 1, 7);
	vector_putf(yq * yp, b, 2 * i + 1);
    }

    if ((c = matrix_cholesky_least_square(a, b)) == NULL)
    {
	*badness = 1e10;
	return (mat3_zero());
    }
    mat3_xz(m) = vector_getf(c, 0);
    mat3_xx(m) = vector_getf(c, 1);
    mat3_xy(m) = vector_getf(c, 2);
    mat3_yz(m) = vector_getf(c, 3);
    mat3_yx(m) = vector_getf(c, 4);
    mat3_yy(m) = vector_getf(c, 5);
    mat3_zz(m) = vector_getf(c, 6);
    mat3_zx(m) = vector_getf(c, 7);
    mat3_zy(m) = 1.0;

    matrix_free(a);
    vector_free(b);
    vector_free(c);

    *badness = MAX(fabs(mat3_zz(m)), fabs(mat3_zx(m)));
    return (m);
}

Mat3    proj_z1(int n, Vec3 * p, Vec3 * q, double *badness)
{
    Mat3    m = {Mat3_id};
    Matrix *a = matrix_alloc(2 * n, 8, matrix_full, double_v);
    Vector *b = vector_alloc(2 * n, double_v);
    Vector *c;
    int     i;

    for (i = 0; i < n; i++)
    {
	double  xp = vec3_x(p[i]), xq = vec3_x(q[i]);
	double  yp = vec3_y(p[i]), yq = vec3_y(q[i]);
	double  zp = vec3_z(p[i]), zq = vec3_z(q[i]);

	matrix_putf(zq * xp, a, 2 * i, 0);
	matrix_putf(zq * yp, a, 2 * i, 1);
	matrix_putf(zq * zp, a, 2 * i, 2);
	matrix_putf(-xq * xp, a, 2 * i, 6);
	matrix_putf(-xq * yp, a, 2 * i, 7);
	vector_putf(xq * zp, b, 2 * i);

	matrix_putf(zq * xp, a, 2 * i + 1, 3);
	matrix_putf(zq * yp, a, 2 * i + 1, 4);
	matrix_putf(zq * zp, a, 2 * i + 1, 5);
	matrix_putf(-yq * xp, a, 2 * i + 1, 6);
	matrix_putf(-yq * yp, a, 2 * i + 1, 7);
	vector_putf(yq * zp, b, 2 * i + 1);
    }

    if ((c = matrix_cholesky_least_square(a, b)) == NULL)
    {
	*badness = 1e10;
	return (mat3_zero());
    }
    mat3_xx(m) = vector_getf(c, 0);
    mat3_xy(m) = vector_getf(c, 1);
    mat3_xz(m) = vector_getf(c, 2);
    mat3_yx(m) = vector_getf(c, 3);
    mat3_yy(m) = vector_getf(c, 4);
    mat3_yz(m) = vector_getf(c, 5);
    mat3_zx(m) = vector_getf(c, 6);
    mat3_zy(m) = vector_getf(c, 7);
    mat3_zz(m) = 1.0;

    matrix_free(a);
    vector_free(b);
    vector_free(c);

    *badness = MAX(fabs(mat3_zx(m)), fabs(mat3_zy(m)));
    return (m);
}

Mat3    proj_between_ls(int n, Vec3 * p, Vec3 * q)
{
    Mat3    mx = {Mat3_id};
    Mat3    my = {Mat3_id};
    Mat3    mz = {Mat3_id};
    double  bx, by, bz, b;

    mx = proj_x1(n, p, q, &bx);
    my = proj_y1(n, p, q, &by);
    mz = proj_z1(n, p, q, &bz);

    b = MIN3(bx, by, bz);
    if (b == bz)
	return (mz);
    if (b == by)
	return (my);
    return (mx);
}
