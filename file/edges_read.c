/**@(#)
  */
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

extern Bool fclose_2(FILE * stream, const char *pathname);
extern FILE *fopen_2(const char *pathname, const char *mode);

Imrect *edges_read_stream(int height, int width, Imregion * region, FILE *
			          stream, const char *pathname)
{
    Imrect *edge_image;
    Imrect *im_alloc();
    float   (*buffer)[4];
    int     count, i;
    unsigned int buffsize;

    if (1 != fread((char *) &count, sizeof(int), 1, stream))
    {
	errorf(non_fatal, "edges_read_stream: empty file: %s\n", pathname);
	return (NULL);
    }
    buffsize = count * sizeof(float[4]);
    buffer = (float (*)[4]) ralloc(buffsize);
    if (fread((char *) buffer, sizeof(float[4]), count, stream)
                      != (unsigned int) count)
    {
	errorf(non_fatal, "edges_read_stream: premature end of file: %s\n", pathname);
	rfree((void *) buffer);
	return (NULL);
    }
    edge_image = im_alloc(height, width, region, ptr_v);
    region = edge_image->region;

    for (i = 0; i < count; ++i)
    {
	Edgel  *eptr;
	Edgel  *edge_alloc();
	extern int er_add_edge(Imrect * edgerect, Edgel * edge);

	float  *edge_buff = buffer[i];

	if (!roi_inregion(region, (int) edge_buff[0], (int) edge_buff[1]))
	    continue;

	eptr = edge_alloc(EDGE_RAW);
	eptr->pos = vec2(edge_buff[1], edge_buff[0]);
	eptr->contrast = edge_buff[2];
	eptr->orient = edge_buff[3];
	(void) er_add_edge(edge_image, eptr);
    }

    rfree((void *) buffer);
    return (edge_image);
}

Imrect *edges_read_file(const char *pathname, const int height, const int width,
			        Imregion * region)
{
    FILE   *stream = fopen_2(pathname, "r");
    Imrect *er = NULL;

    if (stream)
    {
	er = edges_read_stream(height, width, region, stream, pathname);
	(void) fclose_2(stream, pathname);
    }
    return (er);
}
