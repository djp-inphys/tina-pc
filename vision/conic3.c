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

Conic3 *conic3_alloc(unsigned int type)
{
    Conic3 *con3 = ts_ralloc(Conic3);

    con3->type = type;
    return (con3);
}

Conic3 *conic3_copy(Conic3 * con3)
{
    Conic3 *copy;

    if (con3 == NULL)
	return (NULL);

    copy = ts_ralloc(Conic3);
    (void) memcpy((char *) copy, (char *) con3, sizeof(Conic3));
    copy->ts_id = Conic3_id;	/* ANITISE */
    copy->conic = conic_copy(con3->conic);
    return (copy);
}

void    conic3_free(Conic3 * con3)
{
    if (con3 == NULL)
	return;
    conic_free(con3->conic);
    rfree((void *) con3);
}

Conic3 *conic3_make(Conic * con2, Vec3 o, Vec3 ex, Vec3 ey, Vec3 ez)
{
    Conic3 *con3;

    if (con2 == NULL)
	return (NULL);

    con3 = conic3_alloc(con2->type);
    con3->conic = con2;
    con3->origin = o;
    con3->ex = ex;
    con3->ey = ey;
    con3->ez = ez;
    return (con3);
}

void    conic3_transform(Conic3 * conic, Transform3 trans)
{
    if (conic == NULL)
	return;

    conic->origin = trans3_pos(trans, conic->origin);
    conic->ex = trans3_vec(trans, conic->ex);
    conic->ey = trans3_vec(trans, conic->ey);
    conic->ez = trans3_vec(trans, conic->ez);
}

/* find point in 3 space correspondint to param */

Vec3    conic3_point(Conic3 * con3, double t)
{
    Vec2    p2 = {Vec2_id};
    Vec3    p3 = {Vec3_id};

    p2 = conic_point(con3->conic, t);	/* point in plane */
    p3 = vec3_sum(con3->origin, vec3_times(vec2_x(p2), con3->ex));
    return (vec3_sum(p3, vec3_times(vec2_y(p2), con3->ey)));
}

/* find approx parameter of point in 3 space  */

double  conic3_param(Conic3 * con3, Vec3 p3)
{
    Vec2    p2 = {Vec2_id};	/* point in 2D conic coords */

    p3 = vec3_diff(p3, con3->origin);
    p2 = vec2(vec3_dot(p3, con3->ex), vec3_dot(p3, con3->ey));

    return (conic_param(con3->conic, p2));
}

/* Find the parameter offset of c2 with respect to c1.
 * 
 * Find the vector from parameter point zero on c1 to its origin. Add this
 * to the origin on c2 and find the approximate parameter value. */
double  conic3_parameter_offset(Conic3 * c1, Conic3 * c2)
{
    Vec3    p = {Vec3_id};

    p = vec3_diff(conic3_point(c1, 0.0), c1->origin);
    return (conic3_param(c2, vec3_sum(c2->origin, p)));
}

Bool    conic3_overlap(Conic3 * c1, Conic3 * c2, float *t1, float *t2)

/* overlap in coords of c1 */
{
    double  t11, t12, t21, t22;	/* all params in coords of c1 */
    Vec3    p = {Vec3_id};

    t11 = c1->conic->t1;
    t12 = c1->conic->t2;
    p = conic3_point(c2, c2->conic->t1);
    t21 = conic3_param(c1, p);
    t22 = t21 + c2->conic->t2 - c2->conic->t1;

    if (t12 < t21)		/* possible non overlap */
    {
	if (t22 < TWOPI || t11 + TWOPI > t22)
	    return (false);
	t11 += TWOPI;
	t12 += TWOPI;
    } else if (t11 > t22)	/* possible non overlap */
    {
	if (t12 < TWOPI || t21 + TWOPI > t12)
	    return (false);
	t21 += TWOPI;
	t22 += TWOPI;
    }
    *t1 = (float)MAX(t11, t21);
    *t2 = (float)MIN(t12, t22);

    if (*t1 > TWOPI)
    {
	*t1 -= (float)TWOPI;
	*t2 -= (float)TWOPI;
    }
    return (true);
}

Bool    conic3_coincident(Conic3 * c1, Conic3 * c2, double doterror, double poserror)

/* BUG */

{
    float   t1, t2, t, i;	/* overlap in coords of c1 */
    Vec3    p1 = {Vec3_id};
    Vec3    p2 = {Vec3_id};

    if (c1 == NULL || c2 == NULL)
	return (false);

    if (vec3_dot(c1->ez, c2->ez) < 0.0)	/* oposite sign */
	return (false);

    /* if (vec3_dist(c1->origin, c2->origin) > poserror) return
     * (false); */

    if (conic3_overlap(c1, c2, &t1, &t2) == false)
	return (false);

    for (i = (float)0.25; i < 0.8; i += (float)0.25)/* i = {0.27, 0.5, 0.75} */
    {
	t = (t1 + t2) * i;
	p1 = conic3_point(c1, t);
	t = (float)conic3_param(c2, p1);
	p2 = conic3_point(c2, t);
	if (vec3_dist(p1, p2) > poserror)
	    return (false);
    }

    return (true);
}

Bool    conic3_within_error(Conic3 * c1, Conic3 * c2)
{
    Iso_error *iso1;
    Iso_error *iso2;

    if (c1 == NULL || c2 == NULL)
	return (false);

    iso1 = (Iso_error *) prop_get(c1->conic->props, ISO_ERROR);
    iso2 = (Iso_error *) prop_get(c2->conic->props, ISO_ERROR);

    if (iso1 == NULL || iso2 == NULL)
	return (false);

    return (conic3_coincident(c1, c2, iso1->dot * iso2->dot, iso1->pos + iso2->pos));
}

