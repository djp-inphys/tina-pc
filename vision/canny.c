/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Imrect *canny(Imrect * im, double sigma, double precision, double lowthres, double upthres, int lengththres)
{
    Imrect *gim;
    Imrect *edrect;
    Imrect *gradx;
    Imrect *grady;
    Imrect *gradsq;
    unsigned int label;		/* for blocked allocation */

    if (im == NULL)
	return (NULL);

    label = ralloc_end_blocked();

    if (sigma == 0.0)
	gim = im_copy(im);
    else
	gim = imf_gauss(im, sigma, precision);
    gradx = imf_grad_h(gim);
    grady = imf_grad_v(gim);
    im_free(gim);
    gradsq = imf_sumsq(gradx, grady);

    if (label)			/* allocation was blocked */
	(void) ralloc_start_blocked(label);	/* re-start blocking */

    edrect = nonmaxsup(gradx, grady, gradsq, lowthres);
    im_free(gradx);
    im_free(grady);
    im_free(gradsq);
    er_find_edge_strings(edrect);
    er_rm_edges(edrect, EDGE_GET_CONN_MASK, EDGE_NOLINK);
    er_edge_strings_thres(edrect, lengththres, upthres);
    er_set_row_index(edrect);
    return (edrect);
}
