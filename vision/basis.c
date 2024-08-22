/**@(#)
**/
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Basis2 *basis2_alloc(void)
{
    Basis2 *b = ts_ralloc(Basis2);

    b->ex = vec2_ex();
    b->ey = vec2_ey();
    return (b);
}

void    basis2_format(Basis2 * basis)
{
    Vec2    ex = {Vec2_id};
    Vec2    ey = {Vec2_id};

    ex = basis->ex;
    ey = basis->ey;
    format("Basis2:\n");
    format("ex = %15.6f%15.6f\n", vec2_x(ex), vec2_y(ex));
    format("ey = %15.6f%15.6f\n", vec2_x(ey), vec2_y(ey));
}

Basis3 *basis3_alloc(void)
{
    Basis3 *b = ts_ralloc(Basis3);

    b->ex = vec3_ex();
    b->ey = vec3_ey();
    b->ez = vec3_ez();
    return (b);
}

void    basis3_format(Basis3 * basis)
{
    Vec3    ex = {Vec3_id};
    Vec3    ey = {Vec3_id};
    Vec3    ez = {Vec3_id};

    ex = basis->ex;
    ey = basis->ey;
    ez = basis->ez;
    format("Basis3:\n");
    format("ex = %15.6f%15.6f%15.6f\n", vec3_x(ex), vec3_y(ex), vec3_z(ex));
    format("ey = %15.6f%15.6f%15.6f\n", vec3_x(ey), vec3_y(ey), vec3_z(ey));
    format("ez = %15.6f%15.6f%15.6f\n", vec3_x(ez), vec3_y(ez), vec3_z(ez));
}

void    basis_format(void *basis, int type)
{
    switch (type)
    {
	case SCALAR:
	format("Basis0:\n(nil)\n");
	return;
    case POINT2:
    case LINE2:
	basis2_format((Basis2 *) basis);
	return;
    case POINT3:
    case LINE3:
    case PLANE:
	basis3_format((Basis3 *) basis);
	return;
    }
}
