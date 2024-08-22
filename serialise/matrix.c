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

static void format_header(Matrix * mat)
{
  /*    format("matrix  ");*/
  format_shape(mat->shape);
  format(" %d by %d  of ", mat->m, mat->n);
  format_vtype(mat->vtype);
  format(";");
}
void    Matrix_ts_print(Matrix * m)
{
  int i;
  mprintf("struct matrix { ");
  if(m)
   {
     Varptr  v;
     
     /* format_header(m);*/
     if (m->el.char_v)	/* data for this row? */
      {
	v.ptr_v = (void **) m->el.char_v;
	for (i = 0; i < m->m; i++)
	 {
	   v.char_v = m->el.char_v[i];
	   switch (m->shape)
	    {
	    case matrix_symmetric:
	    case matrix_lower:
	      nvector_ts_print(v, 0, i + 1, m->vtype);
	      break;
	    case matrix_upper:	/* must handle offset array */
	      nvector_ts_print(v, i, m->m, m->vtype);
	      break;
	    case matrix_full:
	    default:
	      nvector_ts_print(v, 0, m->n, m->vtype);
	      break;
	    }
	 }
      }
   }
  mprintf("} matrix;");
}

List   *Matrix_ts_serialise(List * lg, Matrix * m)
{
  int     i;
  
  if (serialise_tagged_item(&lg, m, sizeof(Matrix)) == 1)
   {
     if (m->el.char_v)	/* data for this row? */
      {
	/* void **vpp;
	   vpp = (void**)(m->el.char_v);*/
	/* dont follow ptrs */
	/* lg = nvector_ts_serialise(lg, (Varptr)vpp, 0, m->m, int_v); */
	for (i = 0; i < m->m; i++)
	 {
	   Varptr vp;
	   vp.char_v = m->el.char_v[i];
	   switch (m->shape)
	    {
	    case matrix_symmetric:
	    case matrix_lower:
	      lg = nvector_ts_serialise(lg, vp, 0, i + 1, m->vtype);
	      break;
	    case matrix_upper:	/* must handle offset array */
	      lg = nvector_ts_serialise(lg, vp, i, m->m, m->vtype);
	      break;
	    case matrix_full:
	    default:
	      lg = nvector_ts_serialise(lg, vp, 0, m->n, m->vtype);
	      break;
	    }
	 }
      }
   }
  return lg;
  }
List   *Matrix_ts_deserialise(List * lg, Matrix ** mp)
{
  int     i;
  
  if (deserialise_tagged_item(&lg, (void **) mp) == 1)
   {
     Matrix *m = *mp;
     
     if (m->m && m->n && m->el.char_v)	/* was there any data here? */
      {
	/* Varptrptr *vpp;
	   vpp = &(m->el.char_v); */
	/* dont follow ptrs */
	/* lg = nvector_ts_deserialise(lg, (Varptr*)vpp, 0, m->m, int_v);*/
	m->el.char_v=nvector_alloc(0,m->m,sizeof(void*));
	for (i = 0; i < m->m; i++)
	 {
	   Varptr *vp;
	   vp = (Varptr *) &(m->el.char_v[i]);
	   switch (m->shape)
	    {
	    case matrix_symmetric:
	    case matrix_lower:
	      lg = nvector_ts_deserialise(lg, vp, 0, i + 1, m->vtype);
	      break;
	    case matrix_upper:
	      lg = nvector_ts_deserialise(lg, vp, i, m->m, m->vtype);
	      break;
	    case matrix_full:
	    default:
	      lg = nvector_ts_deserialise(lg, vp, 0, m->n, m->vtype);
	      break;
	    }
	 }
      }
   }
  return lg;
}
void    Matrix_ts_free(Matrix * m)
{
  int     i;
  
  if (m->el.char_v)	/* data for this row? */
    {
      for (i = 0; i < m->m; i++)
	{
	  Varptr vp;
	  vp.char_v = m->el.char_v[i];
	  switch (m->shape)
	    {
	    case matrix_symmetric:
	    case matrix_lower:
	      nvector_ts_free(vp, 0, i + 1, m->vtype);
	      break;
	    case matrix_upper:	/* must handle offset array */
	      nvector_ts_free(vp, i, m->m, m->vtype);
	      break;
	    case matrix_full:
	    default:
	      nvector_ts_free(vp, 0, m->n, m->vtype);
	      break;
	    }
	}
      rfree(m->el.char_v);
    }
  rfree(m);
}
