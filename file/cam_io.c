/**@(#)Functions to read/write CAMERA files
*/

#include <stdio.h>
#include <tina/file.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

extern Bool fclose_2(FILE * stream, const char *pathname);
extern FILE *fopen_2(const char *pathname, const char *mode);

Camera *cam_read_stream(FILE * stream, const char *pathname)
{
    Camera *cam_make();
    float   f, pix, ax, ay, cx, cy;
    int     w, h;
    Transform3 transf =
    {Transform3_id};
    Vec3    ex =
    {Vec3_id};
    Vec3    ey =
    {Vec3_id};
    Vec3    ez =
    {Vec3_id};
    Vec3    p =
    {Vec3_id};

    (void) fscanf(stream, "%d %d", &w, &h);
    (void) fscanf(stream, "%f %f", &pix, &f);
    (void) fscanf(stream, "%f %f", &ax, &ay);
    (void) fscanf(stream, "%f %f", &cx, &cy);
    ex = vec3_read(stream);
    ey = vec3_read(stream);
    ez = vec3_read(stream);
    p = vec3_read(stream);

    transf = trans3_to_frame(p, ex, ey, ez);
    return (cam_make(CAMERA_PHYSICAL, &transf, f, pix, ax, ay, cx, cy, w, h));
}

Camera *cam_read(char *pathname, void (*extra_read_func) ( /* ??? */ ))
{
    Camera *cam = NULL;
    FILE   *stream = fopen_2(pathname, "r");

    if (stream)
    {
	cam = cam_read_stream(stream, pathname);
	if (extra_read_func)
	{
	    extra_read_func(cam, stream);
	}
	(void) fclose_2(stream, pathname);
    }
    return (cam);
}

void    cam_write_stream(const Camera * cam, FILE * stream, const char *pathname)
{
    Vec3    ex =
    {Vec3_id};
    Vec3    ey =
    {Vec3_id};
    Vec3    ez =
    {Vec3_id};
    Vec3    p =
    {Vec3_id};

    if (cam)
    {
	(void) fprintf(stream, "%d %d\n\n", cam->width, cam->height);
	(void) fprintf(stream, "%f %f\n\n", cam->pixel, cam->f);
	(void) fprintf(stream, "%f %f\n\n", cam->ax, cam->ay);
	(void) fprintf(stream, "%f %f\n\n", cam->cx, cam->cy);
	trans3_get_frame2in1(*(cam->transf), &p, &ex, &ey, &ez);
	vec3_print(stream, ex);
	(void) fprintf(stream, "\n");
	vec3_print(stream, ey);
	(void) fprintf(stream, "\n");
	vec3_print(stream, ez);
	(void) fprintf(stream, "\n\n");
	vec3_print(stream, p);
	(void) fprintf(stream, "\n");
    }
}

void    cam_write(char *pathname, Camera * cam, void (*extra_write_func) ( /* ??? */ ))
{
    if (cam)
    {
	FILE   *stream = fopen_2(pathname, "w");

	if (stream)
	{
	    cam_write_stream(cam, stream, pathname);
	    if (extra_write_func)
	    {
		extra_write_func(cam, stream);
	    }
	    (void) fclose_2(stream, pathname);
	}
    }
}
