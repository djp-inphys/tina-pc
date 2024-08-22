/**@(#)Matrix to/from Transform3 conversions
**/

#include <tina/sys.h>
#include <tina/math.h>

double  matrix_getf();
Matrix *matrix_alloc();

Matrix *matrix_transform3(Transform3 transf)
{
    Matrix *mat = matrix_alloc(4, 4, matrix_full, float_v);
    float **el;
    int     i, j;

    el = mat->el.float_v;
    for (i = 0; i < 3; ++i)
	for (j = 0; j < 3; ++j)
	    el[i][j] = transf.R.el[i][j];

    for (i = 0; i < 3; ++i)
	el[i][3] = transf.t.el[i];

    el[3][3] = 1.0;

    return (mat);
}

Transform3 trans3_matrix(Matrix * mat)
{
    Transform3 transf = {Transform3_id};
    float **el = mat->el.float_v;
    int     i, j;

    for (i = 0; i < 3; ++i)
	for (j = 0; j < 3; ++j)
	    transf.R.el[i][j] = el[i][j];

    for (i = 0; i < 3; ++i)
	el[i][3] = transf.t.el[i] = el[i][3];

    return (transf);
}
