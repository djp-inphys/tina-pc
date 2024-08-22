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

Point2 *point2_rectify(Point2 * point, Mat3 rect)
{
    Point2 *new;

    new = point2_make(vec2_rectify(rect, point->p), point->type);

    return (new);
}

Point2 *point2_proj(Point2 * point, Mat3 proj)
{
    Point2 *new;

    new = point2_make(vec2_rectify(proj, point->p), point->type);

    return (new);
}
