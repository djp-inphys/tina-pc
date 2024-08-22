/**@(#)Univariate minimisation
**/

double  sqrt(double);

/**
Golden section search for a minimum of f(x, fdata) in the interval [a, b].
Minimum is located to within tolerance defined by function tol(v1, v2, tdata)
**/

double  golden_section(double (*f) ( /* ??? */ ), double a, double b, int (*tol) ( /* ??? */ ), void *fdata, void *tdata)

/* tolerance function */

{
    double  t1 = 1.0 - 0.5 * (sqrt(5.0) - 1.0);
    double  c, d, fc, fd;

    c = a + t1 * (b - a);
    fc = f(c, fdata);
    d = b - t1 * (b - a);
    fd = f(d, fdata);

    do
    {
	if (fc < fd)
	{
	    b = d;
	    d = c;
	    c = a + t1 * (b - a);
	    fd = fc;
	    fc = f(c, fdata);
	} else
	{
	    a = c;
	    c = d;
	    d = b - t1 * (b - a);
	    fc = fd;
	    fd = f(d, fdata);
	}
    } while (tol(a, b, tdata));

    if (fc < fd)
	return (0.5 * (a + d));
    else
	return (0.5 * (c + b));
}
