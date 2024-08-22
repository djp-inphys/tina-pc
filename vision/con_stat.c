/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>
#ifdef _PCC
#include <memory.h>
#endif

Conic_stat *conic_stat_alloc(void)
{
    Conic_stat *stats = ts_ralloc(Conic_stat);

    return (stats);
}

Conic_stat *conic_stat_copy(Conic_stat * stats)
{
    Conic_stat *new = ts_ralloc(Conic_stat);

    (void) memcpy((char *) new, (char *) stats, sizeof(Conic_stat));
    return (new);
}

void    conic_stat_free(Conic_stat * stats)
{
    rfree((void *) stats);
}

/**
initialise covariance to complete uncertainty
**/
void    conic_stat_init(Conic_stat * stats, double lscale, double big)
{
    int     i, j;

    if (stats == NULL)
	return;

    for (i = 0; i < 5; i++)
    {
	stats->x[i] = 0.0;
	stats->u[i][i] = 1.0;
	for (j = 0; j < i; j++)
	    stats->u[i][j] = stats->u[j][i] = 0.0;
    }

    stats->d[0] = big;
    stats->d[1] = big;
    stats->d[2] = lscale * big;
    stats->d[3] = lscale * big;
    stats->d[4] = lscale * lscale * big;
}

/**
make correction  x  to conic in place
**/

void    conic_correct(Conic * conic, double *x)
{
    if (conic == NULL)
	return;

    conic->a += x[0];
    conic->b += x[1];
    conic->c = 1.0 - conic->a;	/**preserve normalisation**/
    conic->d += x[2];
    conic->e += x[3];
    conic->f += x[4];

    x[0] = x[1] = x[2] = x[3] = x[4] = x[5] = 0.0;
}

/**
make correction  x to conic in copy
**/

Conic  *conic_correct_copy(Conic * conic, double *x)
{
    conic = conic_copy(conic);
    conic_correct(conic, x);
    return (conic);
}
