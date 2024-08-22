/**@(#)
**/
/* pwrte.c
 * 
 * code to build and manipulate pair wise relation tables for representing
 * object constraints in matching
 * 
 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

static double sep_error_ratio = 0.05;	/* 5% of separation */

Pwrte  *pwrte_alloc(Ts_id ts_id)
{
    Pwrte  *p = ralloc(sizeof(Pwrte));

    *(Ts_id *) p = ts_id;

    return (p);
}

void    pwrte_free(Pwrte * p)
{
    rfree((void *) p);
}

void    pwtre_table_free(Matrix * tbl)
{
    int     i, j;
    int     m, n;

    if (tbl == NULL)
	return;

    m = tbl->m;
    n = tbl->n;
    for (i = 0; i < m; ++i)
	for (j = 0; j < n; ++j)
	    pwrte_free((Pwrte *) tbl->el.ptr_v[i][j]);
    matrix_free(tbl);
}

Pwrte  *pwrte_point_to_point_make(Point3 * p1, Point3 * p2)
{
    Pwrte  *pwrte;
    Pwrte_point_to_point *p;
    Iso_error *iso1;
    Iso_error *iso2;
    double  seperror, poserror, dist;

    if (p1 == NULL || p2 == NULL)
	return (NULL);

    pwrte = pwrte_alloc(Pwrte_point_to_point_id);
    p = &(pwrte->p_to_p);
    p->type1 = POINT3;
    p->type2 = POINT3;
    p->p1 = (void *) p1;
    p->p2 = (void *) p2;

    dist = vec3_mod(vec3_diff(p2->p, p1->p));

    iso1 = (Iso_error *) prop_get(p1->props, ISO_ERROR);
    iso2 = (Iso_error *) prop_get(p2->props, ISO_ERROR);
    poserror = iso1->pos + iso2->pos;
    seperror = sep_error_ratio * dist;

    if (seperror > poserror)
	poserror = seperror;

    p->lowdist = (float)((dist < poserror) ? 0 : dist - poserror);
    p->hidist = (float)(dist + poserror);
    return (pwrte);
}

Pwrte  *pwrte_point_to_line_make(void *p1, int type1, void *p2, int type2)
{
    Pwrte  *pwrte;
    Pwrte_point_to_vec *p;
    Point3 *point;
    Line3  *line;
    Iso_error *iso1;
    Iso_error *iso2;
    double  poserror, rot_lever, mind, d1, d2;
    Vec3    closest = {Vec3_id};

    if (p1 == NULL || p2 == NULL)
	return (NULL);

    pwrte = pwrte_alloc(Pwrte_point_to_vec_id);
    p = &(pwrte->p_to_v);
    p->type1 = type1;
    p->type2 = type2;
    p->p1 = p1;
    p->p2 = p2;

    line = (type1 == LINE3) ? (Line3 *) p1 : (Line3 *) p2;
    point = (type1 == POINT3) ? (Point3 *) p1 : (Point3 *) p2;

    iso1 = (Iso_error *) prop_get(point->props, ISO_ERROR);
    iso2 = (Iso_error *) prop_get(line->props, ISO_ERROR);

    poserror = iso1->pos + iso2->pos;

    closest = vec3_proj_on_line(point->p, line->p, line->v);

    mind = vec3_mod(vec3_diff(point->p, closest));
    d1 = vec3_dot(line->v, vec3_diff(closest, line->p1));/* signed value */
    d2 = vec3_dot(line->v, vec3_diff(closest, line->p2));

    ORDER(double, d1, d2);
    p->lowvecd = (float)(d1 - poserror - mind * iso2->rot);/* small angle sine
							    * assump */
    p->hivecd = (float)(d2 + poserror + mind * iso2->rot);

    rot_lever = (BETWEEN(0, d1, d2)) ? 0 : fmin(fabs(d1), fabs(d2));
    poserror += atan(iso2->rot) * rot_lever;

    p->lowmind = (float)((mind < poserror) ? 0.0 : mind - poserror);
    p->himind = (float)(mind + poserror);
    return (pwrte);
}

