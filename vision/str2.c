/* 
 * 
 * str2.c
 * 
 * Utilities for dealing with strings of 2D points (Edgels or VEC2's)
 */
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/*
Return centroid of points on 2D string.
*/
Vec2 str2_centroid(Tstring * str)
{
    Vec2 sum = vec2_zero(), p;
    Ddlist *ptr;
    int n = 0;
    if (str == NULL)
	return (sum);
    for (ptr = str->start;  ;  ptr=ptr->next)
    {
	DD_GET_POS2(ptr, p);
	sum = vec2_sum(sum, p);
	n++;
	if(ptr == str->end)
	  break;
    }
    return (vec2_times(1.0 / n, sum));
}

/*
Translate a 2d string by vector v.
*/
void str2_translate(Tstring * str, Vec2 v)
{
    Ddlist *ptr;

    if (str == NULL)
	return;
    for (ptr = str->start; ; ptr = ptr->next)
    {
	Vec2 p;

	DD_GET_POS2(ptr, p);
	p = vec2_sum(p, v);
	DD_SET_POS2(ptr, p);
	if (ptr == str->end)
	    break;
    }
}

/*
Rotate, translate, and scale a 2d string about centre c.
x->t+c+sr(x-c).
*/
void str2_rts(Tstring * str, Vec2 c, Mat2 r, Vec2 t, double s)
{
    Ddlist *ptr;

    if (str == NULL)
	return;
    for (ptr = str->start; ; ptr = ptr->next)
    {
	Vec2 p;

	DD_GET_POS2(ptr, p);
	p = vec2_diff(p, c);
	p = vec2_times(s, p);
	p = mat2_vprod(r, p);
	p = vec2_sum3(c, t, p);
	DD_SET_POS2(ptr, p);
	if (ptr == str->end)
	    break;
    }
}

/*
Return area enclosed by 2D string (0 for type STRING).
*/
double str2_area(Tstring * str)	/* Newcode */
{
    Ddlist *ptr;
    double a = 0.0;
    if (str == NULL)
	 return(0.0);
    if (str->type == STRING)
    {
	error("str2_area: passed open contour", non_fatal);
	return (0.0);
    }
    for (ptr = str->start; ; ptr = ptr->next)
    {
	Vec2 p1, p2;
	DD_GET_POS2(ptr, p1);
	DD_GET_POS2(ptr->next, p2);
	a += vec2_cross(p1, p2);
	if (ptr == str->end)
	    break;
    }
    a *= 0.5;
    return (a);
}

/*
Find major and minor axes (a, b) and angle of principle direction
theta of 2D-string.
*/
void str2_eigen(Tstring * str, double *a, double *b, double *theta)
{
    Ddlist *ptr;
    Mat2 m = mat2_zero();
    Vec2 c = str2_centroid(str);
    if (str == NULL)
	return;
    for (ptr = str->start; ; ptr = ptr->next)
    {
	Vec2 p;
	DD_GET_POS2(ptr, p);
	p = vec2_diff(p, c);
	m = mat2_sum(m, mat2_tensor(p, p));
	if (ptr == str->end)
	    break;
    }
    mat2_sym_eigen(m, theta, a, b);
}

/*
Return angle of major axis of 2D string.
*/
double str2_orientation(Tstring * str)
{
    double a, b, theta;
    str2_eigen(str, &a, &b, &theta);
    return (theta);
}

/*
Allocates Vec2 at same position as Edgel or Vec2 pointer.
*/
static Vec2 *make_vec2_from_edge(void *e, int *type)
{
    Vec2 v;

    GET_POS2(e, *type, v);
    *type = VEC2;
    return (vec2_make(v));
}

/*
Return copy of 2D string (with Vec2 entries).
*/
Tstring *str2_copy(Tstring * str)
{
    return(str_copy(str, (void *(*) ()) vec2_copy, NULL));
}

/*
Return total arc (chord) length of Ddstring, running from
start past nextoend.
*/
double dd2_arc_length(Ddlist *start, Ddlist *nextoend)
{
    Ddlist *ptr;
    double s;
    if (start == NULL || nextoend == NULL || nextoend->next == NULL)
	return (0.0);
    for (s = 0.0, ptr = start;; ptr = ptr->next)
    {
	Vec2 p1, p2;
	DD_GET_POS2(ptr, p1);
	DD_GET_POS2(ptr->next, p2);
	s += vec2_dist(p1, p2);
	if (ptr == nextoend)
	    break;
    }
    return (s);
}

