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

double  conic_chi2(Vec2 p, Conic * conic, Conic_stat * stats)
{
    double  px = vec2_x(p);
    double  py = vec2_y(p);
    double  z, h[5], uh[5];
    double  sum;
    int     i, j;

    if (conic == NULL || stats == NULL)
	return (0.0);

    z = conic_eval(conic, p);
    h[0] = px * px - py * py;
    h[1] = 2.0 * px * py;
    h[2] = 2.0 * px;
    h[3] = 2.0 * py;
    h[4] = 1.0;

    for (i = 0; i < 5; i++)
    {
	sum = 0.0;
	for (j = 0; j < i; j++)
	    sum += stats->u[j][i] * h[j];
	sum += h[i];
	uh[i] = sum;
    }

    sum = 0.0;
    for (i = 0; i < 5; i++)
	sum += uh[i] * stats->d[i] * uh[i];

    return (chisq(z * z / sum, 1));
}

static double neglength(void *geom, int type)
{
    switch (type)
    {
	case CONIC2:
	return (-conic_approx_length((Conic *) geom, 2));
    default:
	return (0.0);
    }
}

#if 0
static double closeness(void *geom, int type, Conic * conic1)
{
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    Vec2    q1 = {Vec2_id};
    Vec2    q2 = {Vec2_id};
    double  d11, d12, d21, d22;

    p1 = conic_point(conic1, conic1->t1);
    p2 = conic_point(conic1, conic1->t2);

    switch (type)
    {
    case CONIC2:
	{
	    Conic  *conic = (Conic *) geom;

	    q1 = conic_point(conic, conic->t1);
	    q2 = conic_point(conic, conic->t2);
	    break;
	}
    case LINE2:
	{
	    Line2  *line = (Line2 *) geom;

	    q1 = line->p1;
	    q2 = line->p2;
	    break;
	}
    default:
	return (1e10);
    }

    d11 = vec2_dist(p1, q1);
    d12 = vec2_dist(p1, q2);
    d21 = vec2_dist(p2, q1);
    d22 = vec2_dist(p2, q2);
    return (MIN4(d11, d12, d21, d22));
}

#endif

static Conic *conic_of_line(Line2 * line)
{
    Tstring *str = (Tstring *) prop_get(line->props, STRING);
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    Vec2    p3 = {Vec2_id};

    if (str->count < 3)
	return (NULL);

    DD_GET_POS2(str->start, p1);
    DD_GET_POS2(str_mid_point(str), p2);
    DD_GET_POS2(str->end, p3);

    return (conic_circ_3pt(p1, p2, p3));
}

Bool    conic_param_between(double t, double t1, double t2)
/* always in range 0 to 2PI */
/* t2 always > t1  and t1 is less than 2 PI */
{
    if (t < t1)
	t += TWOPI;

    return ((t < t2) ? true : false);
}

#define MAXRATIO(a, b) MAX((a)/(b), (b)/(a))

