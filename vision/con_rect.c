/**@(#)
**/
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/**
projective transformation of conic
**/

Conic  *conic_rectify(Conic * conic, Mat3 rect)
{
    Mat3    m = {Mat3_id};
    Mat3    irect = {Mat3_id};
    Vec2    p1 = {Vec2_id};
    Vec2    pmid = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    Conic  *new = conic_alloc((int) NULL);

    irect = mat3_inverse(rect);

    /** transform homogeneous matrix for conic with irect **/
    m = mat3(conic->a, conic->b, conic->d,
	     conic->b, conic->c, conic->e,
	     conic->d, conic->e, conic->f);
    m = mat3_prod(m, irect);
    m = mat3_prod(mat3_transpose(irect), m);
    new->a = mat3_xx(m);
    new->b = mat3_xy(m);
    new->c = mat3_yy(m);
    new->d = mat3_xz(m);
    new->e = mat3_yz(m);
    new->f = mat3_zz(m);

    /** transform 3 points on conic **/
    p1 = conic_point(conic, conic->t1);
    p1 = vec2_rectify(rect, p1);
    pmid = conic_point(conic, 0.5 * (conic->t1 + conic->t2));
    pmid = vec2_rectify(rect, pmid);
    p2 = conic_point(conic, conic->t2);
    p2 = vec2_rectify(rect, p2);

    /** make new conic consistent **/
    conic_setup(new);
    conic_set_ends(new, p1, p2, pmid);

    return (new);
}

Conic  *conic_proj(Conic * conic, Mat3 proj)
{
    Mat3    m = {Mat3_id};
    Mat3    iproj = {Mat3_id};
    Vec2    p1 = {Vec2_id};
    Vec2    pmid = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    Conic  *new = conic_alloc((int) NULL);

    iproj = mat3_inverse(proj);

    /** transform homogeneous matrix for conic with iproj **/
    m = mat3(conic->a, conic->b, conic->d,
	     conic->b, conic->c, conic->e,
	     conic->d, conic->e, conic->f);
    m = mat3_prod(m, iproj);
    m = mat3_prod(mat3_transpose(iproj), m);
    new->a = mat3_xx(m);
    new->b = mat3_xy(m);
    new->c = mat3_yy(m);
    new->d = mat3_xz(m);
    new->e = mat3_yz(m);
    new->f = mat3_zz(m);

    /** transform 3 points on conic **/
    p1 = conic_point(conic, conic->t1);
    p1 = vec2_rectify(proj, p1);
    pmid = conic_point(conic, 0.5 * (conic->t1 + conic->t2));
    pmid = vec2_rectify(proj, pmid);
    p2 = conic_point(conic, conic->t2);
    p2 = vec2_rectify(proj, p2);

    /** make new conic consistent **/
    conic_setup(new);
    conic_set_ends(new, p1, p2, pmid);

    return (new);
}
