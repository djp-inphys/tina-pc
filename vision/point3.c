/**@(#)
**/
/* point.c functions for manipulating 3D points
 * 
 * typedef struct point3 { int type; int label; struct vec3 p; struct list
 * *props; } Point3;
 * 
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#ifdef _PCC
#include <memory.h>
#endif

extern int new_label(void);

Point3 *point3_alloc(unsigned int type)
{

    Point3 *point = ts_ralloc(Point3);

    point->type = type;
    point->label = new_label();
    point->p = vec3_zero();
    point->props = NULL;
    return (point);
}

Point3 *point3_make(Vec3 p, int type)
{
    Point3 *point = ts_ralloc(Point3);

    point->type = type;
    point->label = new_label();
    point->p = p;
    point->props = NULL;
    return (point);
}

void    point3_free(Point3 * point)
{
    if (point == NULL)
	return;
    proplist_freelist(point->props);
    rfree((void *) point);
}

Point3 *point3_copy(Point3 * point)
{
    Point3 *copy;
    List   *proplist_copy();

    if (point == NULL)
	return (NULL);

    copy = ts_ralloc(Point3);
    (void) memcpy((char *) copy, (char *) point, sizeof(Point3));
    copy->props = proplist_copy(point->props);
    return (copy);
}

int     point3_number(List * points)
{
    List   *lptr;
    int     n = 0;

    for (lptr = points; lptr != NULL; lptr = lptr->next)
	((Point3 *) (lptr->to))->label = n++;
    return(n);
}
