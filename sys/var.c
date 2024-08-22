/**@(#)Tina's sizeof (for Tina image type indicators (which are enums))
**/
#include <tina/sys.h>

unsigned int var_size(Vartype type)
{
    switch (type)
    {
	case char_v:
	case uchar_v:
	return (sizeof(char));
    case short_v:
    case ushort_v:
	return (sizeof(short));
    case int_v:
    case uint_v:
	return (sizeof(int));
    case float_v:
	return (sizeof(float));
    case double_v:
	return (sizeof(double));
    case complex_v:
	return (sizeof(Complex));
    case ptr_v:
	return (sizeof(void *));
    default:
	return (sizeof(char));
    }
}
