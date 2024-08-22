/**@(#)Maths (simple functions, eg imax3: (returns biggest of 3 ints)
**/

#include <math.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

double  tina_acos(double c)
{
    if (c > 1.0)
	c = 1.0;
    else if (c < -1.0)
	c = -1.0;
    return (acos(c));
}

double  sqr(double x)
{
    return (x * x);
}

double  dist2(double x1, double y1, double x2, double y2)
{
    double  dx = x2 - x1;
    double  dy = y2 - y1;

    return (sqrt(dx * dx + dy * dy));
}

int     imin(int x, int y)
{
    return ((x < y) ? x : y);
}

int     imax(int x, int y)
{
    return ((x > y) ? x : y);
}

double  fmin(double x, double y)
{
    return ((x < y) ? x : y);
}

double  fmax(double x, double y)
{
    return ((x > y) ? x : y);
}

int     imin3(int x, int y, int z)
{
    return ((x < (y = imin(y, z))) ? x : y);
}

int     imax3(int x, int y, int z)
{
    return ((x > (y = imax(y, z))) ? x : y);
}

double  fmin3(double x, double y, double z)
{
    return ((x < (y = fmin(y, z))) ? x : y);
}

double  fmax3(double x, double y, double z)
{
    return ((x > (y = fmax(y, z))) ? x : y);
}
