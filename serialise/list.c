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

void List_ts_print(List *l)
{
  mprintf("list start{ ");
  while(l)
  {
    mprintf("struct list{ int <type>%d, POINTER *<next> 0x%x; POINTER *<to>0x%x\n",
	    l->type,l->next,l->to);
    ts_print_gen(l->to);
    mprintf("}list;");
    l=l->next;
    if(l && !repeatp_checker(l))
    { mprintf("Repeated list element\n");
      l=NULL;
    }
  }
  mprintf("}list end;");
}

List *List_ts_serialise(List * lg, List *lin)
{
  List *l=lin;
  while(l)
  {
    if(serialise_tagged_item(&lg, l, sizeof(List)))
    {
      lg=ts_serialise_gen(lg,l->to);
      l=l->next;
    }
    else l=NULL;
  }
  return lg;
}

List *List_ts_deserialise(List * lg, List **lin)
{
  List **l=lin;
  do
  {
    if(deserialise_tagged_item(&lg, (void**)l))
    {
      if((*l)->to)
	lg=ts_deserialise_gen(lg,&((*l)->to));
      l=&((*l)->next);
    }
    else
      break;
  }while(*l);
  return lg;
}

void List_ts_free(List *l)
{
  List *l2=l;

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