Pwrte  *pwrte_point_to_conic_make(void *p1, int type1, void *p2, int type2)
{
    Pwrte  *pwrte;
    Pwrte_point_to_vec *p;
    Point3 *point;
    Conic3 *conic;
    Iso_error *iso1;
    Iso_error *iso2;
    double  poserror, seperror, dist;
    Vec3    closest = {Vec3_id};

    if (p1 == NULL || p2 == NULL)
	return (NULL);

    pwrte = pwrte_alloc(Pwrte_point_to_vec_id);
    p = &(pwrte->p_to_v);
    p->type1 = type1;
    p->type2 = type2;
    p->p1 = p1;
    p->p2 = p2;

    conic = (type1 == CONIC3) ? (Conic3 *) p1 : (Conic3 *) p2;
    point = (type1 == POINT3) ? (Point3 *) p1 : (Point3 *) p2;

    dist = vec3_mod(vec3_diff(conic->origin, point->p));

    iso1 = (Iso_error *) prop_get(conic->conic->props, ISO_ERROR);
    iso2 = (Iso_error *) prop_get(point->props, ISO_ERROR);
    poserror = iso1->pos + iso2->pos;
    seperror = sep_error_ratio * dist;

    if (seperror > poserror)
	poserror = seperror;

    p->lowmind = (float)((dist < poserror) ? 0 : dist - poserror);
    p->himind = (float)(dist + poserror);

    closest = vec3_proj_on_line(point->p, conic->origin, conic->ez);
    dist = vec3_mod(vec3_diff(point->p, closest));
    poserror += dist * iso1->rot;	/* small angle sine assumption */
    dist = vec3_dot(conic->ez, vec3_diff(closest, conic->origin));
    p->lowvecd = (float)(dist - poserror);
    p->hivecd = (float)(dist + poserror);

    return (pwrte);
}

Pwrte  *pwrte_line_to_line_make(Line3 * l1, Line3 * l2)
{
    Pwrte  *pwrte;
    Pwrte_vec_to_vec *p;
    Iso_error *iso1;
    Iso_error *iso2;
    double  roterror, poserror;
    double  dp, angle;

    if (l1 == NULL || l2 == NULL)
	return (NULL);

    pwrte = pwrte_alloc(Pwrte_vec_to_vec_id);
    p = &(pwrte->v_to_v);
    p->type1 = LINE3;
    p->type2 = LINE3;
    p->p1 = (void *) l1;
    p->p2 = (void *) l2;

    iso1 = (Iso_error *) prop_get(l1->props, ISO_ERROR);
    iso2 = (Iso_error *) prop_get(l2->props, ISO_ERROR);

    roterror = iso1->rot + iso2->rot;
    poserror = iso1->pos + iso2->pos;

    p->parallel = smm_geom_parallel((void *) l1, LINE3, (void *) l2, LINE3);

    dp = vec3_dot(l1->v, l2->v);
    angle = tina_acos(dp);

    p->lowang = (float)((angle < roterror) ? 0.0 : angle - roterror);
    p->hiang = (float)((angle + roterror > PI) ? PI : angle + roterror);

    if (p->parallel == false)
    {
	Vec3    c1 = {Vec3_id};
	Vec3    c2 = {Vec3_id};
	double  a1, b1, a2, b2, m1, m2;
	double  tanrot, angscale;
	double  mind, minderror;

	tanrot = atan(roterror);
	angscale = tanrot / sin(fabs(angle));

	mind = vec3_closest_app(l1->p1, l1->v, l2->p1, l2->v, &c1, &c2);
	a1 = vec3_dot(l1->v, vec3_diff(c1, l1->p1));	/* directed */
	b1 = vec3_dot(l1->v, vec3_diff(c1, l1->p2));
	a2 = vec3_dot(l2->v, vec3_diff(c2, l2->p1));
	b2 = vec3_dot(l2->v, vec3_diff(c2, l2->p2));
	m1 = (BETWEEN(0, a1, b1)) ? 0 : fmin(fabs(a1), fabs(b1));
	m2 = (BETWEEN(0, a2, b2)) ? 0 : fmin(fabs(a2), fabs(b2));
	ORDER(double, a1, b1);
	ORDER(double, a2, b2);

	p->lowvec1 = (float)(a1 - poserror - m2 * angscale);
	p->hivec1 = (float)(b1 + poserror + m2 * angscale);
	p->lowvec2 = (float)(a2 - poserror - m1 * angscale);
	p->hivec2 = (float)(b2 + poserror + m1 * angscale);

	minderror = (m1 + m2) * tanrot + poserror;

	p->lowmind = (float)(mind - minderror);
	p->himind = (float)(mind + minderror);
    } else
    {
	/* towards parallel */
	double  d1, d2;

	if (l1->length > l2->length)
	{
	    d1 = vec3_dist_point_line(l1->p1, l2->p1, l2->v);
	    d2 = vec3_dist_point_line(l1->p2, l2->p1, l2->v);
	} else
	{
	    d1 = vec3_dist_point_line(l2->p1, l1->p1, l1->v);
	    d2 = vec3_dist_point_line(l2->p2, l1->p1, l1->v);
	}
	ORDER(double, d1, d2);
	p->lowmind = (float)((d1 < poserror) ? 0.0 : d1 - poserror);
	p->himind = (float)(d2 + poserror);
    }
    return (pwrte);
}

