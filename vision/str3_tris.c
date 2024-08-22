/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Bool    dist_to_pos3(Vec3 * ptr, int type, Vec3 * pp, double *dist)
{
    if (ptr == NULL || type != VEC3)
	return (false);

    *dist = vec3_mod(vec3_diff(*pp, *ptr));
    return (true);
}

Vec3   *tri3_make(Vec3 p1, Vec3 p2, Vec3 p3)
{
    Vec3   *tri;

    tri = ts_nvector_alloc(0, 3, Vec3);	/* array of VEC3 */
    tri[0] = p1;
    tri[1] = p2;
    tri[2] = p3;
    return (tri);
}

List   *str3_triangulate(Tstring * s1, Tstring * s2, int sample)
{
    Ddlist *ptr1;
    Ddlist *ptr2;
    Ddlist *end;
    Vec3    p1 = {Vec3_id};
    Vec3    p2 = {Vec3_id};
    Vec3    p1_last = {Vec3_id};
    Vec3    p2_last = {Vec3_id};
    List   *tris = NULL;
    int     i;

    if (s1 == NULL || s2 == NULL || s1->start == s1->end)
	return (NULL);

    ptr1 = s1->start;
    end = s1->end;
    p1_last = *(Vec3 *) (ptr1->to);
    ptr2 = str_get_min(s2, dist_to_pos3, (void *) &p1_last);
    p2_last = *(Vec3 *) (ptr2->to);
    ptr1 = ptr1->next;

    for (i = 1;; i++, ptr1 = ptr1->next)
    {
	if (i % sample == 0 || ptr1 == end)
	{
	    if (ptr1 == end && s1->type == LOOP)
		p1 = *(Vec3 *) (s1->start->to);
	    else
		p1 = *(Vec3 *) (ptr1->to);
	    ptr2 = str_get_min(s2, dist_to_pos3, (void *) &p1);
	    p2 = *(Vec3 *) (ptr2->to);

	    tris = ref_addtostart(tris, (void *) tri3_make(p1_last, p2_last, p2), TRIANGLE3);
	    tris = ref_addtostart(tris, (void *) tri3_make(p1_last, p2, p1), TRIANGLE3);
	    p1_last = p1;
	    p2_last = p2;
	}
	if (ptr1 == end)
	    break;
    }
    return (tris);
}

static Vec3 *make_vec3_from_vec2(Vec2 * v2, int *type, double *z)
{
    Vec3   *v3;

    v3 = vec3_make(vec3_of_vec2(*v2));
    vec3_z(*v3) = (float) *z;
    *type = VEC3;
    return (v3);
}

List   *str2_triangulate3(Tstring * s1, double z1, Tstring * s2, double z2, int sample)
{
    Tstring *s1_3, *s2_3;
    List   *tris;

    s1_3 = reclist_string_update(s1, (void *(*) ()) make_vec3_from_vec2,
				 VEC2, (void *) &z1);
    s2_3 = reclist_string_update(s2, (void *(*) ()) make_vec3_from_vec2,
				 VEC2, (void *) &z2);
    tris = str3_triangulate(s1_3, s2_3, sample);
    str_rm(s1_3, rfree);
    str_rm(s2_3, rfree);
    return (tris);
}
