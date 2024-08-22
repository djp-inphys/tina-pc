/**@(#)Output error messages  (Tina's fprintf(stderr, ...))
 * @(#)Norm is output to Top tool's text subwindow
 * @(#)If 2 (or more) text subwindows, then output to most recently CREATED
 * @(#)If no text subwindow, then output to shell
**/

#include <stdio.h>
#include <stdarg.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <errno.h>

/**Error print function called when text window is not available**/
#ifndef _PCC
#ifdef _ICC

static char *sys_errlist[37][256];
static int sys_nerr = 0;

#else 
extern char *sys_errlist[];
extern int sys_nerr;

#endif /* end _ICC */
#endif /* end _PCC */

void    error_default_print(char *string)
{
    (void) fprintf(stderr, "%s", string);
}

static void (*error_print) () = error_default_print;

void    error_set_print(void (*func) ( /* ??? */ ))
{
    error_print = func;
}

void    (*error_get_print(void)) ( /* ??? */ )
{
    return (error_print);
}

void    error(char *msg, Error type)
{
    void    exit(int);

    char    string[256];

    switch (type)
    {
    case fatal:		/** use only if ABSOLUTELY necessary **/
	(void) string_append(string, "fatal error: ", msg, "\n", NULL);
	error_default_print(string);
	if (errno < sys_nerr)
	{
	    (void) string_append(string, "perror: ", sys_errlist[errno], "\n", NULL);
	    error_default_print(string);
	}
	exit(1);
	break;
    case non_fatal:		/** a bad thing has happened **/
	(void) string_append(string, "non-fatal error: ", msg, "\n", NULL);
	error_print(string);
	if (errno < sys_nerr)
	{
	    (void) string_append(string, "perror: ", sys_errlist[errno], "\n", NULL);
	    error_print(string);
	}
	break;
    case warning:		/** e.g. unable to give response required **/
	(void) string_append(string, "warning: ", msg, "\n", NULL);
	error_print(string);
	break;
    case core_dump:		/** force a core dump **/
	(void) string_append(string, "core-dump error: ", msg, "\n", NULL);
	error_default_print(string);
	error_default_print(" - forcing core dump - ");
	{
	    int     i = *(int *) NULL;

	    i = i;

	}
	break;
    default:
	error("error: no such error type", non_fatal);
    }
}


void    errorf(Error type, char *format,...)
{
    static char err_msg[BUFSIZ];
    static char format_new[BUFSIZ];
    va_list ap;
    void    exit(int);

    va_start(ap, format);

    switch (type)
    {
    case fatal:		/** use only if ABSOLUTELY necessary **/
	(void) string_append(format_new, "fatal errorf: ", format, NULL);
	(void) vsprintf(err_msg, format_new, ap);
	error_default_print(err_msg);
	if (errno < sys_nerr)
	{
	    (void) string_append(err_msg, "perror: ", sys_errlist[errno], "\n", NULL);
	    error_print(err_msg);
	}
	exit(1);
	break;
    case non_fatal:		/** a bad thing has happened **/
	(void) string_append(format_new, "non-fatal errorf: ", format, NULL);
	(void) vsprintf(err_msg, format_new, ap);
	error_print(err_msg);
	if (errno < sys_nerr)
	{
	    (void) string_append(err_msg, "perror: ", sys_errlist[errno], "\n", NULL);
	    error_print(err_msg);
	}
	break;
    case warning:		/** e.g. unable to give response required **/
	(void) string_append(format_new, "warning: ", format, NULL);
	(void) vsprintf(err_msg, format_new, ap);
	error_print(err_msg);
	break;
    case core_dump:		/** force a core dump **/
	(void) string_append(format_new, "core-dump errorf: ", format, NULL);
	(void) vsprintf(err_msg, format_new, ap);
	error_default_print(err_msg);
	error_default_print(" - forcing core dump - ");
	{
	    int     i = *(int *) NULL;

	    i = i;

	}
	break;
    default:
	errorf(non_fatal, "error: no such error type");
    }
}
