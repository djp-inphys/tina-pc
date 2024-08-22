/**@(#)
  */
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

static void point3_fprint(FILE * fp, Point3 * point, int handed)


/* LEFT or RIGHT */
{
    float   handupdate = (float)((handed == LEFT) ? -1.0 : 1.0);
    Vec3    p1 = {Vec3_id};

    p1 = point->p;
    p1.el[1] *= handupdate;	/* for compatibility with old tina
				 * system */
    (void) fprintf(fp, "P %d 1 ", point->label);
    vec3_print(fp, p1);
    (void) fprintf(fp, "\n");
}

static void line3_fprint(FILE * fp, Line3 * line, int handed)


/* LEFT or RIGHT */
{
    float   handupdate = (float)((handed == LEFT) ? -1.0 : 1.0);
    Vec3    p1 = {Vec3_id};
    Vec3    p2 = {Vec3_id};
    Vec3    v = {Vec3_id};

    p1 = line->p1;
    p2 = line->p2;
    p1.el[1] *= handupdate;	/* for compatibility with old tina
				 * system */
    p2.el[1] *= handupdate;
    v = line->v;
    (void) fprintf(fp, "S %d 1 %f ", line->label, line->length);
    vec3_print(fp, p1);
    vec3_print(fp, p2);
    vec3_print(fp, v);
    (void) fprintf(fp, "\n");
}

static void conic3_fprint(FILE * fp, Conic3 * con3, int handed)
{
    float   handupdate = (float)((handed == LEFT) ? -1.0 : 1.0);
    Vec3    origin = {Vec3_id};
    Vec3    ex = {Vec3_id};
    Vec3    ey = {Vec3_id};
    Conic  *conic;

    if (con3->type != ELLIPSE)
	return;

    origin = con3->origin;
    ex = con3->ex;
    ey = con3->ey;
    origin.el[1] *= handupdate;
    ex.el[1] *= handupdate;
    ey.el[1] *= handupdate;

    conic = con3->conic;

    (void) fprintf(fp, "E %d ", conic->label);
    vec3_print(fp, origin);
    vec3_print(fp, ex);
    vec3_print(fp, ey);
    (void) fprintf(fp, "%f %f %f ", conic->theta, conic->alpha, conic->beta);
    (void) fprintf(fp, "%f %f\n", conic->t1, conic->t2);
}

static FILE *fp_static;
static int handed_static;

static void geom_fprintf(void *geom, int type)
{
    switch (type)
    {
	case POINT3:
	point3_fprint(fp_static, (Point3 *) geom, handed_static);
	break;
    case LINE3:
	line3_fprint(fp_static, (Line3 *) geom, handed_static);
	break;
    case CONIC3:
	conic3_fprint(fp_static, (Conic3 *) geom, handed_static);
	break;
    default:
	break;
    }
}

/* BUGFIX: Julian Briggs 1/11/93. Was: List   *geom3_write_fp(FILE *
 * fp, List * geom, int handed) */
void    geom3_write_fp(FILE * fp, List * geom, int handed	/* LEFT or RIGHT handed
		           coords */ )
{
    fp_static = fp;
    handed_static = handed;
    reclist_list_apply(geom, geom_fprintf, (int) NULL, NULL);
}

void    geom3_write(char *pathname, List * geom, int handed)


/* LEFT or RIGHT handed coords */
{
    char    temps[256];
    FILE   *fp;

    if ((fp = fopen(pathname, "w")) == NULL)
    {
	(void) string_append(temps, "can not open file ", pathname, 0);
	error(temps, non_fatal);
	return;
    }
    geom3_write_fp(fp, geom, handed);
    (void) fclose(fp);
}

void    line3_write_geom(char *pathname, List * geom, int handed)	/* historical */


/* LEFT or RIGHT handed coords */
{
    geom3_write(pathname, geom, handed);
}
