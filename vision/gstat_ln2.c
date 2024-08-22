/**@(#)
**/
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Basis2 *line2_basis(Line2 * line)
{
    Basis2 *b;
    Basis2 *basis2_alloc();

    b = basis2_alloc();
    vec2_basis(line->v, &b->ex, &b->ey);
    return (b);
}

void    line2_correct(Line2 * line, Basis2 * basis, Vector * x)
{
    Vec2    up = {Vec2_id};
    double  x0 = vector_getf(x, 0);
    double  x1 = vector_getf(x, 1);

    line->p = vec2_sum(line->p, vec2_times(x0, basis->ex));
    up = vec2_sum(basis->ey, vec2_times(x1, basis->ex));
    vec2_basis(up, &basis->ex, &basis->ey);

    line->v = basis->ex;
    line->p1 = vec2_proj_on_line(line->p1, line->p, line->v);
    line->p2 = vec2_proj_on_line(line->p2, line->p, line->v);
}
