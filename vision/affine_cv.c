/**@(#)
**/
/* affine_cv.c
 * 
 * fitting plane curves to strings of matched edge points by recovering
 * affine transform
 * 
 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

#define HORIZONTAL_THRES 4

static Vec2 aprox_dir2(Ddlist * pos)
{
    Vec3    p1 = {Vec3_id};
    Vec3    p2 = {Vec3_id};
    Vec3    v3 = {Vec3_id};

    /* BUGFIX: was Vec3 v2 */
    Vec2    v2 = {Vec2_id};

    if (pos->next == NULL && pos->last == NULL)
	return (vec2_zero());

    if (pos->last != NULL)
	p1 = *(Vec3 *) pos->last->to;
    else
	p1 = *(Vec3 *) pos->to;

    if (pos->next != NULL)
	p2 = *(Vec3 *) pos->next->to;
    else
	p2 = *(Vec3 *) pos->to;

    v3 = vec3_diff(p2, p1);
    v2 = vec2_of_vec3(v3);
    return (vec2_unit(v2));
}

/* from string of disparity vectors find affine transform between
 * images */
int     affine_curve(Tstring * string, double *a, double *b, double *c, double *resid)
/* string of Vec3 (xl, y, xr-xl) */
/* for affine parameters Xl = a.Xr + b.Yr + c */
/* weighted sum sqr distance */
{
    Ddlist *start;
    Ddlist *end;
    Ddlist *ptr;
    Matrix *A;			/* each row of form  [wXr wYr w] */
    Vector *B;			/* vector of wXl */
    Vector *C;
    Vector *X;
    Vector *W;
    int     i, n;

    if (string == NULL)
	return (0);

    start = string->start;
    end = string->end;

    for (n = 1, ptr = start; ptr != end; ptr = ptr->next)
	++n;

    A = matrix_alloc(n, 3, matrix_full, double_v);
    B = vector_alloc(n, double_v);
    W = vector_alloc(n, double_v);

    /* BUGFIX sumw unused */
    /* double  sumw; sumw = 0; */

    for (i = 0, ptr = start; i < n; ++i, ptr = ptr->next)
    {
	Vec2    v2a = {Vec2_id};
	double  w = fabs(vec2_y(v2a));	/* weight by y component */
	Vec3    p = {Vec3_id};

	v2a = aprox_dir2(ptr);
	p = *(Vec3 *) ptr->to;

	VECTOR_DOUBLE(W, i) = w;
	VECTOR_DOUBLE(B, i) = vec3_x(p) * w;
	A->el.double_v[i][0] = (vec3_x(p) + vec3_z(p)) * w;
	A->el.double_v[i][1] = vec3_y(p) * w;
	A->el.double_v[i][2] = w;

	/* BUGFIX sumw unused */
	/* sumw += w; */
    }

    X = matrix_cholesky_least_square(A, B);	/* solve for affine
						 * parameters */
    if (X == NULL)
    {
	matrix_free(A);
	vector_free(B);
	vector_free(W);
	return (0);
    }
    C = matrix_vprod(A, X);	/* measure weighted residual */
    *resid = 0;
    for (i = 0; i < n; ++i)
	*resid += sqr(VECTOR_DOUBLE(B, i) - VECTOR_DOUBLE(C, i));
    *resid /= n;

    matrix_free(A);
    vector_free(B);
    vector_free(C);
    *a = VECTOR_DOUBLE(X, 0);
    *b = VECTOR_DOUBLE(X, 1);
    *c = VECTOR_DOUBLE(X, 2);
    vector_free(X);

    return (1);
}

int     affine_curve_it(Tstring * string, double thres, double *a, double *b, double *c, double *resid, Vec2 * p1, Vec2 * p2, Vec2 * pm)
/* string of Vec3 (xl, y, xr-xl) */
/* fit threshold */
/* for affine parameters Xl = a.Xr + b.Yr + c */
/* weighted sum sqr distance */

