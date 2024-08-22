/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>
#ifdef _PCC
#include <memory.h>
#endif

Conic  *conic_alloc(unsigned int type)
{
    Conic  *conic = ts_ralloc(Conic);

    conic->type = type;
    conic->label = new_label();
    return (conic);
}

Conic  *conic_make(int type, Vec2 center, double theta, double alpha, double beta, double t1, double t2, int branch)
{
    Conic  *conic = ts_ralloc(Conic);
    Mat3    rot = {Mat3_id};
    Mat3    con = {Mat3_id};
    double  cx, cy, a, b, c, s;

    conic->type = type;
    conic->label = new_label();
    conic->center = center;
    conic->theta = theta;
    conic->alpha = alpha;
    conic->beta = beta;
    conic->t1 = t1;
    conic->t2 = t2;
    conic->branch = branch;

    cx = vec2_x(center);
    cy = vec2_y(center);
    a = 1.0 / (alpha * alpha);
    b = 1.0 / (beta * beta);
    if (type == HYPERBOLA)
	b = -b;

    /** conic in own frame **/
    con = mat3(a, 0.0, 0.0,
	       0.0, b, 0.0,
	       0.0, 0.0, -1.0);

    /** homogeneous transform to image frame **/
    c = cos(theta);
    s = sin(theta);
    rot = mat3(c, s, cx,
	       s, -c, cy,
	       0.0, 0.0, 1.0);

    /** homogeneous transform from image frame **/
    rot = mat3_inverse(rot);

    /** conic in image frame **/
    con = mat3_prod(con, rot);
    con = mat3_prod(mat3_transpose(rot), con);

    conic->a = mat3_xx(con);
    conic->b = mat3_xy(con);
    conic->c = mat3_yy(con);
    conic->d = mat3_xz(con);
    conic->e = mat3_yz(con);
    conic->f = mat3_zz(con);

    return (conic);
}

Conic  *conic_copy(Conic * conic)
{
    Conic  *copy;
    List   *proplist_copy();

    if (conic == NULL)
	return (NULL);

    copy = ts_ralloc(Conic);
    (void) memcpy((char *) copy, (char *) conic, sizeof(Conic));
    copy->props = proplist_copy(conic->props);
    return (copy);
}

/* ARGSUSED quieten lint */
void   *conic_prop_get(Conic * conic, int type, int prop)
{
    if (conic == NULL)
	return (NULL);

    return (prop_get(conic->props, prop));
}


void    conic_free(Conic * conic)
{
    if (conic == NULL)
	return;

    proplist_freelist(conic->props);
    rfree((void *) conic);
}
