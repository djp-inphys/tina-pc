/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

/**
try to support at least 3 image types
**/

Vartype im_sup_vtype(Vartype vtype1, Vartype vtype2)
{
    if (vtype1 == complex_v || vtype2 == complex_v)
	return (complex_v);
    else if (vtype1 == float_v || vtype2 == float_v ||
	     vtype1 == double_v || vtype2 == double_v)
	return (float_v);
    else
	return (int_v);
}