{
    Ddlist *start;
    Ddlist *end;
    Ddlist *ptr;
    Matrix *A;			/* each row of form  [wXr wYr w] */
    Vector *B;			/* vector of wXl */
    Vector *C;
    Vector *X;
    Vector *W;
    Vector *index;
    Vector *pos;
    int     i, j, k, mid, n, ntot, nthres;

    if (string == NULL)
	return (0);

    start = string->start;
    end = string->end;

    for (n = 1, ptr = start; ptr != end; ptr = ptr->next)
	++n;

    if (n < 10)
	return (0);

    nthres = MAX(n / 2, 10);

    A = matrix_alloc(n, 3, matrix_full, double_v);
    B = vector_alloc(n, double_v);
    W = vector_alloc(n, double_v);
    index = vector_alloc(n, int_v);
    pos = vector_alloc(n, ptr_v);

    /* BUGFIX sumw unused */
    /* double  sumw; sumw = 0; */

    for (i = 0, ptr = start; i < n; ++i, ptr = ptr->next)
    {
	double  w = 1.0;	/* fabs(vec2_y(aprox_dir2(ptr)));weight
				 * by y component */
	Vec3    p = {Vec3_id};

	VECTOR_PTR(pos, i) = ptr->to;
	p = *(Vec3 *) ptr->to;
	VECTOR_INT(index, i) = i;

	VECTOR_DOUBLE(W, i) = w;
	VECTOR_DOUBLE(B, i) = vec3_x(p) * w;
	A->el.double_v[i][0] = (vec3_x(p) + vec3_z(p)) * w;
	A->el.double_v[i][1] = vec3_y(p) * w;
	A->el.double_v[i][2] = w;

	/* BUGFIX sumw unused */
	/* sumw += w; */
    }

    ntot = n;
    do
    {
	int     maxi = 0;
	double  diff, max_diff = 0;

	X = matrix_cholesky_least_square(A, B);
	if (X == NULL)
	{
	    A->m = B->n = W->n = ntot;
	    matrix_free(A);
	    vector_free(B);
	    vector_free(W);
	    vector_free(index);	/* BUGFIX line added by JB for Takashi */
	    vector_free(pos);	/* BUGFIX line added by JB for Takashi */
	    return (0);
	}
	/* find outliers */
	C = matrix_vprod(A, X);
	for (i = 0; i < n; ++i)
	{
	    diff = fabs(VECTOR_DOUBLE(B, i) - VECTOR_DOUBLE(C, i));

	    if (diff > max_diff)
	    {
		max_diff = diff;
		maxi = i;
	    }
	}
	vector_free(C);

	if (max_diff < thres)	/* no outlying points */
	    break;

	vector_free(X);
	n--;
	if (n <= nthres)	/* failed */
	{
	    A->m = B->n = W->n = ntot;
	    matrix_free(A);
	    vector_free(B);
	    vector_free(W);
	    vector_free(index);	/* BUGFIX line added by JB for Takashi */
	    vector_free(pos);	/* BUGFIX line added by JB for Takashi */
	    return (0);
	}
	/* swap row maxi with row n-1 */
	(void) matrix_swap_rows(A, maxi, n);
	SWAP(double, VECTOR_DOUBLE(B, maxi), VECTOR_DOUBLE(B, n));
	SWAP(double, VECTOR_DOUBLE(W, maxi), VECTOR_DOUBLE(W, n));
	SWAP(int, VECTOR_INT(index, maxi), VECTOR_INT(index, n));
	A->m = B->n = W->n = n;
    } while (1);

    C = matrix_vprod(A, X);	/* measure weighted residual */
    *resid = 0;
    for (i = 0; i < n; ++i)
	*resid += sqr(VECTOR_DOUBLE(B, i) - VECTOR_DOUBLE(C, i));
    *resid /= n;
    vector_free(C);
    A->m = B->n = W->n = ntot;

    C = matrix_vprod(A, X);
    for (i = n; i < ntot; ++i)	/* these have been eliminated */
    {
	if (fabs(VECTOR_DOUBLE(B, i) - VECTOR_DOUBLE(C, i)) < thres)
	    continue;		/* ok after all */
	j = VECTOR_INT(index, i);
	VECTOR_PTR(pos, j) = NULL;
    }
    vector_free(C);

    for (i = 0; i < ntot; ++i)
	if (VECTOR_PTR(pos, i) != NULL)
	    break;
    *p1 = vec2_of_vec3(*(Vec3 *) VECTOR_PTR(pos, i));

    for (j = ntot - 1; j >= 0; --j)
	if (VECTOR_PTR(pos, j) != NULL)
	    break;
    *p2 = vec2_of_vec3(*(Vec3 *) VECTOR_PTR(pos, j));

    mid = (i + j) / 2;
    for (k = 0; mid + k < j || mid - k > i; ++k)
	if (mid + k < j && VECTOR_PTR(pos, mid + k) != NULL)
	{
	    *pm = vec2_of_vec3(*(Vec3 *) VECTOR_PTR(pos, mid + k));
	    break;
	} else if (mid - k > i && VECTOR_PTR(pos, mid - k) != NULL)
	{
	    *pm = vec2_of_vec3(*(Vec3 *) VECTOR_PTR(pos, mid - k));
	    break;
	}
    matrix_free(A);
    vector_free(B);
    vector_free(W);
    vector_free(index);
    vector_free(pos);
    *a = VECTOR_DOUBLE(X, 0);
    *b = VECTOR_DOUBLE(X, 1);
    *c = VECTOR_DOUBLE(X, 2);
    vector_free(X);

    return (1);
}

