/**@(#)
**/
/* setindex.c
 * 
 * functions for constructing and handling a raster based 2D spatial index
 * of a set of edge contours, the first dimension of the index is the
 * raster. elements in the index are stored as an ordered list along
 * the raster. the second dimension of the index provides a spatial
 * jump along the list.
 * 
 * it is built prior to stereo matching
 * 
 * edge contours are indexed at a sub-string level, that is sub-strings
 * are constructed for that part of an edge contour that crosses a
 * specific raster. Edges may be defined at a much finer scale than the
 * scale of the "image" rasters as a result of prior projective scaling
 * and warping.
 * 
 * Edge strings that run in a near vertical direction across the image
 * will usually produce very short, mainly unit length, within raster
 * sub strings.
 * 
 * The type of the sub-string is used to indicate the direction it runs
 * (either forward of backward) along the raster
 * 
 * It is also useful to identify those longer sub-sections of edge
 * contours that are unique with respect to rasters, ie. sections of
 * strings which cross a set of rasters only once. Some strings
 * (without max or min in the y direction) only have a single section.
 * 
 * Each constituent "within raster" sub-string is given a label to
 * identify which "raster wise unique" edge sub-string it forms a part.
 * Basicly this results in the implicit segmentation of edge contours
 * at turning points wrt the y direction. */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* label for unique string sections (wrt epipolars) */
static int string_label = 0;	/* fist value used is 1 */

/* add an edge countour string to a stereo index
 * 
 * involves identifying short sub-strings that run along the current
 * raster membership of a raster is defined by truncation of y
 * locations
 * 
 * if a string has gaps with respect to the row spacing (ie inbetween rows
 * without any data points on them) the index does not. The closest
 * available indexed sub-string is indexed again (perhaps repeatedly
 * for larger gaps). Due care must be taken when using the index.
 * 
 * label members of the raster wise unique edge sub-strings
 * 
 * leave a hook from the edge to the sub-string it is part of using the
 * SINDEX flexible property value of the Edgel */
static void es_add_to_index(List ** index, Tstring * string)
{
    Ddlist *start;
    Ddlist *end;
    Tstring *laststr = NULL, *str;
    int     row, lastrow = 0;
    int     incrow = 0;

    if (index == NULL || string == NULL)
	return;

    ++string_label;		/* new label for raster wise uniqueness */

    start = string->start;
    while (1)
    {
	row = (int)floor(vec2_y(DD_EDGE_POS(start)));
	if (incrow != 0 && incrow * (row - lastrow) < 0)
	    ++string_label;	/* a change row increment direction */
	if (laststr != NULL)
	    incrow = row - lastrow;

	end = start;
	while (1)		/* find rest of string on this raster */
	{
	    if (end == string->end)
		break;
	    if (row != (int) vec2_y(DD_EDGE_POS(end->next)))
		break;
	    end = end->next;
	}

	if (vec2_x(DD_EDGE_POS(start)) < vec2_x(DD_EDGE_POS(end)))
	    str = str_make(FORWARD, start, end);
	else
	    str = str_make(BACKWARD, start, end);

	/* add the sub-string to the property list of the edges */
	es_add_to_prop_list(str, (void *) str, SINDEX, (void (*) ()) NULL, false);	/* expensive */
	/* add the current label to the property list sub-string */
	str->props = proplist_add(str->props, (void *) string_label, STRING,
				  (void (*) ()) NULL);

	index[row] = ref_addtostart((List *) index[row], (void *) str, STRING);

	/* fill the index over any gaps in the edge contour string */
	if (laststr != NULL && abs(row - lastrow) != 1)
	{
	    int     i, r1 = lastrow, r2 = row;

	    ORDER(int, r1, r2);
	    for (i = r1 + 1; i < r2; ++i)
	    {
		if (abs(i - row) <= abs(i - lastrow))
		    index[i] = ref_addtostart((List *) index[i], (void *) str, STRING);
		else
		    index[i] = ref_addtostart((List *) index[i], (void *) laststr, STRING);
	    }
	}
	laststr = str;
	lastrow = row;
	if (end == string->end)
	    break;
	start = end->next;
    }
}

/* function used to sort epipolar sub-strings along the raster
 * 
 * the type of the string determines the direction, FORWARD or BACKWARD,
 * it runs along the raster */
static double first_xpos(Tstring * string)
{
    if (string->type == FORWARD)
	return (vec2_x(DD_EDGE_POS(string->start)));
    else
	return (vec2_x(DD_EDGE_POS(string->end)));
}

