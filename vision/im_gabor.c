/**@(#)
**/
/* gabor.c
 * 
 * gabor filter functions
 * 
 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Prof1  *prof1_alloc();
Imrect *im_conv_separable();

Prof1  *gabor_profile(float phase, float sigma, float omega, float nsigma)
{
    float  *el;
    Prof1  *prof;
    float   k;
    int     i, n;

    if (nsigma <= 0.0)
	return (NULL);

    /** allocate nsigma*sigma mask **/
    n = (int) (nsigma * sigma);
    prof = prof1_alloc(-n, n + 1, float_v);
    el = prof->el.float_v;

    if (n == 0)
    {
	/** return delta function **/
	el[0] = (float) 1.0;
	return (prof);
    }
    k = (float) (1.0 / (2.0 * sigma * sigma));
    for (i = -n; i < n + 1; i++)
	el[i] = (float) (exp(-k * i * i) * sin(omega * i + phase));

    return (prof);
}

Imrect *im_gabor(Imrect * im1, double phasex, double sigmax, double omegax, double nsigmax, double phasey, double sigmay, double omegay, double nsigmay)
{
    Prof1  *profx = gabor_profile((float)phasex, (float)sigmax, (float)omegax, (float)nsigmax);
    Prof1  *profy = gabor_profile((float)phasey, (float)sigmay, (float)omegay, (float)nsigmay);
    Imrect *im2;

    im2 = im_conv_separable(im1, profx, profy);
    prof1_free(profx);
    prof1_free(profy);
    return (im2);
}

/* fft version of 2D gabor filter: k = centre frequency b = 1-sigma
 * bandwidth in octaves theta = orientation */

Imrect *im_gabor_fft(Imrect * im, double k, double b, double theta)
{
    Imrect *im1;
    Imrect *im2;
    double  s, kx, ky, c1, c2;
    double *px, *py;
    int     x, y, wx, wy;

    /* work in frequency space */
    im1 = im_fft(im,im->region);
    wx = im->width;
    wy = im->height;
    b = pow(2.0, b);
    s = k * (b - 1.0) / (b + 1.0);
    kx = k * cos(theta);
    ky = k * sin(theta);
    c1 = 1.0 / (s * sqrt(TWOPI));
    c2 = -0.5 / (s * s);

    /** set up frequency profiles in x & y (with wrap-around) */
    px = tvector_alloc(0, wx, double);
    for (x = 0; x < wx; x++)
    {
	int     x1, x2;

	x1 = (int)fabs((double)x - kx);
	x2 = wx - x1;
	x1 = MIN(x1, x2);
	px[x] = c1 * exp(c2 * x1 * x1);
    }
    py = tvector_alloc(0, wy, double);
    for (y = 0; y < wy; y++)
    {
	int     y1, y2;

	y1 = (int)fabs((double)y - ky);
	y2 = wy - y1;
	y1 = MIN(y1, y2);
	py[y] = c1 * exp(c2 * y1 * y1);
    }

    /* apply convolutuion as product in frequency space */
    for (x = 0; x < wx; x++)
	for (y = 0; y < wy; y++)
	{
	    Complex z = {Complex_id};

	    IM_PIX_GETZ(im1, y, x, z);
	    z = cmplx_times(px[x] * py[y], z);
	    IM_PIX_SETZ(im1, y, x, z);
	}
    tvector_free(px, 0, double);
    tvector_free(py, 0, double);
    im2 = im_fft_inverse(im1,im1->region);
    im_free(im1);
    return (im2);
}

Imrect *im_fgabor(Imregion *roi, double k, double b, double theta)
{
    Imrect *im1;
    double  s, kx, ky, c1, c2;
    double *px, *py;
    int     x, y, wx, wy;
    Complex z = {Complex_id};
   
    /* work in frequency space */
    wx = roi->ux - roi->lx;
    wy = roi->uy - roi->ly;
    im1 = im_alloc(wy,wx,NULL,complex_v);

    b = pow(2.0, b);
    s = k * (b - 1.0) / (b + 1.0);
    kx = k * cos(theta);
    ky = k * sin(theta);
    c1 = 1.0 / (s * sqrt(TWOPI));
    c2 = -0.5 / (s * s);

    /** set up frequency profiles in x & y (with wrap-around) */
    px = tvector_alloc(0, wx, double);
    for (x = 0; x < wx; x++)
    {
        int     x1, x2;

        x1 = (int)fabs((double)x - kx);
        x2 = wx - x1;
        x1 = MIN(x1, x2);
        px[x] = c1 * exp(c2 * x1 * x1);
    }
    py = tvector_alloc(0, wy, double);
    for (y = 0; y < wy; y++)
    {
        int     y1, y2;

        y1 = (int)fabs((double)y - ky);
        y2 = wy - y1;
        y1 = MIN(y1, y2);
        py[y] = c1 * exp(c2 * y1 * y1);
    }

    /* apply convolutuion as product in frequency space */
    for (x = 0; x < wx; x++)
        for (y = 0; y < wy; y++)
        {
            z = cmplx_unit();
            z = cmplx_times(px[x] * py[y], z);
            IM_PIX_SETZ(im1, y, x, z);
        }
    tvector_free(px, 0, double);
    tvector_free(py, 0, double);
    return (im1);
}
