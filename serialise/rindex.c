#include <stdio.h>
#include <stdlib.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void    nvector_ts_print(Varptr d, int l, int h, Vartype type);
List   *nvector_ts_serialise(List * lg, Varptr d, int l, int h, Vartype type);
List   *nvector_ts_deserialise(List * lg, Varptr * d, int l, int h, Vartype type);

void    Rindex_ts_print(Rindex * ri)
{
    Varptr  v;

    ts_print(ri);
    mprintf("_extra_ {");
    v.ptr_v = ri->index;
    nvector_ts_print(v,
		     ri->region->ly, ri->region->uy,
		     ptr_v);
    mprintf("} Rindex;");
}

List   *Rindex_ts_serialise(List * lg, Rindex * ri)
{
    Varptr  v;

    v.ptr_v = ri->index;
    if (serialise_tagged_item(&lg, ri, sizeof(Rindex)) == 1)
	lg = (List *) nvector_ts_serialise(lg, v,
				       ri->region->ly, ri->region->uy,
					   ptr_v);
    return lg;
}

List   *Rindex_ts_deserialise(List * lg, Rindex ** ri)
{
    if (deserialise_tagged_item(&lg, (void **) ri) == 1)
    {
	Rindex *r = *ri;
	Varptr *vp;

	if (r->index)
	{
	    vp = (Varptr *) & (r->index);
	    lg = (List *) nvector_ts_deserialise(lg, vp,
					 r->region->ly, r->region->uy,
						 ptr_v);
	}
    }
    return lg;
}

void    Rindex_ts_free(Rindex * ri)
{
    void    ts_free_gen();

    rx_free(ri, ts_free_gen);
}
