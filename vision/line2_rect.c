/**@(#)
**/
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/**
projective transformation of line
**/

Line2  *line2_rectify(Line2 * line, Mat3 rect)
{
    Line2  *new;

    new = line2_make(vec2_rectify(rect, line->p1),
		     vec2_rectify(rect, line->p2),
		     line->type);

    return (new);
}

Line2  *line2_proj(Line2 * line, Mat3 proj)
{
    Line2  *new;

    new = line2_make(vec2_rectify(proj, line->p1),
		     vec2_rectify(proj, line->p2),
		     line->type);

    return (new);
}
