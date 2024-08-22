/**@(#)Output (Anit's printf)
  to redirect mprintf calls from ts_printf to format
**/
#include <tina/sys.h>
#include <tina/sysfuncs.h>

int     mprintf(char *formats,...)
{
    va_list args;
    char    message_string[1024];

    va_start(args, formats);
    vsprintf(message_string, formats, args);

    format(message_string);
    return 1;
}
