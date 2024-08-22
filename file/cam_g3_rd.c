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

List   *cal_geom3_list_read(char *pathname)
{
    FILE   *stream = fopen_2(pathname, "r");
    List   *world_3d = NULL;

    if (stream)
    {
	Match  *match_to_3d;
	Vec3   *point;
	char    ch[1024];
	int     i = 0;

	while (readline(stream, ch) != EOF)
	{
	    match_to_3d = match_alloc(0);
	    match_to_3d->to1 = point = vec3_alloc();
	    match_to_3d->label = i++;
	    (void) sscanf(ch, "  %f %f %f", &point->el[0], &point->el[1], &point->el[2]);
	    world_3d = list_append(world_3d, link_alloc((void *) match_to_3d, 0));
	}
	(void) fclose_2(stream, pathname);
    } else
    {
	errorf(warning, "unable to find 3D data\n");
    }
    return (world_3d);
}
