/**@(#)Rotation
**/
#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

Mat3    rot3(double theta, Vec3 axis)
{
    double  c, c1, s, a;
    float   nx, ny, nz;
    double  mxx, mxy, mxz;
    double  myx, myy, myz;
    double  mzx, mzy, mzz;

    a = vec3_mod(axis);
    if (a == 0.0)
	return (mat3_unit());
    vec3_comps(vec3_unit(axis), &nx, &ny, &nz);
    c = cos(theta);
    s = sin(theta);
    c1 = 1.0 - c;
    mxx = c + nx * nx * c1;
    mxy = nx * ny * c1 - nz * s;
    mxz = nx * nz * c1 + ny * s;
    myx = ny * nx * c1 + nz * s;
    myy = c + ny * ny * c1;
    myz = ny * nz * c1 - nx * s;
    mzx = nz * nx * c1 - ny * s;
    mzy = nz * ny * c1 + nx * s;
    mzz = c + nz * nz * c1;
    return (mat3(mxx, mxy, mxz,
		 myx, myy, myz,
		 mzx, mzy, mzz));
}

Mat3    rot3_1(Vec3 axis)
{
    double  theta;
    double  c, c1, s;
    float   nx, ny, nz;
    double  mxx, mxy, mxz;
    double  myx, myy, myz;
    double  mzx, mzy, mzz;

    theta = vec3_mod(axis);
    if (theta == 0.0)
	return (mat3_unit());
    vec3_comps(vec3_unit(axis), &nx, &ny, &nz);
    c = cos(theta);
    s = sin(theta);
    c1 = 1.0 - c;
    mxx = c + nx * nx * c1;
    mxy = nx * ny * c1 - nz * s;
    mxz = nx * nz * c1 + ny * s;
    myx = ny * nx * c1 + nz * s;
    myy = c + ny * ny * c1;
    myz = ny * nz * c1 - nx * s;
    mzx = nz * nx * c1 - ny * s;
    mzy = nz * ny * c1 + nx * s;
    mzz = c + nz * nz * c1;
    return (mat3(mxx, mxy, mxz,
		 myx, myy, myz,
		 mzx, mzy, mzz));
}

void    rot3_angle_axis(Mat3 m, double *theta, Vec3 * axis)
{
    double  c;
    Vec3    v = {Vec3_id};

    c = 0.5 * (mat3_trace(m) - 1.0);
    v = vec3_unit(vec3(mat3_zy(m) - mat3_yz(m),
		       mat3_xz(m) - mat3_zx(m),
		       mat3_yx(m) - mat3_xy(m)));
    if (theta == NULL)
	*axis = vec3_times(tina_acos(c), v);
    else
    {
	*axis = v;
	*theta = tina_acos(c);
    }
}

Mat3    rot3_euler(double theta, double phi, double psi)
{
    Mat3    r1 = {Mat3_id};
    Mat3    r2 = {Mat3_id};
    Mat3    r3 = {Mat3_id};

    r1 = rot3(theta, vec3_ey());
    r2 = rot3(phi, vec3_ez());
    r3 = rot3(psi, vec3_ez());
    return (mat3_prod(r2, mat3_prod(r1, r3)));
}
