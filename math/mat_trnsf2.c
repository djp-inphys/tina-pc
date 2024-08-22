/**@(#)Matrix to/from Transform2 conversions
 */

#include <tina/sys.h>
#include <tina/math.h>

double  matrix_getf();
Matrix *matrix_alloc();

Matrix *matrix_transform2(Transform2 transf)
{
    Matrix *mat = matrix_alloc(3, 3, matrix_full, float_v);
    float **el;
    int     i, j;

    el = mat->el.float_v;
    for (i = 0; i < 2; ++i)
	for (j = 0; j < 2; ++j)
	    el[i][j] = transf.R.el[i][j];

    for (i = 0; i < 2; ++i)
	el[i][2] = transf.t.el[i];

    el[2][2] = 1.0;

    return (mat);
}

Transform2 trans2_matrix(Matrix * mat)
{
    Transform2 transf = {Transform2_id};
    float **el = mat->el.float_v;
    int     i, j;

    for (i = 0; i < 2; ++i)
	for (j = 0; j < 2; ++j)
	    transf.R.el[i][j] = el[i][j];

    for (i = 0; i < 2; ++i)
	el[i][2] = transf.t.el[i] = el[i][2];

    return (transf);
}
