/**@(#)
 */
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

extern Bool fclose_2(FILE * stream, const char *pathname);

void    ffg_new_write_file_stream(List * cliche_list, FILE * stream,
				          const char *pathname)
{
    int     count;
    List   *cptr;
    List   *ptr;

    for (count = 0, cptr = cliche_list; cptr != NULL; cptr = cptr->next)
	count++;

    (void) fprintf(stream, "%d\n", count);

    for (cptr = cliche_list; cptr != NULL; cptr = cptr->next)
    {
	Match_cliche *m = (Match_cliche *) cptr->to;

	for (count = 0, ptr = m->focus; ptr != NULL; ptr = ptr->next)
	    count++;
	(void) fprintf(stream, "%d %d", count, m->fthres);
	for (ptr = m->focus; ptr != NULL; ptr = ptr->next)
	    (void) fprintf(stream, " %d", geom_label_get(ptr->to, ptr->type));


	for (count = 0, ptr = m->group; ptr != NULL; ptr = ptr->next)
	    count++;
	(void) fprintf(stream, " %d %d", count, m->gthres);
	for (ptr = m->group; ptr != NULL; ptr = ptr->next)
	    (void) fprintf(stream, " %d", geom_label_get(ptr->to, ptr->type));
	(void) fprintf(stream, "\n");
    }
}

/* Match_cliche list */
void    ffg_new_write_file(char *pathname, List * cliche_list)
{
    FILE   *stream = fopen(pathname, "w");

    if (stream)
    {
	ffg_new_write_file_stream(cliche_list, stream, pathname);
	(void) fclose_2(stream, pathname);
    }
}