/* check if a pair of conics are compatible for combination */
static Bool conics_compatible(Conic * conic1, Conic * conic2, double low_conf, double hi_conf)
{
    Vec2    p1 = {Vec2_id};
    Vec2    g1 = {Vec2_id};
    Vec2    e1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    Vec2    g2 = {Vec2_id};
    Vec2    e2 = {Vec2_id};
    Vec2    e11 = {Vec2_id};
    Vec2    e12 = {Vec2_id};
    Vec2    e21 = {Vec2_id};
    Vec2    e22 = {Vec2_id};
    Conic_stat *stats1;
    Conic_stat *stats2;
    double  chi1, chi2;
    double  d11, d12, d21, d22;
    double  len1, len2;
    double  rad1, rad2;
    double  t, min_dist;

    if (conic1 == NULL || conic2 == NULL)
	return (false);

    /** conic mid points **/
    p1 = conic_point(conic1, 0.5 * (conic1->t1 + conic1->t2));
    p2 = conic_point(conic2, 0.5 * (conic2->t1 + conic2->t2));

    stats1 = (Conic_stat *) prop_get(conic1->props, STATS);
    stats2 = (Conic_stat *) prop_get(conic2->props, STATS);

    chi1 = conic_chi2(p1, conic2, stats2);
    chi2 = conic_chi2(p2, conic1, stats1);

    /* test for evidence of continuation from chi test */
    if (stats2 != NULL && stats1 != NULL)
    {
	if (chi1 < low_conf && chi2 < low_conf)
	    return (false);
    } else if (stats2 != NULL)
    {
	if (chi1 < low_conf)
	    return (false);
    } else if (stats1 != NULL)
    {
	if (chi2 < low_conf)
	    return (false);
    }
    /* get end points */
    e11 = conic_point(conic1, conic1->t1);
    e12 = conic_point(conic1, conic1->t2);
    e21 = conic_point(conic2, conic2->t1);
    e22 = conic_point(conic2, conic2->t2);

    /* check the conics do not overlap */

    t = conic_param(conic2, e11);
    if (conic_param_between(t, conic2->t1, conic2->t2))
	return (false);

    t = conic_param(conic2, e12);
    if (conic_param_between(t, conic2->t1, conic2->t2))
	return (false);

    t = conic_param(conic1, e21);
    if (conic_param_between(t, conic1->t1, conic1->t2))
	return (false);

    t = conic_param(conic1, e21);
    if (conic_param_between(t, conic1->t1, conic1->t2))
	return (false);

    /* distances between end points */
    d11 = vec2_dist(e11, e21);
    d12 = vec2_dist(e11, e22);
    d21 = vec2_dist(e12, e21);
    d22 = vec2_dist(e12, e22);
    min_dist = MIN4(d11, d12, d21, d22);

    /* if very close end points  then TRUE */
    if (min_dist < 10)
	return (true);

    if (min_dist == d11)
    {
	e1 = e11;
	e2 = e21;
    } else if (min_dist == d12)
    {
	e1 = e11;
	e2 = e22;
    } else if (min_dist == d21)
    {
	e1 = e12;
	e2 = e21;
    } else
    {
	e1 = e12;
	e2 = e22;
    }

    len1 = conic_approx_length(conic1, 5);
    len2 = conic_approx_length(conic2, 5);

    /* if either of the lines is short then FALSE */
    if (len1 < 20 || len2 < 20)
	return (false);

    /* if the gap is shorter than both of the lines then TRUE */
    if (min_dist > len1 || min_dist > len2)
	return (false);

    g1 = vec2_unit(conic_grad(conic1, e1));
    g2 = vec2_unit(conic_grad(conic2, e2));

    /* if ends are co-tangental then TRUE */
    if (fabs(vec2_dot(g1, g2)) > 0.9)
    {
	Vec2    t = {Vec2_id};

	t = vec2_unit(vec2_diff(e2, e1));
	if (fabs(vec2_dot(g1, t)) < 0.15 && fabs(vec2_dot(g2, t)) < 0.15)
	    return (true);
    }
    rad1 = MAX(conic1->alpha, conic1->beta);
    rad2 = MAX(conic2->alpha, conic2->beta);

    /** gross test for closeness **/
    if (vec2_dist(p2, conic1->center) > 3.0 * rad1 &&
	vec2_dist(p1, conic2->center) > 3.0 * rad2)
	return (false);

    if (chi1 > hi_conf || chi2 > hi_conf)
	return (true);

    /** gradients and concavity sign at test point match approximately **/
    g1 = vec2_unit(conic_grad(conic1, p2));
    g2 = vec2_unit(conic_grad(conic2, p2));
    if (vec2_dot(g1, g2) > 0.95)
	return (true);
    g1 = vec2_unit(conic_grad(conic1, p1));
    g2 = vec2_unit(conic_grad(conic2, p1));
    if (vec2_dot(g1, g2) > 0.95)
	return (true);

    return (false);
}

static Bool conic_and_geom_compatible(Conic * conic1, void *geom, int type, double low_conf, double hi_conf)
{
    switch (type)
    {
	case CONIC2:
	return (conics_compatible(conic1, (Conic *) geom, low_conf, hi_conf));
    case LINE2:
	{
	    Conic  *conic2 = conic_of_line((Line2 *) geom);
	    Bool    result;

	    if (conic2 == NULL)
		return (false);
	    result = conics_compatible(conic1, conic2, low_conf, hi_conf);
	    conic_free(conic2);
	    return (result);
	}
    default:
	return (false);
    }
}

static Conic *conic_join_strings(Tstring * str1, Tstring * str2, double lo_th, double hi_th, int max_div)
{
    Tstring *str;
    Conic  *conic;
    List   *strings;

    str = es_combine(str1, str2);
    conic = (Conic *) conic_ellipse_fit(str->start, str->end, 0.2);
    if (conic == NULL)
    {
	str_rm(str, (void (*) ()) NULL);
	return (NULL);
    }
    conic->props = proplist_add(conic->props, (void *) str, STRING, str_rm_only_str);

    strings = list_of(STRING, str1, STRING, str2, NULL);
    if (!conic_check_list(conic, strings, lo_th, hi_th, max_div))
    {
	conic_free(conic);
	list_rm_links(strings);
	return (NULL);
    }
    list_rm_links(strings);
    return (conic);
}

