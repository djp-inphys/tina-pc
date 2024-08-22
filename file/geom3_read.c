/**@(#)
  */
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

static Point3 *point3_sscanf(char *str, int handed)
{
    float   handupdate = (float)((handed == LEFT) ? -1.0 : 1.0);
    int     label;
    Vec3    p1 = {Vec3_id};
    Point3 *point;

    if (sscanf(str, "%*s %d %*d %f %f %f ",
	       &label,
	       &vec3_x(p1), &vec3_y(p1), &vec3_z(p1)) != 4)
	return (NULL);

    p1.el[1] *= handupdate;
    point = point3_make(p1, FROM_FILE);
    point->label = label;
    return (point);
}

static Line3 *line3_sscanf(char *str, int handed)
{
    float   handupdate = (float)((handed == LEFT) ? -1.0 : 1.0);
    int     label;
    Vec3    p1 = {Vec3_id};
    Vec3    p2 = {Vec3_id};
    Line3  *line;

    if (sscanf(str, "%*s %d %*d %*f %f %f %f %f %f %f ",
	       &label,
	       &vec3_x(p1), &vec3_y(p1), &vec3_z(p1),
	       &vec3_x(p2), &vec3_y(p2), &vec3_z(p2)) != 7)
	return (NULL);

    p1.el[1] *= handupdate;
    p2.el[1] *= handupdate;
    line = line3_make(p1, p2, FROM_FILE);
    line->label = label;
    return (line);
}

static Conic3 *ellipse3_sscanf(char *str, int handed)
{
    float   handupdate = (float)((handed == LEFT) ? -1.0 : 1.0);
    int     label;
    Vec3    origin = {Vec3_id};
    Vec3    ex = {Vec3_id};
    Vec3    ey = {Vec3_id};
    Vec3    ez = {Vec3_id};
    float   theta, alpha, beta, t1, t2;
    Conic  *conic;

    if (sscanf(str, "%*s %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
	       &label,
	       &vec3_x(origin), &vec3_y(origin), &vec3_z(origin),
	       &vec3_x(ex), &vec3_y(ex), &vec3_z(ex),
	       &vec3_x(ey), &vec3_y(ey), &vec3_z(ey),
	       &theta, &alpha, &beta, &t1, &t2) != 15)
	return (NULL);

    origin.el[1] *= handupdate;
    ex.el[1] *= handupdate;
    ey.el[1] *= handupdate;
    ez = vec3_unit(vec3_cross(ex, ey));

    conic = conic_make(ELLIPSE, vec2(0.0, 0.0), theta, alpha, beta, t1, t2, 0);
    conic->label = label;
    return (conic3_make(conic, origin, ex, ey, ez));
}

List   *geom3_read_fp(FILE * fp, int handed)

/* LEFT or RIGHT handed coords */
{
    void   *geom;
    char    str[512];
    char    type_s[2];
    List   *list = NULL;
    int     type;

    while (fgets(str, 512, fp) != NULL)
    {
	(void) sscanf(str, "%s", type_s);
	switch (type_s[0])
	{
	case 'P':		/* point */
	    geom = (void *) point3_sscanf(str, handed);
	    type = POINT3;
	    break;
	case 'S':		/* straight line */
	    geom = (void *) line3_sscanf(str, handed);
	    type = LINE3;
	    break;
	case 'E':		/* ellipse section */
	    geom = (void *) ellipse3_sscanf(str, handed);
	    type = CONIC3;
	    break;
	default:
	    continue;
	}
	if (geom != NULL)
	    list = ref_addtostart(list, geom, type);
    }

    return (list_reverse(list));
}

List   *geom3_read(char *pathname, int handed)

/* LEFT or RIGHT handed coords */
{
    char    temps[256];
    List   *geom;
    FILE   *fp;

    if ((fp = fopen(pathname, "r")) == NULL)
    {
	(void) string_append(temps, "can not open file ", pathname, 0);
	error(temps, non_fatal);
	return (NULL);
    }
    geom = geom3_read_fp(fp, handed);
    (void) fclose(fp);
    return (geom);
}

List   *line3_read_geom(char *pathname, int handed)	/* historical */

/* LEFT or RIGHT handed coords */
{
    return (geom3_read(pathname, handed));
}
