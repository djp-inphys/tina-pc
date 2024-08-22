/**@(#)
**/
#include <stdio.h>
#include <math.h>
#ifdef TRANSPUTER
#include <valuesdual.h>
#else
#include <values.h>
#endif
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* FORWARD REFS  */
static void label_grid_lines(List * lines, List ** inter_lines, int num, double grid_thres, double vert_thres, int *label);

static float invariant[9] =
{(float)0.416, (float)0.400, (float)0.375, (float)0.333, (float)0.250,
(float)0.750, (float)0.666, (float)0.625, (float)0.600};

void    grid_match(List * world, List * horiz_lines, List * vert_lines, double grid_thres, double vert_thres, void (*store_vertex) ( /* ??? */ ))
{
    List   *co_lines;
    List   *co_list;
    List  **horiz_grid;
    List  **vert_grid;
    Line2  *line1;
    Line2  *line2;
    Vec2   *vec2_inter_par_test();
    double  min_interx(List * ptr), min_intery(List * ptr);
    int    *horiz_label, *vert_label;
    int     horiz_num, vert_num;
    int     i, j, k, r, c, label;
    int     max_rec, max_num, repeat, num_rec;

    for (co_list = horiz_lines, horiz_num = 0; co_list != NULL; co_list = co_list->next)
	horiz_num++;
    for (co_list = vert_lines, vert_num = 0; co_list != NULL; co_list = co_list->next)
	vert_num++;
    if (horiz_num < 4 || vert_num < 4)
    {
	format("grid matcher failed:  insufficient co_linear lines\n");
	return;
    }
    horiz_grid = (List **) ralloc((unsigned) horiz_num * sizeof(List *));
    vert_grid = (List **) ralloc((unsigned) vert_num * sizeof(List *));
    horiz_label = (int *) ralloc((unsigned) horiz_num * sizeof(int));
    vert_label = (int *) ralloc((unsigned) vert_num * sizeof(int));

    for (i = 0; i < horiz_num; i++)
	horiz_grid[i] = NULL;
    for (i = 0; i < vert_num; i++)
	vert_grid[i] = NULL;

    for (co_list = horiz_lines, i = 0, j = 0; co_list != NULL; co_list = co_list->next)
    {
	co_lines = co_list->to;
	horiz_label[i] = -1;
	horiz_grid[i++] = co_lines;
    }

    for (co_list = vert_lines, i = 0, j = 0; co_list != NULL; co_list = co_list->next)
    {
	co_lines = co_list->to;
	vert_label[i] = -1;
	vert_grid[i++] = co_lines;
    }

    compute_horiz_invariants(world);
    for (i = 0, max_rec = 0, max_num = -1; i < horiz_num; i++)
    {
	label_grid_lines(horiz_grid[i], vert_grid, vert_num, grid_thres, vert_thres, vert_label);
	for (j = 0, repeat = 1, num_rec = 0; j < vert_num; j++)
	{
	    for (k = 0; k < vert_num; k++)
		if (j != k && vert_label[j] >= 0 && vert_label[j] == vert_label[k])
		    repeat = 0;
	    if (vert_label[j] >= 0)
		num_rec++;
	}
	if (num_rec > max_rec && repeat)
	{
	    max_rec = num_rec;
	    max_num = i;
	}
	if (num_rec == 8 && repeat)
	    break;
    }

    if (max_num >= 0 && i != max_num)
	label_grid_lines(horiz_grid[max_num], vert_grid, vert_num, grid_thres, vert_thres, vert_label);
    if (max_num < 0)
    {
	format("grid matcher failed to label vertical lines\n");
	rfree((void *) horiz_label);
	rfree((void *) horiz_grid);
	rfree((void *) vert_label);
	rfree((void *) vert_grid);
	return;
    }
    compute_vert_invariants(world);
    for (i = 0, max_rec = 0, max_num = -1; i < vert_num; i++)
    {
	label_grid_lines(vert_grid[i], horiz_grid, horiz_num, grid_thres, vert_thres, horiz_label);
	for (j = 0, repeat = 1, num_rec = 0; j < horiz_num; j++)
	{
	    for (k = 0; k < horiz_num; k++)
		if (j != k && horiz_label[j] >= 0 && horiz_label[j] == horiz_label[k])
		    repeat = 0;
	    if (horiz_label[j] >= 0)
		num_rec++;
	}
	if (num_rec > max_rec && repeat)
	{
	    max_rec = num_rec;
	    max_num = i;
	}
	if (num_rec == 8 && repeat)
	    break;;
    }
    if (max_num >= 0 && i != max_num)
	label_grid_lines(vert_grid[max_num], horiz_grid, horiz_num, grid_thres, vert_thres, horiz_label);
    if (max_num < 0)
    {
	format("grid matcher failed to label horizontal lines\n");
	rfree((void *) horiz_label);
	rfree((void *) horiz_grid);
	rfree((void *) vert_label);
	rfree((void *) vert_grid);
	return;
    }
    for (i = 0, max_rec = 0, max_num = -1; i < horiz_num; i++)
    {
	if ((r = horiz_label[i]) >= 0)
	{
	    for (j = 0; j < vert_num; j++)
	    {
		if ((c = vert_label[j]) >= 0)
		{
		    get_inter_lines(horiz_grid[i], vert_grid[j], vert_thres, &line1, &line2);
		    if (line1 != NULL && line2 != NULL)
		    {
			label = 8 * (7 - r) + c;
			store_vertex(world, line1, line2, label);
		    }
		}
	    }
	}
    }
    rfree((void *) horiz_label);
    rfree((void *) horiz_grid);
    rfree((void *) vert_label);
    rfree((void *) vert_grid);
}