Plane  *plane_from_affine(double A, double B, double C)
{
    double  div;
    Vec3    n = {Vec3_id};
    Vec3    p = {Vec3_id};

    div = A;
    A = (1 - A) / A;
    B = -B / div;
    C = -C / div;

    n = vec3_unit(vec3(A, B, -1.0));
    p = vec3(0.0, 0.0, C);
    return (plane_make(p, n, DISPARITY));
}

static double y_range(Tstring * str3)
{
    Ddlist *ptr;
    double  ly, uy;

    ly = uy = vec3_y(*(Vec3 *) str3->start->to);
    for (ptr = str3->start;; ptr = ptr->next)
    {
	double  y = vec3_y(*(Vec3 *) ptr->to);

	if (y < ly)
	    ly = y;
	if (y > uy)
	    uy = y;
	if (ptr == str3->end)
	    break;
    }
    return (uy - ly);
}

Plane  *plane_curve_ls(Tstring * curv, Tstring * es, double resid_thres, Vec2 * p1, Vec2 * p2, Vec2 * pm)
/* approximated geometrical string */
/* string of matched edges */
/* residual threshold */

{
    double  A, B, C;		/* affine parameters Xl = A Xr + B Yr
				 * +C */
    int     good_affine = 0;
    double  resid, thres2 = resid_thres * 2;
    Plane  *plane;
    Vec3    c = {Vec3_id};
    Vec3    v = {Vec3_id};
    Tstring *string3d;

    if (curv == NULL || es == NULL)
	return (NULL);

    resid_thres *= resid_thres;

    string3d = es_build_string3(curv, es);

    if (string3d == NULL || y_range(string3d) < HORIZONTAL_THRES)
    {
	str_rm(string3d, rfree);
	return (NULL);
    }
    good_affine = affine_curve_it(string3d, thres2, &A, &B, &C, &resid, p1, p2, pm);
    str_rm(string3d, rfree);

    if (!good_affine || resid > resid_thres)
	return (NULL);

    plane = plane_from_affine(A, B, C);
    if (plane == NULL)
	return (NULL);

    if (fabs(vec3_z(plane->n)) < 0.3)	/* a disparity gradient of 1.5 */
    {
	plane_free(plane);
	return (NULL);
    }
    plane_par_proj_3d(plane);
    par_proj_ray(str2_centroid(curv), &c, &v);	/* find ray through curv
						 * centre */
    plane->p = vec3_inter_line_plane(c, v, plane->p, plane->n);

    return (plane);
}
