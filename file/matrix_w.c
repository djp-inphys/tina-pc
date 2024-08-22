/**@(#)
  */
#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>

void    dmatrix_write_fp(FILE * fp, Matrix * a, int log)
{
    int     i, j;

    if (log)
    {
	for (i = 0; i < a->m; i++)
	{
	    for (j = 0; j < a->n; j++)
		if (a->el.double_v[i][j] >= 0)
		    (void) fprintf(fp, "%7.2f ", log10(1.0 + a->el.double_v[i][j]));
		else
		    (void) fprintf(fp, "%7.2f ", -log10(1.0 - a->el.double_v[i][j]));
	    (void) fprintf(fp, "\n");
	}
    } else
    {
	for (i = 0; i < a->m; i++)
	{
	    for (j = 0; j < a->n; j++)
		(void) fprintf(fp, "%f ", a->el.double_v[i][j]);
	    (void) fprintf(fp, "\n");
	}
    }
}

void    dmatrix_write(char *file, Matrix * a, char *mname, int log)
{
    FILE   *fp;
    Matrix *matrix_prod();

    if (a == NULL)
    {
	error(" NUll matrix passed to printmat \n", non_fatal);
	return;
    }
    if ((fp = fopen(file, "w")) == NULL)
	fp = stdout;
    (void) fprintf(fp, "%s\n", mname);
    dmatrix_write_fp(fp, a, log);
    if (fp != stdout)
	(void) fclose(fp);
}
