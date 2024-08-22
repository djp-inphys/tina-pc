#include <stdio.h>
#include <stdlib.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
List   *nvector_ts_serialise(List * lg, Varptr d, int l, int h, Vartype type);
List   *nvector_ts_deserialise(List * lg, Varptr * d, int l, int h, Vartype type);
void nvector_ts_free(Varptr d, int l, int h, Vartype type);

void    Vector_ts_print(Vector * v)
{
    mprintf("struct vector {");
    vector_format(v);
    mprintf("} vector;");
}

List   *Vector_ts_serialise(List * lg, Vector * v)
{
    if (serialise_tagged_item(&lg, v, sizeof(Vector)) == 1)
      {
	Varptr vp;
	vp.ptr_v=v->data;
	lg=nvector_ts_serialise(lg,vp,0,v->n,v->vtype);
      }
    return lg;
}
List   *Vector_ts_deserialise(List * lg, Vector ** vp)
{
    if (deserialise_tagged_item(&lg, (void **) vp) == 1)
    {
	Vector *v = *vp;
	if (v->n && v->data)
	  lg=nvector_ts_deserialise(lg, (Varptr*)(&(v->data)),0,v->n,v->vtype);
	/* deserialise_item(&lg, &(v->data));*/
    }
    return lg;
}
void    Vector_ts_free(Vector * v)
{
  Varptr vp;
  vp.ptr_v=v->data;
  nvector_ts_free(vp,0,v->n,v->vtype);
  rfree(v);
  /*vector_free(v);*/
}