static void label_grid_lines(List * lines, List ** inter_lines, int num, double grid_thres, double vert_thres, int *label)
{
    int     j, k, n, min_label;
    double  da, db, dc = 0.0, dd = 0.0;
    Vec2   *inter[64];
    Line2  *line1;
    Line2  *line2;

    for (j = 0; j < num; j++)
	label[j] = -1;
    for (j = 0; j < 64; j++)
	inter[j] = NULL;
    for (j = 0, n = 0; j < num; j++)
    {
	get_inter_lines(lines, inter_lines[j], vert_thres, &line1, &line2);
	if (line1 != NULL && line2 != NULL && n < 62)
	{
	    if ((inter[n] = vec2_inter_par_test(line1->p, line1->v, line2->p, line2->v, 0.97)))
	    {
		if (n >= 3)
		{
		    da = vec2_mod(vec2_diff(*(inter[n - 3]), *(inter[n - 2])));
		    db = vec2_mod(vec2_diff(*(inter[n - 1]), *(inter[n])));
		    dc = vec2_mod(vec2_diff(*(inter[n - 2]), *(inter[n])));
		    dd = vec2_mod(vec2_diff(*(inter[n - 3]), *(inter[n - 1])));
		    if (fabs(da * db - invariant[4] * dc * dd) < grid_thres * (da + dc))
			break;
		}
		n++;
	    }
	}
    }
    if ((fabs(da * db - invariant[4] * dc * dd) >= grid_thres * (da + dc))
	|| n < 3)
    {
	for (j = 0; j < 64; j++)
	    if (inter[j] != NULL)
		vec2_free((void *) inter[j]);
	return;
    }
    for (k = 0; k < num; k++)
    {
	get_inter_lines(lines, inter_lines[k], vert_thres, &line1, &line2);
	if (line1 != NULL && line2 != NULL)
	{
	    if ((inter[n + 1] = vec2_inter_par_test(line1->p, line1->v, line2->p, line2->v, 0.97)))
	    {
		if (vec2_mod(vec2_diff(*(inter[n - 3]), *(inter[n + 1]))) < 0.001)
		    label[k] = 6;
		else if (vec2_mod(vec2_diff(*(inter[n - 2]), *(inter[n + 1]))) < 0.001)
		    label[k] = 7;
		else if (vec2_mod(vec2_diff(*(inter[n - 1]), *(inter[n + 1]))) < 0.001)
		    label[k] = 8;
		else if (vec2_mod(vec2_diff(*(inter[n]), *(inter[n + 1]))) < 0.001)
		    label[k] = 9;
		else
		{
		    da = vec2_mod(vec2_diff(*(inter[n + 1]), *(inter[n - 2])));
		    db = vec2_mod(vec2_diff(*(inter[n - 1]), *(inter[n])));
		    dc = vec2_mod(vec2_diff(*(inter[n - 2]), *(inter[n])));
		    dd = vec2_mod(vec2_diff(*(inter[n + 1]), *(inter[n - 1])));
		    if (fabs(da * db - invariant[0] * dc * dd) < grid_thres * (da + db))
			label[k] = 2;
		    else if (fabs(da * db - invariant[1] * dc * dd) < grid_thres * (da + db))
			label[k] = 3;
		    else if (fabs(da * db - invariant[2] * dc * dd) < grid_thres * (da + db))
			label[k] = 4;
		    else if (fabs(da * db - invariant[3] * dc * dd) < grid_thres * (da + db))
			label[k] = 5;
		    else if (fabs(da * db - invariant[5] * dc * dd) < grid_thres * (da + db))
			label[k] = 10;
		    else if (fabs(da * db - invariant[6] * dc * dd) < grid_thres * (da + db))
			label[k] = 11;
		    else if (fabs(da * db - invariant[7] * dc * dd) < grid_thres * (da + db))
			label[k] = 12;
		    else if (fabs(da * db - invariant[8] * dc * dd) < grid_thres * (da + db))
			label[k] = 13;
		}
	    }
	}
    }
    for (k = 0, min_label = 14; k < num; k++)
    {
	if (label[k] > 0 && label[k] < min_label)
	    min_label = label[k];
    }
    for (k = 0; k < num; k++)
	if (label[k] > 0)
	    label[k] -= min_label;

    for (j = 0; j < 64; j++)
	if (inter[j] != NULL)
	    vec2_free((void *) inter[j]);
}

