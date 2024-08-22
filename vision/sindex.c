/**@(#)
**/
/* sindex.c functions to suport 2D raster based indexing schemes */

#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>

Rindex *sx_alloc(Imregion * region, int type)
{
    Rindex *sx;
    Imregion *roi_copy();

    if (region == NULL)
	return (NULL);

    sx = ts_ralloc(Rindex);
    sx->index = (void **) pvector_alloc(region->ly, region->uy);
    sx->type = type;
    sx->region = roi_copy(region);
    return (sx);
}

void    sx_free(Rindex * sx, void (*freefunc) ( /* ??? */ ))
{
    void  **index;
    Imregion *region;
    int     i;

    if (sx == NULL)
	return;

    index = sx->index;
    region = sx->region;

    for (i = region->ly; i < region->uy; ++i)
	list_rm((List *) index[i], freefunc);

    pvector_free((void *) index, region->ly);
    rfree((void *) sx);
}
