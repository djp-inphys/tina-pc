/**@(#)Region handling.
 * @(#)Imregion is {int lx, ly; int ux, uy; }
 * @(#)Ie (top left), (bottom right)
 */

#include <stdio.h>
#include <tina/sys.h>
#include <tina/sys_types.h>
#include <tina/sys_gen.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>

Imregion *roi_alloc(int lx, int ly, int ux, int uy)
{
    Imregion *roi = ts_ralloc(Imregion);

    roi->lx = lx;
    roi->ly = ly;
    roi->ux = ux;
    roi->uy = uy;
    return (roi);
}

Imregion *roi_copy(Imregion * roi)
{
    Imregion *copy;

    if (roi == NULL)
	return (NULL);

    copy = ts_ralloc(Imregion);

    copy->lx = roi->lx;
    copy->ly = roi->ly;
    copy->ux = roi->ux;
    copy->uy = roi->uy;
    return (copy);
}

void    roi_update(Imregion * roi, Imregion * copy)
{
    if (roi == NULL || copy == NULL)
	return;

    copy->lx = roi->lx;
    copy->ly = roi->ly;
    copy->ux = roi->ux;
    copy->uy = roi->uy;
}

Imregion *roi_inter(Imregion * r1, Imregion * r2)
{
    int     lx, ly, ux, uy;

    if (r1 == NULL || r2 == NULL)
	return (NULL);

    lx = MAX(r1->lx, r2->lx);
    ly = MAX(r1->ly, r2->ly);
    ux = MIN(r1->ux, r2->ux);
    uy = MIN(r1->uy, r2->uy);

    if (lx >= ux || ly >= uy)
	return (NULL);
    return (roi_alloc(lx, ly, ux, uy));
}

int     roi_inregion(Imregion * region, int x, int y)
{
    if (region == NULL)
	return (0);

    return (x >= region->lx && x < region->ux && y >= region->ly && y < region->uy);
}


/* Fill in the fields of a region of interest. */
void    roi_fill(Imregion * roi, int lx, int ly, int ux, int uy)
{
    roi->lx = lx;
    roi->ly = ly;
    roi->ux = ux;
    roi->uy = uy;
}