void    get_inter_lines(List * horiz, List * vert, double thres, Line2 ** hline, Line2 ** vline)
{
    List   *hptr;
    List   *vptr;

    for (hptr = horiz; hptr != NULL; hptr = hptr->next)
    {
	for (vptr = vert; vptr != NULL; vptr = vptr->next)
	{
	    *hline = hptr->to;
	    *vline = vptr->to;
	    if ((*hline)->length > 10.0 && (*vline)->length > 10.0)
		if (vec2_mod(vec2_diff((*hline)->p1, (*vline)->p1)) < thres
		    || vec2_mod(vec2_diff((*hline)->p1, (*vline)->p2)) < thres
		    || vec2_mod(vec2_diff((*hline)->p2, (*vline)->p1)) < thres
		    || vec2_mod(vec2_diff((*hline)->p2, (*vline)->p2)) < thres)
		{
		    return;
		}
	}
    }
    *hline = NULL;
    *vline = NULL;
}

double  min_interx(List * ptr)
{
    Line2  *line;
    Vec2    xaxis = {Vec2_id};
    Vec2    origin = {Vec2_id};
    Vec2   *vec2_inter_par_test();
    Vec2   *inters;
    double  inter = MAXDOUBLE;

    xaxis.el[0] = (float)1.0;
    xaxis.el[1] = (float)0.0;
    origin.el[0] = (float)0.0;
    origin.el[1] = (float)0.0;

    line = ptr->to;
    inters = vec2_inter_par_test(line->p, line->v, origin, xaxis, 0.97);
    if (inters != NULL)
    {
	inter = inters->el[0];
	rfree((void *) inters);
    }
    return (inter);
}

