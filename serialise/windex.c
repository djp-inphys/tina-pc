#include <stdio.h>
#include <stdlib.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void    Windex_ts_print(Windex * ri)
{
    extern void narray_ts_print(Varptrptr d, int m1, int n1, int m2, int n2, Vartype type);
    Varptrptr v;

    ts_print(ri);
    mprintf("_extra_ {");
    v.ptr_v = ri->index;
    narray_ts_print(v, 0, 0, ri->m, ri->n, ptr_v);
    mprintf("} Windex;");
}

List   *Windex_ts_serialise(List * lg, Windex * ri)
{
    extern List *narray_ts_serialise(List * lg, Varptrptr d, int m1, int n1, int m2, int n2, Vartype type);
    Varptrptr v;

    v.ptr_v = ri->index;
    if (serialise_tagged_item(&lg, ri, sizeof(Windex)) == 1)
	lg = (List *) narray_ts_serialise(lg, v, 0, 0, ri->m, ri->n, ptr_v);
    return lg;
}

List   *Windex_ts_deserialise(List * lg, Windex ** ri)
{
    extern List *narray_ts_deserialise(List * lg, Varptrptr * d, int m1, int n1, int m2, int n2, Vartype type);

    if (deserialise_tagged_item(&lg, (void **) ri) == 1)
    {
	Windex *r = *ri;
	Varptrptr *vp;

	if (r->index)
	{
	    vp = (Varptrptr *) & (r->index);
	    lg = (List *) narray_ts_deserialise(lg, vp, 0, 0, r->m, r->n, ptr_v);
	}
    }
    return lg;
}

void    Windex_ts_free(Windex * ri)
{
    void    ts_free_gen();

    wx_free(ri, ts_free_gen);
}
