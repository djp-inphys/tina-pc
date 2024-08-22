/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

static int rot_matrix_get(Matrix * M, Vec3 v1, Vec3 v2, double w);
static Mat3 rot_compute(Matrix * M, int *rot_error);

/* compute rotation from pure vector information */
Mat3    mlist_comp_rot_vec3(List * match_list, int *rot_error)
{
    Matrix *A = matrix_alloc(4, 4, matrix_full, float_v);
    Matrix *B = matrix_alloc(4, 4, matrix_full, float_v);
    Mat3    rot = {Mat3_id};
    List   *lptr;

    for (lptr = match_list; lptr != NULL; lptr = lptr->next)
    {
	Match  *mptr = (Match *) lptr->to;
	Vec3    v1 = {Vec3_id};
	Vec3    v2 = {Vec3_id};

	switch (mptr->type)
	{
	default:
	    continue;		/* to next match */
	case LINE3:
	    v1 = ((Line3 *) mptr->to1)->v;
	    v2 = ((Line3 *) mptr->to2)->v;
	    break;
	case CONIC3:
	    v1 = ((Conic3 *) mptr->to1)->ez;
	    v2 = ((Conic3 *) mptr->to2)->ez;
	    break;
	case PLANE:
	    v1 = ((Plane *) mptr->to1)->n;
	    v2 = ((Plane *) mptr->to2)->n;
	    break;
	}

	if (rot_matrix_get(A, v1, v2, mptr->weight))
	    (void) fmatrix_add_inplace(B, A);
    }

    rot = rot_compute(B, rot_error);
    matrix_free(A);
    matrix_free(B);

    return (rot);
}

/* compute rotation from 3D point position information */
Mat3    mlist_comp_rot_pos3(List * match_list, Vec3 c1, Vec3 c2, int *rot_error)

/* centroids */

{
    Matrix *A = matrix_alloc(4, 4, matrix_full, float_v);
    Matrix *B = matrix_alloc(4, 4, matrix_full, float_v);
    Mat3    rot = {Mat3_id};
    List   *lptr;

    for (lptr = match_list; lptr != NULL; lptr = lptr->next)
    {
	Match  *mptr = (Match *) lptr->to;
	Vec3    v1 = {Vec3_id};
	Vec3    v2 = {Vec3_id};
	Point3 *p1;
	Point3 *p2;

	if (mptr->type != POINT3)
	    continue;

	p1 = (Point3 *) mptr->to1;
	p2 = (Point3 *) mptr->to2;

	v1 = vec3_unit(vec3_diff(p1->p, c1));
	v2 = vec3_unit(vec3_diff(p2->p, c2));

	if (rot_matrix_get(A, v1, v2, mptr->weight))
	    (void) fmatrix_add_inplace(B, A);
    }

    rot = rot_compute(B, rot_error);
    matrix_free(A);
    matrix_free(B);

    return (rot);
}

/* compute rotation from all information */
Mat3    mlist_comp_rot_all(List * match_list, int *rot_error)
{
    Matrix *A = matrix_alloc(4, 4, matrix_full, float_v);
    Matrix *B = matrix_alloc(4, 4, matrix_full, float_v);
    Mat3    rot = {Mat3_id};
    List   *lptr1;
    List   *lptr2;

    for (lptr1 = match_list; lptr1 != NULL; lptr1 = lptr1->next)
    {
	Match  *mptr1 = (Match *) lptr1->to;
	Vec3    v1 = {Vec3_id};
	Vec3    v2 = {Vec3_id};
	Vec3    p1 = {Vec3_id};
	Vec3    p2 = {Vec3_id};

	switch (mptr1->type)
	{
	default:
	    continue;
	case POINT3:
	    break;
	case LINE3:
	    v1 = ((Line3 *) mptr1->to1)->v;
	    v2 = ((Line3 *) mptr1->to2)->v;
	    break;
	case CONIC3:
	    v1 = ((Conic3 *) mptr1->to1)->ez;
	    v2 = ((Conic3 *) mptr1->to2)->ez;
	    break;
	case PLANE:
	    v1 = ((Plane *) mptr1->to1)->n;
	    v2 = ((Plane *) mptr1->to2)->n;
	    break;
	}

	if (mptr1->type != POINT3 && rot_matrix_get(A, v1, v2, mptr1->weight))
	    (void) fmatrix_add_inplace(B, A);

	/* consider all pair-wise vectors */

	switch (mptr1->type)
	{
	default:
	    continue;
	case POINT3:
	    p1 = ((Point3 *) mptr1->to1)->p;
	    p2 = ((Point3 *) mptr1->to2)->p;
	    break;
	case CONIC3:
	    p1 = ((Conic3 *) mptr1->to1)->origin;
	    p2 = ((Conic3 *) mptr1->to2)->origin;
	    break;
	}

	for (lptr2 = lptr1->next; lptr2 != NULL; lptr2 = lptr2->next)
	{
	    Match  *mptr2 = (Match *) lptr2->to;

	    switch (mptr2->type)
	    {
	    default:
		continue;
	    case POINT3:
		v1 = vec3_diff(p1, ((Point3 *) mptr2->to1)->p);
		v2 = vec3_diff(p2, ((Point3 *) mptr2->to2)->p);
		break;
	    case CONIC3:
		v1 = vec3_diff(p1, ((Conic3 *) mptr2->to1)->origin);
		v2 = vec3_diff(p2, ((Conic3 *) mptr2->to2)->origin);
		break;
	    }
	    v1 = vec3_unit(v1);
	    v2 = vec3_unit(v2);
	    if (rot_matrix_get(A, v1, v2, (mptr1->weight + mptr2->weight) * 0.5))
		(void) fmatrix_add_inplace(B, A);
	}
    }

    rot = rot_compute(B, rot_error);
    matrix_free(A);
    matrix_free(B);

    return (rot);
}

