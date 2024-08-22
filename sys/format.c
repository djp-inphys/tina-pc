/**@(#)Output (Tina's printf)
 * @(#)Norm is output to Top tool's text subwindow
 * @(#)If 2 (or more) text subwindows, then output to most recently CREATED
 * @(#)If no text subwindow, then output to shell
**/
#include <tina/sys.h>

void    default_print(char *msg)
{
    (void) printf("%s", msg);
}

void    default_print_sw(void* text_subwin, char *msg)
{
    (void) printf("%s", msg);
}

static void (*print) () = default_print;
static void (*print_sw) (void*text_subwin, char *msg) = default_print_sw;

void    format_set_print(void (*func) ( /* ??? */ ))
{
    print = func;
}

void    (*format_get_print(void)) ( /* ??? */ )
{
    return (print);
}
#ifdef _PCC
void    *format_get_print_sw (void (*format_sw)
			      (void* text_subwin, char *msg))
{
    return (void*)print_sw;
}
#else
void    (*format_get_print_sw(void)) (void (*format_sw)
				      (void* text_subwin, char *msg))
{
    return (void *)print_sw;
}
#endif
void    format_set_print_sw(void (*format_sw_func) (void* text_subwin, char *msg))
{
    print_sw = format_sw_func;
}

static void default_flush(void)
{
}

static void (*flush) () = default_flush;

void    format_set_flush(void (*func) ( /* ??? */ ))
{
    flush = func;
}

void    (*format_get_flush(void)) ( /* ??? */ )
{
    return (flush);
}

#ifndef ANSIFYING
#ifdef __STRICT_ANSI__


void    format(char *fmt,...)
{
    va_list ap;
    char    string[1024];

    va_start(ap, fmt);
    (void) vsprintf(string, fmt, ap);
    print(string);
    va_end(ap);
}

void    format_sw(void* text_subwin, char *fmt,...)
{
    va_list ap;
    char    string[1024];

    va_start(ap, fmt);
    (void) vsprintf(string, fmt, ap);
    print_sw(text_subwin, string);
    va_end(ap);
}

/* Print message to tw text window so it appears immediately. */
void    format_flush(char *fmt,...)
{
    va_list ap;
    char    string[1024];

    va_start(ap, fmt);
    (void) vsprintf(string, fmt, ap);
    format(string);
    flush();
    va_end(ap);
}

#else

void    format(fmt, va_alist)
char   *fmt;

va_dcl
{
    va_list ap;
    char    string[1024];

    va_start(ap);
    (void) vsprintf(string, fmt, ap);
    print(string);
    va_end(ap);
}

void    format_flush(fmt, va_alist)
char   *fmt;

va_dcl
{
    va_list ap;
    char    string[1024];

    va_start(ap);
    (void) vsprintf(string, fmt, ap);
    format(string);
    flush();
    va_end(ap);
}

#endif				/* __STRICT_ANSI__ */
#endif				/* ANSIFYING */
