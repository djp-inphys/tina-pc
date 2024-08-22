/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Imrect *imf_gauss(Imrect * image, double sig, double precision)
{
    Imrect *wim;
    Prof1  *prof;

    if (image == NULL)
	return (NULL);

    prof = prof_gauss(sig, precision);
    wim = im_filter_rows(image, smooth_1d_sym, (void *) prof);
    image = im_filter_cols(wim, smooth_1d_sym, (void *) prof);
    prof1_free(prof);
    im_free(wim);
    return (image);
}
