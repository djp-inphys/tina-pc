/**@(#)Quadratic & cubic roots
**/

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>

Bool    quadratic_roots(double a, double b, double c, double *x1, double *x2)
{
    double  disc = b * b - 4.0 * a * c;

    /** assumes non-degenerate quadratic **/

    if (b < 0)
    {
	a *= -1.0;
	b *= -1.0;
	c *= -1.0;
    }
    if (disc >= 0)
    {				/**real roots **/
	double  q = -0.5 * (b + sqrt(disc));

	*x1 = q / a;
	*x2 = c / q;
	return (true);
    } else
    {
	*x1 = -b / (2.0 * a);	/** real part **/
	*x2 = sqrt(-disc) / (2.0 * a);	/** imag part **/
	return (false);
    }
}

Bool    cubic_roots(double a, double b, double c, double d, double *x1, double *x2, double *x3)
{
    double  disc, q, r;

    /** assumes non-degenerate cubic **/
    b /= a;
    c /= a;
    d /= a;

    q = (b * b - 3.0 * c) / 9.0;
    r = (2.0 * b * b * b - 9.0 * b * c + 27.0 * d) / 54.0;
    disc = q * q * q - r * r;

    if (disc >= 0)
    {
	double  theta;
	double  sq = sqrt(q), b3 = b / 3.0, sq3;

	sq3 = sq * sq * sq;
	if (sq3 == 0.0)
	    theta = 0.0;	/**arbitrary**/
	else
	    theta = acos(r / sq3);

	*x1 = -2.0 * sq * cos(theta / 3.0) - b3;
	*x2 = -2.0 * sq * cos((theta + TWOPI) / 3.0) - b3;
	*x3 = -2.0 * sq * cos((theta + 2.0 * TWOPI) / 3.0) - b3;
	return (true);
    } else
    {
	double  s = pow(fabs(r) + sqrt(-disc), 1.0 / 3.0);
	double  b3 = b / 3.0;
	double  x;

	if (r >= 0.0)
	    x = -(s + q / s);
	else
	    x = (s + q / s);

	x -= b3;

	b += x;
	c += x * b;

	*x1 = x;		/** real root **/
	return (quadratic_roots(1.0, b, c, x2, x3));	/** complex roots **/
    }
}
