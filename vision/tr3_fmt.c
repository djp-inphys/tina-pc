/**@(#)
**/
#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

void    transf3_format(Transf3 * transf)
{
    Mat3    R = {Mat3_id};
    Vec3    t = {Vec3_id};

    R = transf->T.R;
    t = transf->T.t;
    format("Transf3:%15d\n", transf->label);
    format("R      :%15.6f%15.6f\n", mat3_xx(R), mat3_xy(R), mat3_xz(R));
    format("        %15.6f%15.6f\n", mat3_yx(R), mat3_yy(R), mat3_yz(R));
    format("        %15.6f%15.6f\n", mat3_zx(R), mat3_zy(R), mat3_zz(R));
    format("t      :%15.6f%15.6f\n", vec3_x(t), vec3_y(t), vec3_z(t));
    format("\n");
}
