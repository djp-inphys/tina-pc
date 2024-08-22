/**@(#)
**/
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Parcam *parcam_alloc(unsigned int type)
{
    Parcam *pcam = ts_ralloc(Parcam);

    pcam->label = new_label();
    pcam->type = type;
    pcam->rect1 = pcam->derect1 = pcam->rect2 = pcam->derect2 = mat3_unit();
    pcam->I = pcam->f = (float) 1.0;	/* default values */
    pcam->pixel = (float) 0.001;	/* notional value */
    return (pcam);
}

/** compute rectification matrix from original image coords to new camera
    coords with focal length adjustment (focal lengths in pixel units) **/
/* image center of original camera */
/* aspect ratios of original camera */
static Vec3 rect_vector(Vec3 e, double f, double cx, double cy, double ax, double ay)
{
    double   x = vec3_x(e) * ax, y = vec3_y(e) * ay, z = vec3_z(e);

    return (vec3(x, y, z * f - cx * x - cy * y));
}

/* original and new focal lengths */
/* directions vectors of original camera */
/* direction vectors of new camera */
/* image center of original camera */
/* aspect ratios of original camera */
static Mat3 rect_image_to_cam(double f1, Vec3 ex1, Vec3 ey1, Vec3 ez1,
                              double f2, Vec3 ex2, Vec3 ey2, Vec3 ez2,
			      double cx, double cy, double ax, double ay)
{
    Vec3    ex = {Vec3_id};
    Vec3    ey = {Vec3_id};
    Vec3    ez = {Vec3_id};

    ex = vec3(vec3_dot(ex2, ex1), vec3_dot(ex2, ey1), vec3_dot(ex2, ez1));
    ey = vec3(vec3_dot(ey2, ex1), vec3_dot(ey2, ey1), vec3_dot(ey2, ez1));
    ez = vec3(vec3_dot(ez2, ex1), vec3_dot(ez2, ey1), vec3_dot(ez2, ez1));

    return (mat3_of_rows(
	  vec3_times(f2, rect_vector(ex, f1, cx, cy, 1 / ax, 1 / ay)),
	  vec3_times(f2, rect_vector(ey, f1, cx, cy, 1 / ax, 1 / ay)),
			 rect_vector(ez, f1, cx, cy, 1 / ax, 1 / ay)));
}

/* Construction of a standard parallel camera geometry */
Parcam *parcam_make(Camera * cam1, Camera * cam2, unsigned int type)
/* a pair of cameras with respect to same origin */

{
    Vec3    p1 = {Vec3_id};
    Vec3    ex1 = {Vec3_id};
    Vec3    ey1 = {Vec3_id};
    Vec3    ez1 = {Vec3_id};
    Vec3    p2 = {Vec3_id};
    Vec3    ex2 = {Vec3_id};
    Vec3    ey2 = {Vec3_id};
    Vec3    ez2 = {Vec3_id};
    Vec3    Px = {Vec3_id};
    Vec3    Py = {Vec3_id};
    Vec3    Pz = {Vec3_id};
    double   f1, f2, fp;		/* focal lengths */
    int     height, width;
    Transform3 transf = {Transform3_id};
    Parcam *pcam = (Parcam *) NULL;

    if (cam1 == NULL || cam2 == NULL)
	return (pcam);

    pcam = parcam_alloc(type);
    pcam->cam1 = cam_copy(cam1);
    pcam->cam2 = cam_copy(cam2);

    pcam->f = cam1->f;
    pcam->pixel = cam1->pixel;

    if (cam1->transf == NULL || cam2->transf == NULL)
	return (pcam);

    width = cam1->width;
    height = cam1->height;

    /* compute camera frames in world coords from transforms */
    trans3_get_frame2in1(*cam1->transf, &p1, &ex1, &ey1, &ez1);
    trans3_get_frame2in1(*cam2->transf, &p2, &ex2, &ey2, &ez2);

    /* construct parallel camera coordinate frame */
    Px = vec3_diff(p2, p1);	/* Interoccular axis from p1 to p2 */
    pcam->I = (float) vec3_mod(Px);	/* Interocular separation */
    Px = vec3_unit(Px);		/* parallel x axis */
    Pz = vec3_unit(vec3_cross(Px, vec3_cross(ez1, Px)));	/* parallel z axis */
    Py = vec3_cross(Pz, Px);	/* parallel y axis */

    /* build left and right hand parallel rectified cameras left camera
     * focal length, pixel size and dimensions origin at (0, 0) no
     * aspect ratio */
    transf = trans3_to_frame(p1, Px, Py, Pz);
    pcam->rcam1 = cam_make(CAMERA_PARALLEL, &transf, pcam->f, pcam->pixel,
			   1.0, 1.0, 0.0, 0.0, width, height);
    pcam->rcam2 = cam_copy(pcam->rcam1);
    *(pcam->rcam2->transf) = trans3_to_frame(p2, Px, Py, Pz);

    /* compute rectification transforms between standard and parallel
     * coords */
    fp = pcam->f / pcam->pixel;	/* focal lengths in pixels */
    f1 = cam1->f / cam1->pixel;
    f2 = cam2->f / cam2->pixel;
    pcam->rect1 = rect_image_to_cam(f1, ex1, ey1, ez1, fp, Px, Py, Pz,
			      cam1->cx, cam1->cy, cam1->ax, cam1->ay);
    pcam->derect1 = mat3_inverse(pcam->rect1);
    pcam->rect2 = rect_image_to_cam(f2, ex2, ey2, ez2, fp, Px, Py, Pz,
			      cam2->cx, cam2->cy, cam2->ax, cam2->ay);
    pcam->derect2 = mat3_inverse(pcam->rect2);

    /** compute E-matrix **/
    pcam->e = mat3(0.0, 0.0, 0.0,
		   0.0, 0.0, 1.0,
		   0.0, -1.0, 0.0);
    pcam->e = mat3_prod(mat3_transpose(pcam->rect1), pcam->e);
    pcam->e = mat3_prod(pcam->e, pcam->rect2);

    return (pcam);
}

