/* @(#)Bresenham's line-drawing algorithm - blame Jim Ivins for any
 * bugs. Apply func to data at integer coordinates on a straight line
 * between p1 and p2 inclusive.  Plot an 8-way connected line if flag is
 * zero; else use 4-way connections. */

#include <tina/math.h>

void    apply_bresenham_line(Vec2 p1, Vec2 p2, int flag,
			             void (*func) (), void *data)
{
    int     temp, delta, pos_e, neg_e, tot_e;

    int     x1 = (int) vec2_x(p1);
    int     y1 = (int) vec2_y(p1);
    int     x2 = (int) vec2_x(p2);
    int     y2 = (int) vec2_y(p2);

    int     dx = (x1 > x2) ? (x1 - x2) : (x2 - x1);
    int     dy = (y1 > y2) ? (y1 - y2) : (y2 - y1);

    if (dy <= dx)
    {
	tot_e = 2 * dy - dx;
	pos_e = 2 * dy;
	neg_e = 2 * (dy - dx);

	if (x1 > x2)
	{
	    temp = x1;
	    x1 = x2;
	    x2 = temp;
	    temp = y1;
	    y1 = y2;
	    y2 = temp;
	}
	func(x1, y1, data);

	delta = (y1 < y2) ? +1 : -1;

	while (x1++ < x2)
	{
	    if (tot_e < 0)
		tot_e += pos_e;
	    else
	    {
		tot_e += neg_e;
		if (flag)
		    func(x1, y1, data);
		y1 += delta;
	    }
	    func(x1, y1, data);
	}
    } else
    {
	tot_e = 2 * dx - dy;
	pos_e = 2 * dx;
	neg_e = 2 * (dx - dy);

	if (y1 > y2)
	{
	    temp = y1;
	    y1 = y2;
	    y2 = temp;
	    temp = x1;
	    x1 = x2;
	    x2 = temp;
	}
	func(x1, y1, data);

	delta = (x1 < x2) ? +1 : -1;

	while (y1++ < y2)
	{
	    if (tot_e < 0)
		tot_e += pos_e;
	    else
	    {
		tot_e += neg_e;
		if (flag)
		    func(x1, y1, data);
		x1 += delta;
	    }
	    func(x1, y1, data);
	}
    }
}
