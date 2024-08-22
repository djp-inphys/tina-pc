/**@(#)Print shape of matrix
**/

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>

void    format_shape(Matrix_shape shape)
{
    switch (shape)
    {
	case matrix_full:
	format("full");
	break;
    case matrix_lower:
	format("lower");
	break;
    case matrix_symmetric:
	format("symmetric");
	break;
    default:
	format("unknown");
	break;
    }
}
