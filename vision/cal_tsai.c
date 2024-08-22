/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

static void stage1ii(void);
static void stage1iii(void);
static int stage2(void);

static int n_points;
static List *tsai_data;
static Vec3 *(*tsai_get_3d) ();
static Vec2 *(*tsai_get_pix) ();

static Mat3 R = {Mat3_id};	/* rotation */
static Vec3 t = {Vec3_id};	/* translation */
static double f;		/* focal length */
static Vector *Tr;		/* some unknowns */
static Mat3 im_to_cam = {Mat3_id};	/* image to camera coordinates */
static Vec2 m_e_pix = {Vec2_id};/* most eccentric point in image */
static Vec3 m_e3 = {Vec3_id};	/* most eccentric world in image */

static int valid_data_count(List * data, Vec3 * (*get_3d) ( /* ??? */ ), Vec2 * (*get_pix) ( /* ??? */ ))
{
    int     i;

    for (i = 0; data != NULL; data = data->next)
    {
	if (get_3d(data) == NULL || get_pix(data) == NULL)
	    continue;
	++i;
    }
    return (i);
}

int     cam_cal_tsai(Camera * cam, List * data, Vec3 * (*get_3d) ( /* ??? */ ), Vec2 * (*get_pix) ( /* ??? */ ))
{
    double  kx, ky;
    double  cx, cy;

    if (data == NULL || cam == NULL)
	return (0);

    n_points = valid_data_count(data, get_3d, get_pix);
    tsai_data = data;
    tsai_get_3d = get_3d;
    tsai_get_pix = get_pix;

    /* ret up image projection */
    kx = cam->ax / cam->pixel;
    ky = cam->ay / cam->pixel;
    cx = cam->cx;
    cy = cam->cy;
    im_to_cam = mat3(1 / kx, 0.0, -cx / kx,
		     0.0, 1 / ky, -cy / ky,
		     0.0, 0.0, 1.0);

    stage1ii();			/* sets Tr */
    if (Tr == NULL)
	return (0);

    stage1iii();
    vector_free(Tr);		/* finished with */

    if (!stage2())
	return (0);

    if (f < 0)			/* change sign and repete stage 2 */
    {
	mat3_xz(R) *= -1;
	mat3_yz(R) *= -1;
	mat3_zx(R) *= -1;
	mat3_zy(R) *= -1;
	if (!stage2())
	    return (0);
    }
    cam->f = (float)f;
    cam->transf = trans3_make(R, t);
    cam_comp_default_rects(cam);/* update camera rectification mats */
    return (1);
}

static void stage1ii(void)
{
    Matrix *M;
    Matrix *W;
    Vector *b;
    List   *ptr;
    double  max_r2 = -1;
    int     i;

    M = matrix_alloc(n_points, 5, matrix_full, double_v);
    W = matrix_alloc(n_points, n_points, matrix_full, double_v);	/* diag */
    b = vector_alloc(n_points, double_v);

    for (i = 0, ptr = tsai_data; ptr != NULL; ptr = ptr->next)
    {
	Vec3    p3 = {Vec3_id};
	Vec3   *pp3;
	Vec2    p2 = {Vec2_id};
	Vec2   *pp2;
	double  r2;

	if ((pp3 = tsai_get_3d(ptr)) == NULL || (pp2 = tsai_get_pix(ptr)) == NULL)
	    continue;
	p3 = *pp3;
	p2 = *pp2;
	p2 = rectify_pos(im_to_cam, p2);

	r2 = SQR(vec2_x(p2)) + SQR(vec2_y(p2));

	matrix_putf(vec2_y(p2) * vec3_x(p3), M, i, 0);
	matrix_putf(vec2_y(p2) * vec3_y(p3), M, i, 1);
	matrix_putf(vec2_y(p2), M, i, 2);
	matrix_putf(-vec2_x(p2) * vec3_x(p3), M, i, 3);
	matrix_putf(-vec2_x(p2) * vec3_y(p3), M, i, 4);
	vector_putf(vec2_x(p2), b, i);
	matrix_putf(r2, W, i, i);
	++i;

	if (r2 > max_r2)
	{
	    max_r2 = r2;
	    m_e_pix = p2;	/* remember for later */
	    m_e3 = p3;
	}
    }

    Tr = matrix_cholesky_least_square(M, b);

    matrix_free(M);
    matrix_free(W);
    vector_free(b);
}

