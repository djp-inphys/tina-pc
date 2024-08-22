/**@(#)
**/
/* cone.c functions for manipulating generic cones
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

Cone   *cone_alloc(int type)
{
    Cone   *cone = ts_ralloc(Cone);

    cone->type = type;
    cone->label = new_label();
    cone->c1 = cone->c2 = NULL;
    cone->offset = 0;
    cone->props = NULL;
    return (cone);
}

Cone   *cone_make(Conic3 * c1, Conic3 * c2, double offset, int type)
{
    Cone   *cone = ts_ralloc(Cone);

    cone->type = type;
    cone->label = new_label();
    cone->c1 = c1;
    cone->c2 = c2;
    cone->offset = offset;
    cone->props = NULL;
    return (cone);
}

void    cone_free(Cone * cone)
{
    if (cone == NULL)
	return;
    proplist_freelist(cone->props);
    conic3_free(cone->c1);
    conic3_free(cone->c2);
    rfree((void *) cone);
}

Cone   *cone_copy(Cone * cone)
{
    Cone   *copy;
    List   *proplist_copy();

    if (cone == NULL)
	return (NULL);

    copy = ts_ralloc(Cone);
    (void) memcpy((char *) copy, (char *) cone, sizeof(Cone));
    copy->c1 = conic3_copy(cone->c1);
    copy->c2 = conic3_copy(cone->c2);
    copy->props = proplist_copy(cone->props);
    return (copy);
}

Vec3    cone_point(Cone * cone, double u, double t)

/* cone parameters */
{
    Vec3    p1 = {Vec3_id};
    Vec3    p2 = {Vec3_id};

    p1 = conic3_point(cone->c1, t);
    p2 = conic3_point(cone->c2, t + cone->offset);

    return (vec3_sum(vec3_times(1 - u, p1), vec3_times(u, p2)));
}
