/**@(#)
**/
#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

static double min_linex(Line2 * line)
{
    if (line->p1.el[0] < line->p2.el[0])
	return (line->p1.el[0]);
    else
	return (line->p2.el[0]);
}

static double min_liney(Line2 * line)
{
    if (line->p1.el[1] < line->p2.el[1])
	return (line->p1.el[1]);
    else
	return (line->p2.el[1]);
}

static List *remerge(List * line_list, double join_thres)
{
    List   *ptr1 = NULL;
    List   *ptr2 = NULL;
    Line2  *line1 = NULL;
    Line2  *line2 = NULL;
    Tstring *s1, *s2, *snew, *es_combine();

    for (ptr1 = line_list; ptr1 != NULL; ptr1 = ptr1->next)
    {
	line1 = ptr1->to;
	if (line1 != NULL && line2 != NULL)
	{
	    if (vec2_mod(vec2_diff(line2->p1, line1->p1)) < join_thres
	     || vec2_mod(vec2_diff(line2->p1, line1->p2)) < join_thres
	     || vec2_mod(vec2_diff(line2->p2, line1->p1)) < join_thres
	    || vec2_mod(vec2_diff(line2->p2, line1->p2)) < join_thres)
	    {
		s1 = prop_get(line1->props, STRING);
		s2 = prop_get(line2->props, STRING);
		snew = es_combine(s1, s2);
		line_list = list_rm_el(line_list, ptr1, line2_free);
		line1 = line2_fit(snew->start, snew->end);
		ptr1 = link_alloc((void *) line1, LINE2);
		link_addafter(ptr2, ptr1);
		line_list = list_rm_el(line_list, ptr2, line2_free);
	    }
	}
	ptr2 = ptr1;
	line2 = line1;
    }
    return (line_list);
}

void    colinear_2Dlist(List * lines, List ** co_horizlist, List ** co_vertlist, double co_thres, double join_thres)
{
    List   *ptr1;
    List   *co_linelist;
    List   *remerge();
    Line2  *line1;
    Line2  *refline;
    Line2  *colinear_2Dlines();
    double  min_linex(), min_liney();
    double  min_intery(), min_interx();

    while (lines != NULL)
    {
	ptr1 = lines;
	line1 = ptr1->to;
	lines = list_rm_el(lines, ptr1, (void (*) ()) NULL);
	co_linelist = ref_addtostart((List *) NULL, (void *) line1, LINE2);
	refline = colinear_2Dlines(&co_linelist, &lines, co_thres);
	if (fabs(refline->p1.el[0] - refline->p2.el[0])
	    > fabs(refline->p1.el[1] - refline->p2.el[1]))
	{
	    co_linelist = sort_list(co_linelist, min_linex, NULL);
	    co_linelist = remerge(co_linelist, join_thres);
	    *co_horizlist = ref_addtostart((List *) * co_horizlist, (void *) co_linelist, LIST);
	} else
	{
	    co_linelist = sort_list(co_linelist, min_liney, NULL);
	    co_linelist = remerge(co_linelist, join_thres);
	    *co_vertlist = ref_addtostart((List *) * co_vertlist, (void *) co_linelist, LIST);
	}
    }
    *co_horizlist = sort_list(*co_horizlist, min_intery, NULL);
    *co_vertlist = sort_list(*co_vertlist, min_interx, NULL);
}