static void stage1iii(void)
{
    double *T = (double *) Tr->data;
    double  Sr;
    double  x, y;
    Vec3    v3a = {Vec3_id};
    Vec3    v3b = {Vec3_id};
    Vec3    v3c = {Vec3_id};


    Sr = T[0] * T[0] + T[1] * T[1] + T[3] * T[3] + T[4] * T[4];

    if ((fabs(T[0]) < 0.000001 || fabs(T[4]) < 0.000001) &&
	(fabs(T[1]) < 0.000001 || fabs(T[3]) < 0.000001))
	vec3_y(t) = (float)sqrt(1 / Sr);
    else
    {
	double  a = T[0] * T[4] - T[1] * T[3];

	a *= 2 * a;
	vec3_y(t) = (float)sqrt((Sr - sqrt(Sr * Sr - 2 * a)) / a);
    }

    mat3_xx(R) = (float)(T[0] * vec3_y(t));
    mat3_xy(R) = (float)(T[1] * vec3_y(t));
    mat3_yx(R) = (float)(T[3] * vec3_y(t));
    mat3_yy(R) = (float)(T[4] * vec3_y(t));
    vec3_x(t) = (float)(T[2] * vec3_y(t));

    /* set the ambiguous sign */

    x = mat3_xx(R) * vec3_x(m_e3) + mat3_xy(R) * vec3_y(m_e3) + vec3_x(t);
    y = mat3_yx(R) * vec3_x(m_e3) + mat3_yy(R) * vec3_y(m_e3) + vec3_y(t);

    if (!SAME_SIGN(vec2_x(m_e_pix), x) || !SAME_SIGN(vec2_y(m_e_pix), y))
    {
	mat3_xx(R) *= -1;
	mat3_xy(R) *= -1;
	mat3_yx(R) *= -1;
	mat3_yy(R) *= -1;
	vec3_x(t) *= -1;
	vec3_y(t) *= -1;
    }
    /* solve for rest of R */

    mat3_xz(R) = (float)sqrt(1 - SQR(mat3_xx(R)) - SQR(mat3_xy(R)));

    if ((mat3_xx(R) * mat3_yx(R) + mat3_xy(R) * mat3_yy(R)) > 0)
	mat3_yz(R) = (float)-sqrt(1 - SQR(mat3_yx(R)) - SQR(mat3_yy(R)));
    else
	mat3_yz(R) = (float)sqrt(1 - SQR(mat3_yx(R)) - SQR(mat3_yy(R)));
    v3a = mat3_rowx(R);
    v3b = mat3_rowy(R);
    v3c = vec3_cross(v3a, v3b);
    mat3_rowz_set(R, v3c);
}

static int stage2(void)
{
    Matrix *M;
    Vector *b;
    Vector *a;
    List   *ptr;
    double  t1;
    int     i;

    M = matrix_alloc(n_points, 2, matrix_full, double_v);
    b = vector_alloc(n_points, double_v);

    t1 = vec3_y(t);

    for (i = 0, ptr = tsai_data; ptr != NULL; ptr = ptr->next)
    {
	Vec3    p3 = {Vec3_id};
	Vec3   *pp3;
	Vec2    p2 = {Vec2_id};
	Vec2   *pp2;
	double  x, y;

	if ((pp3 = tsai_get_3d(ptr)) == NULL || (pp2 = tsai_get_pix(ptr)) == NULL)
	    continue;
	p3 = *pp3;
	p2 = *pp2;
	p2 = rectify_pos(im_to_cam, p2);

	x = vec3_x(p3);
	y = vec3_y(p3);

	matrix_putf(mat3_yx(R) * x + mat3_yy(R) * y + t1, M, i, 0);
	matrix_putf(-vec2_y(p2), M, i, 1);
	vector_putf(vec2_y(p2) * (mat3_zx(R) * x + mat3_zy(R) * y), b, i);
	++i;
    }

    a = matrix_cholesky_least_square(M, b);
    if (a == NULL)
	return (0);

    f = vector_getf(a, 0);
    vec3_z(t) = (float)vector_getf(a, 1);

    matrix_free(M);
    vector_free(a);
    vector_free(b);

    return (1);
}