/* A pair of cameras with respect to same origin */
Parcam *parcam_scaled_make(Camera * cam1, Camera * cam2, double scale, unsigned int type)

/* scale parallel camera image size */

{
    Vec3    p1 = {Vec3_id};
    Vec3    ex1 = {Vec3_id};
    Vec3    ey1 = {Vec3_id};
    Vec3    ez1 = {Vec3_id};
    Vec3    p2 = {Vec3_id};
    Vec3    ex2 = {Vec3_id};
    Vec3    ey2 = {Vec3_id};
    Vec3    ez2 = {Vec3_id};
    Vec3    Px = {Vec3_id};
    Vec3    Py = {Vec3_id};
    Vec3    Pz = {Vec3_id};
    double   f1, f2, fp;		/* focal lengths */
    int     height, width;
    Transform3 transf = {Transform3_id};
    Parcam *pcam = (Parcam *) NULL;

    if (cam1 == NULL || cam2 == NULL)
	return (pcam);

    pcam = parcam_alloc(type);
    pcam->cam1 = cam_copy(cam1);
    pcam->cam2 = cam_copy(cam2);

    pcam->f = cam1->f;
    pcam->pixel = (float) (cam1->pixel / scale);

    if (cam1->transf == NULL || cam2->transf == NULL)
	return (pcam);

    width = (int)(cam1->width * scale);
    height = (int)(cam1->height * scale);

    /* compute camera frames in world coords from transforms */
    trans3_get_frame2in1(*cam1->transf, &p1, &ex1, &ey1, &ez1);
    trans3_get_frame2in1(*cam2->transf, &p2, &ex2, &ey2, &ez2);

    /* construct parallel camera coordinate frame */
    Px = vec3_diff(p2, p1);	/* Interocular axis from p1 to p2 */
    pcam->I = (float) vec3_mod(Px);	/* Interocular separation */
    Px = vec3_unit(Px);		/* parallel x axis */
    Pz = vec3_unit(vec3_cross(Px, vec3_cross(ez1, Px)));	/* parallel z axis */
    Py = vec3_cross(Pz, Px);	/* parallel y axis */

    /* build left and right hand parallel rectified cameras left camera
     * focal length, pixel size and dimensions origin at (0, 0) no
     * aspect ratio */
    transf = trans3_to_frame(p1, Px, Py, Pz);
    pcam->rcam1 = cam_make(CAMERA_PARALLEL, &transf, pcam->f, pcam->pixel,
			   1.0, 1.0, 0.0, 0.0, width, height);
    pcam->rcam2 = cam_copy(pcam->rcam1);
    *(pcam->rcam2->transf) = trans3_to_frame(p2, Px, Py, Pz);

    /* compute rectification transforms between standard and parallel
     * coords */
    fp = pcam->f / pcam->pixel;	/* focal lengths in pixels */
    f1 = cam1->f / cam1->pixel;
    f2 = cam2->f / cam2->pixel;
    pcam->rect1 = rect_image_to_cam(f1, ex1, ey1, ez1, fp, Px, Py, Pz,
			      cam1->cx, cam1->cy, cam1->ax, cam1->ay);
    pcam->derect1 = mat3_inverse(pcam->rect1);
    pcam->rect2 = rect_image_to_cam(f2, ex2, ey2, ez2, fp, Px, Py, Pz,
			      cam2->cx, cam2->cy, cam2->ax, cam2->ay);
    pcam->derect2 = mat3_inverse(pcam->rect2);

    /** compute E-matrix **/
    pcam->e = mat3(0.0, 0.0, 0.0,
		   0.0, 0.0, 1.0,
		   0.0, -1.0, 0.0);
    pcam->e = mat3_prod(mat3_transpose(pcam->rect1), pcam->e);
    pcam->e = mat3_prod(pcam->e, pcam->rect2);

    return (pcam);
}

void    pcam_free(Parcam * pcam)
{
    if (pcam == NULL)
	return;

    cam_free(pcam->cam1);
    cam_free(pcam->rcam1);
    cam_free(pcam->cam2);
    cam_free(pcam->rcam2);

    rfree((void *) pcam);
}
