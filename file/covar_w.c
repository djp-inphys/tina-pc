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

extern void dmatrix_write_fp(FILE * fp, Matrix * a, int log);

void    covar_write_fp(FILE * fp, Covar * cov)
{
    int     i;

    if (cov == NULL)
	return;
    (void) fprintf(fp, " %d \n", cov->n);
    (void) fprintf(fp, " %d \n", cov->label);
    dmatrix_write_fp(fp, cov->mat, 0);
    (void) fprintf(fp, "\n");
    for (i = 0; i < cov->n; i++)
	(void) fprintf(fp, " %f", VECTOR_DOUBLE(cov->vec, i));
    (void) fprintf(fp, "\n");
}

void    covar_write(char *pathname, Covar * cov)
{
    FILE   *fp;
    char    temps[1024];

    if ((fp = fopen(pathname, "w")) == NULL)
    {
	(void) string_append(temps, "cannot open file ", pathname, 0);
	error(temps, non_fatal);
	return;
    }
    covar_write_fp(fp, cov);
    (void) fclose(fp);
}