static Conic *conic_join_list(List * list, double lo_th, double hi_th, int max_div)
{
    Tstring *str;
    Conic  *conic;

    list = list_copy(list, (void *(*) ()) NULL, NULL);
    list = es_list_order(list);
    str = es_list_cat(list);	/* total string */

    conic = (Conic *) conic_ellipse_fit(str->start, str->end, 0.2);
    if (conic == NULL)
    {
	str_rm(str, (void (*) ()) NULL);
	list_rm_links(list);
	return (NULL);
    }
    conic->props = proplist_add(conic->props, (void *) str, STRING, str_rm_only_str);

    if (!conic_check_list(conic, list, lo_th, hi_th, max_div))
    {
	conic_free(conic);
	list_rm_links(list);
	return (NULL);
    }
    list_rm_links(list);
    return (conic);
}

static Conic *conic_join_array(Tstring * str, int *t_array, Tstring ** s_array, int n, double lo_th, double hi_th, int max_div)
{
    List   *list = NULL;
    Conic  *conic;
    int     i;

    for (i = 0; i < n; ++i)
	if (t_array[i])
	    list = ref_addtostart(list, (void *) s_array[i], STRING);

    if (list == NULL)
	return (NULL);

    list = ref_addtostart(list, (void *) str, STRING);
    list = es_list_order(list);
    str = es_list_cat(list);	/* total string */

    conic = (Conic *) conic_ellipse_fit(str->start, str->end, 0.2);
    if (conic == NULL)
    {
	list_rm_links(list);
	str_rm(str, (void (*) ()) NULL);
	return (NULL);
    }
    conic->props = proplist_add(conic->props, (void *) str, STRING, str_rm_only_str);

    if (!conic_check_list(conic, list, lo_th, hi_th, max_div))
    {
	conic_free(conic);
	list_rm_links(list);
	return (NULL);
    }
    list_rm_links(list);
    return (conic);
}

static int rec_max_div;
static double rec_lo_thres, rec_hi_thres, max;
static Conic *best_conic;

static int *b_array;
static int *t_array;
static Tstring **s_array;
static Tstring *rec_str;
static int rec_n;

static void conic_rec_choose(int i, double val)
{
    if (i == rec_n)
    {
	Conic  *conic;

	if (val < max)
	    return;
	conic = conic_join_array(rec_str, t_array, s_array, rec_n,
			     rec_lo_thres, rec_hi_thres, rec_max_div);
	if (conic == NULL)
	    return;
	conic_free(best_conic);
	best_conic = conic;
	(void) memcpy((char *) b_array, (char *) t_array, rec_n * sizeof(int));
	max = val;
	return;
    }
    t_array[i] = 1;
    conic_rec_choose(i + 1, val + s_array[i]->count);
    t_array[i] = 0;
    conic_rec_choose(i + 1, val);
}

static Conic *best_from_list(Conic * conic, List * list, List ** con_list, double lo_thres, double hi_thres, int max_div)
{
    Conic  *new_con;
    List   *ptr;
    List   *slist;
    int     i;

    if (conic == NULL || list == NULL)
	return (NULL);

    slist = reclist_list_update(list, geom_prop_update_get, (int) NULL, (void *) STRING);
    slist = ref_addtostart(slist, (void *) prop_get(conic->props, STRING), STRING);
    new_con = conic_join_list(slist, lo_thres, hi_thres, max_div);
    list_rm_links(slist);

    if (new_con != NULL)
    {
	/* the whole list is consistent */
	*con_list = list_copy(list, (void *(*) ()) NULL, NULL);
	return (new_con);
    }
    best_conic = NULL;
    rec_lo_thres = lo_thres;
    rec_hi_thres = hi_thres;
    rec_max_div = max_div;
    rec_str = (Tstring *) prop_get(conic->props, STRING);
    rec_n = list_length(list);
    t_array = ivector_alloc(0, rec_n);
    b_array = ivector_alloc(0, rec_n);
    s_array = (Tstring **) pvector_alloc(0, rec_n);

    for (i = 0, ptr = list; ptr != NULL; i++, ptr = ptr->next)
    {
	t_array[i] = b_array[i] = 0;
	s_array[i] = (Tstring *) geom_prop_get(ptr->to, ptr->type, STRING);
    }
#ifdef _ICC
    {
	double  zero = 0.0;

	conic_rec_choose(0, zero);
    }
#else
    conic_rec_choose(0, 0.0);
#endif

    *con_list = NULL;
    for (i = 0, ptr = list; ptr != NULL; i++, ptr = ptr->next)
	if (b_array[i])
	    *con_list = ref_addtostart(*con_list, (void *) ptr->to, ptr->type);

    ivector_free((void *) t_array, 0);
    ivector_free((void *) b_array, 0);
    pvector_free((void *) s_array, 0);

    return (best_conic);
}

