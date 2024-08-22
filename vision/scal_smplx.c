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

void    cam_cal_stereo_smplx_params_set(double s_init, double c1, double c2, double a)
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
static Vec3 *(*cal_get_3d) ();
static Vec2 *(*cal_get_pixl) ();
static Vec2 *(*cal_get_pixr) ();
static Covar *cal_in_cov;

static double pixchisq(int n_par, double *a)
{
    double  chisq = MAXDOUBLE;
    double *f = NULL;
    int     n;

    (void) store_camera_int(cal_mask, a + 6, cal_caml);
    (void) store_camera_int(cal_mask, a + n_par / 2 + 6, cal_camr);
    if (store_camera_ext(a, cal_caml) &&
	store_camera_rel(a + n_par / 2, cal_caml, cal_camr))
    {
	n = MAXINT;
	chisq = camerror(&n, f, cal_caml, cal_data, cal_get_pixl, cal_get_3d, accuracy);
	n = MAXINT;
	chisq += camerror(&n, f, cal_camr, cal_data, cal_get_pixr, cal_get_3d, accuracy);
	chisq += stereo_reg(cal_in_cov, cal_mask, a + 6);
    }
    return (chisq);
}

/* inverse covarience */
double  cam_cal_stereo_simplex(Camera * caml, Camera * camr, int mask, List * data, Vec3 * (*get3d) ( /* ??? */ ), Vec2 * (*getpixl) ( /* ??? */ ), Vec2 * (*getpixr) ( /* ??? */ ), Covar * in_cov)
{
    double  chisq, chisq_old;
    double *a;
    int     n_par, n_parm2p12, i;

    if (data == NULL || caml == NULL || camr == NULL)
	return (0.0);

    cal_mask = mask;
    cal_data = data;
    cal_caml = caml;
    cal_camr = camr;
    cal_get_3d = get3d;
    cal_get_pixl = getpixl;
    cal_get_pixr = getpixr;
    cal_in_cov = in_cov;

    for (i = 0, n_par = 0; i < 16; i++)
	if (mask & (1 << i))
	    n_par++;
    n_parm2p12 = 2 * n_par + 12;
    a = (double *) ralloc((unsigned) n_parm2p12 * sizeof(double));

    (void) conv_camera_int(mask, caml, a + 6);
    (void) conv_camera_ext(caml, a);
    (void) conv_camera_int(mask, camr, a + n_par + 12);
    (void) conv_camera_rel(caml, camr, a + n_par + 6);

    format_params("Initial camera parameters = ", a, n_parm2p12);

    chisq_old = pixchisq(n_parm2p12, a);
    for (i = 0; i < 5; ++i)
    {
	chisq = simplexmin(n_parm2p12, a, scale_init, pixchisq, c_test1,
			   (void (*) ()) format);
	if (chisq_old - chisq < c_test2)
	    break;
	chisq_old = chisq;
    }

    format_params("Final camera parameters = ", a, n_parm2p12);

    (void) store_camera_int(mask, a + 6, caml);
    (void) store_camera_ext(a, caml);
    (void) store_camera_int(mask, a + n_par + 12, camr);
    (void) store_camera_rel(a + n_par + 6, caml, camr);
    rfree((void *) a);
    return (chisq);
}

static double stereo_chisq(double *f, int n_data, double *a, int n_par)
{
    double  chisq = MAXDOUBLE;
    double *g = NULL;
    int     n = n_data;

    (void) store_camera_int(cal_mask, a + 6, cal_caml);
    (void) store_camera_int(cal_mask, a + n_par / 2 + 6, cal_camr);
    if (store_camera_ext(a, cal_caml) &&
	store_camera_rel(a + n_par / 2, cal_caml, cal_camr))
    {
	chisq = camerror(&n, f, cal_caml, cal_data, cal_get_pixl, cal_get_3d, accuracy);
	if (f)
	    g = &f[n];
	chisq += camerror(&n_data, g, cal_camr, cal_data, cal_get_pixr, cal_get_3d, accuracy);
    }
    return (chisq);
}

Covar  *cal_full_stereo_covar(Camera * caml, Camera * camr, int mask, List * data, Vec3 * (*get3d) ( /* ??? */ ), Vec2 * (*getpixl) ( /* ??? */ ), Vec2 * (*getpixr) ( /* ??? */ ))
{
    Covar  *cov;
    Covar  *incov;
    double *a;
    int     n_data1 = MAXINT, n_data2 = MAXINT, n_data;
    int     n_par, i;
    double  condition = 1.0e-9;

    if (data == NULL || caml == NULL || camr == NULL)
	return (NULL);

    cal_mask = mask;
    cal_data = data;
    cal_caml = caml;
    cal_camr = camr;
    cal_get_3d = get3d;
    cal_get_pixl = getpixl;
    cal_get_pixr = getpixr;

    for (i = 0, n_par = 6; i < 16; i++)
	if (mask & (1 << i))
	    n_par++;
    a = (double *) ralloc((unsigned) 2 * n_par * sizeof(double));

    (void) conv_camera_int(mask, caml, a + 6);
    (void) conv_camera_int(mask, camr, a + n_par + 6);
    (void) conv_camera_ext(caml, a);
    (void) conv_camera_rel(caml, camr, a + n_par);

    /* .  BUGFIX 1 camerror takes 7 args,  added 1.0 BUGFIX 2 chisq
     * unused */
    /* BUGFIX 3 --- BUGFIX 2 is incorrect. 
     *   Yes, chisq is unused.
     *   However, camerror updates n_data1 & n_data2
     *   The code has been uncommented and enclosed in a local group
     *   SDHC 08/12/93
     */
    {
	    double  *f = NULL; double  chisq; chisq = camerror(&n_data1, f,
	      caml, data, getpixl, get3d, 1.0);
	    chisq += camerror(&n_data2, f, camr, data, getpixr, get3d, 1.0);
    }
    n_data = n_data1 + n_data2;

    cov = covar(2 * n_par, a, stereo_chisq, n_data, condition);
    cov->label = mask;
    incov = invcov(2 * n_par, a, stereo_chisq, n_data);
    dmatrix_checkinv((void (*) ()) format, cov->mat, incov->mat, "covariance matrix");

    rfree((void *) a);
    return (cov);
}

Covar  *cal_full_stereo_invcovar(int mask, Covar * cov, double condition)
{
    int     n_par, i, j, n;
    Covar  *stereo_incov;
    Matrix *subcov;

    if (cov == NULL)
	return (NULL);

    for (i = 0, n_par = 6; i < 16; i++)
	if (mask & (1 << i))
	    n_par++;
    n = n_par * 2 - 6;

    stereo_incov = covar_alloc(n);
    subcov = matrix_alloc(n, n, matrix_full, double_v);
    stereo_incov->n = n;
    stereo_incov->label = mask;
    stereo_incov->vec = vector_alloc(n, double_v);
    for (i = 0; i < n; i++)
    {
	VECTOR_SET(stereo_incov->vec, i, VECTOR_DOUBLE(cov->vec, i + 6));
	for (j = 0; j < n; j++)
	    subcov->el.double_v[i][j] = cov->mat->el.double_v[i + 6][j + 6];
    }

    stereo_incov->mat = matrix_invsvd(subcov, condition);
    dmatrix_checkinv((void (*) ()) format, stereo_incov->mat, subcov, "sub covariance inverse");
    matrix_free(subcov);

    return (stereo_incov);
}
