#include <math.h>

int tina_int(double x)
/* return next integer below x */
{
    return((int)floor(x));
}

int tina_rint(double x)
/* return nearest integer to x */
{
    return(tina_int(x+0.5));
}
