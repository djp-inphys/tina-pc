/**@(#)Array handling. 2+ dimensions (1 dimension arrays are called vectors).
 * @(#)Allocation and freeing.
**/
#include <tina/sys.h>
#include <tina/sysfuncs.h>

static void *rec_array_alloc(int i, int n, unsigned int s, int *m1, int *m2)
{
    void  **vector;
    void   *nvector_alloc();
    int     j;

    if (i == n - 1)		/* use s to determine block size */
	return (nvector_alloc(m1[i], m2[i], s));

    vector = (void **) nvector_alloc(m1[i], m2[i], sizeof(void *));

    for (j = m1[i]; j < m2[i]; j++)
	vector[j] = rec_array_alloc(i + 1, n, s, m1, m2);

    return ((void *) vector);
}

void   *ndim_array_alloc(int n, unsigned int s, int *m1, int *m2)
/* No of dimensions */
/* element size */
/* m1 and m2 for each of the dimensions   */
{
    if (n == 0)
	return ((void *) 0);
    return (rec_array_alloc(0, n, s, m1, m2));
}


static void rec_array_free(void **vector, int i, int n, unsigned int s, int *m1, int *m2)
{
    void    nvector_free();
    int     j;

    if (i == n - 1)
    {
	nvector_free((void *) vector, m1[i], s);
	return;
    }
    for (j = m1[i]; j < m2[i]; j++)
	rec_array_free((void **) vector[i], i + 1, n, s, m1, m2);

    nvector_free((void *) vector, m1[i], sizeof(void *));
}

void    ndim_array_free(void *array, int n, unsigned int s, int *m1, int *m2)
/* previously created array */
/* number of dimensions */
/* element size */
/* m1 and m2 for each of the dimensions */

{
    if (n)
    {
	rec_array_free((void **) array, 0, n, s, m1, m2);
    }
}

#ifndef ANSIFYING
#ifdef __STRICT_ANSI__


/* Variable argument variable dimension array allocation. array =
 * vdim_array_alloc(n, s, a1, b1, c1, d1, ..., a2, b2, c2, d2, ...); */
/* No of dimensions */
/* element size */
void   *vdim_array_alloc(int n, unsigned int s,...)
{
    va_list ap;
    int    *m1, *m2;		/* m1 and m2 for each of the dimensions */

    void   *array;
    int     i;

    if (n == 0)
	return ((void *) 0);

    m1 = (int *) ralloc((unsigned) n * sizeof(int));
    m2 = (int *) ralloc((unsigned) n * sizeof(int));
    va_start(ap, s);
    for (i = 0; i != n; ++i)
	m1[i] = va_arg(ap, int);
    for (i = 0; i != n; ++i)
	m2[i] = va_arg(ap, int);
    va_end(ap);

    array = rec_array_alloc(0, n, s, m1, m2);
    rfree((void *) m1);
    rfree((void *) m2);
    return (array);
}


/* array previously created array */
/* n No of dimensions */
/* s element size */
void    vdim_array_free(void *array, int n, unsigned int s,...)
{
    va_list ap;
    int    *m1, *m2;		/* m1 and m2 for each of the dimensions */
    int     i;

    if (n == 0)
	return;

    m1 = (int *) ralloc((unsigned) n * sizeof(int));
    m2 = (int *) ralloc((unsigned) n * sizeof(int));
    va_start(ap, s);

    for (i = 0; i != n; ++i)
	m1[i] = va_arg(ap, int);
    for (i = 0; i != n; ++i)
	m2[i] = va_arg(ap, int);
    va_end(ap);

    rec_array_free((void **) array, 0, n, s, m1, m2);
    rfree((void *) m1);
    rfree((void *) m2);
}

#else

/* Variable argument variable dimension array allocation. array =
 * vdim_array_alloc(n, s, a1, b1, c1, d1, ..., a2, b2, c2, d2, ...); */
void   *vdim_array_alloc(n, s, va_alist)
int     n;			/* No of dimensions */
unsigned int s;			/* element size */

va_dcl				/* m1 and m2 for each of the dimensions */
{
    va_list ap;
    int    *m1, *m2;
    void   *array;
    int     i;

    if (n == 0)
	return ((void *) 0);

    m1 = (int *) ralloc((unsigned) n * sizeof(int));
    m2 = (int *) ralloc((unsigned) n * sizeof(int));
    va_start(ap);
    for (i = 0; i != n; ++i)
	m1[i] = va_arg(ap, int);
    for (i = 0; i != n; ++i)
	m2[i] = va_arg(ap, int);
    va_end(ap);

    array = rec_array_alloc(0, n, s, m1, m2);
    rfree((void *) m1);
    rfree((void *) m2);
    return (array);
}

void    vdim_array_free(array, n, s, va_alist)
void   *array;			/* previously created array */
int     n;			/* No of dimensions */
unsigned int s;			/* element size */

va_dcl				/* m1 and m2 for each of the dimensions */
{
    va_list ap;
    int    *m1, *m2;
    int     i;

    if (n == 0)
	return;

    m1 = (int *) ralloc((unsigned) n * sizeof(int));
    m2 = (int *) ralloc((unsigned) n * sizeof(int));
    va_start(ap);
    for (i = 0; i != n; ++i)
	m1[i] = va_arg(ap, int);
    for (i = 0; i != n; ++i)
	m2[i] = va_arg(ap, int);
    va_end(ap);

    rec_array_free((void **) array, 0, n, s, m1, m2);
    rfree((void *) m1);
    rfree((void *) m2);
}

#endif				/* __STRICT_ANSI__ */
#endif				/* ANSIFYING */
