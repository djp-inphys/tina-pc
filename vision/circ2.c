/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Circ2  *circ2_alloc(int type)
{
    Circ2  *circ = ts_ralloc(Circ2);

    circ->type = type;
    circ->label = new_label();
    return (circ);
}

void    circ2_free(Circ2 * circ)
{
    if (circ == NULL)
	return;
    proplist_freelist(circ->props);
    rfree((void *) circ);
}
