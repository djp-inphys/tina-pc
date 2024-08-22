/**@(#)
**/
#ifdef TRANSPUTER
#include <valuesdual.h>
#else
#include <values.h>
#endif
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* routine for calculating summed squared error in the image plane for
 * the first n_data points stored in the world3d matched structure NAT
 * 6/2/91     */
/* BUG camerror often called without 6th arg (accuracy) */
double  camerror(int *n_data, double *f, Camera * cam, List * world3d, Vec2 * (*pix_get) ( /* ??? */ ), Vec3 * (*world_get) ( /* ??? */ ), double accuracy)
{
    List   *l;
    Vec2    e = {Vec2_id};
    Vec2    cam_proj();
    Vec2   *c;
    Vec3   *v;
    double  diffx, diffy;
    double  errorsq = 0.0;
    int     i = 0;

    for (l = world3d; l != NULL; l = l->next)
    {
	if ((c = pix_get(l)) && (v = world_get(l)))
	{
	    e = cam_proj(cam, *v);
	    diffx = e.el[0] - c->el[0];
	    diffy = e.el[1] - c->el[1];
	    if (diffx > 3.0 * accuracy)
		diffx = 3.0 * accuracy;
	    if (diffx < -3.0 * accuracy)
		diffx = -3.0 * accuracy;
	    if (diffy > 3.0 * accuracy)
		diffy = 3.0 * accuracy;
	    if (diffy < -3.0 * accuracy)
		diffy = -3.0 * accuracy;
	    errorsq += diffx * diffx + diffy * diffy;
	    if (f != NULL)
	    {
		f[i++] = diffx;
		f[i++] = diffy;
	    } else
		i += 2;
	    if (i == *n_data)
		break;
	}
    }
    *n_data = i;
    if (errorsq > 0.0 || errorsq >= 0.0)
	return (errorsq);
    else
	return (MAXDOUBLE);
}


/* routine for calculating summed squared error in the image plane for
 * the first n_data points stored in the world3d matched structure NAT
 * 6/2/91 */
double  rad_camerror(int *n_data, double *rad, double *err, Camera * cam, List * world3d, Vec2 * (*pix_get) ( /* ??? */ ), Vec3 * (*world_get) ( /* ??? */ ))
{
    List   *l;
    Vec2    e = {Vec2_id};
    Vec2    cam_proj();
    Vec2   *c;
    Vec3   *v;
    double  diff;
    double  errorsq = 0.0;
    double  rad1, rad2;
    int     i = 0;

    for (l = world3d; l != NULL; l = l->next)
    {
	if ((c = pix_get(l)) && (v = world_get(l)))
	{
	    e = cam_proj(cam, *v);
	    e.el[0] -= cam->cx;
	    e.el[1] -= cam->cy;
	    rad1 = e.el[0] * e.el[0] / (cam->ax * cam->ax)
		+ e.el[1] * e.el[1] / (cam->ay * cam->ay);
	    rad1 = sqrt(rad1);
	    rad2 = (c->el[0] - cam->cx) * (c->el[0] - cam->cx) / (cam->ax * cam->ax)
		+ (c->el[1] - cam->cy) * (c->el[1] - cam->cy) / (cam->ay * cam->ay);
	    rad2 = sqrt(rad2);
	    diff = rad1 - rad2;
	    errorsq += diff * diff;
	    if (rad != NULL && err != NULL)
	    {
		rad[i] = rad1;
		err[i++] = diff;
	    } else
		i++;
	    if (i == *n_data)
		break;
	}
    }
    *n_data = i;
    if (errorsq > 0.0 || errorsq >= 0.0)
	return (errorsq);
    else
	return (MAXDOUBLE);
}


/* calculates the total off-epipolar error for a set of matched stereo
 * data points using the Trivedi formulation for the between camera
 * transformation NAT 6/6/91 */
