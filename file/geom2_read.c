/**@(#)
  */
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

static Line2 *line2_sscanf(char *str)
{
    int     label;
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    Line2  *line;

    if (sscanf(str, "%*s %d %*d %*f %f %f %*f %f %f %*f ",
	       &label,
	       &vec2_x(p1), &vec2_y(p1),
	       &vec2_x(p2), &vec2_y(p2)) != 5)
	return (NULL);

    line = line2_make(p1, p2, FROM_FILE);
    line->label = label;
    return (line);
}

static Conic *ellipse2_sscanf(char *str)
{
    int     label;
    Vec2    center = {Vec2_id};
    float   theta, alpha, beta, t1, t2;
    Conic  *conic;


    if (sscanf(str, "%*s %d %f %f %*f %*f %*f %*f %*f %*f %*f %f %f %f %f %f",
	       &label,
	       &vec2_x(center), &vec2_y(center),
	       &theta, &alpha, &beta, &t1, &t2) != 8)
	return (NULL);
    conic = conic_make(ELLIPSE, center, theta, alpha, beta, t1, t2, 0);
    conic->label = label;
    return (conic);
}

List   *geom2_read_fp(FILE * fp)
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
	case 'S':		/* straight line */
	    geom = (void *) line2_sscanf(str);
	    type = LINE2;
	    break;
	case 'E':		/* ellipse section */
	    geom = (void *) ellipse2_sscanf(str);
	    type = CONIC2;
	    break;
	default:
	    continue;
	}
	if (geom != NULL)
	    list = ref_addtostart(list, geom, type);
    }

    return (list_reverse(list));
}

List   *geom2_read(char *pathname)
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
    geom = geom2_read_fp(fp);
    (void) fclose(fp);
    return (geom);
}

List   *line2_read_geom(char *pathname)	/* historical */

{
    return (geom2_read(pathname));
}
