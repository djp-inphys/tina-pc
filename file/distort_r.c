/**@(#)
  */
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

void    rdist_read_fp(Camera * cam, FILE * fp)
{
    void   *cam_distort_copy();
    Vec2    radial_distort();
    Vec2    radial_correct();
    int     n, i;
    double *a;
    char    ch[256];

    if (readline(fp, ch) != EOF)
    {
	(void) sscanf(ch, "%d", &n);
	a = (double *) ralloc((unsigned) (sizeof(double) * (n + 1)));
	a[0] = n;
	for (i = 0; i < n; i++)
	    (void) fscanf(fp, "%lf", &(a[i + 1]));
	cam->distort_func = radial_distort;
	cam->correct_func = radial_correct;
	cam->distort_params = a;
	cam->copy_dist_func = cam_distort_copy;
    } else
    {
	cam->distort_params = NULL;
	cam->distort_func = NULL;
	cam->correct_func = NULL;
	cam->copy_dist_func = NULL;
    }
}
