/**@(#)
**/
#ifdef TRANSPUTER
#include <valuesdual.h>
#else
#include <values.h>
#endif
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

static double scale_init = 0.04, c_test1 = 0.00001, c_test2 = 0.1;
static double accuracy = 1.0;

void    cam_cal_smplx_params_set(double s_init, double c1, double c2, double a)
{
    scale_init = s_init;
    c_test1 = c1;
    c_test2 = c2;
    accuracy = a;
}

static void format_params(char *string, double *a, int n)
{
    int     i;

    format(string);
    for (i = 0; i < n; i++)
	format("%f ", a[i]);
    format("\n");
}

static Camera *cal_cam;
static int cal_mask;
static List *cal_data;
static Vec3 *(*cal_get_3d) ();
static Vec2 *(*cal_get_pix) ();
static Covar *cal_in_cov;

static double pixchisq(int n_par, double *a)
/* BUG n_par unused */


{
    double  chisq = MAXDOUBLE;
    double *f = NULL;
    int     n_data = MAXINT;

    (void) store_camera_int(cal_mask, a + 6, cal_cam);
    if (store_camera_ext(a, cal_cam))
    {
	chisq = camerror(&n_data, f, cal_cam, cal_data, cal_get_pix, cal_get_3d, accuracy);
	chisq += cam_reg(cal_in_cov, cal_mask, a);
    }
    return (chisq);
}

double  cam_cal_simplex(Camera * cam, int mask, List * data, Vec3 * (*get_3d) ( /* ??? */ ), Vec2 * (*get_pix) ( /* ??? */ ), Covar * in_cov)





/* inverse covarience */
{
    double  chisq, chisq_old;
    double *a;
    int     n_par, i;

    if (data == NULL || cam == NULL)
	return (0.0);

    cal_mask = mask;
    cal_data = data;
    cal_cam = cam;
    cal_get_3d = get_3d;
    cal_get_pix = get_pix;
    cal_in_cov = in_cov;

    for (i = 0, n_par = 6; i < 16; i++)
	if (mask & (1 << i))
	    n_par++;
    a = (double *) ralloc((unsigned) n_par * sizeof(double));

    (void) conv_camera_int(mask, cam, a + 6);
    (void) conv_camera_ext(cam, a);

    format_params("Initial camera parameters = ", a, n_par);

    chisq_old = pixchisq(n_par, a);
    for (i = 0; i < 5; ++i)
    {
	chisq = simplexmin(n_par, a, scale_init, pixchisq, c_test1,
			   (void (*) ()) format);
	if (chisq_old - chisq < c_test2)
	    break;
	chisq_old = chisq;
    }

    format_params("Final camera parameters = ", a, n_par);

    (void) store_camera_int(mask, a + 6, cam);
    (void) store_camera_ext(a, cam);
    rfree((void *) a);
    return (chisq);
}
