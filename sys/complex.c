/**@(#)Complex handling.
 * @(#)Complex is {float x; float y;}
**/

#include <math.h>
#include <tina/sys.h>

Complex cmplx_sum(Complex a, Complex b)
{
    Complex c = {Complex_id};

    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return (c);
}

Complex cmplx_diff(Complex a, Complex b)
{
    Complex c = {Complex_id};

    c.x = a.x - b.x;
    c.y = a.y - b.y;
    return (c);
}

Complex cmplx_minus(Complex a)
{
    Complex c = {Complex_id};

    c.x = -a.x;
    c.y = -a.y;
    return (c);
}

Complex cmplx_prod(Complex a, Complex b)
{
    Complex c = {Complex_id};

    c.x = a.x * b.x - a.y * b.y;
    c.y = a.y * b.x + a.x * b.y;
    return (c);
}

Complex cmplx_cprod(Complex a, Complex b)
{
    Complex c = {Complex_id};

    /** a times conjugate of b **/
    c.x = a.x * b.x + a.y * b.y;
    c.y = a.y * b.x - a.x * b.y;
    return (c);
}

Complex cmplx_times(double a, Complex b)
{
    Complex c = {Complex_id};

    c.x = a * b.x;
    c.y = a * b.y;
    return (c);
}

Complex cmplx(double x, double y)
{
    Complex c = {Complex_id};

    c.x = x;
    c.y = y;
    return (c);
}

Complex cmplx_zero(void)
{
    Complex zero = {Complex_id};

    zero.x = zero.y = 0.0;
    return (zero);
}

Complex cmplx_unit(void)
{
    Complex unit = {Complex_id};

    unit.x = 1.0;
    unit.y = 0.0;
    return (unit);
}

Complex cmplx_conj(Complex z)
{
    Complex c = {Complex_id};

    c.x = z.x;
    c.y = -z.y;
    return (c);
}

Complex cmplx_div(Complex a, Complex b)
{
    Complex c = {Complex_id};
    double  r, den;

    if (fabs(b.x) >= fabs(b.y))
    {
	r = b.y / b.x;
	den = b.x + r * b.y;
	c.x = (a.x + r * a.y) / den;
	c.y = (a.y - r * a.x) / den;
    } else
    {
	r = b.x / b.y;
	den = b.y + r * b.x;
	c.x = (a.x * r + a.y) / den;
	c.y = (a.y * r - a.x) / den;
    }
    return (c);
}

double  cmplx_mod(Complex z)
{
    double  x, y, ans, temp;

    x = fabs(z.x);
    y = fabs(z.y);
    if (x == 0.0)
	ans = y;
    else if (y == 0.0)
	ans = x;
    else if (x > y)
    {
	temp = y / x;
	ans = x * sqrt(1.0 + temp * temp);
    } else
    {
	temp = x / y;
	ans = y * sqrt(1.0 + temp * temp);
    }
    return (ans);
}

double  cmplx_sqrmod(Complex z)
{
    double  x, y;

    x = z.x;
    y = z.y;
    return (x * x + y * y);
}

double  cmplx_arg(Complex z)
{
    if (z.x == 0.0 && z.y == 0.0)
	return (0.0);
    return (atan2(z.y, z.x));
}

Complex cmplx_phase(Complex z)
{
    double  r = cmplx_mod(z);

    if (r == 0.0)
	return (cmplx(1.0, 0.0));
    else
	return (cmplx(z.x / r, z.y / r));
}

Complex cmplx_sqr(Complex a)
{
    Complex c = {Complex_id};

    c.x = a.x * a.x - a.y * a.y;
    c.y = a.y * a.x + a.x * a.y;
    return (c);
}

Complex cmplx_sqrt(Complex z)
{
    Complex c = {Complex_id};
    double  x, y, w, r;

    if ((z.x == 0.0) && (z.y == 0.0))
    {
	c.x = 0.0;
	c.y = 0.0;
	return (c);
    } else
    {
	x = fabs(z.x);
	y = fabs(z.y);
	if (x >= y)
	{
	    r = y / x;
	    w = sqrt(x) * sqrt(0.5 * (1.0 + sqrt(1.0 + r * r)));
	} else
	{
	    r = x / y;
	    w = sqrt(y) * sqrt(0.5 * (r + sqrt(1.0 + r * r)));
	}
	if (z.x >= 0.0)
	{
	    c.x = w;
	    c.y = z.y / (2.0 * w);
	} else
	{
	    c.y = (z.y >= 0) ? w : -w;
	    c.x = z.y / (2.0 * c.y);
	}
	return (c);
    }
}

Complex cmplx_log(Complex z)
{
    Complex l = {Complex_id};

    l.x = 0.5 * log(z.x * z.x + z.y * z.y);
    l.y = atan2(z.y, z.x);
    return (l);
}

Complex cmplx_exp(Complex z)
{
    Complex l = {Complex_id};
    double expx;
    double tany;

    expx = exp(z.x);
    tany = tan(z.y);
    l.x = expx/sqrt(1.0+tany*tany);
    l.y = expx/sqrt(1.0/(tany*tany) + 1.0);
    
    return (l);
}

Complex cmplx_sin(Complex z)
{
    Complex l = {Complex_id};

    l.x = sin(z.x) * cosh(z.y);
    l.y = cos(z.x) * sinh(z.y);
    return (l);
}

Complex cmplx_asin(Complex z)
{
    Complex l = {Complex_id};
    double alpha,beta,a,b;

    a = 0.5*sqrt((z.x + 1.0)*(z.x + 1.0) + z.y*z.y);
    b = 0.5*sqrt((z.x - 1.0)*(z.x - 1.0) + z.y*z.y);
    alpha = a+b;
    beta = a-b;

    l.x = asin(beta);
    l.y = log(alpha + sqrt(alpha*alpha -1.0));
    return (l);
}

Complex cmplx_cis(double theta)
{
    return (cmplx(cos(theta), sin(theta)));
}