/*
Return total arc (chord) length of 2D string.
*/
double str2_arc_length(Tstring * str)
{
    if (str == NULL || str->count < 2)
	return (0.0);
    switch(str->type)
    {
	case LOOP:
	    return(dd2_arc_length(str->start, str->end));
	case STRING:
	    return(dd2_arc_length(str->start, str->end->last));
	default:
	    return(-1.0);
    }
}

/*
Return total absolute angle turned through by 2D Ddlist,
summing angles at nextostart up to nextoend.
*/
double dd2_ang_length(Ddlist *nextostart, Ddlist *nextoend)
{
    Ddlist *ptr;
    double s;
    if (nextostart == NULL || nextoend == NULL)
	return (0.0);
    for (s = 0.0, ptr = nextostart;; ptr = ptr->next)
    {
	Vec2 p1, p2, p3;
	DD_GET_POS2(ptr->last, p1);
	DD_GET_POS2(ptr,       p2);
	DD_GET_POS2(ptr->next, p3);
	s += fabs(vec2_angle(vec2_diff(p3, p2), vec2_diff(p2, p1)));
	if (ptr == nextoend)
	    break;
    }
    return (s);
}

/*
Return total absolute angle turned through by 2D string.
*/
double str2_ang_length(Tstring * str)
{
    if (str == NULL ||
	(str->type == LOOP && str->count < 2) ||
	(str->type == STRING && str->count < 3))
	return (0.0);
    switch(str->type)
    {
	case LOOP:
	    return(dd2_ang_length(str->start, str->end));
	case STRING:
	    return(dd2_ang_length(str->start->next, str->end->last));
	default:
	    return(-1.0);
    }
}

/*
Put n equally spaced points from 2D string in Vec2 array
p[0],i...,p[n-1]. (Note points are always on string, to get
interpolated points see str2_get_interp_vec2_knots below)
*/
void str2_get_vec2_knots(Tstring * str, int n, Vec2 * p)
{
    Ddlist *ptr;
    int i, j;
    double s, ds;

    s = str->count;
    switch (str->type)
    {
      case STRING:
	ds = (s-1) / (n - 1);
	break;
      case LOOP:
	ds = s / (n-1);
	break;
      default:
	return;
    }
    for (i = 0, j = 0, ptr = str->start; j < n; i++, ptr = ptr->next)
    {
	if (i >= j * ds || (str->type == STRING && ptr == str->end))
	{
	    DD_GET_POS2(ptr, p[j]);
	    j++;
	}
    }
}

/*
Get point given arc-length along 2D string.
*/
Vec2 str2_point(Tstring *str, double t)
{
    Ddlist *ptr, *end;
    double s;
    if(str == NULL)
	return(vec2_zero());
    if(str->count == 1 || t <= 0)
    {
	Vec2 p;
	DD_GET_POS2(str->start, p);
	return(p);
    }
    switch(str->type)
    {
	case LOOP:
	    end = str->start;
	    break;
	case STRING:
	    end = str->end;
	    break;
    }
    for(s = 0, ptr = str->start; ; ptr = ptr->next)
    {
	Vec2 p1, p2;
	double ds;
	DD_GET_POS2(ptr, p1);
	DD_GET_POS2(ptr->next, p2);
	ds = vec2_dist(p1, p2);
	if(ds != 0.0 && s+ds >= t)
	    return(vec2_interp((t-s) / ds, p1, p2));
	s += ds;
	if(ptr->next == end)
	    return(p2);
    }
}

/*
Put n equally spaced points interpolated from 2D string
in Vec2 array p[0],i...,p[n-1].
*/
void str2_get_interp_vec2_knots(Tstring * str, int n, Vec2 * p)
{
    double s;
    int i, m;
    if(str == NULL)
	return;
    switch(str->type)
    {
	case STRING:
	    m = n-1;
	    break;
	case LOOP:
	    m = n;
	    break;
	default:
	    return;
    }
    /* get str length */
    s = str2_arc_length(str);
    for(i = 0; i < n; i++)
    {
	double t = (i*s)/m;
	p[i] = str2_point(str, t);
    }
}

/*
Return an 8-neighbour connected string linearly interpolating str.
*/
Tstring *str2_fill(Tstring *str)
{
    double s = str2_arc_length(str);
    return (str2_of_curve2(str2_point, str, 0, s, (void *) NULL));
}

/*
Free a 2D string.
*/
void str2_free(Tstring *str)
{
    str_free(str, rfree);
}
