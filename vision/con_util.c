/**@(#)
**/
/**
* con_util.c
* utility functions for conics
*
**/

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/**
scale coefficients so  a+c=1
**/
void    conic_normalise(Conic * conic)
{
    double  k;

    if (conic == NULL)
	return;

    k = 1.0 / (conic->a + conic->c);

    conic->a *= k;
    conic->b *= k;
    conic->c *= k;
    conic->d *= k;
    conic->e *= k;
    conic->f *= k;
}

/**

evaluate conic quadratic form at point (x y)
**/
double  conic_eval(Conic * conic, Vec2 p)
{
    double  a = conic->a, b = conic->b, c = conic->c;
    double  d = conic->d, e = conic->e, f = conic->f;
    double  x = vec2_x(p), y = vec2_y(p);

    return (a * x * x + 2.0 * b * x * y + c * y * y + 2.0 * d * x + 2.0 * e * y + f);
}

/**

evaluate conic gradient vector at point (x y)
**/
Vec2    conic_grad(Conic * conic, Vec2 p)
{
    double  x = vec2_x(p), y = vec2_y(p);

    return (vec2(2.0 * (conic->a * x + conic->b * y + conic->d),
		 2.0 * (conic->b * x + conic->c * y + conic->e)));
}

/**
discriminant of conic - positive for ellipse, negative for hyperbola
**/
double  conic_discrim(Conic * conic)
{
    double  a = conic->a, b = conic->b, c = conic->c;

    return (a * c - b * b);
}

/**
eigendirection and eigenvalues of symmetric 2by2 matrix
|a b|
|b c|
**/
void    conic_eigen(double a, double b, double c, double *theta, double *lambda1, double *lambda2)
{
    double  p = (a + c) / 2.0, q = (a - c) / 2.0, r;

    r = sqrt(q * q + b * b);
    if (b == 0.0 && q == 0.0)
	*theta = 0.0;
    else
	*theta = 0.5 * atan2(b, q);
    *lambda1 = p + r;
    *lambda2 = p - r;
}

/**

value of  lambda  such that  lambda*C0+(1-lambda)*C1 = 0  at  (x y)
**/
double  conic_lambda(Conic * conic0, Conic * conic1, Vec2 p)
{
    double  c0 = conic_eval(conic0, p);
    double  c1 = conic_eval(conic1, p);

    return (c1 / (c1 - c0));
}

/**
point on ellipse with angular parameter t
**/
Vec2    ellipse_point(Conic * conic, double t)
{
    double  c, s, x, y;

    c = cos(conic->theta);
    s = sin(conic->theta);
    x = conic->alpha * cos(t);
    y = conic->beta * sin(t);
    return (vec2_sum(conic->center, vec2(x * c - y * s, x * s + y * c)));
}

/**
point on hyperbola with angular parameter t
**/
Vec2    hyperbola_point(Conic * conic, double t)
{
    double  c, s, x, y;

    c = cos(conic->theta);
    s = sin(conic->theta);
    x = conic->branch * conic->alpha * cosh(t);
    y = conic->beta * sinh(t);
    return (vec2_sum(conic->center, vec2(x * c - y * s, x * s + y * c)));
}

/**
angular parameter of point near ellipse

return values in [0, twopi)
**/
double  ellipse_param(Conic * conic, Vec2 p)
{
    double  c, s, x, y;
    double  t;

    p = vec2_diff(p, conic->center);
    c = cos(conic->theta);
    s = sin(conic->theta);
    x = vec2_x(p) * c + vec2_y(p) * s;
    y = -vec2_x(p) * s + vec2_y(p) * c;

    t = atan2(conic->alpha * y, conic->beta * x);
    if (t < 0.0)
	t += TWOPI;
    return (t);
}

/**
angular parameter of point near hyperbola
**/
double  hyperbola_param(Conic * conic, Vec2 p)
{
    double  c, s;


    p = vec2_diff(p, conic->center);
    c = cos(conic->theta);
    s = sin(conic->theta);
    return (asinh((-vec2_x(p) * s + vec2_y(p) * c) / conic->beta));
}

int     hyperbola_branch(Conic * conic, Vec2 p)
{
    double  c, s;

    p = vec2_diff(p, conic->center);
    c = cos(conic->theta);
    s = sin(conic->theta);
    return (((vec2_x(p) * c + vec2_y(p) * s) > 0.0) ? 1 : -1);
}

/**
approximate squared distance of point from conic
**/
double  conic_approx_sqrdist(Conic * conic, Vec2 p)
{
    double  a = conic->a, b = conic->b, c = conic->c;
    double  d = conic->d, e = conic->e, f = conic->f;
    double  q0, qx, qy;
    double  x = vec2_x(p), y = vec2_y(p);

    q0 = a * x * x + 2.0 * b * x * y + c * y * y + 2.0 * d * x + 2.0 * e * y + f;
    qx = 2.0 * (a * x + b * y + d);
    qy = 2.0 * (b * x + c * y + e);
    return (q0 * q0 / (qx * qx + qy * qy));
}

