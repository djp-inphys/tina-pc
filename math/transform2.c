/**@(#)Transforms
 * @(#)Transform2 is {int type; struct mat2 R; struct vec2 t;}
**/

#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

void   *trans2_alloc(void)
{
    Transform2 *transf = ts_ralloc(Transform2);

    transf->R = mat2_unit();
    transf->t = vec2_zero();
    return ((void *) transf);
}

void    trans2_free(void *transf)
{
    rfree((void *) transf);
}

/**
2D rotation through theta about point p

(leaves p unchanged)
**/

Transform2 trans2_rot_about(double theta, Vec2 p)
{
    Transform2 transf = {Transform2_id};

    transf.R = rot2(theta);
    transf.t = vec2_diff(p, mat2_vprod(transf.R, p));
    return (transf);
}

Transform2 trans2_prod(Transform2 transf2, Transform2 transf1)
{
    Transform2 prod = {Transform2_id};

    prod.R = mat2_prod(transf2.R, transf1.R);
    prod.t = vec2_sum(transf2.t, mat2_vprod(transf2.R, transf1.t));
    return (prod);
}

Transform2 trans2_inverse(Transform2 transf)
{
    Transform2 inv = {Transform2_id};

    inv.R = mat2_transpose(transf.R);
    inv.t = mat2_vprod(inv.R, vec2_minus(transf.t));
    return (inv);
}

Vec2    trans2_pos(Transform2 transf, Vec2 v)
{
    return (vec2_sum(mat2_vprod(transf.R, v), transf.t));
}

Vec2    trans2_vec(Transform2 transf, Vec2 v)
{
    return (mat2_vprod(transf.R, v));
}

void    trans2_print(FILE * fp, Transform2 trans)
{
    mat2_print(fp, trans.R);
    vec2_print(fp, trans.t);
}

void    trans2_format(Transform2 trans)
{
    mat2_format(trans.R);
    format("\n");
    vec2_format(trans.t);
}