Pwrte  *pwrte_conic_to_line_make(Conic3 * conic, Line3 * line)
{
    Pwrte  *pwrte;
    Pwrte_vec_to_vec *p;
    Iso_error *iso1;
    Iso_error *iso2;
    double  roterror, poserror;
    double  dp, angle, dist, d1, d2, minderror, rot_lever;
    Vec3    closest = {Vec3_id};

    if (conic == NULL || line == NULL)
	return (NULL);

    pwrte = pwrte_alloc(Pwrte_vec_to_vec_id);
    p = &(pwrte->v_to_v);
    p->type1 = CONIC3;
    p->type2 = LINE3;
    p->p1 = (void *) conic;
    p->p2 = (void *) line;

    iso1 = (Iso_error *) prop_get(conic->conic->props, ISO_ERROR);
    iso2 = (Iso_error *) prop_get(line->props, ISO_ERROR);

    roterror = iso1->rot + iso2->rot;
    poserror = iso1->pos + iso2->pos;

    p->parallel = smm_geom_parallel((void *) conic, CONIC3, (void *) line, LINE3);

    dp = vec3_dot(conic->ez, line->v);
    angle = tina_acos(dp);

    p->lowang = (float)((angle < roterror) ? 0.0 : angle - roterror);
    p->hiang = (float)((angle + roterror > PI) ? PI : angle + roterror);

    closest = vec3_proj_on_line(conic->origin, line->p, line->v);

    dist = vec3_mod(vec3_diff(conic->origin, closest));
    d1 = vec3_dot(line->v, vec3_diff(closest, line->p1));	/* signed value */
    d2 = vec3_dot(line->v, vec3_diff(closest, line->p2));

    ORDER(double, d1, d2);
    p->lowvec2 = (float)(d1 - poserror - dist * iso2->rot);
    p->hivec2 = (float)(d2 + poserror + dist * iso2->rot);

    rot_lever = (BETWEEN(0, d1, d2)) ? 0 : fmin(fabs(d1), fabs(d2));
    minderror = poserror + atan(iso2->rot) * rot_lever;

    p->lowmind = (float)((dist < minderror) ? 0.0 : dist - minderror);
    p->himind = (float)(dist + minderror);

    if (p->parallel == false)
    {
	Vec3    c1 = {Vec3_id};
	Vec3    c2 = {Vec3_id};
	double  tanrot, angscale;

	tanrot = atan(roterror);
	angscale = tanrot / sin(fabs(angle));

	(void) vec3_closest_app(conic->origin, conic->ez, line->p1, line->v, &c1, &c2);
	dist = vec3_dot(conic->ez, vec3_diff(c1, conic->origin));
	d1 = vec3_dot(line->v, vec3_diff(c1, line->p1));
	d2 = vec3_dot(line->v, vec3_diff(c1, line->p2));
	angscale *= (BETWEEN(0, d1, d2)) ? 0 : fmin(fabs(d1), fabs(d2));

	p->lowvec1 = (float)(dist - poserror - angscale);
	p->hivec1 = (float)(dist + poserror + angscale);
    }
    return (pwrte);
}

