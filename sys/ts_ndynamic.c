/**@(#)Vector (1 dimension array) handling for Tstructs
 * @(#)Allocate and free displaced vectors & arrays.
 * @(#)Elements (of general size) are initialised to zero.
 */

#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/dynamic.h>

/* Allocate and tag multiple Tina structures */
void   *ts_nralloc_fn(int n, size_t size, Ts_id ts_id)
{
    char   *structure = (char *) ralloc(n * size);

    while (n--)
    {
	*(Ts_id *) (structure + n * size) = ts_id;
    }

    return (void *) structure;
}

/* Generic tagged structure create function */
void   *ts_ralloc_fn(size_t size, Ts_id ts_id)
{
    void   *structure = (void *) ralloc(size);

    *(Ts_id *) structure = ts_id;
    return structure;
}

/* Displaced array of Tstruct's whose type is coded by ts_id.
 * vector[i]: n1 <= i < n2 */
void   *ts_nvector_alloc_fn(int n1, int n2, size_t size, Ts_id ts_id)
{
    return ((n1 < n2) ?
	  ((char *) ts_nralloc_fn((n2 - n1), size, ts_id) - n1 * size)
	    : (NULL));
}

/* Displaced array of Tstruct's whose type is coded by ts_id.
 * array[i][j]: m1 <= i < m2, n1 <= j < n2 */
void  **ts_narray_alloc_fn(int m1, int n1, int m2, int n2, size_t size, Ts_id ts_id)
{
    int     i;
    void  **array = NULL;

    if (m1 < m2 && n1 < n2)
    {
	array = (void **) nvector_alloc(m1, m2, sizeof(void *));
	for (i = m1; i < m2; ++i)
	{
	    array[i] = ts_nvector_alloc_fn(n1, n2, size, ts_id);
	}
    }
    return array;
}

/* Displaced lower triangle of Tstruct's whose type is coded by ts_id.
 * Element size s a[i][j]: n1 <=i < n2, i <= j < n2. */
void  **ts_nlower_alloc_fn(int n1, int n2, size_t size, Ts_id ts_id)
{
    char  **a;
    int     n = n2 - n1;
    int     i;

    if (n < 1)
	return (NULL);
    a = (char **) nvector_alloc(n1, n2, sizeof(char *));
    for (i = n1; i < n2; ++i)
	a[i] = (char *) ts_nvector_alloc_fn(n1, i + 1, size, ts_id);
    return ((void **) a);
}

/* Displaced upper triangle of Tstruct's whose type is coded by ts_id.
 * Element size s a[i][j]: n1 <=i < n2, i <= j < n2. */
void  **ts_nupper_alloc_fn(int n1, int n2, size_t size, Ts_id ts_id)
{
    char  **a;
    int     n = n2 - n1;
    int     i;

    if (n < 1)
	return (NULL);
    a = (char **) nvector_alloc(n1, n2, sizeof(char *));
    for (i = n1; i < n2; ++i)
	a[i] = (char *) ts_nvector_alloc_fn(i, n2, size, ts_id);
    return ((void **) a);
}
