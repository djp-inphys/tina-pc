/**@(#)Vector (1 dimension array) handling.
 * @(#)Allocate and free displaced vectors &arrays.
 * @(#)Elements (of general size) are initialised to zero.
 */

#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include  <tina/dynamic.h>

#ifdef __STRICT_ANSI__
#include  <string.h>
#elif __GNUC__
#ifndef ANSIFYING
void   *memcpy();
void   *memset();

#endif				/* ANSIFYING */
#else
char   *memcpy();
char   *memset();

#endif

/* Displaced vector of size s v[i]: n1 <= i < n2 */
void   *nvector_alloc(int n1, int n2, size_t size)
{
    char   *v = NULL;
    int     n = n2 - n1;

    if (n >= 1)
    {
	v = ((char *) ralloc((size_t) n * size)) - (n1 * size);
    }
    return (void *) v;
}

void   *nvector_copy(char *v, int n1, int n2, unsigned int s)


/* element size */
{
    char   *w;
    int     n = n2 - n1;

    if (v == NULL || n < 1 || s < 1)
	return (NULL);
    w = (char *) nvector_alloc(n1, n2, s);
    (void) memcpy(w + n1 * (int) s, v + n1 * (int) s, n * (int) s);
    return ((void *) w);
}

void    nvector_copy_inplace(char *w, char *v, int n1, int n2, unsigned int s)
/* s: element size */
{
    int     n = n2 - n1;

    if (w == NULL || v == NULL || n < 1 || s < 1)
	return;
    (void) memcpy(w + n1 * (int) s, v + n1 * (int) s, n * (int) s);
}

void    nvector_zero_inplace(char *v, int n1, int n2, unsigned int s)
/* element size */
{
    int     n = n2 - n1;

    if (v == NULL || n < 1 || s < 1)
	return;
    (void) memset(v + n1 * (int) s, 0, n * (int) s);
}

void    nvector_free(void *v, int n1, unsigned int s)
{
    rfree((void *) ((char *) v + n1 * s));
}

/* displaced array, element size s a[i][j]: m1 <=i < m2, n1 <= j < n2 */
void  **narray_alloc(int m1, int n1, int m2, int n2, unsigned int s)
{
    char  **a;
    int     m = m2 - m1, n = n2 - n1;
    int     i;

    if (m < 1 || n < 1 || s < 1)
	return (NULL);
    a = (char **) nvector_alloc(m1, m2, (int) sizeof(char *));
    for (i = m1; i < m2; ++i)
	a[i] = (char *) nvector_alloc(n1, n2, s);
    return ((void **) a);
}

void  **narray_copy(char **a, int m1, int n1, int m2, int n2, unsigned int s)
{
    char  **b;
    int     m = m2 - m1, n = n2 - n1;
    int     i;

    if (a == NULL || m < 1 || n < 1 || s < 1)
	return (NULL);
    b = (char **) narray_alloc(m1, n1, m2, n2, s);
    for (i = m1; i < m2; ++i)
	nvector_copy_inplace(b[i], a[i], n1, n2, s);
    return ((void **) b);
}

void    narray_copy_inplace(char **b, char **a, int m1, int n1, int m2, int n2, unsigned int s)
{
    int     m = m2 - m1, n = n2 - n1;
    int     i;

    if (b == NULL || a == NULL || m < 1 || n < 1 || s < 1)
	return;
    for (i = m1; i < m2; ++i)
	nvector_copy_inplace(b[i], a[i], n1, n2, s);
}

void    narray_zero_inplace(char **a, int m1, int n1, int m2, int n2, unsigned int s)
{
    int     m = m2 - m1, n = n2 - n1;
    int     i;

    if (a == NULL || m < 1 || n < 1 || s < 1)
	return;
    for (i = m1; i < m2; ++i)
	nvector_zero_inplace(a[i], n1, n2, s);
}

/* ARGSUSED Quieten Lint */
void    narray_free(char **a, int m1, int n1, int m2, int n2, unsigned int s)
{
    int     i;

    if (a == NULL)
	return;
    for (i = m1; i < m2; ++i)
	nvector_free((void *) a[i], n1, s);
    nvector_free((void *) a, m1, sizeof(char *));
}