static double str_tres;

void   *conic_pos_thres(void *pos, int type, Conic * conic)
{
    Vec2    p = {Vec2_id};
    double  t;

    GET_POS2(pos, type, p);
    t = conic_param(conic, p);
    t = vec2_sqrdist(p, conic_point(conic, t));
    if (t > str_tres)
	return (NULL);
    return (pos);
}

Tstring *conic_threshold_string(Conic * conic, Tstring * string, double thres)
{
    str_tres = thres;
    return (reclist_string_copy(string, conic_pos_thres, (int) NULL, (void *) conic));
}

Vec2    geom2_mid_point(void *geom, int type)
{
    switch (type)
    {
	case POINT2:
	return (((Point2 *) geom)->p);
    case LINE2:
	{
	    Vec2    p1 = {Vec2_id};
	    Vec2    p2 = {Vec2_id};

	    p1 = ((Line2 *) geom)->p1;
	    p2 = ((Line2 *) geom)->p2;

	    return (vec2_times(0.5, vec2_sum(p1, p2)));
	}
    case CONIC2:
	{
	    double  t1 = ((Conic *) geom)->t1;
	    double  t2 = ((Conic *) geom)->t2;

	    return (conic_point((Conic *) geom, (t1 + t2) * 0.5));
	}
    default:
	return (vec2_zero());	/* could be MAXFLOAT */
    }
}

Vec2    geom2_p1(void *geom, int type)
{
    switch (type)
    {
	case POINT2:
	return (((Point2 *) geom)->p);
    case LINE2:
	return (((Line2 *) geom)->p1);
    case CONIC2:
	return (conic_point((Conic *) geom, ((Conic *) geom)->t1));
    default:
	return (vec2_zero());	/* could be MAXFLOAT */
    }
}

Vec2    geom2_p2(void *geom, int type)
{
    switch (type)
    {
	case POINT2:
	return (((Point2 *) geom)->p);
    case LINE2:
	return (((Line2 *) geom)->p2);
    case CONIC2:
	return (conic_point((Conic *) geom, ((Conic *) geom)->t2));
    default:
	return (vec2_zero());	/* could be MAXFLOAT */
    }
}

static void geom2_mid_add_to_index(void *geom, int type, Windex * index)
{
    Ipos    pos = {Ipos_id};

    pos = wx_get_index(index, geom2_mid_point(geom, type));
    wx_add_entry(index, geom, type, ipos_y(pos), ipos_x(pos));
}

static void geom2_mid_rm_from_index(void *geom, int type, Windex * index)
{
    Ipos    pos = {Ipos_id};

    pos = wx_get_index(index, geom2_mid_point(geom, type));
    wx_rm_entry(index, geom, ipos_y(pos), ipos_x(pos));
}

/* ARGSUSED quieten lint */
static void vec2_inc_region(Vec2 p, int type, Imregion * roi)
{
    int     x, y;

    x = (int)floor(vec2_x(p));
    y = (int)floor(vec2_y(p));

    if (roi->lx == LARGEST_INT)
    {
	roi->lx = roi->ux = x;
	roi->ly = roi->uy = y;
	return;
    }
    if (x < roi->lx)
	roi->lx = x;
    if (y < roi->ly)
	roi->ly = y;
    if (x > roi->ux)
	roi->ux = x;
    if (y > roi->uy)
	roi->uy = y;
}


static void geom_inc_region(void *geom, int type, Imregion * roi)
{
    vec2_inc_region(geom2_mid_point(geom, type), VEC2, roi);
    vec2_inc_region(geom2_p1(geom, type), VEC2, roi);
    vec2_inc_region(geom2_p2(geom, type), VEC2, roi);
}

