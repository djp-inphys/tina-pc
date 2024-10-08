/**@(#)Fast Fourier Transform
**/

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>

void    fourier(double *data, int nn, int isign);

void    fft_cmplx_inplace(Complex * z, int n)	/** assumes n is a power of 2 **/


{
    int     i;
    double *y = dvector_alloc(0, 2 * n);

    for (i = 0; i < n; i++)
    {
	y[2 * i] = cmplx_re(z[i]);
	y[2 * i + 1] = cmplx_im(z[i]);
    }

    fourier(y - 1, n, 1);


    for (i = 0; i < n; i++)
    {
	cmplx_re(z[i]) = y[2 * i];
	cmplx_im(z[i]) = y[2 * i + 1];
    }

    dvector_free((void *) y, 0);
}

void    fft_inverse_cmplx_inplace(Complex * z, int n)	/** assumes n is a power of 2 **/


{
    int     i;
    double *y = dvector_alloc(0, 2 * n);

    for (i = 0; i < n; i++)
    {
	y[2 * i] = cmplx_re(z[i]);
	y[2 * i + 1] = cmplx_im(z[i]);
    }

    fourier(y - 1, n, -1);

    for (i = 0; i < n; i++)
    {
	cmplx_re(z[i]) = y[2 * i] / n;
	cmplx_im(z[i]) = y[2 * i + 1] / n;
    }

    dvector_free((void *) y, 0);
}

/** assumes complex data is interlaced in data[1] ... data[2n] **/

void    fourier(double *data, int nn, int isign)
{
    int     n, mmax, m, j, istep, i;
    double  wtemp, wr, wpr, wpi, wi, theta;
    double  tempr, tempi;

    n = nn << 1;
    j = 1;
    for (i = 1; i < n; i += 2)
    {
	if (j > i)
	{
	    SWAP(double, data[j], data[i]);
	    SWAP(double, data[j + 1], data[i + 1]);
	}
	m = n >> 1;
	while (m >= 2 && j > m)
	{
	    j -= m;
	    m >>= 1;
	}
	j += m;
    }
    mmax = 2;
    while (n > mmax)
    {
	istep = 2 * mmax;
	theta = TWOPI / (isign * mmax);
	wtemp = sin(0.5 * theta);
	wpr = -2.0 * wtemp * wtemp;
	wpi = sin(theta);
	wr = 1.0;
	wi = 0.0;
	for (m = 1; m < mmax; m += 2)
	{
	    for (i = m; i <= n; i += istep)
	    {
		j = i + mmax;
		tempr = wr * data[j] - wi * data[j + 1];
		tempi = wr * data[j + 1] + wi * data[j];
		data[j] = data[i] - tempr;
		data[j + 1] = data[i + 1] - tempi;
		data[i] += tempr;
		data[i + 1] += tempi;
	    }
	    wr = (wtemp = wr) * wpr - wi * wpi + wr;
	    wi = wi * wpr + wtemp * wpi + wi;
	}
	mmax = istep;
    }
}
