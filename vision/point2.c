/**@(#)
**/
/* point.c functions for manipulating 2D points
 * 
 * typedef struct point2 { int type; int label; struct vec2 p; struct list
 * *props; } Point2;
 * 
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>
#ifdef _PCC
#include <memory.h>
#endif


Point2 *point2_alloc(unsigned int type)
{
    Point2 *point = ts_ralloc(Point2);

    point->type = type;
    point->label = new_label();
    point->p = vec2_zero();
    point->props = NULL;
    return (point);
}

Point2 *point2_make(Vec2 p, unsigned int type)
{
    Point2 *point = ts_ralloc(Point2);

    point->type = type;
    point->label = new_label();
    point->p = p;
    point->props = NULL;
    return (point);
}

void    point2_free(Point2 * point)
{
    if (point == NULL)
	return;
    proplist_freelist(point->props);
    rfree((void *) point);
}

Point2 *point2_copy(Point2 * point)
{
    Point2 *copy;
    List   *proplist_copy();

    if (point == NULL)
	return (NULL);

    copy = ts_ralloc(Point2);
    (void) memcpy((char *) copy, (char *) point, sizeof(Point2));
    copy->props = proplist_copy(point->props);
    return (copy);
}

int     point2_number(List * points)
{
    List   *lptr;
    int     n = 0;

    for (lptr = points; lptr != NULL; lptr = lptr->next)
	((Point2 *) (lptr->to))->label = n++;
    return(n);
}
