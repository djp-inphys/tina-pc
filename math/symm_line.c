/* @(#)Symmetric Double Step Line Algorithm by Brian Wyvill See
 * "Graphics Gems", Academic Press, 1990. */

#include <tina/math.h>
#define swap(a,b)           {a^=b; b^=a; a^=b;}
#define absolute(i,j,k)     ( (i-j)*(k = ( (i-j)<0 ? -1 : 1)))

static void apply_pix(int x, int y, int flag, void (*func) (), void *data)
{
    if (flag)
	func(y, x, data);
    else
	func(x, y, data);
}

void    apply_symmetric_line(Vec2 p1, Vec2 p2, void (*func) (), void *data)
{
    int     x1, y1;
    int     dx, dy, incr1, incr2, D, x, y, xend, c, pixels_left;
    int     sign_x, sign_y, step, reverse, j;
    int     a1 = (int) vec2_x(p1);
    int     b1 = (int) vec2_y(p1);
    int     a2 = (int) vec2_x(p2);
    int     b2 = (int) vec2_y(p2);

    dx = absolute(a2, a1, sign_x);
    dy = absolute(b2, b1, sign_y);

    if (sign_x == sign_y)
	step = 1;
    else
	step = -1;

    if (dy > dx)
    {
	swap(a1, b1);
	swap(a2, b2);
	swap(dx, dy);
	reverse = 1;
    } else
	reverse = 0;

    /* note: check for dx==0 should be included here */
    if (a1 > a2)
    {
	x = a2;
	y = b2;
	x1 = a1;
	y1 = b1;
    } else
    {
	x = a1;
	y = b1;
	x1 = a2;
	y1 = b2;
    }

    xend = (dx - 1) / 4;
    pixels_left = (dx - 1) % 4;
    apply_pix(x, y, reverse, func, data);

    if (pixels_left < 0)
	return;

    apply_pix(x1, y1, reverse, func, data);
    incr2 = 4 * dy - 2 * dx;

    if (incr2 < 0)		/* slope less than 1/2 */
    {
	c = 2 * dy;
	incr1 = 2 * c;
	D = incr1 - dx;

	for (j = 0; j < xend; j++)
	{
	    ++x;
	    --x1;
	    if (D < 0)
	    {
		apply_pix(x, y, reverse, func, data);
		apply_pix(++x, y, reverse, func, data);
		apply_pix(x1, y1, reverse, func, data);
		apply_pix(--x1, y1, reverse, func, data);
		D += incr1;
	    } else
	    {
		if (D < c)
		{
		    apply_pix(x, y, reverse, func, data);
		    y += step;
		    apply_pix(++x, y, reverse, func, data);
		    apply_pix(x1, y1, reverse, func, data);
		    y1 -= step;
		    apply_pix(--x1, y1, reverse, func, data);
		} else
		{
		    y += step;
		    apply_pix(x, y, reverse, func, data);
		    apply_pix(++x, y, reverse, func, data);
		    y1 -= step;
		    apply_pix(x1, y1, reverse, func, data);
		    apply_pix(--x1, y1, reverse, func, data);
		}
		D += incr2;
	    }
	}

	if (pixels_left)
	{
	    if (D < 0)
	    {
		apply_pix(++x, y, reverse, func, data);
		if (pixels_left > 1)
		    apply_pix(++x, y, reverse, func, data);
		if (pixels_left > 2)
		{
		    --x1;
		    apply_pix(x1, y1, reverse, func, data);
		}
	    } else
	    {
		if (D < c)
		{
		    apply_pix(++x, y, reverse, func, data);
		    if (pixels_left > 1)
		    {
			y += step;
			apply_pix(++x, y, reverse, func, data);
		    }
		    if (pixels_left > 2)
			apply_pix(--x1, y1, reverse, func, data);
		} else
		{
		    y += step;
		    apply_pix(++x, y, reverse, func, data);
		    if (pixels_left > 1)
			apply_pix(++x, y, reverse, func, data);
		    if (pixels_left > 2)
		    {
			y1 -= step;
			apply_pix(--x1, y1, reverse, func, data);
		    }
		}
	    }
	}
    } else
    {
	c = 2 * (dy - dx);
	incr1 = 2 * c;
	D = incr1 + dx;
	for (j = 0; j < xend; j++)
	{
	    ++x;
	    --x1;
	    if (D > 0)
	    {
		apply_pix(x, y += step, reverse, func, data);
		apply_pix(++x, y += step, reverse, func, data);
		apply_pix(x1, y1 -= step, reverse, func, data);
		apply_pix(--x1, y1 -= step, reverse, func, data);

		D += incr1;
	    } else
	    {
		if (D < c)
		{
		    apply_pix(x, y, reverse, func, data);
		    apply_pix(++x, y += step, reverse, func, data);
		    apply_pix(x1, y1, reverse, func, data);
		    apply_pix(--x1, y1 -= step, reverse, func, data);
		} else
		{
		    y += step;
		    apply_pix(x, y, reverse, func, data);
		    apply_pix(++x, y, reverse, func, data);
		    y1 -= step;
		    apply_pix(x1, y1, reverse, func, data);
		    apply_pix(--x1, y1, reverse, func, data);
		}
		D += incr2;
	    }
	}

	if (pixels_left)
	{
	    if (D > 0)
	    {
		apply_pix(++x, y += step, reverse, func, data);
		if (pixels_left > 1)
		{
		    y += step;
		    apply_pix(++x, y, reverse, func, data);
		}
		if (pixels_left > 2)
		{
		    y1 -= step;
		    apply_pix(--x1, y1, reverse, func, data);
		}
	    } else
	    {
		if (D < c)
		{
		    apply_pix(++x, y, reverse, func, data);
		    if (pixels_left > 1)
			apply_pix(++x, y += step, reverse, func, data);
		    if (pixels_left > 2)
			apply_pix(--x1, y1, reverse, func, data);
		} else
		{
		    apply_pix(++x, y += step, reverse, func, data);
		    if (pixels_left > 1)
			apply_pix(++x, y, reverse, func, data);
		    if (pixels_left > 2)
		    {
			if (D > c)
			    apply_pix(--x1, y1 -= step, reverse, func, data);
			else
			    apply_pix(--x1, y1, reverse, func, data);
		    }
		}
	    }
	}
    }
}
