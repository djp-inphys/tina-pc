/**@(#)General structure to wrap around data that does not possess property list
*/

#include <tina/sys.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>

extern int new_label();

Generic *generic_alloc(void)
{
    Generic *gen = ts_ralloc(Generic);

    gen->label = new_label();
    return (gen);
}

Generic *generic_make(void *ptr, int type)
{
    Generic *gen = ts_ralloc(Generic);

    gen->type = type;
    gen->label = new_label();
    gen->to = ptr;
    gen->props = NULL;
    return (gen);
}

void    generic_free(Generic * gen)
{
    if (gen == NULL)
	return;
    proplist_freelist(gen->props);
    rfree((void *) gen);
}

Generic *generic_copy(Generic * gen)
{
    Generic *copy;
    List   *proplist_copy();
	void *memcpy();

    if (gen == NULL)
	return (NULL);

    copy = ts_ralloc(Generic);
    (void *) memcpy((char *) copy, (char *) gen, sizeof(Generic));
    copy->props = proplist_copy(gen->props);
    return (copy);
}

int     generic_number(List * gens)
{
    List   *ptr;
    int     n = 0;

    for (ptr = gens; ptr != NULL; ptr = ptr->next)
	((Generic *) (ptr->to))->label = n++;
    return n;
}
