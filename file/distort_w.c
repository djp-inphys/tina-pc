/**@(#)
  */
#include <stdio.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

void    rdist_write_fp(FILE * fp, Camera * cam)
{
    int     i, n;
    double *a;

    if (cam->distort_params != NULL)
    {
	a = cam->distort_params;
	n = (int) a[0];
	(void) fprintf(fp, "%d \n", n);
	for (i = 0; i < n; i++)
	    (void) fprintf(fp, "%f ", a[i + 1]);
	(void) fprintf(fp, "\n");
    }
}
