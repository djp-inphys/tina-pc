/**@(#)
**/
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Basis3 *line3_basis(Line3 * line)
{
    Basis3 *b;
    Basis3 *basis3_alloc();

    b = basis3_alloc();
    vec3_basis(line->v, vec3_ey(), &b->ex, &b->ey, &b->ez);
    return (b);
}

void    line3_correct(Line3 * line, Basis3 * basis, Vector * x)
{
    double  x0 = vector_getf(x, 0);
    double  x1 = vector_getf(x, 1);
    double  x2 = vector_getf(x, 2);
    double  x3 = vector_getf(x, 3);
    Vec3    aim = {Vec3_id};
    Vec3    up = {Vec3_id};

    line->p = vec3_sum3(line->p, vec3_times(x0, basis->ex),
			vec3_times(x1, basis->ey));
    aim = vec3_sum3(basis->ez, vec3_times(x2, basis->ex),
		    vec3_times(x3, basis->ey));
    up = vec3_sum(basis->ey, vec3_times(-x3, basis->ez));
    vec3_basis(aim, up, &basis->ex, &basis->ey, &basis->ez);

    line->v = basis->ez;
    line->p1 = vec3_closest_lines(line->p, line->v,
				  vec3_zero(), vec3_unit(line->p1));
    line->p2 = vec3_closest_lines(line->p, line->v,
				  vec3_zero(), vec3_unit(line->p2));

    /**
    alternatively:
    line->p1 = vec3_proj_on_line(line->p1, line->p, line->v);
    line->p2 = vec3_proj_on_line(line->p2, line->p, line->v);
    **/
}