Pwrte  *pwrte_line_to_conic_make(Line3 * line, Conic3 * conic)
{
    Pwrte  *pwrte;
    Pwrte_vec_to_vec *p;
    Iso_error *iso1;
    Iso_error *iso2;
    double  roterror, poserror;
    double  dp, angle, dist, d1, d2, minderror, rot_lever;
    Vec3    closest = {Vec3_id};

    if (conic == NULL || line == NULL)
	return (NULL);

    pwrte = pwrte_alloc(Pwrte_vec_to_vec_id);
    p = &(pwrte->v_to_v);
    p->type1 = LINE3;
    p->type2 = CONIC3;
    p->p1 = (void *) line;
    p->p2 = (void *) conic;

    iso1 = (Iso_error *) prop_get(line->props, ISO_ERROR);
    iso2 = (Iso_error *) prop_get(conic->conic->props, ISO_ERROR);

    roterror = iso1->rot + iso2->rot;
    poserror = iso1->pos + iso2->pos;

    p->parallel = smm_geom_parallel((void *) conic, CONIC3, (void *) line, LINE3);

    dp = vec3_dot(conic->ez, line->v);
    angle = tina_acos(dp);

    p->lowang = (float)((angle < roterror) ? 0.0 : angle - roterror);
    p->hiang = (float)((angle + roterror > PI) ? PI : angle + roterror);

    closest = vec3_proj_on_line(conic->origin, line->p, line->v);

    dist = vec3_mod(vec3_diff(conic->origin, closest));
    d1 = vec3_dot(line->v, vec3_diff(closest, line->p1));	/* signed value */
    d2 = vec3_dot(line->v, vec3_diff(closest, line->p2));

    ORDER(double, d1, d2);
    p->lowvec1 = (float)(d1 - poserror - dist * iso2->rot);
    p->hivec1 = (float)(d2 + poserror + dist * iso2->rot);

    rot_lever = (BETWEEN(0, d1, d2)) ? 0 : fmin(fabs(d1), fabs(d2));
    minderror = poserror + atan(iso2->rot) * rot_lever;

    p->lowmind = (float)((dist < minderror) ? 0.0 : dist - minderror);
    p->himind = (float)(dist + minderror);

    if (p->parallel == false)
    {
	Vec3    c1 = {Vec3_id};
	Vec3    c2 = {Vec3_id};
	double  tanrot, angscale;

	tanrot = atan(roterror);
	angscale = tanrot / sin(fabs(angle));

	(void) vec3_closest_app(conic->origin, conic->ez, line->p1, line->v, &c1, &c2);
	dist = vec3_dot(conic->ez, vec3_diff(c1, conic->origin));
	d1 = vec3_dot(line->v, vec3_diff(c1, line->p1));
	d2 = vec3_dot(line->v, vec3_diff(c1, line->p2));
	angscale *= (BETWEEN(0, d1, d2)) ? 0 : fmin(fabs(d1), fabs(d2));

	p->lowvec2 = (float)(dist - poserror - angscale);
	p->hivec2 = (float)(dist + poserror + angscale);
    }
    return (pwrte);
}

