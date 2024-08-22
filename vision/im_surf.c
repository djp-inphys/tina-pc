/**@(#)
**/
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

void    terrain_data_free(Terrain_data * surf)
{
    if (surf == NULL)
	return;

    narray_free((char **) surf->data, 0, surf->m, 0, surf->n, sizeof(Vec3));
    carray_free(surf->mask, 0, surf->m, 0, surf->n);
    rfree((void *) surf);
}

Terrain_data *terrain_alloc(int type, int m, int n)
{
    Terrain_data *surf;

    surf = ts_ralloc(Terrain_data);
#ifdef TSTRUCT
    surf->data = ts_narray_alloc(0, 0, m, n, Vec3);
#else
    surf->data = (Vec3 **) narray_alloc(0, 0, m, n, sizeof(Vec3));
#endif
    surf->mask = carray_alloc(0, 0, m, n);
    surf->type = type;
    surf->m = m;
    surf->n = n;
    return (surf);
}

Terrain_data *terrain_copy(Terrain_data * surf)
{
    Terrain_data *copy;
    int     m, n, i, j;

    if (surf == NULL)
	return (NULL);

    m = surf->m;
    n = surf->n;

    copy = terrain_alloc(surf->type, m, n);

    for (i = 0; i < m; ++i)
	for (j = 0; j < n; ++j)
	{
	    copy->mask[i][j] = surf->mask[i][j];
	    copy->data[i][j] = surf->data[i][j];
	}

    return (copy);
}

Terrain_data *terrain_make(Imregion * region, Imrect * mask, int samplex, int sampley)
{
    Terrain_data *surf;
    int     lx, ly, ux, uy;
    int     m, n;		/* mrows and n columns */
    int     i, j, r, c;
    float   x, y;

    if (region == NULL)
	return (NULL);

    lx = region->lx;
    ly = region->ly;
    ux = region->ux;
    uy = region->uy;

    m = (uy - ly) / sampley;
    n = (ux - lx) / samplex;

    uy--;
    ux--;
    surf = terrain_alloc(IMAGE, m + 1, n + 1);

    for (i = 0; i < m; i++)
    {
        r = ly + i * sampley;
	y = (float)r; 
	for (j = 0; j < n; ++j)
	{
            c = lx + j * samplex;
	    x = (float)c;
	    surf->data[i][j] = vec3(x, y, 0.0);
	    if (mask == NULL || im_get_pix(mask, r, c))
		surf->mask[i][j] = 1;
	}
	surf->data[i][j] = vec3((float) ux, y, 0.0);
	if (mask == NULL || im_get_pix(mask, r, ux))
	    surf->mask[i][j] = 1;
    }

    for (j = 0; j < n; ++j)
    {
        c = lx + j * samplex;
	x = (float)c;
	surf->data[i][j] = vec3(x, (float) uy, 0.0);
	if (mask == NULL || im_get_pix(mask, uy, c))
	    surf->mask[i][j] = 1;
    }

    surf->data[i][j] = vec3((float) ux, (float) uy, 0.0);
    if (mask == NULL || im_get_pix(mask, uy, ux))
	surf->mask[i][j] = 1;

    return (surf);
}

Terrain_data *im_surface(Imrect * im, Imrect * mask, int samplex, int sampley, double scale)
{
    Terrain_data *surf;
    int     lx, ly, ux, uy;
    int     m, n;		/* mrows and n columns */
    int     i, j, r, c;
    float   x, y;

    if (im == NULL || im->region == NULL)
	return (NULL);

    lx = im->region->lx;
    ly = im->region->ly;
    ux = im->region->ux;
    uy = im->region->uy;

    m = (uy - ly) / sampley;
    n = (ux - lx) / samplex;

    uy--;
    ux--;
    surf = terrain_alloc(IMAGE, m + 1, n + 1);

    for (i = 0; i < m; i++)
    {
        r = ly + i * sampley;
	y = (float) r;
	for (j = 0; j < n; ++j)
	{
            c = lx + j * samplex;
	    x = (float) c;
	    if (mask == NULL || im_get_pix(mask, r, c))
	    {
		surf->data[i][j] = vec3(x, y, im_get_pixf(im, r, c) * scale);
		surf->mask[i][j] = 1;
	    } else
		surf->data[i][j] = vec3(x, y, 0.0);
	}
	if (mask == NULL || im_get_pix(mask, r, ux))
	{
	    surf->data[i][j] = vec3((float) ux, y, im_get_pixf(im, r, ux) * scale);
	    surf->mask[i][j] = 1;
	} else
	    surf->data[i][j] = vec3((float) ux, y, 0.0);
    }

    for (j = 0; j < n; ++j)
    {
        c = lx + j * samplex;
	x = (float) c;
	if (mask == NULL || im_get_pix(mask, uy, c))
	{
	    surf->data[i][j] = vec3(x, (float) uy, im_get_pixf(im, uy, c) * scale);
	    surf->mask[i][j] = 1;
	} else
	    surf->data[i][j] = vec3(x, (float) uy, 0.0);
    }
    if (mask == NULL || im_get_pix(mask, uy, ux))
    {
	surf->data[i][j] = vec3((float) ux, (float) uy, im_get_pixf(im, uy, ux) * scale);
	surf->mask[i][j] = 1;
    } else
	surf->data[i][j] = vec3((float) ux, (float) uy, 0.0);
    return (surf);
}
