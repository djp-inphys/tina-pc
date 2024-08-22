/**@(#)Quaternion handling
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

Vec3    vec3_quat(Vec4 q)
{
    Vec3    v = {Vec3_id};

    vec3_x(v) = vec4_x(q);
    vec3_y(v) = vec4_y(q);
    vec3_z(v) = vec4_z(q);
    return (v);
}

Vec4    quat_vec3(Vec3 v)
{
    Vec4    q = {Vec4_id};

    vec4_x(q) = vec3_x(v);
    vec4_y(q) = vec3_y(v);
    vec4_z(q) = vec3_z(v);
    vec4_w(q) = 0.0;
    return (q);
}

Vec4    quat_rot3(Mat3 r)
{
    double  theta;
    Vec3    axis = {Vec3_id};
    Vec4    q = {Vec4_id};

    rot3_angle_axis(r, &theta, &axis);
    q = quat_vec3(vec3_times(sin(0.5 * theta), axis));
    vec4_w(q) = cos(0.5 * theta);
    return (q);
}

Mat3    rot3_quat(Vec4 q)
{
    double  theta, s;
    Vec3    axis = {Vec3_id};

    theta = 2.0 * acos(vec4_w(q));
    s = sin(0.5 * theta);
    if (s == 0.0)
	return (mat3_unit());
    s = 1.0 / s;
    vec3_x(axis) = s * vec4_x(q);
    vec3_y(axis) = s * vec4_y(q);
    vec3_z(axis) = s * vec4_z(q);
    return (rot3(theta, axis));
}

Vec4    quat_prod(Vec4 p, Vec4 q)
{
    Vec4    prod = {Vec4_id};
    double  px = vec4_x(p), qx = vec4_x(q);
    double  py = vec4_y(p), qy = vec4_y(q);
    double  pz = vec4_z(p), qz = vec4_z(q);
    double  p0 = vec4_w(p), q0 = vec4_w(q);

    vec4_x(prod) = p0 * qx + px * q0 + py * qz - pz * qy;
    vec4_y(prod) = p0 * qy + py * q0 + pz * qx - px * qz;
    vec4_z(prod) = p0 * qz + pz * q0 + px * qy - py * qx;
    vec4_w(prod) = p0 * q0 - px * qx - py * qy - pz * qz;

    return (prod);
}

Vec4    quat_conj(Vec4 q)
{
    Vec4    conj = {Vec4_id};

    vec4_x(conj) = -vec4_x(q);
    vec4_y(conj) = -vec4_y(q);
    vec4_z(conj) = -vec4_z(q);
    vec4_w(conj) = vec4_w(q);
    return (conj);
}

Vec4    quat_inverse(Vec4 q)
{
    double  mod2 = vec4_sqrmod(q);

    return (vec4_times(1.0 / mod2, quat_conj(q)));
}

Vec3    vec3_rot_quat(Vec4 q, Vec3 v)
{
    Vec4    p = {Vec4_id};

    p = quat_vec3(v);
    p = quat_prod(q, p);
    p = quat_prod(p, quat_inverse(q));
    return (vec3_quat(p));
}
