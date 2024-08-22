/**@(#)
**/
/* rindex.c functions to suport raster based indexing schemes
 * 
 * typedef struct rindex { int type; int lr, ur; void **index; } Rindex;
 * 
 */

#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>

Rindex *rx_alloc(Imregion * region, int type)
{
    Rindex *r;

    if (region == NULL)
	return (NULL);

    r = ts_ralloc(Rindex);

    r->index = (void **) pvector_alloc(region->ly, region->uy);
    r->type = type;
    r->region = roi_copy(region);

    return (r);
}

void    rx_free_links(Rindex * r)
{
    int     ly, uy, i;
    void  **index;
    void    list_rm_links();

    if (r == NULL)
	return;

    ly = r->region->ly;
    uy = r->region->uy;
    index = r->index;

    for (i = ly; i < uy; ++i)
	list_rm_links((List *) index[i]);

    pvector_free((void *) index, ly);
    rfree((void *) r);
}

void    rx_free(Rindex * r, void (*freefunc) ( /* ??? */ ))
{
    int     ly, uy, i;
    void  **index;

    if (r == NULL)
	return;

    ly = r->region->ly;
    uy = r->region->uy;
    index = r->index;

    for (i = ly; i < uy; ++i)
	list_rm((List *) index[i], freefunc);

    pvector_free((void *) index, ly);
    rfree((void *) r);
}
