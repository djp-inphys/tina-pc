#include <stdio.h>
#include <stdlib.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>

void    ts_free_gen(void *data);
void    ts_print_gen(void *data);
List   *ts_deserialise_gen(List * lg, void **data);
List   *ts_serialise_gen(List * lg, void *d);
int     deserialise_tagged_item(List ** lgp, void **data);
int     serialise_tagged_item(List ** lgp, void *data, size_t s);

void    Prop_ts_print(Prop * p)
{
    ts_print(p);
    if (p->type == DP_INDEX || p->freefunc == NULL)
	mprintf("_extra_ { int <to>%d} Prop;", p->to);
    else
    {
	mprintf("_extra_ Ts *<to>{");
	ts_print_gen(p->to);
	mprintf("} Prop; ");
    }
}

List   *Prop_ts_serialise(List * lg, Prop * p)
{
    if (serialise_tagged_item(&lg, p, sizeof(Prop)) == 1)
	if (p->type != DP_INDEX && p->freefunc != NULL)
	    lg = ts_serialise_gen(lg, p->to);
    return lg;
}

List   *Prop_ts_deserialise(List * lg, Prop ** pp)
{
    if (deserialise_tagged_item(&lg, (void **) pp) == 1)
    {
	Prop   *p = *pp;

	if (p->to && p->type != DP_INDEX && p->freefunc != NULL)
	    lg = ts_deserialise_gen(lg, &p->to);
    }
    return lg;
}

void    Prop_ts_free(Prop * p)
{
    ts_free_gen(p);
    if (p->type != DP_INDEX && p->freefunc != NULL)
	ts_free_gen(p->to);
}
