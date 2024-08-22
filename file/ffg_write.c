/**@(#)
  */
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void    ffg_write_file_fp(FILE * fp, List * list)
{
    int     count;
    List   *lptr;
    List   *gptr;

    for (count = 0, lptr = list; lptr != NULL; lptr = lptr->next)
	count++;

    (void) fprintf(fp, "%d\n", count);

    for (lptr = list; lptr != NULL; lptr = lptr->next)
    {
	Match_cliche *m = (Match_cliche *) lptr->to;

	if (m->focus == NULL || m->group == NULL)
	    continue;

	(void) fprintf(fp, "%d ", geom_label_get(m->focus->to, m->focus->type));
	for (count = 0, gptr = m->group; gptr != NULL; gptr = gptr->next)
	    count++;
	(void) fprintf(fp, "%d ", count);
	for (gptr = m->group; gptr != NULL; gptr = gptr->next)
	    (void) fprintf(fp, "%d ", geom_label_get(gptr->to, gptr->type));
	(void) fprintf(fp, "\n");
    }
}

void    ffg_write_file(char *pathname, List * list)

/* Match_cliche list */
{
    char    temps[256];
    FILE   *fp;

    if ((fp = fopen(pathname, "w")) == NULL)
    {
	(void) string_append(temps, "can not open file ", pathname, 0);
	error(temps, non_fatal);
	return;
    }
    ffg_write_file_fp(fp, list);
    (void) fclose(fp);
}
