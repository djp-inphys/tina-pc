#include <stdio.h>
#include <stdlib.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>

void    ts_free(void *data);
void    ts_print(void *data);
List   *ts_deserialise(List * lg, void **data);
List   *ts_serialise(List * lg, void *d);

void    Edge_conn_ts_print(Edge_conn * e)
{
    mprintf("struct edge_conn{unsigned short <count>%hu,"
	    "struct edgel *<c1>0x%x, struct edgel *<c2>0x%x,"
	    "struct list *<conns>0x%x}edge_conn",
	    e->count, e->c1, e->c2, e->conns);
}

List   *Edge_conn_ts_serialise(List * lg, Edge_conn * e)
{
    lg = ts_serialise(lg, e);
    return lg;
}

List   *Edge_conn_ts_deserialise(List * lg, Edge_conn ** e)
{

    lg = ts_deserialise(lg, (void **) e);
    return lg;
}

void    Edge_conn_ts_free(List * e)
{
    ts_free(e);
}
