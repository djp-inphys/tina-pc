/**@(#)World point corresponding to projective point, etc
**/

#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

/** world point corresponding to projective point **/
static Vec3 vec3_of_proj3(Vec4 v)
{
    double  w = vec4_w(v);

    return (vec3(vec4_x(v) / w, vec4_y(v) / w, vec4_z(v) / w));
}

/** (unit) projective point corresponding to world point **/
static Vec4 proj3_of_vec3(Vec3 v)
{
    return (vec4(vec3_x(v), vec3_y(v), vec3_z(v), 1.0));
}

/** result of applying projective transform to projective point **/
Vec4    proj3_rectify(Mat4 m, Vec4 v)
{
    return (vec4_unit(mat4_vprod(m, v)));
}

/** result of applying projective transform to world point **/
Vec3    vec3_rectify(Mat4 m, Vec3 v)
{
    Vec4    w = {Vec4_id};

    w = mat4_vprod(m, proj3_of_vec3(v));
    return (vec3_of_proj3(w));
}
