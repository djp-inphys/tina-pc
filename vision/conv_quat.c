/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

void    conv_rot_to_quat(Mat3 * mat, double *q)
{
    q[0] = 0.5 * sqrt(mat->el[0][0] + mat->el[1][1] + mat->el[2][2] + 1.0);
    if (q[0] > 1.0)
    {
	q[0] = 1.0;
	q[1] = 0.0;
	q[2] = 0.0;
	q[3] = 0.0;
    } else if (q[0] == 0.0)
    {
	q[1] = 1.0;
	q[2] = 0.0;
	q[3] = 0.0;
    } else
    {
	q[1] = (mat->el[2][1] - mat->el[1][2]) / (4.0 * q[0]);
	q[2] = (mat->el[0][2] - mat->el[2][0]) / (4.0 * q[0]);
	q[3] = (mat->el[1][0] - mat->el[0][1]) / (4.0 * q[0]);
    }
}

void    conv_quat_to_rot(double *q, Mat3 * mat)
{
    mat->el[0][0] = (float)(q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3]);
    mat->el[1][0] = (float)(2.0 * (q[1] * q[2] + q[0] * q[3]));
    mat->el[2][0] = (float)(2.0 * (q[1] * q[3] - q[0] * q[2]));
    mat->el[0][1] = (float)(2.0 * (q[1] * q[2] - q[0] * q[3]));
    mat->el[1][1] = (float)(q[0] * q[0] - q[1] * q[1] + q[2] * q[2] - q[3] * q[3]);
    mat->el[2][1] = (float)(2.0 * (q[2] * q[3] + q[0] * q[1]));
    mat->el[0][2] = (float)(2.0 * (q[1] * q[3] + q[0] * q[2]));
    mat->el[1][2] = (float)(2.0 * (q[2] * q[3] - q[0] * q[1]));
    mat->el[2][2] = (float)(q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3]);
}
