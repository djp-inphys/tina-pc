/**@(#)Array & Vector copying. (double version)
 * Ie copy displaced vectors and arrays,  casting as necessary.
 */

#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>

void    error();

/* make double copy of displaced vector of unsigned chars */

double *dvector_uccopy(unsigned char *v, int n1, int n2)
{
    double *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("dvector_uccopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (double *) ralloc((unsigned) (n2 - n1) * sizeof(double)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = v[i];
    }
    return (ptr);
}

/* make double copy of displaced array of unsigned chars */

double **darray_uccopy(unsigned char **a, int m1, int n1, int m2, int n2)
{
    double **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("darray_uccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("darray_uccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (double **) ralloc((unsigned) m * sizeof(double *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (double *) ralloc((unsigned) n * sizeof(double)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make double copy of displaced lower triangle of unsigned chars */

double **dlower_uccopy(unsigned char **a, int m1, int n1, int m2, int n2)
{
    double **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("dlower_uccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("dlower_uccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (double **) ralloc((unsigned) m * sizeof(double *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (double *) ralloc((unsigned) n * sizeof(double)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make double copy of displaced upper triangle of unsigned chars */

double **dupper_uccopy(unsigned char **a, int n1, int n2)
{
    double **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("dupper_uccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("dupper_uccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (double **) ralloc((unsigned) n * sizeof(double *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (double *) ralloc((unsigned) (n2 - i) * sizeof(double)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make double copy of displaced vector of chars */

double *dvector_ccopy(char *v, int n1, int n2)
{
    double *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("dvector_ccopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (double *) ralloc((unsigned) (n2 - n1) * sizeof(double)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = v[i];
    }
    return (ptr);
}

/* make double copy of displaced array of chars */

double **darray_ccopy(char **a, int m1, int n1, int m2, int n2)
{
    double **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("darray_ccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("darray_ccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (double **) ralloc((unsigned) m * sizeof(double *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (double *) ralloc((unsigned) n * sizeof(double)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make double copy of displaced lower triangle of chars */

double **dlower_ccopy(char **a, int m1, int n1, int m2, int n2)
{
    double **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("dlower_ccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("dlower_ccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (double **) ralloc((unsigned) m * sizeof(double *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (double *) ralloc((unsigned) n * sizeof(double)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make double copy of displaced upper triangle of chars */

double **dupper_ccopy(char **a, int n1, int n2)
{
    double **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("dupper_ccopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("dupper_ccopy: zero array size", warning);
	return (NULL);
    }
    ptr = (double **) ralloc((unsigned) n * sizeof(double *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (double *) ralloc((unsigned) (n2 - i) * sizeof(double)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make double copy of displaced vector of shorts */

double *dvector_scopy(short int *v, int n1, int n2)
{
    double *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("dvector_scopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (double *) ralloc((unsigned) (n2 - n1) * sizeof(double)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = v[i];
    }
    return (ptr);
}

/* make double copy of displaced array of shorts */

double **darray_scopy(short int **a, int m1, int n1, int m2, int n2)
{
    double **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("darray_scopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("darray_scopy: zero array size", warning);
	return (NULL);
    }
    ptr = (double **) ralloc((unsigned) m * sizeof(double *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (double *) ralloc((unsigned) n * sizeof(double)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make double copy of displaced lower triangle of shorts */

double **dlower_scopy(short int **a, int m1, int n1, int m2, int n2)
{
    double **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("dlower_scopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("dlower_scopy: zero array size", warning);
	return (NULL);
    }
    ptr = (double **) ralloc((unsigned) m * sizeof(double *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (double *) ralloc((unsigned) n * sizeof(double)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make double copy of displaced upper triangle of shorts */

double **dupper_scopy(short int **a, int n1, int n2)
{
    double **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("dupper_scopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("dupper_scopy: zero array size", warning);
	return (NULL);
    }
    ptr = (double **) ralloc((unsigned) n * sizeof(double *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (double *) ralloc((unsigned) (n2 - i) * sizeof(double)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make double copy of displaced vector of ints */

double *dvector_icopy(int *v, int n1, int n2)
{
    double *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("dvector_icopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (double *) ralloc((unsigned) (n2 - n1) * sizeof(double)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = v[i];
    }
    return (ptr);
}

/* make double copy of displaced array of ints */

double **darray_icopy(int **a, int m1, int n1, int m2, int n2)
{
    double **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("darray_icopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("darray_icopy: zero array size", warning);
	return (NULL);
    }
    ptr = (double **) ralloc((unsigned) m * sizeof(double *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (double *) ralloc((unsigned) n * sizeof(double)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make double copy of displaced lower triangle of ints */

double **dlower_icopy(int **a, int m1, int n1, int m2, int n2)
{
    double **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("dlower_icopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("dlower_icopy: zero array size", warning);
	return (NULL);
    }
    ptr = (double **) ralloc((unsigned) m * sizeof(double *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (double *) ralloc((unsigned) n * sizeof(double)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make double copy of displaced upper triangle of ints */

double **dupper_icopy(int **a, int n1, int n2)
{
    double **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("dupper_icopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("dupper_icopy: zero array size", warning);
	return (NULL);
    }
    ptr = (double **) ralloc((unsigned) n * sizeof(double *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (double *) ralloc((unsigned) (n2 - i) * sizeof(double)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make double copy of displaced vector of floats */

double *dvector_fcopy(float *v, int n1, int n2)
{
    double *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("dvector_fcopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (double *) ralloc((unsigned) (n2 - n1) * sizeof(double)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = v[i];
    }
    return (ptr);
}

/* make double copy of displaced array of floats */

double **darray_fcopy(float **a, int m1, int n1, int m2, int n2)
{
    double **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("darray_fcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("darray_fcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (double **) ralloc((unsigned) m * sizeof(double *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (double *) ralloc((unsigned) n * sizeof(double)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make double copy of displaced lower triangle of floats */

double **dlower_fcopy(float **a, int m1, int n1, int m2, int n2)
{
    double **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("dlower_fcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("dlower_fcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (double **) ralloc((unsigned) m * sizeof(double *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (double *) ralloc((unsigned) n * sizeof(double)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make double copy of displaced upper triangle of floats */

double **dupper_fcopy(float **a, int n1, int n2)
{
    double **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("dupper_fcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("dupper_fcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (double **) ralloc((unsigned) n * sizeof(double *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (double *) ralloc((unsigned) (n2 - i) * sizeof(double)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make double copy of displaced vector of doubles */

double *dvector_dcopy(double *v, int n1, int n2)
{
    double *ptr;
    int     i;

    if (n2 <= n1)
    {
	error("dvector_dcopy: bad array bounds", warning);
	return (NULL);
    }
    ptr = (double *) ralloc((unsigned) (n2 - n1) * sizeof(double)) - n1;
    for (i = n1; i < n2; ++i)
    {
	ptr[i] = v[i];
    }
    return (ptr);
}

/* make double copy of displaced array of doubles */

double **darray_dcopy(double **a, int m1, int n1, int m2, int n2)
{
    double **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("darray_dcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("darray_dcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (double **) ralloc((unsigned) m * sizeof(double *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (double *) ralloc((unsigned) n * sizeof(double)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* Make double copy of displaced lower triangle of doubles */
double **dlower_dcopy(double **a, int m1, int n1, int m2, int n2)
{
    double **ptr;
    int     m = m2 - m1, n = n2 - n1;
    int     i, j;

    if (m < 0 || n < 0)
    {
	error("dlower_dcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("dlower_dcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (double **) ralloc((unsigned) m * sizeof(double *)) - m1;
    for (i = m1; i < m2; ++i)
	ptr[i] = (double *) ralloc((unsigned) n * sizeof(double)) - n1;
    for (i = m1; i < m2; ++i)
	for (j = n1; j <= i; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}

/* make double copy of displaced upper triangle of doubles */

double **dupper_dcopy(double **a, int n1, int n2)
{
    double **ptr;
    int     n = n2 - n1;
    int     i, j;

    if (n < 0)
    {
	error("dupper_dcopy: bad array bounds", non_fatal);
	return (NULL);
    }
    if (n == 0)
    {
	error("dupper_dcopy: zero array size", warning);
	return (NULL);
    }
    ptr = (double **) ralloc((unsigned) n * sizeof(double *)) - n1;
    for (i = n1; i < n2; ++i)
	ptr[i] = (double *) ralloc((unsigned) (n2 - i) * sizeof(double)) - i;
    for (i = n1; i < n2; ++i)
	for (j = i; j < n2; ++j)
	    ptr[i][j] = a[i][j];
    return (ptr);
}
