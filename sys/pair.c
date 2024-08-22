/**@(#)Pair handling. Pair is {int type1; int type2; void *to1; void *to2;}
**/

#include <tina/sys.h>
#include <tina/sysfuncs.h>

Pair   *pair_alloc(void *ptr1, int type1, void *ptr2, int type2)
{
    Pair   *pair;

    pair = ts_ralloc(Pair);
    pair->type1 = type1;
    pair->to1 = ptr1;
    pair->type2 = type2;
    pair->to2 = ptr2;
    return (pair);
}

Pair   *pair_make(void *ptr1, int type1, void *ptr2, int type2)
{
    Pair   *pair;

    pair = ts_ralloc(Pair);
    pair->type1 = type1;
    pair->to1 = ptr1;
    pair->type2 = type2;
    pair->to2 = ptr2;
    return (pair);
}
