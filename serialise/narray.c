#include <stdio.h>
#include <stdlib.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

void    nvector_ts_free(Varptr d, int l, int h, Vartype type);
void    nvector_ts_print(Varptr d, int l, int h, Vartype type);
List   *nvector_ts_serialise(List * lg, Varptr d, int l, int h, Vartype type);
List   *nvector_ts_deserialise(List * lg, Varptr * d, int l, int h, Vartype type);

void    narray_ts_print(Varptrptr d, int m1, int n1, int m2, int n2, Vartype type)
{
    int     i;

    mprintf("narray { Low1 %d high1 %d Low2 %d high2 %d type ", m1, m2, n1, n2);
    print_vtype(stdout, type);
    mprintf("; [");
    for (i = m1; i < m2; i++)
    {
	Varptr  v;

	v.ptr_v = d.ptr_v[i];
	nvector_ts_print(v, n1, n2, type);
    }
    mprintf("]};");
}

List   *narray_ts_serialise(List * lg, Varptrptr d,
		         int m1, int n1, int m2, int n2, Vartype type)
{
    int     i;
    Varptr  v;

    v.ptr_v = (void **) d.char_v;
    lg = nvector_ts_serialise(lg, v, m1, m2, int_v);
    for (i = m1; i < m2; i++)
    {
	v.char_v = d.char_v[i];
	if(v.char_v) lg = nvector_ts_serialise(lg, v, n1, n2, type);
    }
    return lg;
}

List   *narray_ts_deserialise(List * lg, Varptrptr * d,
		         int m1, int n1, int m2, int n2, Vartype type)
{
    int     i;
    Varptr *vp;

    vp = (Varptr *) & (d->ptr_v);
    lg = nvector_ts_deserialise(lg, vp, m1, m2, int_v);
    for (i = m1; i < m2; i++)
    {
	vp = (Varptr *) d->char_v + i;
	if(vp->char_v) lg = nvector_ts_deserialise(lg, vp, n1, n2, type);
    }
    return lg;
}
void narray_ts_free(Varptrptr d,
		    int m1, int n1, int m2, int n2, Vartype type)
{
    int     i;
    Varptr  v;

    v.ptr_v = (void **) d.char_v;
    for (i = m1; i < m2; i++)
    {
	v.char_v = d.char_v[i];
	if(v.char_v) nvector_ts_free(v, n1, n2, type);
    }
    rfree(d.char_v);
}