Windex *geom_mid_point_index_build(List * geom, Imregion * region)
{
    Windex *index;
    int     m, n;

    if (region == NULL)
    {
	region = roi_alloc(LARGEST_INT, LARGEST_INT, LARGEST_INT, LARGEST_INT);
	reclist_list_apply(geom, geom_inc_region, (int) NULL, (void *) region);
	region->lx -= 20;
	region->ly -= 20;
	region->ux += 20;
	region->uy += 20;
    }
    m = (region->uy - region->ly) / 20 + 1;
    n = (region->ux - region->lx) / 20 + 1;
    index = wx_alloc(region, m, n, GEOMETRY_2);
    reclist_list_apply(geom, geom2_mid_add_to_index, (int) NULL, (void *) index);
    return (index);
}

List   *geom_from_index(Conic * conic, Conic_stat * stats, Windex * index, char **mask, Ipos p, double conf)
{
    int     i, ii, j, jj;
    Vec2    v = {Vec2_id};
    Vec2    v1 = {Vec2_id};
    Vec2    v2 = {Vec2_id};
    List   *list = NULL;
    double  t;

    i = ipos_y(p);
    j = ipos_x(p);

    if (wx_in_index(index, i, j) == false || mask[i][j])
	return (NULL);

    mask[i][j] = 1;

    v = wx_get_mid_pos2(index, p);
    t = conic_param(conic, v);
    if (t < conic->t1)
    {
	if (t + TWOPI < conic->t2)
	    return (NULL);
    } else if (t < conic->t2)
	return (NULL);

    v1 = wx_get_pos2(index, p);
    v2 = wx_get_pos2(index, ipos(j + 1, i + 1));

    if (conic_chi2(v, conic, stats) < conf &&
	conic_chi2(v1, conic, stats) < conf &&
	conic_chi2(v2, conic, stats) < conf &&
	conic_chi2(wx_get_pos2(index, ipos(j, i + 1)), conic, stats) < conf &&
	conic_chi2(wx_get_pos2(index, ipos(j + 1, i)), conic, stats) < conf)
    {
	v = conic_point(conic, t);	/* closest point on conic */

	/* does the conic NOT pass through this grid point */
	if (!BETWEEN(vec2_x(v), vec2_x(v1), vec2_x(v2)) ||
	    !BETWEEN(vec2_y(v), vec2_y(v1), vec2_y(v2)))
	    return (NULL);
    }
    list = list_copy((List *) wx_get(index, i, j), (void *(*) ()) NULL, NULL);

    for (ii = -1; ii <= 1; ++ii)
	for (jj = -1; jj <= 1; ++jj)
	    if (ii != 0 || jj != 0)
	    {
		List   *sub;

		p = ipos(j + jj, i + ii);
		sub = geom_from_index(conic, stats, index, mask, p, conf);
		list = list_append(sub, list);
	    }
    return (list);
}

static Bool conic_below_thres(Conic * c, double ang_th, double len_th)

/* angle threshold in radians */
/* angle threshold in radians */
{
    if (c == NULL)
	return (true);

    if (c->t2 - c->t1 > ang_th)
	return (false);

    if (conic_approx_length(c, 10) > len_th)
	return (false);

    return (true);
}

