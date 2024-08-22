/**@(#)Interchange mat2's and matrices
 */

#include <tina/sys.h>
#include <tina/math.h>

double  matrix_getf();
Matrix *matrix_alloc();

Matrix *matrix_mat2(Mat2 m)
{
    Matrix *mat = matrix_alloc(2, 2, matrix_full, float_v);
    float **el;
    int     i, j;

    el = mat->el.float_v;
    for (i = 0; i < 2; ++i)
	for (j = 0; j < 2; ++j)
	    el[i][j] = m.el[i][j];
    return (mat);
}

Mat2    mat2_matrix(Matrix * mat)
{
    Mat2    m = {Mat2_id};
    int     i, j;

    for (i = 0; i < 2; ++i)
	for (j = 0; j < 2; ++j)
	    m.el[i][j] = matrix_getf(mat, i, j);
    return (m);
}