void    conic3_negate(Conic3 * con3)
{
    double  t1, t2;
    Conic  *conic;

    if (con3 == NULL)
	return;

    conic = con3->conic;
    con3->ez = vec3_minus(con3->ez);
    con3->ey = vec3_minus(con3->ey);
    conic->theta = -conic->theta;

    t1 = TWOPI - conic->t2;
    if (t1 < 0)
	t1 += TWOPI;

    t2 = t1 + conic->t2 - conic->t1;

    conic->t1 = t1;
    conic->t2 = t2;
}

Conic3 *conic3_negative(Conic3 * con3)
{
    con3 = conic3_copy(con3);
    conic3_negate(con3);
    return (con3);
}

Conic3 *conic_par_proj_to_plane(Conic * conic, Plane * plane)
{
    Vec3    p = {Vec3_id};
    Vec3    n = {Vec3_id};
    Vec3    c = {Vec3_id};
    Vec3    ex = {Vec3_id};
    Vec3    ey = {Vec3_id};
    Vec2    p2 = {Vec2_id};
    Vec2    p_array[5] = {{Vec2_id}, {Vec2_id}, {Vec2_id}, {Vec2_id}, {Vec2_id}};
    Vec3    p3 = {Vec3_id};
    Vec3    v = {Vec3_id};
    Vec3    o = {Vec3_id};
    double  t, t1, t2, step = TWOPI / 6;
    Conic  *conic_new;
    int     i;

    if (conic == NULL || plane == NULL)
	return (NULL);

    p = plane->p;
    n = plane->n;

    t1 = conic->t1;
    t2 = conic->t2;

    par_proj_ray(conic->center, &o, &v);
    c = vec3_inter_line_plane(o, v, p, n);
    p2 = vec2_sum(conic->center, vec2(cos(conic->theta), sin(conic->theta)));
    par_proj_ray(p2, &o, &v);
    p3 = vec3_inter_line_plane(o, v, p, n);
    ex = vec3_unit(vec3_diff(p3, c));
    ey = vec3_cross(n, ex);

    for (i = 0, t = 0; i < 5; ++i, t += step)
    {
	p2 = conic_point(conic, t);
	par_proj_ray(p2, &o, &v);
	p3 = vec3_inter_line_plane(o, v, p, n);
	p3 = vec3_diff(p3, c);
	vec2_x(p2) = (float)vec3_dot(p3, ex);
	vec2_y(p2) = (float)vec3_dot(p3, ey);
	p_array[i] = p2;
    }

    conic_new = conic_5pt(p_array[0], p_array[1], p_array[2], p_array[3], p_array[4]);

    step = (t2 - t1) / 2.0;

    for (i = 0, t = t1; i < 3; ++i, t += step)
    {
	p2 = conic_point(conic, t);
	par_proj_ray(p2, &o, &v);
	p3 = vec3_inter_line_plane(o, v, p, n);
	p3 = vec3_diff(p3, c);
	vec2_x(p2) = (float)vec3_dot(p3, ex);
	vec2_y(p2) = (float)vec3_dot(p3, ey);
	p_array[i] = p2;
    }

    conic_set_ends(conic_new, p_array[0], p_array[2], p_array[1]);
    return (conic3_make(conic_new, c, ex, ey, n));
}

void    conic3_shift_origin_to_center(Conic3 * con3)
{
    Conic  *conic;
    Vec3    shift = {Vec3_id};

    if (con3 == NULL || con3->conic == NULL)
	return;

    conic = con3->conic;
    shift = vec3_times(vec2_x(conic->center), con3->ex);
    shift = vec3_sum(shift, vec3_times(vec2_y(conic->center), con3->ey));
    con3->origin = vec3_sum(con3->origin, shift);
    conic->center = vec2_zero();
}

Conic3 *conic3_from_conic2(Conic * conic, double fit_thres)
{
    Tstring *curve, *str;
    Conic   copy = {Conic_id};
    Conic3 *con3;
    Plane  *plane;
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    Vec2    pm = {Vec2_id};

    str = (Tstring *) prop_get(conic->props, STRING);
    if (str == NULL)
	return (NULL);
    curve = conic2_string(conic);
    plane = plane_curve_ls(curve, str, fit_thres, &p1, &p2, &pm);
    str_rm(curve, rfree);
    copy = *conic;
    conic_set_ends(&copy, p1, p2, pm);
    con3 = conic_par_proj_to_plane(&copy, plane);
    conic3_shift_origin_to_center(con3);
    return (con3);
}

void    conic3_format(Conic3 * conic)
{
    Vec3    p = {Vec3_id};

    if (conic == NULL)
	return;

    format("conic3   :\n");
    p = conic->origin;
    format("origin   : %15.6f %15.6f %15.6f\n", vec3_x(p), vec3_y(p), vec3_z(p));
    p = conic->ex;
    format("x axis   : %15.6f %15.6f %15.6f\n", vec3_x(p), vec3_y(p), vec3_z(p));
    p = conic->ey;
    format("y axis   : %15.6f %15.6f %15.6f\n", vec3_x(p), vec3_y(p), vec3_z(p));
    p = conic->ez;
    format("z axis   : %15.6f %15.6f %15.6f\n", vec3_x(p), vec3_y(p), vec3_z(p));
    conic_format(conic->conic);
    p = conic3_point(conic, conic->conic->t1);
    format("p1       : %15.6f %15.6f %15.6f\n", vec3_x(p), vec3_y(p), vec3_z(p));
    p = conic3_point(conic, conic->conic->t2);
    format("p2       : %15.6f %15.6f %15.6f\n", vec3_x(p), vec3_y(p), vec3_z(p));
    format("\n");
}
