/**@(#)
**/
/* circprox.c
 * 
 * fitting a string of 2D pos data with circles the circles are
 * represented using the conic data structure
 * 
 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

static int init_sample = 12;

/* grow the original circle "conic" along the implicit string between
 * start and end from original p1 and p2 starting and
 * 
 * ending points (these positions are updated) */
Conic  *conic_circ_grow(Conic * conic, Ddlist * start, Ddlist * end, Ddlist ** p1, Ddlist ** p2, double lo_th, double hi_th, int max_div)
{
    Bool    updated;
    Ddlist *m1 = *p1;
    Ddlist *m2 = *p2;

    do
    {
	Bool    string_grown;

	/** grow start and end along conic **/
	string_grown = conic_grow_string(conic, start, end, &m1, &m2,
					 lo_th, hi_th, max_div);

	if (string_grown)	/** fit a new circ and see if still good **/
	{
	    Conic  *new_conic = ddstr_conic_circ_3pt(m1, m2);

	    if (new_conic != NULL &&
		conic_check(new_conic, m1, m2, lo_th, hi_th, max_div))
	    {
		updated = true;
		conic_free(conic);
		conic = new_conic;
	    } else
	    {
		updated = false;
		if (new_conic != NULL)
		    conic_free(new_conic);
	    }
	} else
	    updated = false;
    } while (updated);

    *p1 = m1;
    *p2 = m2;

    return (conic);
}

/* perform a recursive approximation between start and end use the
 * conic version of a circle as primitive failing to fit a circle use
 * straight line approximation */
static Ddlist *conic_circ_prox(Ddlist * start, Ddlist * end, int sample, double lo_th, double hi_th, int max_div)
{
    Ddlist *p1;
    Ddlist *p2;
    Ddlist *m1;
    Ddlist *m2;
    Ddlist *list1 = NULL;
    Ddlist *list2 = NULL;
    Conic  *conic = NULL;
    double  lo_sqth = lo_th * lo_th;
    double  hi_sqth = hi_th * hi_th;
    int     i, maxcount = 0;

    if (start == NULL || end == NULL || start == end)
	return (NULL);

    p1 = start;
    p2 = ddstr_nth_point(start, end, 2 * sample + 1);
    if (p2 == NULL)
	p2 = end;

    while (1)
    {
	conic = ddstr_conic_circ_3pt(p1, p2);
	if (conic != NULL &&
	    conic_check(conic, p1, p2, lo_sqth, hi_sqth, max_div))
	{
	    int     count = conic_count(conic, start, end, sample / 2, lo_sqth);

	    if (count > maxcount)
	    {
		maxcount = count;
		m1 = p1;
		m2 = p2;
	    }
	}
	conic_free(conic);
	conic = NULL;

	if (p2 == end)
	    break;

	for (i = 0; i < sample; ++i)
	{
	    p1 = p1->next;
	    p2 = p2->next;
	    if (p2 == end)
		break;
	}
    }

    if (maxcount >= 5)
    {
	conic = ddstr_conic_circ_3pt(m1, m2);
	conic = conic_circ_grow(conic, start, end, &m1, &m2,
				lo_sqth, hi_sqth, max_div);
    }
    if (conic == NULL)		/* failed */
    {
	sample = (int)(sample*0.75);		/* increase sample frequency */
	if (sample > 1)
	    return (conic_circ_prox(start, end, sample, lo_th, hi_th, max_div));
	return (linear_prox(start, end, (float)lo_th, init_sample));
    }
    if (m1 != start)
	list1 = conic_circ_prox(start, m1, sample, lo_th, hi_th, max_div);
    if (m2 != end)
	list2 = conic_circ_prox(m2, end, sample, lo_th, hi_th, max_div);

    return (dd_append(list1, dd_append(dd_link_alloc((void *) conic, CONIC2), list2)));
}

/* approximate given string by circular sections represented as conics
 * straight lines are used for sections that can not be fit as a circle
 * return a new string of conics and straight line sections */
Tstring *conic_circ_string(Tstring * string, int init_smpl, double lo_th, double hi_th, int max_div)
{
    Ddlist *conic_list;

    if (string == NULL)
	return (NULL);

    init_sample = init_smpl;

    conic_list = conic_circ_prox(string->start, string->end, init_sample,
				 lo_th, hi_th, max_div);

    if (conic_list == NULL)
	return (NULL);

    return (str_make(STRING, conic_list, dd_get_end(conic_list)));
}

List   *conic_circ_strings(List * strings, int init_smpl, double lo_th, double hi_th, int max_div)
{
    List   *sptr;
    List   *splist = NULL;

    for (sptr = strings; sptr != NULL; sptr = sptr->next)
    {
	Tstring *string = (Tstring *) sptr->to;

	string = conic_circ_string(string, init_smpl, lo_th, hi_th, max_div);
	splist = ref_addtostart(splist, (void *) string, STRING);
    }
    return (splist);
}
