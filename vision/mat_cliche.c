/**@(#)
**/
/* mat_cliche.c
 * 
 * 
 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

Match_cliche *match_cliche_make(List * focus, int fthres, List * group, int gthres)
{
    Match_cliche *mc = ts_ralloc(Match_cliche);

    mc->focus = focus;
    mc->fthres = fthres;
    mc->group = group;
    mc->gthres = gthres;

    return (mc);
}

void    match_cliche_free(Match_cliche * mc)
{
    if (mc == NULL)
	return;

    list_rm_links(mc->group);
    rfree((void *) mc);
}
