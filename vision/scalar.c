/**@(#)
**/
/* scalar.c functions for manipulating scalar quantities
 * 
 * typedef struct scalar { int type; int label; float val; struct list
 * *props; } Scalar;
 * 
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>
#ifdef _PCC
#include <memory.h>
#endif

Scalar *scalar_alloc(unsigned int type)
{
    Scalar *scalar = ts_ralloc(Scalar);

    scalar->type = type;
    scalar->label = new_label();
    scalar->val = (float) 0.0;
    scalar->props = NULL;
    return (scalar);
}

Scalar *scalar_make(double val, int type)
{
    Scalar *scalar = ts_ralloc(Scalar);

    scalar->type = type;
    scalar->label = new_label();
    scalar->val = (float) val;
    scalar->props = NULL;
    return (scalar);
}

void    scalar_free(Scalar * scalar)
{
    if (scalar == NULL)
	return;
    proplist_freelist(scalar->props);
    rfree((void *) scalar);
}

Scalar *scalar_copy(Scalar * scalar)
{
    Scalar *copy;
    List   *proplist_copy();

    if (scalar == NULL)
	return (NULL);

    copy = ts_ralloc(Scalar);
    (void) memcpy((char *) copy, (char *) scalar, sizeof(Scalar));
    copy->props = proplist_copy(scalar->props);
    return (copy);
}

int     scalar_number(List * scalars)
{
    List   *lptr;
    int     n = 0;

    for (lptr = scalars; lptr != NULL; lptr = lptr->next)
	((Scalar *) (lptr->to))->label = n++;
    return(n);
}
