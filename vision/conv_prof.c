/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/vision.h>

static double prof_intg(double x, double s2)
{
    float   i, sum = (float) 0.0;
    short   tot = 0;

    for (i = (float)(x - 0.5); i <= (float)(x + 0.5); i += (float)0.1)
    {
	sum += (float)exp(-i * i / s2);
	tot++;
    }
    return (sum / tot);
}

static double prof_g(double x, double s2)
{
    return (exp(-x * x / s2));
}

Prof1  *prof_gauss_simple(double sig, double precision)
{
    float   sig2;
    float  *profile;
    Prof1  *prof;
    Prof1  *prof1_alloc();
    int     n, i;

    sig2 = (float)(2.0 * sig * sig);

    for (n = 1;; ++n)
	if (prof_g((double) n, sig2) < precision)
	    break;

    prof = prof1_alloc(-n + 1, n, float_v);
    profile = prof->el.float_v;

    for (i = 0; i < n; ++i)
	profile[-i] = profile[i] = (float)prof_intg((float) i, sig2);
    return (prof);
}

Prof1  *prof_gauss(double sig, double precision)

/* as a ratio of max value */
{
    float   sig2, total = (float) 0.0;
    float  *profile;
    Prof1  *prof;
    Prof1  *prof1_alloc();
    int     n, i;

    sig2 = (float)(2.0 * sig * sig);

    for (n = 1;; ++n)
	if (prof_g((double) n, sig2) < precision)
	    break;

    prof = prof1_alloc(-n + 1, n, float_v);
    profile = prof->el.float_v;

    for (i = 0; i < n; ++i)
	total += profile[-i] = profile[i] = (float)prof_intg((float) i, sig2);

    total *= 2;
    total -= profile[0];

    for (i = -n + 1; i < n; ++i)
	profile[-i] /= total;

    return (prof);
}
