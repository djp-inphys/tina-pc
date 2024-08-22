/**@(#)Array & Vector copying. (int verion)
 * Ie copy displaced vectors and arrays, casting as necessary.
 */

#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>

void    error();

/* make int copy of displaced vector of unsigned chars */

int    *ivector_uccopy(unsigned char *v, int n1, int n2)
{
    int    *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("ivector_uccopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (int *) ralloc((unsigned) (n2 - n1) * sizeof(int)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = v[i];
    }
    return (ptr);
}

/* make int copy of displaced array of unsigned chars */

int   **iarray_uccopy(unsigned char **a, int m1, int n1, int m2, int n2)
{
    int   **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("iarray_uccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("iarray_uccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (int **) ralloc((unsigned) m * sizeof(int *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (int *) ralloc((unsigned) n * sizeof(int)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make int copy of displaced lower triangle of unsigned chars */

int   **ilower_uccopy(unsigned char **a, int m1, int n1, int m2, int n2)
{
    int   **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("ilower_uccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("ilower_uccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (int **) ralloc((unsigned) m * sizeof(int *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (int *) ralloc((unsigned) n * sizeof(int)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make int copy of displaced upper triangle of unsigned chars */

int   **iupper_uccopy(unsigned char **a, int n1, int n2)
{
    int   **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("iupper_uccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("iupper_uccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (int **) ralloc((unsigned) n * sizeof(int *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (int *) ralloc((unsigned) (n2 - i) * sizeof(int)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make int copy of displaced vector of chars */

int    *ivector_ccopy(char *v, int n1, int n2)
{
    int    *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("ivector_ccopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (int *) ralloc((unsigned) (n2 - n1) * sizeof(int)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = v[i];
    }
    return (ptr);
}

/* make int copy of displaced array of chars */

int   **iarray_ccopy(char **a, int m1, int n1, int m2, int n2)
{
    int   **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("iarray_ccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("iarray_ccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (int **) ralloc((unsigned) m * sizeof(int *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (int *) ralloc((unsigned) n * sizeof(int)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make int copy of displaced lower triangle of chars */

int   **ilower_ccopy(char **a, int m1, int n1, int m2, int n2)
{
    int   **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("ilower_ccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("ilower_ccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (int **) ralloc((unsigned) m * sizeof(int *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (int *) ralloc((unsigned) n * sizeof(int)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make int copy of displaced upper triangle of chars */

int   **iupper_ccopy(char **a, int n1, int n2)
{
    int   **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("iupper_ccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("iupper_ccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (int **) ralloc((unsigned) n * sizeof(int *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (int *) ralloc((unsigned) (n2 - i) * sizeof(int)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make int copy of displaced vector of shorts */

int    *ivector_scopy(short int *v, int n1, int n2)
{
    int    *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("ivector_scopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (int *) ralloc((unsigned) (n2 - n1) * sizeof(int)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = v[i];
    }
    return (ptr);
}

/* make int copy of displaced array of shorts */

int   **iarray_scopy(short int **a, int m1, int n1, int m2, int n2)
{
    int   **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("iarray_scopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("iarray_scopy: zero array size", warning);
	return (NULL);
    }
    ptr = (int **) ralloc((unsigned) m * sizeof(int *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (int *) ralloc((unsigned) n * sizeof(int)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make int copy of displaced lower triangle of shorts */

int   **ilower_scopy(short int **a, int m1, int n1, int m2, int n2)
{
    int   **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("ilower_scopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("ilower_scopy: zero array size", warning);
	return (NULL);
    }
    ptr = (int **) ralloc((unsigned) m * sizeof(int *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (int *) ralloc((unsigned) n * sizeof(int)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make int copy of displaced upper triangle of shorts */

int   **iupper_scopy(short int **a, int n1, int n2)
{
    int   **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("iupper_scopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("iupper_scopy: zero array size", warning);
	return (NULL);
    }
    ptr = (int **) ralloc((unsigned) n * sizeof(int *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (int *) ralloc((unsigned) (n2 - i) * sizeof(int)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make int copy of displaced vector of floats */

int    *ivector_icopy(int *v, int n1, int n2)
{
    int    *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("ivector_icopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (int *) ralloc((unsigned) (n2 - n1) * sizeof(int)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = v[i];
    }
    return (ptr);
}

/* make int copy of displaced array of floats */

int   **iarray_icopy(int **a, int m1, int n1, int m2, int n2)
{
    int   **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("iarray_icopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("iarray_icopy: zero array size", warning);
	return (NULL);
    }
    ptr = (int **) ralloc((unsigned) m * sizeof(int *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (int *) ralloc((unsigned) n * sizeof(int)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make int copy of displaced lower triangle of floats */

int   **ilower_icopy(int **a, int m1, int n1, int m2, int n2)
{
    int   **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("ilower_icopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("ilower_icopy: zero array size", warning);
	return (NULL);
    }
    ptr = (int **) ralloc((unsigned) m * sizeof(int *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (int *) ralloc((unsigned) n * sizeof(int)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make int copy of displaced upper triangle of floats */

int   **iupper_icopy(int **a, int n1, int n2)
{
    int   **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("iupper_icopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("iupper_icopy: zero array size", warning);
	return (NULL);
    }
    ptr = (int **) ralloc((unsigned) n * sizeof(int *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (int *) ralloc((unsigned) (n2 - i) * sizeof(int)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make int copy of displaced vector of floats */

int    *ivector_fcopy(float *v, int n1, int n2)
{
    int    *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("ivector_fcopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (int *) ralloc((unsigned) (n2 - n1) * sizeof(int)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = (int) v[i];
    }
    return (ptr);
}

/* make int copy of displaced array of floats */

int   **iarray_fcopy(float **a, int m1, int n1, int m2, int n2)
{
    int   **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("iarray_fcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("iarray_fcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (int **) ralloc((unsigned) m * sizeof(int *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (int *) ralloc((unsigned) n * sizeof(int)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = (int) a[i][j];
    return (ptr);
}

/* make int copy of displaced lower triangle of floats */

int   **ilower_fcopy(float **a, int m1, int n1, int m2, int n2)
{
    int   **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("ilower_fcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("ilower_fcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (int **) ralloc((unsigned) m * sizeof(int *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (int *) ralloc((unsigned) n * sizeof(int)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = (int) a[i][j];
    return (ptr);
}

/* make int copy of displaced upper triangle of floats */

int   **iupper_fcopy(float **a, int n1, int n2)
{
    int   **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("iupper_fcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("iupper_fcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (int **) ralloc((unsigned) n * sizeof(int *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (int *) ralloc((unsigned) (n2 - i) * sizeof(int)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = (int) a[i][j];
    return (ptr);
}

/* make int copy of displaced vector of doubles */

int    *ivector_dcopy(double *v, int n1, int n2)
{
    int    *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("ivector_dcopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (int *) ralloc((unsigned) (n2 - n1) * sizeof(int)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = (int) v[i];
    }
    return (ptr);
}

/* make int copy of displaced array of doubles */

int   **iarray_dcopy(double **a, int m1, int n1, int m2, int n2)
{
    int   **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("iarray_dcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("iarray_dcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (int **) ralloc((unsigned) m * sizeof(int *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (int *) ralloc((unsigned) n * sizeof(int)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = (int) a[i][j];
    return (ptr);
}

/* make int copy of displaced lower triangle of doubles */

int   **ilower_dcopy(double **a, int m1, int n1, int m2, int n2)
{
    int   **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("ilower_dcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("ilower_dcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (int **) ralloc((unsigned) m * sizeof(int *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (int *) ralloc((unsigned) n * sizeof(int)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = (int) a[i][j];
    return (ptr);
}

/* make int copy of displaced upper triangle of doubles */

int   **iupper_dcopy(double **a, int n1, int n2)
{
    int   **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("iupper_dcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("iupper_dcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (int **) ralloc((unsigned) n * sizeof(int *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (int *) ralloc((unsigned) (n2 - i) * sizeof(int)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = (int) a[i][j];
    return (ptr);
}