static Mat3 rot_compute(Matrix * M, int *rot_error)
{
    Matrix *evec;
    Vector *eval;
    Vector *quat;
    double  theta, sin_theta;
    float  *el;
    Vec3    axis = {Vec3_id};

    if (M == NULL || M->m != 4 || M->n != 4)
    {
	*rot_error = 1;
	return (mat3_unit());
    }
    evec = matrix_alloc(4, 4, matrix_full, float_v);
    eval = vector_alloc(4, float_v);

    if (!matrix_eigen_sym(M, eval, evec))
    {
	matrix_free(evec);
	vector_free(eval);
	*rot_error = 1;
	return (mat3_unit());
    }
    *rot_error = 0;
    quat = matrix_col_vector(evec, 0);
    el = quat->data;
    if (el[0] < 0)
	vector_minus_inplace(quat);

    theta = tina_acos(el[0]);
    sin_theta = sin(theta);
    if (fabs(sin_theta) < 0.000000001)
	axis = vec3_ex();
    else
	axis = vec3_unit(vec3(el[1] / sin_theta, el[2] / sin_theta, el[3] / sin_theta));
    matrix_free(evec);
    vector_free(eval);
    vector_free(quat);
    return (rot3(theta * 2, axis));
}

static int rot_matrix_get(Matrix * M, Vec3 v1, Vec3 v2, double w)
/* of type float */

/* weight factor */
{
    double  xY, yX, xZ, zX, yZ, zY;
    double  xpXs, ypYs, zpZs;
    double  xmXs, ymYs, zmZs;
    double  w2 = 2 * w;
    float **el;

    if (M->vtype != float_v || M->shape != matrix_full)
	return (0);

    if (M->m != 4 || M->n != 4)
	return (0);

    el = M->el.float_v;

    xpXs = sqr(vec3_x(v1) + vec3_x(v2));
    ypYs = sqr(vec3_y(v1) + vec3_y(v2));
    zpZs = sqr(vec3_z(v1) + vec3_z(v2));
    xmXs = sqr(vec3_x(v1) - vec3_x(v2));
    ymYs = sqr(vec3_y(v1) - vec3_y(v2));
    zmZs = sqr(vec3_z(v1) - vec3_z(v2));

    xY = vec3_x(v1) * vec3_y(v2);
    yX = vec3_y(v1) * vec3_x(v2);
    xZ = vec3_x(v1) * vec3_z(v2);
    zX = vec3_z(v1) * vec3_x(v2);
    yZ = vec3_y(v1) * vec3_z(v2);
    zY = vec3_z(v1) * vec3_y(v2);

    el[0][0] = (float)((xmXs + ymYs + zmZs) * w);
    el[1][1] = (float)((xmXs + ypYs + zpZs) * w);
    el[2][2] = (float)((xpXs + ymYs + zpZs) * w);
    el[3][3] = (float)((xpXs + ypYs + zmZs) * w);
    el[0][1] = el[1][0] = (float)(w2 * (zY - yZ));
    el[0][2] = el[2][0] = (float)(w2 * (xZ - zX));
    el[0][3] = el[3][0] = (float)(w2 * (yX - xY));
    el[1][2] = el[2][1] = (float)(-w2 * (xY + yX));
    el[1][3] = el[3][1] = (float)(-w2 * (xZ + zX));
    el[2][3] = el[3][2] = (float)(-w2 * (yZ + zY));
    return (1);
}
