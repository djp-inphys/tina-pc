/**@(#)
**/
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

static Mat3 trans_mat3_get(Vec3 p1, Vec3 v1, Vec3 p2, Vec3 v2, double weight)
/* BUG p1 & p2 unused */


{
    Mat3    V = {Mat3_id};
    int     i, j;

    for (i = 0; i < 3; ++i)
	V.el[i][i] = (float)((2 - v1.el[i] * v1.el[i] - v2.el[i] * v2.el[i]) * weight);

    for (i = 0; i < 3; ++i)
	for (j = i + 1; j < 3; ++j)
	{
	    float   val;

	    val = (float)((-v1.el[i] * v1.el[j] - v2.el[i] * v2.el[j]) * weight);
	    V.el[i][j] = V.el[j][i] = val;
	}

    return (V);
}

Vec3    mlist_comp_translate_vec3(List * match_list, Mat3 R)
{
    Mat3    P = {Mat3_id};
    Mat3    V = {Mat3_id};
    Vec3    Y = {Vec3_id};
    List   *lptr;

    Y = vec3_zero();
    P = mat3_zero();

    for (lptr = match_list; lptr != NULL; lptr = lptr->next)
    {
	Match  *mptr = (Match *) lptr->to;
	Vec3    p1 = {Vec3_id};
	Vec3    p2 = {Vec3_id};
	Vec3    v1 = {Vec3_id};
	Vec3    v2 = {Vec3_id};
	Vec3    diff = {Vec3_id};

	switch (mptr->type)
	{
	case LINE3:
	    v1 = ((Line3 *) mptr->to1)->v;
	    p1 = ((Line3 *) mptr->to1)->p;
	    v2 = ((Line3 *) mptr->to2)->v;
	    p2 = ((Line3 *) mptr->to2)->p;
	    break;
	case CONIC3:
	    v1 = ((Conic3 *) mptr->to1)->ez;
	    p1 = ((Conic3 *) mptr->to1)->origin;
	    v2 = ((Conic3 *) mptr->to2)->ez;
	    p2 = ((Conic3 *) mptr->to2)->origin;
	    break;
	default:
	    continue;
	}

	p1 = mat3_vprod(R, p1);
	v1 = mat3_vprod(R, v1);
	diff = vec3_diff(p2, p1);
	V = trans_mat3_get(p1, v1, p2, v2, mptr->weight);
	P = mat3_sum(P, V);
	Y = vec3_sum(Y, mat3_vprod(V, diff));
    }

    return (mat3_vprod(mat3_inverse(P), Y));
}

Vec3    mlist_comp_translate_all(List * match_list, Mat3 R)
{
    Mat3    P = {Mat3_id};
    Mat3    V = {Mat3_id};
    Vec3    Y = {Vec3_id};
    List   *lptr1;
    List   *lptr2;

    Y = vec3_zero();
    P = mat3_zero();

    for (lptr1 = match_list; lptr1 != NULL; lptr1 = lptr1->next)
    {
	Match  *mptr1 = (Match *) lptr1->to;
	Vec3    p1 = {Vec3_id};
	Vec3    p2 = {Vec3_id};
	Vec3    v1 = {Vec3_id};
	Vec3    v2 = {Vec3_id};
	Vec3    diff = {Vec3_id};

	switch (mptr1->type)
	{
	case POINT3:
	    break;
	case LINE3:
	    v1 = ((Line3 *) mptr1->to1)->v;
	    p1 = ((Line3 *) mptr1->to1)->p;
	    v2 = ((Line3 *) mptr1->to2)->v;
	    p2 = ((Line3 *) mptr1->to2)->p;
	    break;
	case CONIC3:
	    v1 = ((Conic3 *) mptr1->to1)->ez;
	    p1 = ((Conic3 *) mptr1->to1)->origin;
	    v2 = ((Conic3 *) mptr1->to2)->ez;
	    p2 = ((Conic3 *) mptr1->to2)->origin;
	    break;
	default:
	    continue;
	}

	if (mptr1->type != POINT3)
	{
	    p1 = mat3_vprod(R, p1);
	    v1 = mat3_vprod(R, v1);
	    diff = vec3_diff(p2, p1);
	    V = trans_mat3_get(p1, v1, p2, v2, mptr1->weight);
	    P = mat3_sum(P, V);
	    Y = vec3_sum(Y, mat3_vprod(V, diff));
	}
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
		v1 = vec3_diff(((Point3 *) mptr2->to1)->p, p1);
		v2 = vec3_diff(((Point3 *) mptr2->to2)->p, p2);
		break;
	    case CONIC3:
		v1 = vec3_diff(((Conic3 *) mptr2->to1)->origin, p1);
		v2 = vec3_diff(((Conic3 *) mptr2->to2)->origin, p2);
		break;
	    }
	    v1 = vec3_unit(v1);
	    v2 = vec3_unit(v2);

	    p1 = mat3_vprod(R, p1);
	    v1 = mat3_vprod(R, v1);
	    diff = vec3_diff(p2, p1);
	    V = trans_mat3_get(p1, v1, p2, v2, (mptr1->weight + mptr2->weight) * 0.5);
	    P = mat3_sum(P, V);
	    Y = vec3_sum(Y, mat3_vprod(V, diff));
	}
    }

    return (mat3_vprod(mat3_inverse(P), Y));
}

Vec3    mlist_comp_translate_pos3(List * match_list, Mat3 R)
{
    Vec3    T = {Vec3_id};
    List   *lptr;
    float   tot_weight = (float)0.0;

    T = vec3_zero();

    for (lptr = match_list; lptr != NULL; lptr = lptr->next)
    {
	Match  *mptr = (Match *) lptr->to;
	Vec3    p1 = {Vec3_id};
	Vec3    p2 = {Vec3_id};
	Vec3    diff = {Vec3_id};

	switch (mptr->type)
	{
	default:
	    continue;
	case POINT3:
	    p1 = ((Point3 *) mptr->to1)->p;
	    p2 = ((Point3 *) mptr->to2)->p;
	    break;
	case CONIC3:
	    p1 = ((Conic3 *) mptr->to1)->origin;
	    p2 = ((Conic3 *) mptr->to2)->origin;
	    break;
	}

	diff = vec3_diff(p2, mat3_vprod(R, p1));
	T = vec3_sum(T, vec3_times(mptr->weight, diff));
	tot_weight += mptr->weight;
    }

    return (vec3_times(1 / tot_weight, T));
}
