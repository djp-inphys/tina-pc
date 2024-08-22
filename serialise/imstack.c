/**@(#)Serialise (etc) Imstack
 */
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/cvr.h>
void    nvector_ts_print(Varptr d, int l, int h, Vartype type);
List   *nvector_ts_serialise(List * lg, Varptr d, int l, int h, Vartype type);
List   *nvector_ts_deserialise(List * lg, Varptr * d, int l, int h, Vartype type);

void    Imstack_ts_print(Imstack * is)
{
    int     i;

    ts_print(is);
    mprintf(" _extra_ {");
    for (i = is->first; i < is->end; i++)
	ts_print_gen(is->imrect[i]);
    mprintf("} Imstack;");
}

List   *Imstack_ts_serialise(List * lg, Imstack * is)
{
    int     i;

    if (serialise_tagged_item(&lg, is, sizeof(Imstack)) == 1)
	if (is->imrect)		/* any image data? */
	{
	    Varptr  v;

	    v.ptr_v = (void **) is->imrect;
	    lg = nvector_ts_serialise(lg, v, is->first, is->end, ptr_v);
	    for (i = is->first; i < is->end; i++)
		lg = ts_serialise_gen(lg, is->imrect[i]);
	}
    return lg;
}

List   *Imstack_ts_deserialise(List * lg, Imstack ** is)
{
    int     i;

    if (deserialise_tagged_item(&lg, (void **) is) == 1)
    {
	Imstack *is2 = *is;

	if (is2->imrect)	/* was the pointer NULL */
	{
	    Varptr *vp;

	    vp = (Varptr *) & (is2->imrect);
	    lg = nvector_ts_deserialise(lg, vp, is2->first, is2->end, ptr_v);
	    for (i = is2->first; i < is2->end; i++)
		lg = ts_deserialise_gen(lg, (void **) (is2->imrect + i));
	}
    }
    return lg;
}

void    Imstack_ts_free(Imstack * is)
{
    int     i;

    if (is->imrect)
	for (i = is->first; i < is->end; i++)
	    ts_free_gen(is->imrect[i]);
}