Pwrte  *pwrte_conic_to_conic_make(Conic3 * c1, Conic3 * c2)
{
    Pwrte  *pwrte;
    Pwrte_vec_to_vec *p;
    Iso_error *iso1;
    Iso_error *iso2;
    double  roterror, poserror, seperror;
    double  dp, angle, dist;
    Vec3    closest = {Vec3_id};

    if (c1 == NULL || c2 == NULL)
	return (NULL);

    pwrte = pwrte_alloc(Pwrte_vec_to_vec_id);
    p = &(pwrte->v_to_v);
    p->type1 = CONIC3;
    p->type2 = CONIC3;
    p->p1 = (void *) c1;
    p->p2 = (void *) c2;

    dist = vec3_mod(vec3_diff(c1->origin, c2->origin));

    iso1 = (Iso_error *) prop_get(c1->conic->props, ISO_ERROR);
    iso2 = (Iso_error *) prop_get(c2->conic->props, ISO_ERROR);

    roterror = iso1->rot + iso2->rot;
    poserror = iso1->pos + iso2->pos;
    seperror = sep_error_ratio * dist;

    if (seperror > poserror)
	poserror = seperror;

    p->parallel = false;

    dp = vec3_dot(c1->ez, c2->ez);
    angle = tina_acos(dp);

    p->lowang = (float)((angle < roterror) ? 0.0 : angle - roterror);
    p->hiang = (float)((angle + roterror > PI) ? PI : angle + roterror);

    p->lowmind = (float)((dist < poserror) ? 0 : dist - poserror);
    p->himind = (float)(dist + poserror);

    closest = vec3_proj_on_line(c2->origin, c1->origin, c1->ez);
    roterror = vec3_mod(vec3_diff(closest, c2->origin)) * iso1->rot;
    dist = vec3_dot(c1->ez, vec3_diff(closest, c1->origin));
    p->lowvec1 = (float)(dist - poserror - roterror);
    p->hivec1 = (float)(dist + poserror + roterror);

    closest = vec3_proj_on_line(c1->origin, c2->origin, c2->ez);
    roterror = vec3_mod(vec3_diff(closest, c1->origin)) * iso2->rot;
    dist = vec3_dot(c2->ez, vec3_diff(closest, c2->origin));
    p->lowvec2 = (float)(dist - poserror - roterror);
    p->hivec2 = (float)(dist + poserror + roterror);

    return (pwrte);
}

Pwrte  *pwrte_make(void *p1, int type1, void *p2, int type2)
{
    switch (PAIR(type1, type2))
    {
	case PAIR(POINT3, POINT3):
	return (pwrte_point_to_point_make((Point3 *) p1, (Point3 *) p2));
    case PAIR(POINT3, LINE3):
	return (pwrte_point_to_line_make(p1, type1, p2, type2));
    case PAIR(POINT3, CONIC3):
	return (pwrte_point_to_conic_make(p1, type1, p2, type2));
    case PAIR(LINE3, LINE3):
	return (pwrte_line_to_line_make((Line3 *) p1, (Line3 *) p2));
    case PAIR(LINE3, CONIC3):
	switch (OPAIR(type1, type2))
	{
	case OPAIR(LINE3, CONIC3):
	    return (pwrte_line_to_conic_make((Line3 *) p1, (Conic3 *) p2));
	case OPAIR(CONIC3, LINE3):
	    return (pwrte_conic_to_line_make((Conic3 *) p1, (Line3 *) p2));
	}
    case PAIR(CONIC3, CONIC3):
	return (pwrte_conic_to_conic_make((Conic3 *) p1, (Conic3 *) p2));
    default:
	return (NULL);
    }
}