/* main function for stereo index building
 * 
 * takes a list of edge strings representing contours and constructs a
 * suitable stereo index for them
 * 
 * first finds a region that surrounds the edge locations this may have
 * little to do with the region of the edgerect the latter is
 * determined by storage requirements wrt original image the former may
 * subsequently have been subject to a projective transformation
 * 
 * then each edge string is considered in tern and added to the rows
 * 
 * of the stereo index (this also sets the gross string labels)
 * 
 * each row of the index is sorted in the x direction and spatially
 * indexed */
Rindex *strings_set_sindex(List * strings)
{
    List   *sptr;
    Rindex *sx;
    Rindex *rx_alloc();
    List  **index;
    Imregion *region;
    Imregion *strings_bounding_region();
    int     ly, uy;
    int     i;

    region = strings_bounding_region(strings);
    if (region == NULL)
    {
	error("sindex: nil region", warning);
	return (NULL);
    }
    ly = region->ly;
    uy = region->uy;
    sx = rx_alloc(region, SINDEX);
    index = (List **) sx->index;

    for (sptr = strings; sptr != NULL; sptr = sptr->next)
	es_add_to_index(index, (Tstring *) sptr->to);

    for (i = ly; i < uy; ++i)
	index[i] = sort_list(index[i], first_xpos, NULL);

    return (sx);
}

/* function for adding/replacing the stereo index of an edgerect
 * 
 * updates the SINDEX propety of the edgerect for future reference
 * 
 * function strings_set_sindex does the actual work */
void    er_set_sindex(Imrect * er)
/* edge rect ptr image */
{
    List   *strings;
    void    rx_free_links();
    Rindex *sx;

    if (er == NULL || er->vtype != ptr_v)
    {
	error("sindex: passed non edge rect", warning);
	return;
    }
    strings = (List *) prop_get(er->props, STRING);
    if (strings == NULL)
    {
	error("sindex: no strings available", warning);
	return;
    }
    sx = strings_set_sindex(strings);
    if (sx == NULL)
	return;

    er->props = proplist_addifnp(er->props, (void *) sx, SINDEX, rx_free_links, true);
}

/* apply function to each stereo index sub-string of given string
 * 
 * uses the SINDEX property of the edgel to get to the sub-string and from
 * their the next element and sub-string in the list. */
void    es_apply_to_sindex_strings(Tstring * es, void (*func) ( /* ??? */ ), void *data)
{
    Ddlist *dptr;
    Ddlist *end;

    if (es == NULL)
	return;

    end = es->end;
    for (dptr = es->start;; dptr = dptr->next)
    {
	Edgel  *e = (Edgel *) dptr->to;
	Tstring *sub;

	sub = (Tstring *) prop_get(e->props, SINDEX);
	if (sub != NULL)
	{
	    func(sub, STRING, data);
	    dptr = sub->end;
	}
	if (dptr == end)
	    break;
    }
}

/* apply to every entry of the stereo index
 * 
 * note that some entries could have multiple entries */
void    er_apply_through_sindex(Imrect * er, void (*func) ( /* ??? */ ), void *data)
{
    Rindex *sx;
    List   *lptr;
    int     i;

    if (er == NULL || (sx = (Rindex *) prop_get(er->props, SINDEX)) == NULL)
	return;

    for (i = sx->region->ly; i < sx->region->uy; ++i)
	for (lptr = (List *) (sx->index[i]); lptr != NULL; lptr = lptr->next)
	    func(lptr->to, lptr->type, data);
}

/* copy edge string to string of sub-strings */
Tstring *string_of_sindex_strings(Tstring * es)
{
    Ddlist *start;
    Ddlist *end;
    Ddlist *ptr;
    Ddlist *substrings = NULL;

    if (es == NULL)
	return (NULL);

    start = es->start;
    end = es->end;

    for (ptr = start;; ptr = ptr->next)
    {
	Edgel  *edge = (Edgel *) ptr->to;
	Tstring *sub;

	sub = (Tstring *) prop_get(edge->props, SINDEX);
	if (sub == NULL)
	    continue;
	substrings = dd_ref_addtostart(substrings, (void *) sub, STRING);
	ptr = sub->end;
	if (ptr == end)
	    break;
    }
    if (substrings == NULL)
	return (NULL);
    return (str_make(SINDEX, substrings, dd_get_end(substrings)));
}
