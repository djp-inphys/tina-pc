/**@(#)
**/
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Line2  *colinear_2Dlines(List ** co_linelist, List ** lines, double co_thres)
{
    List   *ptr1;
    List   *ptr2;
    List   *ptr2_next;
    Line2  *line1;
    Line2  *line2;
    Line2  *refline;
    double  dist1, dist2, dist3, dist4, vec2_perp_dist();

    refline = (*co_linelist)->to;
    for (ptr1 = *co_linelist; ptr1 != NULL; ptr1 = ptr1->next)
    {
	line1 = ptr1->to;
	if (line1->length > refline->length)
	    refline = line1;
	for (ptr2 = *lines; ptr2 != NULL; ptr2 = ptr2_next)
	{
	    line2 = ptr2->to;
	    ptr2_next = ptr2->next;

	    dist1 = vec2_perp_dist(line1->p, line1->v, line2->p1);
	    dist2 = vec2_perp_dist(line1->p, line1->v, line2->p2);
	    dist3 = vec2_perp_dist(line2->p, line2->v, line1->p1);
	    dist4 = vec2_perp_dist(line2->p, line2->v, line1->p1);
	    if (dist1 < co_thres && dist2 < co_thres && dist3 < co_thres && dist4 < co_thres)
	    {
		*lines = list_rm_el(*lines, ptr2, (void (*) ()) NULL);
		(void) ref_addtoend(list_get_end(*co_linelist), (void *) line2, LINE2);
	    }
	}
    }
    return (refline);
}
