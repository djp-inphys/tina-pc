/**@(#)Transforms
 * @(#)Transform3 is {int type; struct mat3 R; struct vec3 t;}
**/

#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

Transform3 trans3(Mat3 R, Vec3 t)
{
    Transform3 transf = {Transform3_id};

    transf.R = R;
    transf.t = t;
    return (transf);
}

Transform3 *trans3_alloc(void)
{
    Transform3 *transf = ts_ralloc(Transform3);

    transf->R = mat3_unit();
    transf->t = vec3_zero();
    return (transf);
}

Transform3 *trans3_make(Mat3 R, Vec3 t)
{
    Transform3 *transf = ts_ralloc(Transform3);

    transf->R = R;
    transf->t = t;
    return (transf);
}

Transform3 *trans3_copy(Transform3 * transf)
{
    if (transf == NULL)
	return (NULL);

    return (trans3_make(transf->R, transf->t));
}

void    trans3_free(void *transf)
{
    rfree((void *) transf);
}

Transform3 trans3_unit(void)
{
    Transform3 transf = {Transform3_id};

    transf.R = mat3_unit();
    transf.t = vec3_zero();
    return (transf);
}

Transform3 trans3_prod(Transform3 transf2, Transform3 transf1)
{
    Transform3 prod = {Transform3_id};

    prod.R = mat3_prod(transf2.R, transf1.R);
    prod.t = vec3_sum(transf2.t, mat3_vprod(transf2.R, transf1.t));
    return (prod);
}

Transform3 trans3_inverse(Transform3 transf)
{
    Transform3 inv = {Transform3_id};

    inv.R = mat3_transpose(transf.R);
    inv.t = mat3_vprod(inv.R, vec3_minus(transf.t));
    return (inv);
}

Vec3    trans3_pos(Transform3 transf, Vec3 v)
{
    return (vec3_sum(mat3_vprod(transf.R, v), transf.t));
}

Vec3    trans3_inverse_pos(Transform3 transf, Vec3 v)
{
    return (mat3_transpose_vprod(transf.R, vec3_diff(v, transf.t)));
}

Vec3    trans3_vec(Transform3 transf, Vec3 v)
{
    return (mat3_vprod(transf.R, v));
}

Vec3    trans3_inverse_vec(Transform3 transf, Vec3 v)
{
    return (mat3_transpose_vprod(transf.R, v));
}

void    trans3_get_frame1in2(Transform3 transf, Vec3 * p, Vec3 * ex, Vec3 * ey, Vec3 * ez)
{
    *p = transf.t;
    *ex = mat3_colx(transf.R);
    *ey = mat3_coly(transf.R);
    *ez = mat3_colz(transf.R);
}

void    trans3_get_frame2in1(Transform3 transf, Vec3 * p, Vec3 * ex, Vec3 * ey, Vec3 * ez)
{
    *p = mat3_transpose_vprod(transf.R, vec3_minus(transf.t));
    *ex = mat3_rowx(transf.R);
    *ey = mat3_rowy(transf.R);
    *ez = mat3_rowz(transf.R);
}

Vec3    trans3_get_origin2in1(Transform3 transf)
{
    return (mat3_transpose_vprod(transf.R, vec3_minus(transf.t)));
}

/** compute transform from given frame to current frame **/

Transform3 trans3_from_frame(Vec3 p, Vec3 ex, Vec3 ey, Vec3 ez)
{
    Transform3 transf = {Transform3_id};

    transf.t = p;
    transf.R = mat3_of_cols(ex, ey, ez);
    return (transf);
}

/** compute transform to given frame from current frame **/

Transform3 trans3_to_frame(Vec3 p, Vec3 ex, Vec3 ey, Vec3 ez)
{
    return (trans3_inverse(trans3_from_frame(p, ex, ey, ez)));
}

Transform3 trans3_from_frame_to_frame(Vec3 p1, Vec3 ex1, Vec3 ey1, Vec3 ez1, Vec3 p2, Vec3 ex2, Vec3 ey2, Vec3 ez2)
{
    Transform3 t1 = {Transform3_id};
    Transform3 t2 = {Transform3_id};

    t1 = trans3_from_frame(p1, ex1, ey1, ez1);
    t2 = trans3_to_frame(p2, ex2, ey2, ez2);
    return (trans3_prod(t1, t2));
}

void    trans3_print(FILE * fp, Transform3 trans)
{
    mat3_print(fp, trans.R);
    vec3_print(fp, trans.t);
}

void    trans3_format(Transform3 trans)
{
    mat3_format(trans.R);
    format("\n");
    vec3_format(trans.t);
}

/**
3D rotation r about point p

(leaves p unchanged)
**/

Transform3 trans3_rot_about(Mat3 r, Vec3 p)
{
    Transform3 transf = {Transform3_id};

    transf.R = r;
    transf.t = vec3_diff(p, mat3_vprod(transf.R, p));
    return (transf);
}
