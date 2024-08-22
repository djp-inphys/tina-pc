/**@(#)String (eg ``Hello world'') handling.
**/
#include <stdio.h>
#include <string.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>

#ifndef ANSIFYING
#ifdef __STRICT_ANSI__

char   *string_append(char *string,...)
{
    va_list ap;
    char   *substring;

    va_start(ap, string);
    (void) strcpy(string, "");
    while ((substring = va_arg(ap, char *)) != (char *) 0)
	(void) strcat(string, substring);
    va_end(ap);

    return (string);
}


char   *string_alloc_append(char *substr0,...)
{
    int     n = 0;
    va_list ap;
    char   *str;
    char   *substr;

    va_start(ap, substr0);

    for (n = 0, substr = substr0; substr; substr = va_arg(ap, char *))
    {
	n += strlen(substr);
    }

    va_end(ap);

    str = (char *) ralloc((unsigned) (n + 1) * sizeof(char));

    va_start(ap, substr0);

    (void) strcpy(str, "");

    for (substr = substr0; substr; substr = va_arg(ap, char *))
    {
	(void) strcat(str, substr);
    }

    va_end(ap);

    return (str);
}

#else

char   *string_append(string, va_alist)
char   *string;

va_dcl
{
    va_list ap;
    char   *substring;

    va_start(ap);
    (void) strcpy(string, "");
    while ((substring = va_arg(ap, char *)) != (char *) 0)
	(void) strcat(string, substring);
    va_end(ap);

    return (string);
}

char   *string_alloc_append(va_alist) va_dcl
{
    int     n;
    va_list ap;
    char   *str, *substr;

    n = 0;
    va_start(ap);
    for (n = 0; (substr = va_arg(ap, char *)) != NULL; n += strlen(substr));
    va_end(ap);

    str = (char *) ralloc((unsigned) (n + 1) * sizeof(char));

    va_start(ap);
    (void) strcpy(str, "");
    while ((substr = va_arg(ap, char *)) != (char *) 0)
	(void) strcat(str, substr);
    va_end(ap);

    return (str);
}

#endif				/* __STRICT_ANSI__ */
#endif				/* ANSIFYING */

char   *string_copy(char *string)
{
    char   *copy;

    copy = (char *) ralloc((unsigned) strlen(string) + 1);
    (void) strcpy(copy, string);
    return (copy);
}

static int isspace(int c)
{
    return (c == ' ' || c == '\n');
}

int     readline(FILE * fp, char *string)
{
    int     c;
    int     i = 0;

    while (isspace(c = getc(fp)));

    if (c == EOF)
	return (EOF);
    do
    {
	string[i++] = c;
    } while ((c = getc(fp)) != '\n' && c != EOF);
    string[i++] = '\0';
    return (i);
}

int     read_into_int(int *x, char *string, char *msg)
{
    int     y;
    char    temps[256];

    if (sscanf(string, "%d", &y) == 1)
    {
	*x = y;
	message(string_append(temps, msg, string, "\n", 0));
	return (1);
    }
    message("read_into_int: string not an int\n");
    return (0);
}

int     read_into_short(short int *x, char *string, char *msg)
{
    short   y;
    char    temps[256];

    if (sscanf(string, "%hd", &y) == 1)
    {
	*x = y;
	message(string_append(temps, msg, string, "\n", 0));
	return (1);
    }
    message("read_into_short: string not a short\n");
    return (0);
}

int     read_into_float(float *x, char *string, char *msg)
{
    float   y;
    char    temps[256];

    if (sscanf(string, "%f", &y) == 1)
    {
	*x = y;
	message(string_append(temps, msg, string, "\n", 0));
	return (1);
    }
    message("read_into_float: string not a float\n");
    return (0);
}

int     read_into_double(double *x, char *string, char *msg)
{
    double  y;
    char    temps[256];

    if (sscanf(string, "%lf", &y) == 1)
    {
	*x = y;
	message(string_append(temps, msg, string, "\n", 0));
	return (1);
    }
    message("read_into_double: string not a float\n");
    return (0);
}

int     read_into_string(char *x, char *string, char *msg)
{
    char    temps[256];

    (void) strcpy(x, string);
    message(string_append(temps, msg, string, "\n", 0));
    return (1);
}
