#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

Imrect *im_fft(Imrect *im1,Imregion *region)
{
    Imrect *im2;
    Imregion roi;
    Complex *line;
    int nx, ny;
    int lx, ux, ly, uy;
    int i;

    if (im1 == NULL)
	return (NULL);

    if (region==NULL) region = im1->region;
    if (region == NULL) return (NULL);

    lx = roi.lx = region->lx;
    ux = roi.ux = region->ux;
    ly = roi.ly = region->ly;
    uy = roi.uy = region->uy;

    for(nx = 1; nx <= ux-lx; nx *= 2);
    for(ny = 1; ny <= uy-ly; ny *= 2);
    nx/=2;
    ny/=2;

    ux = roi.ux = lx + nx;
    uy = roi.uy = ly + ny;

    im2 = im_alloc(ny, nx, &roi, complex_v);
    line = zvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowz(line, im1, i, lx, ux);
        line += lx;
	fft_cmplx_inplace(line, nx);
        line -= lx;
	im_put_rowz(line, im2, i, lx, ux);
    }

    zvector_free(line, lx);
    line = zvector_alloc(ly, uy);
    for (i = lx; i < ux; ++i)
    {
	im_get_colz(line, im2, i, ly, uy);
        line += ly;
	fft_cmplx_inplace(line, ny);
        line -= ly;
	im_put_colz(line, im2, i, ly, uy);
    }

    zvector_free(line, ly);
    return (im2);
}

Imrect *im_fft_inverse(Imrect *im1,Imregion *region)
{
    Imrect *im2;
    Imregion roi;
    Complex *line;
    int nx, ny;
    int lx, ux, ly, uy;
    int i;

    if (im1 == NULL)
        return (NULL);

    if (region==NULL) region = im1->region;
    if (region == NULL) return (NULL);

    lx = roi.lx = region->lx;
    ux = roi.ux = region->ux;
    ly = roi.ly = region->ly;
    uy = roi.uy = region->uy;

    for(nx = 1; nx <= ux-lx; nx *= 2);
    for(ny = 1; ny <= uy-ly; ny *= 2);
    nx/=2;
    ny/=2;

    ux = roi.ux = lx + nx;
    uy = roi.uy = ly + ny;

    im2 = im_alloc(ny, nx, &roi, complex_v);
    line = zvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowz(line, im1, i, lx, ux);
        line += lx;
	fft_inverse_cmplx_inplace(line, nx);
        line -= lx;
	im_put_rowz(line, im2, i, lx, ux);
    }

    zvector_free(line, lx);
    line = zvector_alloc(ly, uy);
    for (i = lx; i < ux; ++i)
    {
	im_get_colz(line, im2, i, ly, uy);
        line += ly;
	fft_inverse_cmplx_inplace(line, ny);
        line -= ly;
	im_put_colz(line, im2, i, ly, uy);
    }

    zvector_free(line, ly);
    return (im2);
}

static void line_power_spectrum(Complex *l1, float *l2, int from, int to)
{
    int i;

    for(i = from; i < to; i++)
	l2[i] = (float)cmplx_sqrmod(l1[i]);
}

Imrect *im_power_spectrum(Imrect *im1)
{
    Imrect *im2;
    Complex *l1;
    float *l2;
    int i;
    int ux, uy, hx, hy;

    if (im1 == NULL)
	return (NULL);

    ux = im1->width;  hx = ux/2;
    uy = im1->height; hy = uy/2;

    im2 = im_alloc(uy, ux, NULL, float_v);
    l1 = zvector_alloc(0, ux);
    l2 = fvector_alloc(0, ux);

    for (i = 0; i < hy; ++i)
    {
	im_get_rowz(l1, im1, i, 0, hx);
	line_power_spectrum(l1, l2, 0, hx);
	im_put_rowf(l2-hx, im2, i+hy, hx, ux);

	im_get_rowz(l1, im1, i, hx, ux);
	line_power_spectrum(l1, l2, hx, ux);
	im_put_rowf(l2+hx, im2, i+hy, 0, hx);
    }

    for (i = hy; i < uy; ++i)
    {
	im_get_rowz(l1, im1, i, 0, hx);
	line_power_spectrum(l1, l2, 0, hx);
	im_put_rowf(l2-hx, im2, i-hy, hx, ux);

	im_get_rowz(l1, im1, i, hx, ux);
	line_power_spectrum(l1, l2, hx, ux);
	im_put_rowf(l2+hx, im2, i-hy, 0, hx);
    }

    zvector_free(l1, 0);
    fvector_free(l2, 0);

    return(im2);
}