List   *conic_join(List * geom, Imregion * roi, double conf, double lo_thres, double hi_thres, int max_div)
{
    List   *newgeom;
    List   *ptr1;
    Windex *index;
    char  **mask;
    int     m, n;
    int     i, j;

    if (geom == NULL)
	return (NULL);

    /** flatten input list, then sort by approx length **/
    newgeom = reclist_list_flat(geom, (void *(*) ()) NULL, (int) NULL, NULL);
    newgeom = sort_list(newgeom, neglength, NULL);

    index = geom_mid_point_index_build(newgeom, roi);
    m = index->m;
    n = index->n;
    mask = carray_alloc(0, 0, m, n);

    ptr1 = newgeom;
    while (ptr1 != NULL)
    {
	Conic  *conic;
	Conic  *new_conic;
	Conic_stat *stats;
	List   *ptr2;
	List   *test_geom;
	Tstring *str1, *str2;
	Bool    changed = false;
	Vec2    v = {Vec2_id};
	Ipos    p = {Ipos_id};

	if (ptr1->type != CONIC2 || conic_below_thres((Conic *) ptr1->to, 0.5, 20.0))
	{
	    ptr1 = ptr1->next;
	    continue;
	}
	conic = (Conic *) ptr1->to;

	stats = (Conic_stat *) prop_get(conic->props, STATS);
	if (stats == NULL)
	{
	    ptr1 = ptr1->next;
	    continue;
	}
	for (i = 0; i < m; ++i)
	    for (j = 0; j < n; ++j)
		mask[i][j] = 0;

	v = conic_point(conic, PI + (conic->t1 + conic->t2) * 0.5);
	p = wx_get_index(index, v);
	test_geom = geom_from_index(conic, stats, index, mask, p, conf);
	v = conic_point(conic, conic->t1 - 0.1);
	p = wx_get_index(index, v);
	ptr2 = geom_from_index(conic, stats, index, mask, p, conf);
	test_geom = list_append(ptr2, test_geom);
	v = conic_point(conic, conic->t2 + 0.1);
	p = wx_get_index(index, v);
	ptr2 = geom_from_index(conic, stats, index, mask, p, conf);
	test_geom = list_append(ptr2, test_geom);

	do
	{
	    List   *compat = NULL;
	    List   *chosen = NULL;

	    str1 = (Tstring *) prop_get(conic->props, STRING);

	    /** find candidates for joining **/
	    for (ptr2 = test_geom; ptr2 != NULL; ptr2 = ptr2->next)
	    {
		if (ptr1->to == ptr2->to)	/* the same conic */
		    continue;

		if (conic_and_geom_compatible(conic, ptr2->to, ptr2->type, conf, 0.1))
		{
		    str2 = (Tstring *) geom_prop_get(ptr2->to, ptr2->type, STRING);
		    new_conic = conic_join_strings(str1, str2, lo_thres, hi_thres, max_div);
		    if (new_conic == NULL)
			continue;

		    conic_free(new_conic);
		    compat = ref_addtostart((List *) compat, (void *) ptr2->to, ptr2->type);
		}
	    }

	    new_conic = best_from_list(conic, compat, &chosen, lo_thres, hi_thres, max_div);
	    list_rm_links(compat);

	    if (new_conic != NULL)	/** new fit suceeded **/
	    {
		changed = true;
		for (ptr2 = chosen; ptr2 != NULL; ptr2 = ptr2->next)
		{
		    test_geom = list_rm_ref(test_geom, ptr2->to, (void (*) ()) NULL);
		    geom2_mid_rm_from_index(ptr2->to, ptr2->type, index);
		    newgeom = list_rm_ref(newgeom, ptr2->to, (void (*) ()) geom_free);
		}
		list_rm_links(chosen);

		str2 = (Tstring *) prop_get(new_conic->props, STRING);
		str2 = conic_threshold_string(new_conic, str2, lo_thres);
		(void) prop_set(new_conic->props, (void *) str2, STRING, true);

		conic_free(conic);

		geom2_mid_rm_from_index(ptr1->to, ptr1->type, index);
		ptr1->to = conic = new_conic;
		geom2_mid_add_to_index(ptr1->to, ptr1->type, index);
	    }
	} while (new_conic != NULL);
	list_rm_links(test_geom);
	if (changed == false)
	    ptr1 = ptr1->next;
    }
    (void) reclist_list_free(geom, (void (*) ()) NULL, (int) NULL, NULL);
    wx_free(index, list_rm_links);

    return (newgeom);
}

List   *conic_compatible(Conic * conic, List * geom, double lo_thres, double hi_thres, int max_div)
{
    Conic  *new_conic;
    List   *ptr;
    List   *candidates = NULL;
    Tstring *str1, *str2;

    geom = reclist_list_flat(geom, (void *(*) ()) NULL, (int) NULL, NULL);
    str1 = (Tstring *) prop_get(conic->props, STRING);

    /** find candidates for joining **/
    for (ptr = geom; ptr != NULL; ptr = ptr->next)
    {
	if (conic == ptr->to)	/* the same conic */
	    continue;

	if (conic_and_geom_compatible(conic, ptr->to, ptr->type, 0.01, 0.1))
	{
	    str2 = (Tstring *) geom_prop_get(ptr->to, ptr->type, STRING);
	    new_conic = conic_join_strings(str1, str2, lo_thres, hi_thres, max_div);
	    if (new_conic == NULL)
		continue;
	    conic_free(new_conic);
	    candidates = ref_addtostart((List *) candidates, (void *) ptr->to, ptr->type);
	}
    }
    list_rm_links(geom);
    return (candidates);
}