Bool    point_to_point_pwrte_compatible(Pwrte_point_to_point * p1, Pwrte_point_to_point * p2)
{
    if (p1 == NULL || p2 == NULL)
	return (false);

    if (!OVERLAPPED(p1->lowdist, p1->hidist, p2->lowdist, p2->hidist))
	return (false);
    return (true);
}

Bool    point_to_vec_pwrte_compatible(Pwrte_point_to_vec * p1, Pwrte_point_to_vec * p2)
{
    if (p1 == NULL || p2 == NULL)
	return (false);

    if (!OVERLAPPED(p1->lowmind, p1->himind, p2->lowmind, p2->himind))
	return (false);

    if (!OVERLAPPED(p1->lowvecd, p1->hivecd, p2->lowvecd, p2->hivecd))
	return (false);

    return (true);
}

Bool    line_to_line_pwrte_compatible(Pwrte_vec_to_vec * p1, Pwrte_vec_to_vec * p2)
{
    if (p1 == NULL || p2 == NULL)
	return (false);

    if (!OVERLAPPED(p1->lowang, p1->hiang, p2->lowang, p2->hiang))
	return (false);

    if (p1->parallel == false && p2->parallel == false)
    {
	if (!OVERLAPPED(p1->lowmind, p1->himind, p2->lowmind, p2->himind))
	    return (false);

	if (!OVERLAPPED(p1->lowvec1, p1->hivec1, p2->lowvec1, p2->hivec1))
	    return (false);

	if (!OVERLAPPED(p1->lowvec2, p1->hivec2, p2->lowvec2, p2->hivec2))
	    return (false);

	return (true);
    }
    if (p1->parallel == p2->parallel)	/* both parallel */
    {
	if (OVERLAPPED(p1->lowmind, p1->himind, p2->lowmind, p2->himind))
	    return (true);
	else
	    return (false);
    }
    if (p1->parallel == true)
    {
	double  d1, d2;
	Line3  *l1 = (Line3 *) p2->p1;
	Line3  *l2 = (Line3 *) p2->p2;

	if (l1->length > l2->length)
	{
	    d1 = vec3_dist_point_line(l1->p1, l2->p1, l2->v);
	    d2 = vec3_dist_point_line(l1->p2, l2->p1, l2->v);
	} else
	{
	    d1 = vec3_dist_point_line(l2->p1, l1->p1, l1->v);
	    d2 = vec3_dist_point_line(l2->p2, l1->p1, l1->v);
	}
	ORDER(double, d1, d2);
	return (OVERLAPPED(p1->lowmind, p1->himind, d1, d2) ? true : false);
    } else
    {
	/* p2 parallel */
	double  d1, d2;
	Line3  *l1 = (Line3 *) p1->p1;
	Line3  *l2 = (Line3 *) p1->p2;

	if (l1->length > l2->length)
	{
	    d1 = vec3_dist_point_line(l1->p1, l2->p1, l2->v);
	    d2 = vec3_dist_point_line(l1->p2, l2->p1, l2->v);
	} else
	{
	    d1 = vec3_dist_point_line(l2->p1, l1->p1, l1->v);
	    d2 = vec3_dist_point_line(l2->p2, l1->p1, l1->v);
	}
	ORDER(double, d1, d2);
	return (OVERLAPPED(p2->lowmind, p2->himind, d1, d2) ? true : false);
    }
}

Bool    line_to_conic_pwrte_compatible(Pwrte_vec_to_vec * p1, Pwrte_vec_to_vec * p2)
{
    Bool    parallel;

    if (p1 == NULL || p2 == NULL)
	return (false);

    if (!OVERLAPPED(p1->lowang, p1->hiang, p2->lowang, p2->hiang))
	return (false);

    if (!OVERLAPPED(p1->lowmind, p1->himind, p2->lowmind, p2->himind))
	return (false);

    parallel = (Bool) (p1->parallel == true || p2->parallel == true);

    if ((parallel == false || p1->type1 == LINE3) &&	/* if // only test line */
	!OVERLAPPED(p1->lowvec1, p1->hivec1, p2->lowvec1, p2->hivec1))
	return (false);

    if ((parallel == false || p1->type2 == LINE3) &&	/* if // only test line */
	!OVERLAPPED(p1->lowvec2, p1->hivec2, p2->lowvec2, p2->hivec2))
	return (false);

    return (true);
}

