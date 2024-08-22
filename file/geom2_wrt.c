/**@(#)
  */
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void    line2_fprint(FILE * fp, Line2 * line)
{
    Vec3    v = {Vec3_id};

    (void) fprintf(fp, "S %d 1 %f ", line->label, line->length);

	vec3_x( v ) = vec2_x( line->p1 ); 
	vec3_y( v ) = vec2_y( line->p1 ); 
	vec3_z( v ) = (float) 0.0;

    vec3_print(fp, v);

	vec3_x( v ) = vec2_x( line->p2 ); 
	vec3_y( v ) = vec2_y( line->p2 ); 
	vec3_z( v ) = (float) 0.0;

    vec3_print(fp, v);

	vec3_x( v ) = vec2_x( line->v ); 
	vec3_y( v ) = vec2_y( line->v ); 
	vec3_z( v ) = (float) 0.0;

    vec3_print(fp, v);

    (void) fprintf(fp, "\n");
}

void    conic2_fprint(FILE * fp, Conic * conic)
{
    if (conic->type != ELLIPSE)
	return;

    (void) fprintf(fp, "E %d ", conic->label);
    vec3_print(fp, vec3_of_vec2(conic->center));
    vec3_print(fp, vec3(1.0, 0.0, 0.0));
    vec3_print(fp, vec3(0.0, 1.0, 0.0));
    (void) fprintf(fp, "%f %f %f ", conic->theta, conic->alpha, conic->beta);
    (void) fprintf(fp, "%f %f\n", conic->t1, conic->t2);
}

static void geom_fprintf(void *geom, int type, FILE * fp)
{
    switch (type)
    {
	case LINE2:
	line2_fprint(fp, (Line2 *) geom);
	break;
    case CONIC2:
	conic2_fprint(fp, (Conic *) geom);
	break;
    default:
	break;
    }
}

/* BUGFIX: Julian Briggs 1/11/93. Was:List   *geom2_write_fp(FILE * fp,
 * List * geom) */
void    geom2_write_fp(FILE * fp, List * geom)
{
    reclist_list_apply(geom, geom_fprintf, (int) NULL, fp);
}

void    geom2_write(char *pathname, List * geom)
{
    char    temps[256];
    FILE   *fp;

    if ((fp = fopen(pathname, "w")) == NULL)
    {
	(void) string_append(temps, "can not open file ", pathname, 0);
	error(temps, non_fatal);
	return;
    }
    geom2_write_fp(fp, geom);
    (void) fclose(fp);
}

void    line2_write_geom(char *pathname, List * geom)	/* historical */


{
    geom2_write(pathname, geom);
}