double  min_intery(List * ptr)
{
    Line2  *line;
    Vec2    yaxis = {Vec2_id};
    Vec2    origin = {Vec2_id};
    Vec2   *inters;
    Vec2   *vec2_inter_par_test();
    double  inter = MAXDOUBLE;

    yaxis.el[0] = (float)0.0;
    yaxis.el[1] = (float)1.0;
    origin.el[0] = (float)0.0;
    origin.el[1] = (float)0.0;

    line = ptr->to;
    inters = vec2_inter_par_test(line->p, line->v, origin, yaxis, 0.97);
    if (inters != NULL)
    {
	inter = inters->el[1];
	rfree((void *) inters);
    }
    return (inter);
}

void    compute_vert_invariants(List * world)
{
    List   *ptr;
    int     i;
    Match  *match_to_3d;
    Vec3   *vertex[8];
    float   da, db, dc, dd;

    for (i = 0; i < 64; i += 8)
    {
	for (ptr = world; ptr != NULL; ptr = ptr->next)
	{
	    match_to_3d = ptr->to;
	    if (match_to_3d->label == i)
	    {
		vertex[i / 8] = match_to_3d->to1;
		break;
	    }
	}
    }
    for (i = 4; i < 8; i++)
    {
	da = (float)vec3_mod(vec3_diff(*(vertex[i]), *(vertex[1])));
	db = (float)vec3_mod(vec3_diff(*(vertex[2]), *(vertex[3])));
	dc = (float)vec3_mod(vec3_diff(*(vertex[1]), *(vertex[3])));
	dd = (float)vec3_mod(vec3_diff(*(vertex[i]), *(vertex[2])));
	invariant[i + 1] = da * db / (dc * dd);
    }
    for (i = 0; i < 5; i++)
    {
	da = (float)vec3_mod(vec3_diff(*(vertex[i]), *(vertex[5])));
	db = (float)vec3_mod(vec3_diff(*(vertex[6]), *(vertex[7])));
	dc = (float)vec3_mod(vec3_diff(*(vertex[5]), *(vertex[7])));
	dd = (float)vec3_mod(vec3_diff(*(vertex[i]), *(vertex[6])));
	invariant[i] = da * db / (dc * dd);
    }
}

void    compute_horiz_invariants(List * world)
{
    List   *ptr;
    int     i;
    Match  *match_to_3d;
    Vec3   *vertex[8];
    float   da, db, dc, dd;

    for (i = 0; i < 8; i++)
    {
	for (ptr = world; ptr != NULL; ptr = ptr->next)
	{
	    match_to_3d = ptr->to;
	    if (match_to_3d->label == i)
	    {
		vertex[i] = match_to_3d->to1;
		break;
	    }
	}
    }
    for (i = 4; i < 8; i++)
    {
	da = (float)vec3_mod(vec3_diff(*(vertex[i]), *(vertex[1])));
	db = (float)vec3_mod(vec3_diff(*(vertex[2]), *(vertex[3])));
	dc = (float)vec3_mod(vec3_diff(*(vertex[1]), *(vertex[3])));
	dd = (float)vec3_mod(vec3_diff(*(vertex[i]), *(vertex[2])));
	invariant[i + 1] = da * db / (dc * dd);
    }
    for (i = 0; i < 5; i++)
    {
	da = (float)vec3_mod(vec3_diff(*(vertex[i]), *(vertex[5])));
	db = (float)vec3_mod(vec3_diff(*(vertex[6]), *(vertex[7])));
	dc = (float)vec3_mod(vec3_diff(*(vertex[5]), *(vertex[7])));
	dd = (float)vec3_mod(vec3_diff(*(vertex[i]), *(vertex[6])));
	invariant[i] = da * db / (dc * dd);
    }
}
