/**@(#)
  */
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

extern Bool fclose_2(FILE * stream, const char *pathname);
extern FILE *fopen_2(const char *pathname, const char *mode);

Match_cliche *match_cliche_read(FILE * stream, List * list)
{
    int     label;
    void   *focus;
    void   *geom_getbylabel();
    int     ftype;
    List   *group = NULL;
    int     i, count;

    if (fscanf(stream, "%d %d", &label, &count) == EOF)
    {
	error("unexpected end of file", non_fatal);
	return (NULL);
    }
    focus = geom_getbylabel(list, label, &ftype);
    if (focus == NULL)
	return (NULL);

    for (i = 0; i < count; ++i)
    {
	void   *feature;
	int     type;

	if (fscanf(stream, "%d", &label) == EOF)
	{
	    error("unexpected end of file", non_fatal);
	    return (NULL);
	}
	feature = geom_getbylabel(list, label, &type);
	group = ref_addtostart(group, feature, type);
    }
    return (match_cliche_make(link_alloc(focus, ftype), 1, group, 5));
}

List   *ffg_read_file_fp(FILE * stream, List * list)
{
    List   *cliche_list = NULL;
    int     i, count;

    if (fscanf(stream, "%d", &count) == EOF)
    {
	error("unexpected end of file", non_fatal);
	return (NULL);
    }
    for (i = 0; i < count; ++i)
    {
	Match_cliche *cliche = match_cliche_read(stream, list);

	if (cliche == NULL)
	{
	    error("problem reading ffg file", non_fatal);
	    list_rm(cliche_list, match_cliche_free);
	    return (NULL);
	}
	cliche_list = ref_addtostart(cliche_list, (void *) cliche, MATCH_CLICHE);
    }
    return (list_reverse(cliche_list));
}

List   *ffg_read_file(char *pathname, List * list)
{
    List   *cliche_list = NULL;
    FILE   *stream = fopen_2(pathname, "r");

    if (stream)
    {
	cliche_list = ffg_read_file_fp(stream, list);
	(void) fclose_2(stream, pathname);
    }
    return (cliche_list);
}