double  triv_camerror(int *n_data, double *x, Camera * cam1, Camera * cam2, List * world3d, Vec2 * (*pix_get1) ( /* ??? */ ), Vec2 * (*pix_get2) ( /* ??? */ ), double accuracy)
{
    Transform3 rel2to1 = {Transform3_id};
    Transform3 inv2 = {Transform3_id};
    List   *plist;
    Vec2    tl = {Vec2_id};
    Vec2    tr = {Vec2_id};
    Vec2   *l;
    Vec2   *r;
    Vec3    lp = {Vec3_id};
    Vec3    rp = {Vec3_id};
    Vec3    gradfl = {Vec3_id};
    Vec3    gradfr = {Vec3_id};
    Vec3    mat3_vprod();
    Vec3    mat3_transpose_vprod();
    int     i = 0;
    Mat3    R = {Mat3_id};
    Mat3    S = {Mat3_id};
    Mat3    T = {Mat3_id};
    Mat3    S_array(double T1, double T2, double T3);
    double  f, gradsq, lam;
    double  m, toterr = 0.0, errorsq;
    double  elx, ely, erx, ery;

    if (cam1 == NULL || cam2 == NULL || world3d == NULL)
	return (0.0);

    inv2 = trans3_inverse(*(cam2->transf));
    rel2to1 = trans3_prod(*(cam1->transf), inv2);
    m = sqrt(rel2to1.t.el[0] * rel2to1.t.el[0]
	     + rel2to1.t.el[1] * rel2to1.t.el[1]
	     + rel2to1.t.el[2] * rel2to1.t.el[2]);
    R = rel2to1.R;
    S = S_array(rel2to1.t.el[0] / m, rel2to1.t.el[1] / m, rel2to1.t.el[2] / m);
    T = mat3_prod(S, R);

    for (plist = world3d; plist != NULL; plist = plist->next)
    {
	if ((l = pix_get1(plist)) && (r = pix_get2(plist)))
	{
	    tl = cam_correct(*l, cam1);
	    tr = cam_correct(*r, cam2);
	    lp.el[0] = (tl.el[0] - cam1->cx) / cam1->ax;
	    lp.el[1] = (tl.el[1] - cam1->cy) / cam1->ay;
	    lp.el[2] = cam1->f / cam1->pixel;
	    rp.el[0] = (tr.el[0] - cam2->cx) / cam2->ax;
	    rp.el[1] = (tr.el[1] - cam2->cy) / cam2->ay;
	    rp.el[2] = cam2->f / cam2->pixel;
	    gradfl = mat3_vprod(T, rp);
	    gradfr = mat3_transpose_vprod(T, lp);

	    f = gradfl.el[0] * lp.el[0]
		+ gradfl.el[1] * lp.el[1]
		+ gradfl.el[2] * lp.el[2];

	    gradsq = gradfl.el[0] * gradfl.el[0] / (cam1->ax * cam1->ax)
		+ gradfl.el[1] * gradfl.el[1] / (cam1->ay * cam1->ay)
		+ gradfr.el[0] * gradfr.el[0] / (cam2->ax * cam2->ax)
		+ gradfr.el[1] * gradfr.el[1] / (cam2->ay * cam2->ay);

	    lam = f / gradsq;

	    elx = -gradfl.el[0] * lam / (cam1->ax * cam1->ax);
	    ely = -gradfl.el[1] * lam / (cam1->ay * cam1->ay);
	    erx = -gradfr.el[0] * lam / (cam2->ax * cam2->ax);
	    ery = -gradfr.el[1] * lam / (cam2->ay * cam2->ay);

	    if (elx > 3.0 * accuracy)
		elx = 3.0 * accuracy;
	    if (ely > 3.0 * accuracy)
		ely = 3.0 * accuracy;
	    if (erx > 3.0 * accuracy)
		erx = 3.0 * accuracy;
	    if (ery > 3.0 * accuracy)
		ery = 3.0 * accuracy;
	    if (elx < -3.0 * accuracy)
		elx = -3.0 * accuracy;
	    if (ely < -3.0 * accuracy)
		ely = -3.0 * accuracy;
	    if (erx < -3.0 * accuracy)
		erx = -3.0 * accuracy;
	    if (ery < -3.0 * accuracy)
		ery = -3.0 * accuracy;

	    /* errorsq = lam*f; */
	    errorsq = elx * elx + ely * ely + erx * erx + ery * ery;
	    if (x != NULL)
	    {
		x[i++] = elx;
		x[i++] = ely;
		x[i++] = erx;
		x[i++] = ery;
	    } else
		i += 4;
	    toterr += errorsq;
	    if (i == *n_data)
		break;
	}
    }
    *n_data = i;
    if (toterr >= 0.0)
	return (toterr);
    else
	return (MAXDOUBLE);
}

double  cam_reg(Covar * incov, int mask, double *a)
{
    Matrix *matrix_alloc();
    Matrix *matrix_prod();
    Matrix *delta;
    Matrix *dprod;
    double  chisq = 0.0;
    int     i, n_par;

    if (incov == NULL)
	return (0.0);

    for (i = 0, n_par = 6; i < 16; i++)
	if (mask & (1 << i))
	    n_par++;
    delta = matrix_alloc(1, n_par, matrix_full, double_v);
    for (i = 0; i < n_par; i++)
    {
	delta->el.double_v[0][i] = a[i + 6] - VECTOR_DOUBLE(incov->vec, i);
    }
    dprod = matrix_prod(delta, incov->mat);
    for (i = 0; i < n_par; i++)
    {
	chisq += dprod->el.double_v[0][i] * delta->el.double_v[0][i];
    }
    matrix_free(delta);
    matrix_free(dprod);
    return (chisq);
}

double  stereo_reg(Covar * incov, int mask, double *a)
{
    Matrix *matrix_alloc();
    Matrix *matrix_prod();
    Matrix *delta;
    Matrix *dprod;
    double  chisq = 0.0;
    int     i, n_par = 0;

    if (incov == NULL)
	return (0.0);

    for (i = 0; i < 16; i++)
	if (mask & (1 << i))
	    n_par++;
    delta = matrix_alloc(1, 2 * n_par + 6, matrix_full, double_v);
    for (i = 0; i < 2 * n_par + 6; i++)
    {
	delta->el.double_v[0][i] = a[i] - VECTOR_DOUBLE(incov->vec, i);
    }
    dprod = matrix_prod(delta, incov->mat);
    for (i = 0; i < 2 * n_par + 6; i++)
    {
	chisq += dprod->el.double_v[0][i] * delta->el.double_v[0][i];
    }
    matrix_free(delta);
    matrix_free(dprod);

    return (chisq);
}

Mat3    S_array(double T1, double T2, double T3)
{
    Mat3    S = {Mat3_id};

    S.el[0][0] = (float)0.0;
    S.el[1][0] = (float)T3;
    S.el[2][0] = (float)-T2;
    S.el[0][1] = (float)-T3;
    S.el[1][1] = (float)0.0;
    S.el[2][1] = (float)T1;
    S.el[0][2] = (float)T2;
    S.el[1][2] = (float)-T1;
    S.el[2][2] = (float)0.0;
    return (S);
}
