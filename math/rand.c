/**@(#)Random number generation (various)
**/

#include <math.h>
#ifdef _ICC			/* ICC doesn't use the time see below */
#include <stdlib.h>
#include <process.h>
#define random() rand()

#elif defined SOLARIS
#include <time.h>
#include <stdlib.h>
#define random() lrand48()
extern long lrand48(void);
extern void srand48(long seedval);

#elif defined _PCC
#include <time.h>
#define random() rand()

#else
#include <sys/time.h>
long    random();

#endif

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>

#ifdef RAND_MAX
#undef RAND_MAX
#endif
#define RAND_MAX (((unsigned long) 1<<31)-1)

#define RAND_STEP (1.0/(RAND_MAX+1.0))
#define RAND_ITMAX 	100
#define RAND_EPS 	3.0e-7

double  rand_1(void)
{
    return (random() * RAND_STEP);
}

int     rand_bit(void)
{
    return (random() & 01);
}

int     rand_int(int a, int b)
{
    return (a + random() % (b - a));
}

double  rand_unif(double x, double y)
{
    return (x + (y - x) * random() * RAND_STEP);
}

static double rand_normal_1(void)
{
    static Bool saved = false;
    static double v1, v2;
    double  r, k;

    if (saved == false)
    {
	do
	{
	    v1 = 2.0 * rand_1() - 1.0;
	    v2 = 2.0 * rand_1() - 1.0;
	    r = v1 * v1 + v2 * v2;
	} while (r >= 1.0 && r != 0.0);
	k = sqrt(-2.0 * log(r) / r);
	v1 *= k;
	v2 *= k;
	saved = true;
	return (v1);
    } else
    {
	saved = false;
	return (v2);
    }
}

double  rand_normal(double mu, double sigma)
{
    return (mu + sigma * rand_normal_1());
}

double  gammln(double x)
{
    double  tmp, sum;
    static double cof[6] =
    {76.18009173, -86.50532033, 24.01409822,
    -1.231739516, 0.120858003e-2, -0.536382e-5};
    int     j;

    x -= 1.0;
    tmp = x + 5.5;
    tmp -= (x + 0.5) * log(tmp);
    sum = 1.0;
    for (j = 0; j <= 5; j++)
    {
	x += 1.0;
	sum += cof[j] / x;
    }
    return (-tmp + log(2.50662827465 * sum));
}

static void gser(double *gamser, double a, double x, double *gln)
{
    int     n;
    double  sum, del, ap;

    *gln = gammln(a);
    if (x <= 0.0)
    {
	if (x < 0.0)
	    return;
	*gamser = 0.0;
	return;
    } else
    {
	ap = a;
	del = sum = 1.0 / a;
	for (n = 1; n <= RAND_ITMAX; n++)
	{
	    ap += 1.0;
	    del *= x / ap;
	    sum += del;
	    if (fabs(del) < fabs(sum) * RAND_EPS)
	    {
		*gamser = sum * exp(-x + a * log(x) - (*gln));
		return;
	    }
	}
	message("a too large, RAND_ITMAX too small in routine GSER");
	return;
    }
}

static void gcf(double *gammcf, double a, double x, double *gln)
{
    int     n;
    double  gold = 0.0, g, fac = 1.0, b1 = 1.0;
    double  b0 = 0.0, anf, ana, an, a1, a0 = 1.0;

    *gln = gammln(a);
    a1 = x;
    for (n = 1; n <= RAND_ITMAX; n++)
    {
	an = (double) n;
	ana = an - a;
	a0 = (a1 + a0 * ana) * fac;
	b0 = (b1 + b0 * ana) * fac;
	anf = an * fac;
	a1 = x * a0 + anf * a1;
	b1 = x * b0 + anf * b1;
	if (a1)
	{
	    fac = 1.0 / a1;
	    g = b1 * fac;
	    if (fabs((g - gold) / g) < RAND_EPS)
	    {
		*gammcf = exp(-x + a * log(x) - (*gln)) * g;
		return;
	    }
	    gold = g;
	}
    }
}

double  gammp(double a, double x)
{
    double  gamser, gammcf, gln;

    if (x < 0.0 || a <= 0.0)
	return (0.0);
    if (x < (a + 1.0))
    {
	gser(&gamser, a, x, &gln);
	return (gamser);
    } else
    {
	gcf(&gammcf, a, x, &gln);
	return (1.0 - gammcf);
    }
}

double  gammq(double a, double x)
{
    double  gamser, gammcf, gln;

    if (x < 0.0 || a <= 0.0)
	return (0.0);
    if (x < (a + 1.0))
    {
	gser(&gamser, a, x, &gln);
	return 1.0 - gamser;
    } else
    {
	gcf(&gammcf, a, x, &gln);
	return (gammcf);
    }
}

double  chisq(double x, int n)
{
    if (x == 0.0)
	return (1.0);
    if (n == 0)
	return (0.0);
    return (gammq(n * 0.5, x * 0.5));
}

/* Seed random with microsecond part of time */
void    rand_time_seed(void)
{
#ifdef _ICC
    srand(ProcTime());
#elif defined _POSIX_SOURCE ||  defined  SOLARIS
    time_t  tm;

    (void) time(&tm);
    srand48((long) tm);
#elif defined  SOLARIS_OLD
    struct timeval tp;

    (void) gettimeofday(&tp, (struct timezone *) NULL);

    srand48(tp.tv_usec);
#elif defined _PCC
    time_t  tm;

    (void) time(&tm);
    srand((unsigned int) tm);
#else
    struct timeval tp;

    (void) gettimeofday(&tp, (struct timezone *) NULL);
    srandom((int) tp.tv_usec);
#endif
}

#undef RAND_MAX
#undef RAND_STEP
#undef RAND_ITMAX
#undef RAND_EPS
