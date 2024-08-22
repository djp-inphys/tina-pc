/**@(#)Array & Vector copying. (char version)
 * Ie copy displaced vectors and arrays,  casting as necessary.
 */

#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>

void    error();

/* make char copy of displaced vector of unsigned chars */

char   *cvector_uccopy(unsigned char *v, int n1, int n2)
{
    char   *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("cvector_uccopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (char *) ralloc((unsigned) (n2 - n1) * sizeof(char)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = v[i];
    }
    return (ptr);
}

/* make char copy of displaced array of unsigned chars */

char  **carray_uccopy(unsigned char **a, int m1, int n1, int m2, int n2)
{
    char  **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("carray_uccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("carray_uccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (char **) ralloc((unsigned) m * sizeof(char *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (char *) ralloc((unsigned) n * sizeof(char)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make char copy of displaced lower triangle of unsigned chars */

char  **clower_uccopy(unsigned char **a, int m1, int n1, int m2, int n2)
{
    char  **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("clower_uccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("clower_uccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (char **) ralloc((unsigned) m * sizeof(char *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (char *) ralloc((unsigned) n * sizeof(char)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make char copy of displaced upper triangle of unsigned chars */

char  **cupper_uccopy(unsigned char **a, int n1, int n2)
{
    char  **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("cupper_uccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("cupper_uccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (char **) ralloc((unsigned) n * sizeof(char *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (char *) ralloc((unsigned) (n2 - i) * sizeof(char)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make char copy of displaced vector of chars */

char   *cvector_ccopy(char *v, int n1, int n2)
{
    char   *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("cvector_ccopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (char *) ralloc((unsigned) (n2 - n1) * sizeof(char)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = v[i];
    }
    return (ptr);
}

/* make char copy of displaced array of chars */

char  **carray_ccopy(char **a, int m1, int n1, int m2, int n2)
{
    char  **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("carray_ccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("carray_ccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (char **) ralloc((unsigned) m * sizeof(char *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (char *) ralloc((unsigned) n * sizeof(char)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make char copy of displaced lower triangle of chars */

char  **clower_ccopy(char **a, int m1, int n1, int m2, int n2)
{
    char  **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("clower_ccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("clower_ccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (char **) ralloc((unsigned) m * sizeof(char *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (char *) ralloc((unsigned) n * sizeof(char)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make char copy of displaced upper triangle of chars */

char  **cupper_ccopy(char **a, int n1, int n2)
{
    char  **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("cupper_ccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("cupper_ccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (char **) ralloc((unsigned) n * sizeof(char *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (char *) ralloc((unsigned) (n2 - i) * sizeof(char)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make char copy of displaced vector of shorts */

char   *cvector_scopy(short int *v, int n1, int n2)
{
    char   *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("cvector_scopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (char *) ralloc((unsigned) (n2 - n1) * sizeof(char)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = (char) v[i];
    }
    return (ptr);
}

/* make char copy of displaced array of shorts */

char  **carray_scopy(short int **a, int m1, int n1, int m2, int n2)
{
    char  **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("carray_scopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("carray_scopy: zero array size", warning);
	return (NULL);
    }
    ptr = (char **) ralloc((unsigned) m * sizeof(char *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (char *) ralloc((unsigned) n * sizeof(char)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = (char) a[i][j];
    return (ptr);
}

/* make char copy of displaced lower triangle of shorts */

char  **clower_scopy(short int **a, int m1, int n1, int m2, int n2)
{
    char  **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("clower_scopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("clower_scopy: zero array size", warning);
	return (NULL);
    }
    ptr = (char **) ralloc((unsigned) m * sizeof(char *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (char *) ralloc((unsigned) n * sizeof(char)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = (char) a[i][j];
    return (ptr);
}

/* make char copy of displaced upper triangle of shorts */

char  **cupper_scopy(short int **a, int n1, int n2)
{
    char  **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("cupper_scopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("cupper_scopy: zero array size", warning);
	return (NULL);
    }
    ptr = (char **) ralloc((unsigned) n * sizeof(char *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (char *) ralloc((unsigned) (n2 - i) * sizeof(char)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = (char) a[i][j];
    return (ptr);
}

/* make char copy of displaced vector of ints */

char   *cvector_icopy(int *v, int n1, int n2)
{
    char   *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("cvector_icopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (char *) ralloc((unsigned) (n2 - n1) * sizeof(char)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = v[i];
    }
    return (ptr);
}

/* make char copy of displaced array of ints */

char  **carray_icopy(int **a, int m1, int n1, int m2, int n2)
{
    char  **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("carray_icopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("carray_icopy: zero array size", warning);
	return (NULL);
    }
    ptr = (char **) ralloc((unsigned) m * sizeof(char *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (char *) ralloc((unsigned) n * sizeof(char)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make char copy of displaced lower triangle of ints */

char  **clower_icopy(int **a, int m1, int n1, int m2, int n2)
{
    char  **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("clower_icopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("clower_icopy: zero array size", warning);
	return (NULL);
    }
    ptr = (char **) ralloc((unsigned) m * sizeof(char *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (char *) ralloc((unsigned) n * sizeof(char)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make char copy of displaced upper triangle of ints */

char  **cupper_icopy(int **a, int n1, int n2)
{
    char  **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("cupper_icopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("cupper_icopy: zero array size", warning);
	return (NULL);
    }
    ptr = (char **) ralloc((unsigned) n * sizeof(char *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (char *) ralloc((unsigned) (n2 - i) * sizeof(char)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make char copy of displaced vector of floats */

char   *cvector_fcopy(float *v, int n1, int n2)
{
    char   *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("cvector_fcopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (char *) ralloc((unsigned) (n2 - n1) * sizeof(char)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = (char) v[i];
    }
    return (ptr);
}

/* make char copy of displaced array of floats */

char  **carray_fcopy(float **a, int m1, int n1, int m2, int n2)
{
    char  **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("carray_fcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("carray_fcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (char **) ralloc((unsigned) m * sizeof(char *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (char *) ralloc((unsigned) n * sizeof(char)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = (char) a[i][j];
    return (ptr);
}

/* make char copy of displaced lower triangle of floats */

char  **clower_fcopy(float **a, int m1, int n1, int m2, int n2)
{
    char  **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("clower_fcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("clower_fcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (char **) ralloc((unsigned) m * sizeof(char *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (char *) ralloc((unsigned) n * sizeof(char)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = (char) a[i][j];
    return (ptr);
}

/* make char copy of displaced upper triangle of floats */

char  **cupper_fcopy(float **a, int n1, int n2)
{
    char  **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("cupper_fcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("cupper_fcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (char **) ralloc((unsigned) n * sizeof(char *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (char *) ralloc((unsigned) (n2 - i) * sizeof(char)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = (char) a[i][j];
    return (ptr);
}

/* make char copy of displaced vector of doubles */

char   *cvector_dcopy(double *v, int n1, int n2)
{
    char   *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("cvector_dcopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (char *) ralloc((unsigned) (n2 - n1) * sizeof(char)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = (char) v[i];
    }
    return (ptr);
}

/* make char copy of displaced array of doubles */

char  **carray_dcopy(double **a, int m1, int n1, int m2, int n2)
{
    char  **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("carray_dcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("carray_dcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (char **) ralloc((unsigned) m * sizeof(char *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (char *) ralloc((unsigned) n * sizeof(char)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = (char) a[i][j];
    return (ptr);
}

/* make char copy of displaced lower triangle of doubles */

char  **clower_dcopy(double **a, int m1, int n1, int m2, int n2)
{
    char  **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("clower_dcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("clower_dcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (char **) ralloc((unsigned) m * sizeof(char *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (char *) ralloc((unsigned) n * sizeof(char)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = (char) a[i][j];
    return (ptr);
}

/* make char copy of displaced upper triangle of doubles */

char  **cupper_dcopy(double **a, int n1, int n2)
{
    char  **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("cupper_dcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("cupper_dcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (char **) ralloc((unsigned) n * sizeof(char *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (char *) ralloc((unsigned) (n2 - i) * sizeof(char)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = (char) a[i][j];
    return (ptr);
}
