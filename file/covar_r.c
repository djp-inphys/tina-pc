/**@(#)
  */
#include <stdio.h>
#include <values.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Covar  *covar_read(char *pathname)
{
    Covar  *cov;
    Covar  *covar_read_fp(FILE * fp);
    FILE   *fp;
    char    temps[1024];

    if ((fp = fopen(pathname, "r")) == NULL)
    {
	(void) string_append(temps, "cannot open file ", pathname, 0);
	error(temps, non_fatal);
	return (NULL);
    }
    cov = covar_read_fp(fp);
    (void) fclose(fp);
    return (cov);
}

Covar  *covar_read_fp(FILE * fp)
{
    Covar  *covar_alloc();
    Covar  *cov;
    Matrix *dmatrix_read_fp();
    Vector *vector_alloc();
    int     i, n;

    (void) fscanf(fp, "%d ", &n);
    cov = covar_alloc(n);
    cov->n = n;
    (void) fscanf(fp, "%d ", &(cov->label));
    cov->mat = dmatrix_read_fp(fp, n, n);
    cov->vec = vector_alloc(n, double_v);
    for (i = 0; i < n; i++)
	(void) fscanf(fp, " %lf", &VECTOR_DOUBLE(cov->vec, i));
    return (cov);
}
