/**@(#)List (List & Ddlist) handling (extra utilities).
 */

#include <stdio.h>
#include <tina/sys.h>

int     list_length(List * list)
{
    int     count;
    List   *ptr;

    for (ptr = list, count = 0; ptr != NULL; ptr = ptr->next, ++count);
    return (count);
}

int     dd_list_length(Ddlist * list)
{
    int     count;
    Ddlist *ptr;

    for (ptr = list, count = 0; ptr != NULL; ptr = ptr->next, ++count);
    return (count);
}

int     ddstr_length(Ddlist * start, Ddlist * end)
{
    int     count;
    Ddlist *ptr;

    for (ptr = start, count = 0; ptr != end; ptr = ptr->next, ++count);
    if (end != NULL)
	++count;
    return (count);
}

void    proplist_pprint(FILE * fp, List * plist)
{
    List   *ptr;
    Prop   *prop;

    (void) fprintf(fp, "Begin proplist:\n");
    for (ptr = plist; ptr != NULL; ptr = ptr->next)
    {
	prop = (Prop *) ptr->to;
	(void) fprintf(fp, "type %ld ptr %d\n", prop->type, (long) prop->to);
    }
    (void) fprintf(fp, "End proplist:\n");
}

List   *list_nth(List * list, int n)
{
    int     count;
    List   *ptr;

    for (ptr = list, count = 0; count < n; ptr = ptr->next, ++count);
    return (ptr);
}

Ddlist *ddlist_nth(Ddlist * ddlist, int n)
{
    int     count;
    Ddlist *ptr;

    for (ptr = ddlist, count = 0; count < n; ptr = ptr->next, ++count);
    return (ptr);
}
