/**@(#)Array & Vector copying. (float version)
 * Ie copy displaced vectors and arrays, casting as necessary.
 */

#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>

void    error();

/* make float copy of displaced vector of unsigned chars */

float  *fvector_uccopy(unsigned char *v, int n1, int n2)
{
    float  *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("fvector_uccopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (float *) ralloc((unsigned) (n2 - n1) * sizeof(float)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = v[i];
    }
    return (ptr);
}

/* make float copy of displaced array of unsigned chars */

float **farray_uccopy(unsigned char **a, int m1, int n1, int m2, int n2)
{
    float **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("farray_uccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("farray_uccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (float **) ralloc((unsigned) m * sizeof(float *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (float *) ralloc((unsigned) n * sizeof(float)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make float copy of displaced lower triangle of unsigned chars */

float **flower_uccopy(unsigned char **a, int m1, int n1, int m2, int n2)
{
    float **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("flower_uccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("flower_uccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (float **) ralloc((unsigned) m * sizeof(float *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (float *) ralloc((unsigned) n * sizeof(float)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make float copy of displaced upper triangle of unsigned chars */

float **fupper_uccopy(unsigned char **a, int n1, int n2)
{
    float **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("fupper_uccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("fupper_uccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (float **) ralloc((unsigned) n * sizeof(float *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (float *) ralloc((unsigned) (n2 - i) * sizeof(float)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make float copy of displaced vector of chars */

float  *fvector_ccopy(char *v, int n1, int n2)
{
    float  *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("fvector_ccopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (float *) ralloc((unsigned) (n2 - n1) * sizeof(float)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = v[i];
    }
    return (ptr);
}

/* make float copy of displaced array of chars */

float **farray_ccopy(char **a, int m1, int n1, int m2, int n2)
{
    float **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("farray_ccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("farray_ccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (float **) ralloc((unsigned) m * sizeof(float *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (float *) ralloc((unsigned) n * sizeof(float)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make float copy of displaced lower triangle of chars */

float **flower_ccopy(char **a, int m1, int n1, int m2, int n2)
{
    float **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("flower_ccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("flower_ccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (float **) ralloc((unsigned) m * sizeof(float *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (float *) ralloc((unsigned) n * sizeof(float)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make float copy of displaced upper triangle of chars */

float **fupper_ccopy(char **a, int n1, int n2)
{
    float **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("fupper_ccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("fupper_ccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (float **) ralloc((unsigned) n * sizeof(float *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (float *) ralloc((unsigned) (n2 - i) * sizeof(float)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make float copy of displaced vector of shorts */

float  *fvector_scopy(short int *v, int n1, int n2)
{
    float  *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("fvector_scopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (float *) ralloc((unsigned) (n2 - n1) * sizeof(float)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = v[i];
    }
    return (ptr);
}

/* make float copy of displaced array of shorts */

float **farray_scopy(short int **a, int m1, int n1, int m2, int n2)
{
    float **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("farray_scopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("farray_scopy: zero array size", warning);
	return (NULL);
    }
    ptr = (float **) ralloc((unsigned) m * sizeof(float *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (float *) ralloc((unsigned) n * sizeof(float)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make float copy of displaced lower triangle of shorts */

float **flower_scopy(short int **a, int m1, int n1, int m2, int n2)
{
    float **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("flower_scopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("flower_scopy: zero array size", warning);
	return (NULL);
    }
    ptr = (float **) ralloc((unsigned) m * sizeof(float *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (float *) ralloc((unsigned) n * sizeof(float)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make float copy of displaced upper triangle of shorts */

float **fupper_scopy(short int **a, int n1, int n2)
{
    float **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("fupper_scopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("fupper_scopy: zero array size", warning);
	return (NULL);
    }
    ptr = (float **) ralloc((unsigned) n * sizeof(float *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (float *) ralloc((unsigned) (n2 - i) * sizeof(float)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make float copy of displaced vector of ints */

float  *fvector_icopy(int *v, int n1, int n2)
{
    float  *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("fvector_icopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (float *) ralloc((unsigned) (n2 - n1) * sizeof(float)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = (float) v[i];
    }
    return (ptr);
}

/* make float copy of displaced array of ints */

float **farray_icopy(int **a, int m1, int n1, int m2, int n2)
{
    float **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("farray_icopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("farray_icopy: zero array size", warning);
	return (NULL);
    }
    ptr = (float **) ralloc((unsigned) m * sizeof(float *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (float *) ralloc((unsigned) n * sizeof(float)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = (float) a[i][j];
    return (ptr);
}

/* make float copy of displaced lower triangle of ints */

float **flower_icopy(int **a, int m1, int n1, int m2, int n2)
{
    float **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("flower_icopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("flower_icopy: zero array size", warning);
	return (NULL);
    }
    ptr = (float **) ralloc((unsigned) m * sizeof(float *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (float *) ralloc((unsigned) n * sizeof(float)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = (float) a[i][j];
    return (ptr);
}

/* make float copy of displaced upper triangle of ints */

float **fupper_icopy(int **a, int n1, int n2)
{
    float **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("fupper_icopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("fupper_icopy: zero array size", warning);
	return (NULL);
    }
    ptr = (float **) ralloc((unsigned) n * sizeof(float *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (float *) ralloc((unsigned) (n2 - i) * sizeof(float)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = (float) a[i][j];
    return (ptr);
}

/* make float copy of displaced vector of floats */

float  *fvector_fcopy(float *v, int n1, int n2)
{
    float  *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("fvector_fcopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (float *) ralloc((unsigned) (n2 - n1) * sizeof(float)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = v[i];
    }
    return (ptr);
}

/* make float copy of displaced array of floats */

float **farray_fcopy(float **a, int m1, int n1, int m2, int n2)
{
    float **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("farray_fcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("farray_fcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (float **) ralloc((unsigned) m * sizeof(float *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (float *) ralloc((unsigned) n * sizeof(float)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make float copy of displaced lower triangle of floats */

float **flower_fcopy(float **a, int m1, int n1, int m2, int n2)
{
    float **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("flower_fcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("flower_fcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (float **) ralloc((unsigned) m * sizeof(float *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (float *) ralloc((unsigned) n * sizeof(float)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make float copy of displaced upper triangle of floats */

float **fupper_fcopy(float **a, int n1, int n2)
{
    float **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("fupper_fcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("fupper_fcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (float **) ralloc((unsigned) n * sizeof(float *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (float *) ralloc((unsigned) (n2 - i) * sizeof(float)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make float copy of displaced vector of doubles */

float  *fvector_dcopy(double *v, int n1, int n2)
{
    float  *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("fvector_dcopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (float *) ralloc((unsigned) (n2 - n1) * sizeof(float)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = (float) v[i];
    }
    return (ptr);
}

/* make float copy of displaced array of doubles */

float **farray_dcopy(double **a, int m1, int n1, int m2, int n2)
{
    float **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("farray_dcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("farray_dcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (float **) ralloc((unsigned) m * sizeof(float *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (float *) ralloc((unsigned) n * sizeof(float)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = (float) a[i][j];
    return (ptr);
}

/* make float copy of displaced lower triangle of doubles */

float **flower_dcopy(double **a, int m1, int n1, int m2, int n2)
{
    float **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("flower_dcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("flower_dcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (float **) ralloc((unsigned) m * sizeof(float *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (float *) ralloc((unsigned) n * sizeof(float)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = (float) a[i][j];
    return (ptr);
}

/* make float copy of displaced upper triangle of doubles */

float **fupper_dcopy(double **a, int n1, int n2)
{
    float **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("fupper_dcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("fupper_dcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (float **) ralloc((unsigned) n * sizeof(float *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (float *) ralloc((unsigned) (n2 - i) * sizeof(float)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = (float) a[i][j];
    return (ptr);
}
