/**@(#)
**/
/**
camera.c:
general camera functions
**/

#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/**
transformation to the coordinate system standing
at point p,
z-axis along aim
y-axis in plane of aim and down
**/

Transform3 trans3_from_aim(Vec3 p, Vec3 aim, Vec3 down)
{
    Vec3    ex = {Vec3_id};
    Vec3    ey = {Vec3_id};
    Vec3    ez = {Vec3_id};

    vec3_basis(aim, down, &ex, &ey, &ez);
    return (trans3_to_frame(p, ex, ey, ez));
}

/**
camera with position and orientation specified as above

Note:

get simplest camera model
    type = 0
    f = ax = ay = 1.0;
    width = height = 1;
    cx = cy = 0.0;
    pix = 1.0;

can get more realistic, centred camera with given field of view using
    type = 0
    f = ax = ay = 1.0;
    width = height (e.g. 256.0 or 512.0)
    cx = cy = width/2.0
    pix = (2.0/width)*tan(theta*DEGREE/2.0) (theta = field of view in degrees)

standard Tina camera has position and orientation
    p = vec3_zero()
    aim = vec3_ez()
    down = vec3_ey()
**/

Camera *cam_from_aim(unsigned int type, Vec3 p, Vec3 aim, Vec3 down, double f, double pix, double ax, double ay, double cx, double cy, int width, int height)
{
    Transform3 transf = {Transform3_id};

    transf = trans3_from_aim(p, aim, down);

    return (cam_make(type, &transf, f, pix, ax, ay, cx, cy, width, height));
}
