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

static FILE *stream;
static Bool first = true;
static float cx, cy;
static float ax, ay;

static void wisp_write_edge(Edgel * edge)
{
    if (first == true)
    {
	(void) fprintf(stream, "\nm ");
	first = false;
    } else
	(void) fprintf(stream, "c ");

    (void) fprintf(stream, "%f %f\n", (vec2_x(edge->pos) - cx) * ay, (cy - vec2_y(edge->pos)) * ax);
}

static void wisp_write_poly(Line2 * line)
{
    if (first == true)
    {
	(void) fprintf(stream, "\nm %f %f\n", (vec2_x(line->p1) - cx) * ay, (cy - vec2_y(line->p1)) * ax);
	first = false;
    }
    (void) fprintf(stream, "c %f %f\n", (vec2_x(line->p2) - cx) * ay, (cy - vec2_y(line->p2)) * ax);
}

void    wisp_write_edge_string(Tstring * s)
{
    first = true;
    str_apply_func(s, wisp_write_edge, NULL);
}

static void wisp_write_poly_string(Tstring * s)
{
    Tstring *p;
    double  dummy = 0.0;

    first = true;

    /* BUG poly_string requires 2nd argument: double thres. dummy added */
    p = poly_string(s, dummy);
    str_apply_func(p, wisp_write_poly, NULL);
}

void    wisp_write_edges_stream(Imrect * er, Camera * camera, FILE * stream_out)
{
    float   f;

    if (er)
    {
	stream = stream_out;

	if (camera == NULL)
	{
	    f = (float) 1.0;
	    cx = (float) (er->width / 2); /* these two lines may cause a
                                             roundoff bug NAT 3/5/95 */
	    cy = (float) (er->height / 2);
	    ax = (float) 1.0;
	    ay = (float) 1.0;
	} else
	{
	    f = camera->f / camera->pixel * camera->ax;
	    cx = camera->cx;
	    cy = camera->cy;
	    ax = camera->ax;
	    ay = camera->ay;
	}

	(void) fprintf(stream, "ICF %f %d\n", f, er->width / 2);

	er_apply_to_all_strings(er, wisp_write_poly_string, NULL);
    }
}

void    wisp_write_edges(char *pathname, Imrect * er, Camera * camera)
{
    if (er)
    {
	FILE   *stream = fopen_2(pathname, "w");

	if (stream)
	{
	    wisp_write_edges_stream(er, camera, stream);
	    (void) fclose_2(stream, pathname);
	}
    }
}
