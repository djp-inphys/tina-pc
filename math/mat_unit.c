/**@(#)Unit matrix
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

Matrix *matrix_alloc();

Matrix *matrix_unit(int m, int n, Matrix_shape shape, Vartype vtype)
{
    Matrix *unit;
    int     i;

    if (m < 0 || n < 0)
    {
	error("matrix_unit: bad array bound", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("matrix_unit: zero array bound", warning);
	return (NULL);
    }
    unit = matrix_alloc(m, n, shape, vtype);
    for (i = 0; i < MIN(m, n); ++i)
	matrix_put(1, unit, i, i);

    return (unit);
}
