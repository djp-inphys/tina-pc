/**@(#)Output (Tina's 2nd printf)
 * @(#)Norm is output to Top tool's text subwindow
 * @(#)If 2 (or more) text subwindows, then output to most recently CREATED
 * @(#)If no text subwindow, then output to shell
**/
#include <stdio.h>

void    message_default_print(char *string)
{
    (void) printf("%s", string);
}

static void (*message_print) (char *string) = message_default_print;

void    message_set_print(void (*func) (char *string))
{
    message_print = func;
}

void    (*message_get_print(void)) (char *string)
{
    return (message_print);
}

void    message(char *msg)
{
    char    string[256];

    (void) sprintf(string, "message: %s\n", msg);
    message_print(string);
}
