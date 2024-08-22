/**@(#)
  */
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

extern Bool fclose_2(FILE * stream, const char *pathname);
extern FILE *fopen_2(const char *pathname, const char *mode);

void    view_params_write_stream(FILE * fp, Camera * caml, Camera * camr)
{
    Vec3    lex =
    {Vec3_id};
    Vec3    ley =
    {Vec3_id};
    Vec3    lez =
    {Vec3_id};
    Vec3    lp =
    {Vec3_id};
    Vec3    rex =
    {Vec3_id};
    Vec3    rey =
    {Vec3_id};
    Vec3    rez =
    {Vec3_id};
    Vec3    rp =
    {Vec3_id};

    if (caml == NULL || camr == NULL)
	return;

    trans3_get_frame2in1(*(caml->transf), &lp, &lex, &ley, &lez);
    vec3_x(lp) *= -1;
    vec3_z(lp) *= -1;
    vec3_y(lex) *= -1;
    vec3_y(ley) *= -1;
    vec3_x(lez) *= -1;
    vec3_z(lez) *= -1;
    trans3_get_frame2in1(*(camr->transf), &rp, &rex, &rey, &rez);
    vec3_x(rp) *= -1;
    vec3_z(rp) *= -1;
    vec3_y(rex) *= -1;
    vec3_y(rey) *= -1;
    vec3_x(rez) *= -1;
    vec3_z(rez) *= -1;

    (void) fprintf(fp, "%d %f ", caml->width, caml->pixel);
    (void) fprintf(fp, "%f\n\n", vec3_mod(vec3_diff(lp, rp)));

    (void) fprintf(fp, "%f %f ", 1 / caml->ax, caml->f);
    (void) fprintf(fp, "%f %f\n", caml->cx, caml->cy);
    (void) fprintf(fp, "%f %f %f\n", vec3_x(lex), vec3_x(ley), vec3_x(lez));
    (void) fprintf(fp, "%f %f %f\n", vec3_y(lex), vec3_y(ley), vec3_y(lez));
    (void) fprintf(fp, "%f %f %f\n", vec3_z(lex), vec3_z(ley), vec3_z(lez));
    vec3_print(fp, lp);
    (void) fprintf(fp, "\n\n");

    (void) fprintf(fp, "%f %f ", 1 / camr->ax, camr->f);
    (void) fprintf(fp, "%f %f\n", camr->cx, camr->cy);
    (void) fprintf(fp, "%f %f %f\n", vec3_x(rex), vec3_x(rey), vec3_x(rez));
    (void) fprintf(fp, "%f %f %f\n", vec3_y(rex), vec3_y(rey), vec3_y(rez));
    (void) fprintf(fp, "%f %f %f\n", vec3_z(rex), vec3_z(rey), vec3_z(rez));
    vec3_print(fp, rp);
    (void) fprintf(fp, "\n");
}

void    view_params_read_stream(FILE * fp, void (*cam1_func) ( /* ??? */ ), void (*cam2_func) ( /* ??? */ ))
{
    Transform3 transf =
    {Transform3_id};
    float   f, pix, ax, ay = (float) 1.0, cx, cy;
    Vec3    ex =
    {Vec3_id};
    Vec3    ey =
    {Vec3_id};
    Vec3    ez =
    {Vec3_id};
    Vec3    p =
    {Vec3_id};
    int     w, h;

    (void) fscanf(fp, "%d %f %*f", &w, &pix);
    h = w;
    (void) fscanf(fp, "%f %f %f %f", &ax, &f, &cx, &cy);
    ax = 1 / ax;
    (void) fscanf(fp, "%f %f %f", &vec3_x(ex), &vec3_x(ey), &vec3_x(ez));
    (void) fscanf(fp, "%f %f %f", &vec3_y(ex), &vec3_y(ey), &vec3_y(ez));
    (void) fscanf(fp, "%f %f %f", &vec3_z(ex), &vec3_z(ey), &vec3_z(ez));
    /* correct to new camera definition and coordinate frame */
    ex.el[1] *= (float) -1.0;
    ey.el[1] *= (float) -1.0;
    ez.el[0] *= (float) -1.0;
    ez.el[2] *= (float) -1.0;
    p = vec3_read(fp);
    p.el[0] *= (float) -1.0;
    p.el[2] *= (float) -1.0;

    transf = trans3_to_frame(p, ex, ey, ez);
    cam1_func(cam_make(CAMERA_PHYSICAL, &transf, f, pix, ax, ay, cx, cy, w, h));

    (void) fscanf(fp, "%f %f %f %f", &ax, &f, &cx, &cy);
    ax = 1 / ax;
    (void) fscanf(fp, "%f %f %f", &vec3_x(ex), &vec3_x(ey), &vec3_x(ez));
    (void) fscanf(fp, "%f %f %f", &vec3_y(ex), &vec3_y(ey), &vec3_y(ez));
    (void) fscanf(fp, "%f %f %f", &vec3_z(ex), &vec3_z(ey), &vec3_z(ez));
    /* correct to new camera definition and coordinate frame */
    ex.el[1] *= (float) -1.0;
    ey.el[1] *= (float) -1.0;
    ez.el[0] *= (float) -1.0;
    ez.el[2] *= (float) -1.0;
    p = vec3_read(fp);
    p.el[0] *= (float) -1.0;
    p.el[2] *= (float) -1.0;

    transf = trans3_to_frame(p, ex, ey, ez);
    cam2_func(cam_make(CAMERA_PHYSICAL, &transf, f, pix, ax, ay, cx, cy, w, h));
}

void    view_params_read(char *pathname, void (*cam1_func) ( /* ??? */ ), void (*cam2_func) ( /* ??? */ ))
{
    FILE   *stream = fopen_2(pathname, "r");

    if (stream)
    {
	view_params_read_stream(stream, cam1_func, cam2_func);
	(void) fclose_2(stream, pathname);
    }
}

void    view_params_write(char *pathname, Camera * cam1, Camera * cam2)
{
    FILE   *stream = fopen_2(pathname, "w");

    if (stream)
    {
	view_params_write_stream(stream, cam1, cam2);
	(void) fclose_2(stream, pathname);
    }
}
