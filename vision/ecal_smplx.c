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

void    cam_cal_triv_smplx_params_set(double s_init, double c1, double c2, double a)
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

static Camera *cal_caml;
static Camera *cal_camr;
static int cal_mask;
static List *cal_data;
static Vec2 *(*cal_get_pixl) ();
static Vec2 *(*cal_get_pixr) ();
static Covar *cal_in_cov;

static double pixchisq(int n_par, double *a)
{
    double  chisq = MAXDOUBLE;
    double *f = NULL;

    (void) store_camera_int(cal_mask, a, cal_caml);
    (void) store_camera_int(cal_mask, a + n_par / 2 + 3, cal_camr);
    if (store_camera_rel(a + n_par / 2 - 3, cal_caml, cal_camr))
    {
	int     n = MAXINT;

	chisq = triv_camerror(&n, f, cal_caml, cal_camr, cal_data, cal_get_pixl, cal_get_pixr, accuracy);
	chisq += stereo_reg(cal_in_cov, cal_mask, a);
    }
    return (chisq);
}

double  cam_cal_triv_simplex(Camera * caml, Camera * camr, int mask, List * data, Vec2 * (*getpixl) ( /* ??? */ ), Vec2 * (*getpixr) ( /* ??? */ ), Covar * in_cov)





/* inverse covarience */
{
    double  chisq, chisq_old;
    double *a;
    int     n_par, n_parm2p6, i;

    if (data == NULL || caml == NULL || camr == NULL)
	return (0.0);

    cal_mask = mask;
    cal_data = data;
    cal_caml = caml;
    cal_camr = camr;
    cal_get_pixl = getpixl;
    cal_get_pixr = getpixr;
    cal_in_cov = in_cov;

    for (i = 0, n_par = 0; i < 16; i++)
	if (mask & (1 << i))
	    n_par++;
    n_parm2p6 = 2 * n_par + 6;
    a = (double *) ralloc((unsigned) n_parm2p6 * sizeof(double));

    (void) conv_camera_int(mask, caml, a);
    (void) conv_camera_int(mask, camr, a + n_par + 6);
    (void) conv_camera_rel(caml, camr, a + n_par);

    format_params("Initial camera parameters = ", a, n_parm2p6);

    chisq_old = pixchisq(n_parm2p6, a);
    for (i = 0; i < 5; ++i)
    {
	chisq = simplexmin(n_parm2p6, a, scale_init, pixchisq, c_test1,
			   (void (*) ()) format);
	if (chisq_old - chisq < c_test2)
	    break;
	chisq_old = chisq;
    }

    format_params("Final camera parameters = ", a, n_parm2p6);

    (void) store_camera_int(mask, a, caml);
    (void) store_camera_int(mask, a + n_par + 6, camr);
    (void) store_camera_rel(a + n_par, caml, camr);
    rfree((void *) a);
    return (chisq);
}

static double trivedi_chisq(double *f, int n, double *a, int n_par)
{
    double  chisq = MAXDOUBLE;

    (void) store_camera_int(cal_mask, a, cal_caml);
    (void) store_camera_int(cal_mask, a + n_par / 2 + 3, cal_camr);
    if (store_camera_rel(a + n_par / 2 - 3, cal_caml, cal_camr))
	chisq = triv_camerror(&n, f, cal_caml, cal_camr, cal_data, cal_get_pixl,
			      cal_get_pixr, accuracy);
    return (chisq);
}

Covar  *cal_trivedi_invcovar(Camera * caml, Camera * camr, int mask, List * data, Vec2 * (*getpixl) ( /* ??? */ ), Vec2 * (*getpixr) ( /* ??? */ ))
{
    Covar  *incov;
    double *a;
    int     n_data = MAXINT;
    int     n_par, i;

    if (data == NULL || caml == NULL || camr == NULL)
	return (NULL);

    cal_mask = mask;
    cal_data = data;
    cal_caml = caml;
    cal_camr = camr;
    cal_get_pixl = getpixl;
    cal_get_pixr = getpixr;

    for (i = 0, n_par = 0; i < 16; i++)
	if (mask & (1 << i))
	    n_par++;
    a = (double *) ralloc((unsigned) ((2 * n_par + 6) * sizeof(double)));

    (void) conv_camera_int(mask, caml, a);
    (void) conv_camera_int(mask, camr, a + n_par + 6);
    (void) conv_camera_rel(caml, camr, a + n_par);

    /* BUGFIX chisq unused */
    /* double  *f = NULL; double  chisq; chisq = triv_camerror(&n_data,
     * f, caml, camr, data, getpixl, getpixr, accuracy); */
    incov = invcov(2 * n_par + 6, a, trivedi_chisq, n_data);
    incov->label = mask;

    rfree((void *) a);
    return (incov);
}
