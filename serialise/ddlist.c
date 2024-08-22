#include <stdio.h>
#include <stdlib.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/genfuncs.h>
void    ts_free_gen(void *data);
void    ts_print_gen(void *data);
List   *ts_deserialise_gen (List * lg, void **data);
List   *ts_serialise_gen(List * lg, void *d);
int     deserialise_tagged_item (List ** lgp, void **data);
int     serialise_tagged_item(List ** lgp, void *data, size_t s);

void Ddlist_ts_print(Ddlist *l)
{
  mprintf("ddlist start{");
  while(l)
  {
    mprintf("struct ddlist{ int <type>%d, POINTER *<next>0x%x, "
	    "POINTER *<last>0x%x, POINTER *<to>",
	    l->type,l->next,l->last);
    ts_print_gen(l->to);
    mprintf("}ddlist; ");
    l=l->next;
    if(l && !repeatp_checker(l))
    { mprintf("Repeated list element\n");
      l=NULL;
    }
  }
  mprintf("}ddlist end ;");
}

List *Ddlist_ts_serialise(List * lg, Ddlist *l)
{
  while(l)
  {
    if(serialise_tagged_item(&lg, l, sizeof(List)))
    {
      lg=ts_serialise_gen(lg,l->to);
      lg=Ddlist_ts_serialise(lg,l->last);
      l=l->next;
    }
    else break;
  }
  return lg;
}

List *Ddlist_ts_deserialise(List * lg, Ddlist **l)
{
  do
  {
    if(deserialise_tagged_item(&lg, (void**)l))
    {
      if((*l)->to)
	lg=ts_deserialise_gen(lg,&((*l)->to));
      if((*l)->last)
	lg=Ddlist_ts_deserialise(lg,&((*l)->last));
      l=&((*l)->next);
    }
    else break;
  }while(*l);
  return lg;
}
  
void Ddlist_ts_free(Ddlist *l)
{
  Ddlist *l2=l;

  while(l)
  {
    l2=l->next;
    ts_free_gen(l->to);
    rfree(l);
    if(l2 && !repeatp_checker(l2))
      l=NULL;
    else
      l=l2;
  }
}
