/**@(#)
**/
/* cone_trans.c
 * 
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void    cone_transform(Cone * cone, Transform3 trans)
{
    if (cone == NULL)
	return;

    conic3_transform(cone->c1, trans);
    conic3_transform(cone->c2, trans);
}