Bool    conic_to_conic_pwrte_compatible(Pwrte_vec_to_vec * p1, Pwrte_vec_to_vec * p2)
{
    if (p1 == NULL || p2 == NULL)
	return (false);

    if (!OVERLAPPED(p1->lowang, p1->hiang, p2->lowang, p2->hiang))
	return (false);

    if (!OVERLAPPED(p1->lowmind, p1->himind, p2->lowmind, p2->himind))
	return (false);

    if (!OVERLAPPED(p1->lowvec1, p1->hivec1, p2->lowvec1, p2->hivec1))
	return (false);

    if (!OVERLAPPED(p1->lowvec2, p1->hivec2, p2->lowvec2, p2->hivec2))
	return (false);

    return (true);
}

Bool    pwrte_compatible(Pwrte * p1, Pwrte * p2)
{
    if (p1 == NULL || p2 == NULL)
	return (false);

    if (OPAIR(p1->gen.type1, p1->gen.type2) != OPAIR(p2->gen.type1, p2->gen.type2))
	return (false);

    switch (PAIR(p1->gen.type1, p1->gen.type2))
    {
    case PAIR(POINT3, POINT3):
	return (point_to_point_pwrte_compatible(&(p1->p_to_p), &(p2->p_to_p)));
    case PAIR(POINT3, LINE3):
    case PAIR(POINT3, CONIC3):
	return (point_to_vec_pwrte_compatible(&(p1->p_to_v), &(p2->p_to_v)));
    case PAIR(LINE3, LINE3):
	return (line_to_line_pwrte_compatible(&(p1->v_to_v), &(p2->v_to_v)));
    case PAIR(LINE3, CONIC3):
	return (line_to_conic_pwrte_compatible(&(p1->v_to_v), &(p2->v_to_v)));
    case PAIR(CONIC3, CONIC3):
	return (conic_to_conic_pwrte_compatible(&(p1->v_to_v), &(p2->v_to_v)));
    }
    return (false);
}

void    pwrte_set_entry(Matrix * table, void *p1, int type1, void *p2, int type2)
/* of shape full; type ptr_v */


{
    int     i, j;

    i = (int) geom_prop_get(p1, type1, PWR);
    j = (int) geom_prop_get(p2, type2, PWR);

    if (table->el.ptr_v[i][j] == NULL)
	table->el.ptr_v[i][j] = (void *) pwrte_make(p1, type1, p2, type2);
    if (i != j && table->el.ptr_v[j][i] == NULL)
	table->el.ptr_v[j][i] = (void *) pwrte_make(p2, type2, p1, type1);
}

Matrix *pwrte_build_full_table(List * list)
/* list of geom primitives */
{
    List   *l1;
    List   *l2;
    Matrix *table;
    int     n;

    if (list == NULL)
	return (NULL);

    for (n = 0, l1 = list; l1 != NULL; l1 = l1->next, n++)
	geom_prop_addifnp(l1->to, l1->type, (void *) n, PWR, (void (*) ()) NULL, false);

    table = matrix_alloc(n, n, matrix_full, ptr_v);

    if (list->next == NULL)
	return (table);

    for (l1 = list; l1->next != NULL; l1 = l1->next)
	for (l2 = l1->next; l2 != NULL; l2 = l2->next)
	    pwrte_set_entry(table, l1->to, l1->type, l2->to, l2->type);

    return (table);
}