/**
set type, orientation and semiaxes of conic and return center
**/
void    conic_setup(Conic * conic)
{
    double  a, b, c, d, e;
    double  lambda1, lambda2;
    double  q0, disc;

    if (conic == NULL)
	return;

    a = conic->a;
    b = conic->b;
    c = conic->c;
    d = conic->d;
    e = conic->e;

    disc = conic_discrim(conic);
    if (disc > 0.0)
    {
	conic->type = ELLIPSE;
	conic->t1 = 0.0;
	conic->t2 = TWOPI;
    } else if (disc < 0.0)
    {
	conic->type = HYPERBOLA;
	conic->t1 = -2.0;
	conic->t2 = 2.0;
	conic->branch = 1;
    } else
    {
	conic->type = DEGENERATE;
	return;
    }
    conic->center = vec2(-(c * d - b * e) / disc, -(a * e - b * d) / disc);

    q0 = conic_eval(conic, conic->center);
    conic_eigen(a, b, c, &conic->theta, &lambda1, &lambda2);
    if (lambda1 == 0.0 || lambda2 == 0.0 || q0 == 0.0)
    {
	conic->type = DEGENERATE;
	return;
    }
    lambda1 /= -q0;
    lambda2 /= -q0;
    conic->alpha = 1.0 / sqrt(fabs(lambda1));
    conic->beta = 1.0 / sqrt(fabs(lambda2));
}

Vec2    conic_point(Conic * conic, double t)
{
    Vec2    vec_2 = {Vec2_id};

    switch (conic->type)
    {
    case ELLIPSE:
	vec_2 = (ellipse_point(conic, t));
	break;
    case HYPERBOLA:
	vec_2 = (hyperbola_point(conic, t));
	break;
    case DEGENERATE:
    default:
	vec_2 = (vec2_zero());
    }
    return vec_2;
}

double  conic_param(Conic * conic, Vec2 p)
{
    switch (conic->type)
    {
	case ELLIPSE:
	return (ellipse_param(conic, p));
    case HYPERBOLA:
	return (hyperbola_param(conic, p));
    case DEGENERATE:
    default:
	return (0.0);
    }
}

static int ordered(double t1, double t2, double t3)
{
    int     o = ((t1 < t2) && (t2 < t3)) ||
    ((t2 < t3) && (t3 < t1)) ||
    ((t3 < t1) && (t1 < t2));

    return (o);
}

void    conic_set_ends(Conic * conic, Vec2 p1, Vec2 p2, Vec2 pmid)

/* set end points to be from p1 to p2 */
/* another point defining the sence of the curve */
{
    double  t1, t2, tmid;

    if (conic == NULL || conic->type == DEGENERATE)
	return;

    t1 = conic_param(conic, p1);
    t2 = conic_param(conic, p2);

    if (conic->type == HYPERBOLA)
    {
	conic->branch = hyperbola_branch(conic, p1);
	conic->t1 = t1;
	conic->t2 = t2;
	return;
    }
    tmid = conic_param(conic, pmid);

    if (ordered(t1, tmid, t2))
    {
	if (t1 > t2)
	    t2 += TWOPI;
	conic->t1 = t1;
	conic->t2 = t2;
    } else
    {
	if (t2 >= t1)
	    t1 += TWOPI;
	conic->t1 = t2;
	conic->t2 = t1;
    }
}

double  conic_approx_length(Conic * conic, int n)
{
    int     i;
    Vec2    p = {Vec2_id};
    Vec2    q = {Vec2_id};
    double  dt = (conic->t2 - conic->t1) / n, len = 0.0;

    p = conic_point(conic, conic->t1);
    for (i = 1; i <= n; i++)
    {
	q = conic_point(conic, conic->t1 + i * dt);
	len += vec2_dist(p, q);
	p = q;
    }
    return (len);
}

double  conic_param_length(Conic * conic, Vec2 p1, Vec2 p2, Vec2 pmid)
{
    double  t1, t2, tmid;

    if (conic == NULL || conic->type == DEGENERATE)
	return (0.0);

    t1 = conic_param(conic, p1);
    t2 = conic_param(conic, p2);

    if (conic->type == HYPERBOLA)
	return (fabs(t2 - t1));

    tmid = conic_param(conic, pmid);
    if (ordered(t1, tmid, t2))
    {
	if (t1 > t2)
	    t2 += TWOPI;
    } else
    {
	if (t2 > t1)
	    t1 += TWOPI;
    }
    return (fabs(t2 - t1));
}


void    ellipse_format(Conic * conic)
{
    Vec2    center = {Vec2_id};

    if (conic == NULL)
	return;

    center = conic->center;
    format("ellipse  : %15d\n", conic->label);
    format("center   : %15.6f %15.6f\n", vec2_x(center), vec2_y(center));
    format("theta    : %15.6f\n", conic->theta);
    format("alpha    : %15.6f\n", conic->alpha);
    format("beta     : %15.6f\n", conic->beta);
}

void    hyperbola_format(Conic * conic)
{
    Vec2    center = {Vec2_id};

    if (conic == NULL)
	return;

    center = conic->center;
    format("hyperbola: %15d\n", conic->label);
    format("branch   : %3d\n", conic->branch);
    format("center   : %15.6f %15.6f\n", vec2_x(center), vec2_y(center));
    format("theta    : %15.6f\n", conic->theta);
    format("alpha    : %15.6f\n", conic->alpha);
    format("beta     : %15.6f\n", conic->beta);
}

void    conic_format(Conic * conic)
{
    Vec2    p = {Vec2_id};

    if (conic == NULL)
	return;
    switch (conic->type)
    {
    case ELLIPSE:
	ellipse_format(conic);
	break;
    case HYPERBOLA:
	hyperbola_format(conic);
	break;
    case DEGENERATE:
    default:
	return;
    }
    p = conic_point(conic, conic->t1);
    format("p1       : %15.6f %15.6f\n", vec2_x(p), vec2_y(p));
    p = conic_point(conic, conic->t2);
    format("p2       : %15.6f %15.6f\n", vec2_x(p), vec2_y(p));
    format("\n");
}

/** ratio of minor to major axes (< 1.0) **/
double  conic_aratio(Conic * conic)
{
    double  aratio;

    aratio = conic->alpha / conic->beta;
    aratio = MIN(aratio, 1.0 / aratio);
    return (aratio);
}
