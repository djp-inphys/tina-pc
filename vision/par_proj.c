/**@(#)
**/
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* module to project from parallel camera disparity coords to word
 * coords and visa versa
 * 
 * f is focal length of parallel camera in pixel units I is inter-ocular
 * separation in units of the word coord */

static float f = (float)1.0, I = (float)1.0;

void    set_par_proj(double fnew, double Inew)
{
    f = (float)fnew;
    I = (float)Inew;
}

void    par_proj_set(double fnew, double Inew)
{
    f = (float)fnew;
    I = (float)Inew;
}

void    par_proj_get(float *fp, float *Ip)
{
    *fp = f;
    *Ip = I;
}

void    par_proj_ray(Vec2 u, Vec3 * p, Vec3 * v)
{
    *p = vec3_zero();		/* the origin of parallel coords */

    *v = vec3_of_vec2(u);
    vec3_z(*v) = f;
    *v = vec3_unit(*v);
}

Vec3    vec3_par_proj_3d(Vec3 p)
{
    float   proj = -I / vec3_z(p);

    vec3_z(p) = f;
    return (vec3_times(proj, p));
}

Vec3    vec3_par_proj_disp(Vec3 p)
{
    float   proj = f / vec3_z(p);

    vec3_z(p) = -I;
    return (vec3_times(proj, p));
}

void    vec3_pp3d_inplace(Vec3 * p)
{
    float   proj;

    if (p == NULL)
	return;

    proj = -I / vec3_z(*p);
    vec3_z(*p) = f;
    *p = vec3_times(proj, *p);
}

void    vec3_ppdisp_inplace(Vec3 * p)
{
    float   proj;

    if (p == NULL)
	return;

    proj = f / vec3_z(*p);
    vec3_z(*p) = -I;
    *p = vec3_times(proj, *p);
}

void    line3_par_proj_3d(Line3 * line)
{
    if (line == NULL)
	return;

    line->p1 = vec3_par_proj_3d(line->p1);
    line->p2 = vec3_par_proj_3d(line->p2);
    line3_remake(line, THREEDIM);
}

void    line3_par_proj_disp(Line3 * line)
{
    if (line == NULL)
	return;

    line->p1 = vec3_par_proj_disp(line->p1);
    line->p2 = vec3_par_proj_disp(line->p2);
    line3_remake((Line3 *) line, DISPARITY);
}

void    plane_par_proj_3d(Plane * plane)
{
    float   D;			/* PX + QY + RZ = D disparity coords */
    float   d;			/* px + qy + rz = d world coords */
    Vec3    n = {Vec3_id};
    float   mag;

    if (plane == NULL)
	return;

    n = plane->n;

    /* first convert plane to algerbraic form n.x = n.p */
    D = (float)vec3_dot(plane->p, plane->n);	/* |closest approach to origin| */

    /* derive 3D algebra from disp algebra Px + Qy - Dz/f = RI */
    d = vec3_z(n) * I;
    vec3_z(n) = -D / f;

    mag = (float)vec3_mod(n);
    plane->n = vec3_times(1 / mag, n);	/* make unit vector */
    plane->p = vec3_times(d / mag, plane->n);	/* point closest to
						 * origin */
    plane->type = THREEDIM;
}
