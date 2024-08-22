/**@(#)
**/
/* iso_error.c
 * 
 * simple isotropic error model for geometric data
 * 
 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

static float pos_error = (float) 2.0;	/* position error in mm */
static float rot_error = (float) 0.05;	/* rotation error in radians */

void    iso_set_defaults(double p, double r)
{
    pos_error = (float) p;
    rot_error = (float) r;
}

Iso_error *iso_alloc(void)
{
    Iso_error *iso = ts_ralloc(Iso_error);

    iso->dot = (float) 1.0;
    iso->pos = iso->rot = (float) 0.0;
    return (iso);
}

void    geom_add_iso_prop(void *geom, int type)
{
    Iso_error *lerror;

    if (geom == NULL)
	return;

    lerror = iso_alloc();
    geom_prop_add(geom, type, (void *) lerror, ISO_ERROR, rfree);
}

void    geom_addifnp_iso_prop(void *geom, int type)
{
    Iso_error *lerror;

    if (geom == NULL)
	return;

    lerror = iso_alloc();
    geom_prop_addifnp(geom, type, (void *) lerror, ISO_ERROR, rfree, true);
}

void    geom_set_iso_default_error(void *geom, int type)
{
    Iso_error *lerror;

    if (geom == NULL)
	return;

    lerror = (Iso_error *) geom_prop_get(geom, type, ISO_ERROR);
    if (lerror == NULL)
    {
	lerror = iso_alloc();
	geom_prop_add(geom, type, (void *) lerror, ISO_ERROR, rfree);
    }
    lerror->pos = pos_error;
    lerror->rot = (type == CONIC3) ? 3 * rot_error : rot_error;
    lerror->dot = (float) cos(lerror->rot);
}

void    geom_set_iso_zero_error(void *geom, int type)
{
    Iso_error *lerror;

    if (geom == NULL)
	return;

    lerror = (Iso_error *) geom_prop_get(geom, type, ISO_ERROR);
    if (lerror == NULL)
    {
	lerror = iso_alloc();
	geom_prop_add(geom, type, (void *) lerror, ISO_ERROR, rfree);
    }
    lerror->pos = (float) 0.0;
    lerror->rot = (float) 0.0;
    lerror->dot = (float) 1.0;
}
