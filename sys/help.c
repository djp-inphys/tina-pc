#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define TINA_HELPDIR "TINA_HELPDIR"
#define HELP_DEFAULT "default"

/* Print help from a file <help_file_name> in <help_win>, searching
 * directories in this order: current directory, directory specified by
 * environment variable TINA_HELPDIR, home directory. (Re-reads file on
 * each button press to simplify adding help (instant gratification!).
 * (Usually output to Help tool's text subwindow.) */
void print_help(void *help_win, char *help_file_name)
{
    char help_file_path[256];
    FILE *help_file;
    char *string_append();
    void format_sw();

    /* Ensure help file name is not NULL or "" */
    if (!help_file_name || !*help_file_name)
    {
#ifdef DEBUG
	format_sw(help_win, "NULL help filename passed,"
		  "using \"default\" instead\n");
#endif				/* DEBUG */
	help_file_name = HELP_DEFAULT;
    }

    /* Try to find in current directory */
    string_append(help_file_path, help_file_name, ".hlp", NULL);
    help_file = fopen(help_file_path, "r");

    /* Try to find in help directory (from env var */
    if (!help_file)
    {
	char *helpdir = getenv(TINA_HELPDIR);

#ifdef DEBUG
	format_sw(help_win, "Can't open %s\n", help_file_path);
#endif				/* DEBUG */

	if (helpdir)
	{
	    string_append(help_file_path, helpdir, "/", help_file_name, ".hlp", NULL);
	    help_file = fopen(help_file_path, "r");
	}
    }

    /* Try to find in home directory */
    if (!help_file)
    {
	char *home = getenv("HOME");
#ifdef DEBUG
	format_sw(help_win, "Can't open %s\n", help_file_path);
#endif				/* DEBUG */
	if (home)
	{
	    string_append(help_file_path, home, "/", help_file_name, ".hlp", NULL);
	    help_file = fopen(help_file_path, "r");
	}
    }

    /* Print contents of help file (if found) */
    if (help_file)
    {
	char helpline[256];
	while (fgets(helpline, 256, help_file))
	{
	    format_sw(help_win, "%s", helpline);
	}
	fclose(help_file);
    }
    else
    {
#ifdef DEBUG
	format_sw(help_win, "Can't open %s\n", help_file_path);
#endif				/* DEBUG */
	format_sw(help_win, "No help available yet on this.\n");
    }
}
