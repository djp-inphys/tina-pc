#include <stdio.h>
#include <stdlib.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

void    nvector_ts_print(Varptr d, int l, int h, Vartype type)
{
    int     i;

    mprintf("nvector {Low %i high %i type ", l, h);
    format_vtype(type);
    mprintf("; {");
    switch (type)
    {
    case char_v:
	for (i = l; i < h; mprintf("0x%x,"
				   ,d.char_v[i]), i++);
	break;
    case uchar_v:
	for (i = l; i < h; mprintf("%c,",
				   d.uchar_v[i]), i++);
	break;
    case short_v:
	for (i = l; i < h; mprintf("%hi,",
				   d.short_v[i]), i++);
	break;
    case ushort_v:
	for (i = l; i < h; mprintf("%hu,",
				   d.ushort_v[i]), i++);
	break;
    case int_v:
	for (i = l; i < h; mprintf("%i,",
				   d.int_v[i]), i++);
	break;
    case uint_v:
	for (i = l; i < h; mprintf("%u,",
				   d.uint_v[i]), i++);
	break;
    case float_v:
	for (i = l; i < h; mprintf("%g,",
				   d.float_v[i]), i++);
	break;
    case double_v:
	for (i = l; i < h; mprintf("%g,",
				   d.double_v[i]), i++);
	break;
    case complex_v:
	/** BUGFIX Julian Briggs 12/11/93: was
	  for (i = l; i < h; ts_print_gen(d.complex_v[i]), i++);**/
	for (i = l; i < h; ts_print_gen(&d.complex_v[i]), i++);
	break;
    case ptr_v:
	for (i = l; i < h; i++)
	 {
	   mprintf("*0x%x ",d.ptr_v[i]);
	   ts_print_gen(d.ptr_v[i]);
	 }
	break;
    }
    mprintf("}};");
}

List   *nvector_ts_serialise(List * lg, Varptr d, int l, int h, Vartype type)
{
  int i;

  serialise_item(&lg, d.char_v + var_size(type) * l, var_size(type) * (h - l));
  if(type==ptr_v)
   for (i = l; i < h; i++)
    if(d.ptr_v[i])
     lg=ts_serialise_gen(lg,d.ptr_v[i]);
  return lg;
}

List   *nvector_ts_deserialise(List * lg, Varptr * d, int l, int h, Vartype type)
{
  int     i;
  
  deserialise_item(&lg, (void **) d);
  d->char_v -= l * var_size(type);
  switch (type)
   {
   case short_v:
   case ushort_v:
     for (i = l; i < h; i++)
      short_swap((char *) (d->short_v + i));
     break;
   case int_v:
   case uint_v:
   case float_v:
   case complex_v:
     for (i = l; i < h; i++)
      word_swap((char *) (d->int_v + i));
     break;
   case ptr_v:
     for (i = l; i < h; i++)
      if(d->ptr_v[i])
       lg=ts_deserialise_gen(lg, &(d->ptr_v[i]));
     break;
   case double_v:
     for (i = l; i < h; i++)
      long_swap((char *) (d->double_v + i));
     break;
   }
  return lg;
}
void nvector_ts_free(Varptr d, int l, int h, Vartype type)
{
  int i;

  if(type==ptr_v)
    {
      for (i = l; i < h; i++)
	if(d.ptr_v[i])
	  ts_free_gen(d.ptr_v[i]);
    }
  else
    nvector_free(d.char_v,l,var_size(type));
}
