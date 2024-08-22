/**@(#)
  */
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/file.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

extern Bool fclose_2(FILE * stream, const char *pathname);
extern FILE *fopen_2(const char *pathname, const char *mode);

/* ARGSUSED Quieten Lint */
void    edge_write(Edgel * edge, int type, Edge_fp * efp)
{
    float   buffer[4];

    buffer[0] = vec2_y(edge->pos);
    buffer[1] = vec2_x(edge->pos);
    buffer[2] = edge->contrast;
    buffer[3] = edge->orient;
    (void) fwrite((char *) buffer, sizeof(float), 4, efp->fp);
    efp->count++;
}

void    edges_write_stream(FILE * stream, Imrect * er)
{
    Edge_fp efp =
    {Edge_fp_id};

    efp.fp = stream;
    efp.count = 0;

    (void) fwrite((char *) &efp.count, sizeof(int), 1, stream);
    er_apply_to_all_edges(er, edge_write, (void *) &efp);
    (void) fseek(stream, (long) 0, 0);
    (void) fwrite((char *) &efp.count, sizeof(int), 1, stream);
}

void    edges_write_file(char *pathname, Imrect * er)
{
    FILE   *stream = fopen_2(pathname, "w");

    if (stream)
    {
	edges_write_stream(stream, er);
	(void) fclose_2(stream, pathname);
    }
}
