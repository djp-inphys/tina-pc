/**@(#)Ipos handling. Ipos is {int x; int y;}
**/

#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

/** for use with list utilities **/

Ipos   *ipos_alloc(void)
{
    Ipos   *pos = ts_ralloc(Ipos);

    pos->x = 0;
    pos->y = 0;
    return (pos);
}

Ipos   *ipos_make(int x, int y)
{
    Ipos   *pos = ts_ralloc(Ipos);

    pos->x = x;
    pos->y = y;
    return (pos);
}

void    ipos_free(void *pos)
{
    rfree((void *) pos);
}

Bool    ipos_equal(Ipos pos1, Ipos pos2)
{
    return ((Bool) ((ipos_x(pos1) == ipos_x(pos2)) &&
		    (ipos_y(pos1) == ipos_y(pos2))));
}


Ipos    ipos(int x, int y)
{
    Ipos    pos = {Ipos_id};

    pos.x = x;
    pos.y = y;
    return (pos);
}

Ipos    ipos_zero(void)
{
    return (ipos(0, 0));
}

Ipos    ipos_ex(void)
{
    return (ipos(1, 0));
}

Ipos    ipos_ey(void)
{
    return (ipos(0, 1));
}

void    ipos_comps(Ipos pos, int *x, int *y)
{
    *x = pos.x;
    *y = pos.y;
}

Ipos    ipos_sum(Ipos pos1, Ipos pos2)
{
    Ipos    sum = {Ipos_id};

    sum.x = pos1.x + pos2.x;
    sum.y = pos1.y + pos2.y;
    return (sum);
}

Ipos    ipos_sum3(Ipos pos0, Ipos pos1, Ipos pos2)
{
    Ipos    sum = {Ipos_id};

    sum.x = pos0.x + pos1.x + pos2.x;
    sum.y = pos0.y + pos1.y + pos2.y;
    return (sum);
}

Ipos    ipos_sum4(Ipos pos0, Ipos pos1, Ipos pos2, Ipos pos3)
{
    Ipos    sum = {Ipos_id};

    sum.x = pos0.x + pos1.x + pos2.x + pos3.x;
    sum.y = pos0.y + pos1.y + pos2.y + pos3.y;
    return (sum);
}

Ipos    ipos_minus(Ipos pos)
{
    Ipos    minus = {Ipos_id};

    minus.x = -pos.x;
    minus.y = -pos.y;
    return (minus);
}

Ipos    ipos_diff(Ipos pos1, Ipos pos2)
{
    Ipos    diff = {Ipos_id};

    diff.x = pos1.x - pos2.x;
    diff.y = pos1.y - pos2.y;
    return (diff);
}

Ipos    ipos_times(double k, Ipos pos)
{
    Ipos    prod = {Ipos_id};

    prod.x = (int) k * pos.x;
    prod.y = (int) k * pos.y;
    return (prod);
}

int     ipos_dot(Ipos pos1, Ipos pos2)
{
    return (pos1.x * pos2.x + pos1.y * pos2.y);
}

int     ipos_cross(Ipos pos1, Ipos pos2)
{
    return (pos1.x * pos2.y - pos1.y * pos2.x);
}

double  ipos_mod(Ipos pos)
{
    double  vx = pos.x, vy = pos.y;

    return (sqrt(vx * vx + vy * vy));
}

double  ipos_sqrmod(Ipos pos)
{
    double  vx = pos.x, vy = pos.y;

    return (vx * vx + vy * vy);
}

double  ipos_dist(Ipos pos1, Ipos pos2)
{
    double  dx = pos1.x - pos2.x;
    double  dy = pos1.y - pos2.y;

    return (sqrt(dx * dx + dy * dy));
}

int     ipos_manhattan(Ipos pos1, Ipos pos2)
{
    return (abs(pos1.x - pos2.x) + abs(pos1.y - pos2.y));
}

int     ipos_maxabs(Ipos pos1, Ipos pos2)
{
    int     dx = abs(pos1.x - pos2.x);
    int     dy = abs(pos1.y - pos2.y);

    return (MAX(dx, dy));
}

double  ipos_sqrdist(Ipos pos1, Ipos pos2)
{
    double  dx = pos1.x - pos2.x;
    double  dy = pos1.y - pos2.y;

    return (dx * dx + dy * dy);
}

double  ipos_dist_seg(Ipos p, Ipos e1, Ipos e2)
{
    double  x = ipos_x(p);
    double  y = ipos_y(p);
    double  x1 = ipos_x(e1);
    double  y1 = ipos_y(e1);
    double  x2 = ipos_x(e2);
    double  y2 = ipos_y(e2);
    double  dx, dy, dx1, dy1, l, t, d;

    dx = x2 - x1;
    dy = y2 - y1;
    dx1 = x - x1;
    dy1 = y - y1;
    l = sqrt(dx * dx + dy * dy);
    t = (dx1 * dx + dy1 * dy) / l;
    if (t < 0.0)
	d = sqrt(dx1 * dx1 + dy1 * dy1);
    else if (t > l)
	d = sqrt(sqr(x - x2) + sqr(y - y2));
    else
	d = fabs(dx1 * dy - dy1 * dx) / l;

    return (d);
}

Ipos    ipos_midpoint(Ipos p1, Ipos p2)
{
    return (ipos((p1.x + p2.x) / 2, (p1.y + p2.y) / 2));
}

Ipos    ipos_read(FILE * fp)
{
    Ipos    pos = {Ipos_id};

    (void) fscanf(fp, "%d %d", &pos.x, &pos.y);
    return (pos);
}

void    ipos_print(FILE * fp, Ipos pos)
{
    (void) fprintf(fp, "%d %d ", pos.x, pos.y);
}

void    ipos_pprint(FILE * fp, char *msg, Ipos pos)
{
    (void) fprintf(fp, "%s(%15d%15d)\n", msg, pos.x, pos.y);
}
