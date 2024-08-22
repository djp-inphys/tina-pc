/**@(#)Newton_raphson
**/

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>

static double err(double x, double y)
{
    /* BUGFIX: was if (fabs(x < 1.0)) */
    if (fabs(x) < 1.0)
	return (fabs(x - y));
    else
	return (fabs(y / x - 1.0));
}

double  newton_raphson(double (*f) ( /* ??? */ ), double (*df) ( /* ??? */ ), double x, double eps)
{
    double  x0;

    do
    {
	x0 = x;
	x -= f(x) / df(x);
    } while (err(x, x0) > eps);
    return (x);
}
