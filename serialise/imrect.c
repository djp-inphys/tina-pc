#include <stdio.h>
#include <stdlib.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>

void    narray_ts_print(Varptrptr d, int m1, int n1, int m2, int n2, Vartype type);
List   *narray_ts_serialise(List * lg, Varptrptr d,
		        int m1, int n1, int m2, int n2, Vartype type);
List   *narray_ts_deserialise(List * lg, Varptrptr * d,
		        int m1, int n1, int m2, int n2, Vartype type);

void    Imrect_ts_print(Imrect * im)
{
    Varptrptr vp;

    ts_print(im);
    vp.char_v = (char **) im->data;
    mprintf(" _extra_ {");
    narray_ts_print(vp,
		    im->region->ly, im->region->lx,
		    im->region->uy, im->region->ux,
		    im->vtype);
    mprintf("}Imrect;");
}

List   *Imrect_ts_serialise(List * lg, Imrect * im)
{
    Varptrptr vp;

    vp.char_v = (char **) im->data;
    if (serialise_tagged_item(&lg, im, sizeof(Imrect)) == 1)
	if (im->data)		/* any image data? */
	    lg = narray_ts_serialise(lg, vp,
				     im->region->ly, im->region->lx,
				     im->region->uy, im->region->ux,
				     im->vtype);
    return lg;
}

List   *Imrect_ts_deserialise(List * lg, Imrect ** im)
{
    if (deserialise_tagged_item(&lg, (void **) im) == 1)
    {
	Imrect *i = *im;

	if (i->data)		/* was there any data? */
	{
	    Varptrptr *vpp;

	    vpp = (Varptrptr *) & (i->data);
	    lg = narray_ts_deserialise(lg, vpp,
				       i->region->ly, i->region->lx,
				       i->region->uy, i->region->ux,
				       i->vtype);
	}
    }
    return lg;
}

void    Imrect_ts_free(Imrect * im)
{
  ts_free_gen(im->props);
  narray_free(im->data,
	      im->region->ly, im->region->lx,
	      im->region->uy, im->region->ux,
	      var_size(im->vtype));
  ts_free_gen(im->region);
  rfree(im);
}
