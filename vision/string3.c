/**@(#)
**/
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/**
recover string of Vec3 from curve function
**/

static  Vec3(*curve_func) ();
static void *curve_data;
static double max_sep = 2.0;

void    str_to_curve3_sep_set(double sep)
{
    max_sep = sep;
}

double  str_to_curve3_sep_get(void)
{
    return (max_sep);
}

static Ddlist *curve3_chop(double t1, double t2, Vec3 v1, Vec3 v2)
{
    double  t;
    Vec3    v = {Vec3_id};

    if (vec3_mod(vec3_diff(v1, v2)) < max_sep)
	return (dd_link_alloc((void *) vec3_make(v2), VEC3));

    t = (t1 + t2) * 0.5;
    v = curve_func(curve_data, t);
    return (dd_append(curve3_chop(t1, t, v1, v), curve3_chop(t, t2, v, v2)));
}

Tstring *str3_of_curve3(Vec3(*c_func) ( /* ??? */ ), void *c_data, double t1, double t2)
{
    Ddlist *list;
    Tstring *str;
    double  tm;
    Vec3    v1 = {Vec3_id};
    Vec3    v2 = {Vec3_id};
    Vec3    vm = {Vec3_id};

    if (c_func == NULL)
	return (NULL);

    curve_func = c_func;
    curve_data = c_data;

    tm = (t1 + t2) * 0.5;
    v1 = curve_func(curve_data, t1);
    v2 = curve_func(curve_data, t2);
    vm = curve_func(curve_data, tm);
    list = dd_link_alloc((void *) vec3_make(v1), VEC3);
    list = dd_append(list, curve3_chop(t1, tm, v1, vm));
    list = dd_append(list, curve3_chop(tm, t2, vm, v2));

    str = str_make(STRING, list, dd_get_end(list));
    return (str);
}
