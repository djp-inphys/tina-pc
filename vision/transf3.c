/**@(#)Functions for manipulating 3D transforms
 **/

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>
#ifdef _PCC
#include <memory.h>
#endif

Transf3 *transf3_alloc(unsigned int type)
{
    Transf3 *transf = ts_ralloc(Transf3);

    transf->type = type;
    transf->label = new_label();
    transf->T = trans3_unit();
    transf->props = NULL;
    return (transf);
}

Transf3 *transf3_make(Transform3 T, int type)
{
    Transf3 *transf = ts_ralloc(Transf3);

    transf->type = type;
    transf->label = new_label();
    transf->T = T;
    transf->props = NULL;
    return (transf);
}

void    transf3_free(Transf3 * transf)
{
    if (transf == NULL)
	return;
    proplist_freelist(transf->props);
    rfree((void *) transf);
}

Transf3 *transf3_copy(Transf3 * transf)
{
    Transf3 *copy;
    List   *proplist_copy();

    if (transf == NULL)
	return (NULL);

    copy = ts_ralloc(Transf3);
    (void) memcpy((char *) copy, (char *) transf, sizeof(Transf3));
    copy->props = proplist_copy(transf->props);
    return (copy);
}

int     transf3_number(List * transfs)
{
    List   *ptr;
    int     n = 0;

    for (ptr = transfs; ptr != NULL; ptr = ptr->next)
	((Transf3 *) (ptr->to))->label = n++;
    return(n);
}
