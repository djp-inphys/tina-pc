/**@(#)Interchange mat3's and matrices
 */

#include <tina/sys.h>
#include <tina/math.h>

double  matrix_getf();
Matrix *matrix_alloc();

Matrix *matrix_mat3(Mat3 m)
{
    Matrix *mat = matrix_alloc(3, 3, matrix_full, float_v);
    float **el;
    int     i, j;

    el = mat->el.float_v;
    for (i = 0; i < 3; ++i)
	for (j = 0; j < 3; ++j)
	    el[i][j] = m.el[i][j];
    return (mat);
}

Mat3    mat3_matrix(Matrix * mat)
{
    Mat3    m = {Mat3_id};
    int     i, j;

    for (i = 0; i < 3; ++i)
	for (j = 0; j < 3; ++j)
	    m.el[i][j] = matrix_getf(mat, i, j);
    return (m);
}
