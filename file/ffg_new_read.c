/**@(#)
  */
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

extern Bool fclose_2(FILE * stream, const char *pathname);

Match_cliche *match_cliche_new_read(List * list, FILE * stream, const char *pathname)
{
    int     label;
    void   *geom_getbylabel();
    List   *focus = NULL;
    List   *group = NULL;
    int     i, fthres, gthres, count;

    if (fscanf(stream, "%d %d", &count, &fthres) == EOF)
    {
	errorf(non_fatal, "unexpected end of file: %s\n", pathname);
	return (NULL);
    }
    for (i = 0; i < count; ++i)
    {
	void   *feature;
	int     type;

	if (fscanf(stream, "%d", &label) == EOF)
	{
	    errorf(non_fatal, "unexpected end of file: %s\n", pathname);
	    return (NULL);
	}
	feature = geom_getbylabel(list, label, &type);
	focus = ref_addtostart(focus, feature, type);
    }

    if (fscanf(stream, "%d %d", &count, &gthres) == EOF)
    {
	error("unexpected end of file", non_fatal);
	return (NULL);
    }
    for (i = 0; i < count; ++i)
    {
	void   *feature;
	int     type;

	if (fscanf(stream, "%d", &label) == EOF)
	{
	    errorf(non_fatal, "unexpected end of file: %s\n", pathname);
	    return (NULL);
	}
	feature = geom_getbylabel(list, label, &type);
	group = ref_addtostart(group, feature, type);
    }

    return (match_cliche_make(focus, fthres, group, gthres));
}

List   *ffg_new_read_file_stream(List * list, FILE * stream, const char *pathname)
{
    List   *cliche_list = NULL;
    int     i, count;

    if (fscanf(stream, "%d", &count) == EOF)
    {
	errorf(non_fatal, "unexpected end of file: %s\n", pathname);
	return (NULL);
    }
    for (i = 0; i < count; ++i)
    {
	Match_cliche *cliche = match_cliche_new_read(list, stream, pathname);

	if (cliche == NULL)
	{
	    errorf(non_fatal, "problem reading ffg file: %s\n", pathname);
	    list_rm(cliche_list, match_cliche_free);
	    return (NULL);
	}
	cliche_list = ref_addtostart(cliche_list, (void *) cliche, MATCH_CLICHE);
    }
    return (list_reverse(cliche_list));
}

List   *ffg_new_read_file(char *pathname, List * list)
{
    List   *cliche_list;
    FILE   *stream = fopen(pathname, "r");

    if (stream)
    {
	cliche_list = ffg_new_read_file_stream(list, stream, pathname);
	(void) fclose_2(stream, pathname);
    }
    return (cliche_list);
}