/* displaced lower triangle, element size s a[i][j]: n1 <=i < n2, i <=
 * j < n2 */
void  **nlower_alloc(int n1, int n2, unsigned int s)
{
    char  **a;
    int     n = n2 - n1;
    int     i;

    if (n < 1 || s < 1)
	return (NULL);
    a = (char **) nvector_alloc(n1, n2, sizeof(char *));
    for (i = n1; i < n2; ++i)
	a[i] = (char *) nvector_alloc(n1, i + 1, s);
    return ((void **) a);
}

void  **nlower_copy(char **a, int n1, int n2, unsigned int s)
{
    char  **b;
    int     n = n2 - n1;
    int     i;

    if (a == NULL || n < 1 || s < 1)
	return (NULL);
    b = (char **) nlower_alloc(n1, n2, s);
    for (i = n1; i < n2; ++i)
	nvector_copy_inplace(b[i], a[i], n1, i + 1, s);
    return ((void **) b);
}

void    nlower_copy_inplace(char **b, char **a, int n1, int n2, unsigned int s)
{
    int     n = n2 - n1;
    int     i;

    if (b == NULL || a == NULL || n < 1 || s < 1)
	return;
    b = (char **) nlower_alloc(n1, n2, s);
    for (i = n1; i < n2; ++i)
	nvector_copy_inplace(b[i], a[i], n1, i + 1, s);
}

void    nlower_zero_inplace(char **a, int n1, int n2, unsigned int s)
{
    int     n = n2 - n1;
    int     i;

    if (a == NULL || n < 1 || s < 1)
	return;
    for (i = n1; i < n2; ++i)
	nvector_zero_inplace(a[i], n1, i + 1, s);
}

void    nlower_free(char **a, int n1, int n2, unsigned int s)
{
    int     i;

    if (a == NULL)
	return;
    for (i = n1; i < n2; ++i)
	nvector_free((void *) a[i], n1, s);
    nvector_free((void *) a, n1, sizeof(char *));
}

/* displaced upper triangle, element size s a[i][j]: n1 <=i < n2, 0 <=
 * j <= i */
void  **nupper_alloc(int n1, int n2, unsigned int s)
{
    char  **a;
    int     n = n2 - n1;
    int     i;

    if (n < 1 || s < 1)
	return (NULL);
    a = (char **) nvector_alloc(n1, n2, sizeof(char *));
    for (i = n1; i < n2; ++i)
	a[i] = (char *) nvector_alloc(i, n2, s);
    return ((void **) a);
}

void  **nupper_copy(char **a, int n1, int n2, unsigned int s)
{
    char  **b;
    int     n = n2 - n1;
    int     i;

    if (a == NULL || n < 1 || s < 1)
	return (NULL);
    b = (char **) nupper_alloc(n1, n2, s);
    for (i = n1; i < n2; ++i)
	nvector_copy_inplace(b[i], a[i], i, n2, s);
    return ((void **) b);
}

void    nupper_copy_inplace(char **b, char **a, int n1, int n2, unsigned int s)
{
    int     n = n2 - n1;
    int     i;

    if (b == NULL || a == NULL || n < 1 || s < 1)
	return;
    b = (char **) nupper_alloc(n1, n2, s);
    for (i = n1; i < n2; ++i)
	nvector_copy_inplace(b[i], a[i], i, n2, s);
}

void    nupper_zero_inplace(char **a, int n1, int n2, unsigned int s)
{
    int     n = n2 - n1;
    int     i;

    if (a == NULL || n < 1 || s < 1)
	return;
    for (i = n1; i < n2; ++i)
	nvector_zero_inplace(a[i], i, n2, s);
}

void    nupper_free(char **a, int n1, int n2, unsigned int s)
{
    int     i;

    if (a == NULL)
	return;
    for (i = n1; i < n2; ++i)
	nvector_free((void *) a[i], i, s);
    nvector_free((void *) a, n1, sizeof(char *));
}
