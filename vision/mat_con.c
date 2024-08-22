/**@(#)
**/
/* matches consistent with match list clique */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Bool    smm_con_with_mlist(Match * match, List * list)
{
    List   *ptr;

    for (ptr = list; ptr != NULL; ptr = ptr->next)
	if (smm_consistent_matches(match, (Match *) ptr->to) == false)
	    return (false);

    return (true);
}

List   *smm_mats_con_with_mlist(List * model, List * scene, List * matches)
{
    List   *new_matches = NULL;
    List   *m;
    List   *s;
    List   *ptr;
    Match   test = {Match_id};

    test.props = NULL;

    model = list_copy(model, (void *(*) ()) NULL, NULL);
    scene = list_copy(scene, (void *(*) ()) NULL, NULL);

    for (ptr = matches; ptr != NULL; ptr = ptr->next)
    {
	Match  *mat = (Match *) ptr->to;

	model = list_rm_ref(model, mat->to1, (void (*) ()) NULL);
	scene = list_rm_ref(scene, mat->to2, (void (*) ()) NULL);
    }

    for (m = model; m != NULL; m = m->next)
    {
	int     type;

	test.type = type = m->type;
	test.to1 = m->to;
	for (s = scene; s != NULL; s = s->next)
	{
	    if (s->type != type || !smm_reasonable_match(m->to, s->to, type))
		continue;

	    test.to2 = s->to;
	    if (smm_con_with_mlist(&test, matches) == false)
		continue;

	    if (smm_con_with_mlist(&test, matches) == false)
		continue;

	    test.weight = (float)smm_match_strength(&test);
	    test.label = new_label();
	    new_matches = ref_addtostart((List *) new_matches, (void *) match_copy(&test), MATCH);
	}
    }
    list_rm_links(model);
    list_rm_links(scene);

    return (list_append(matches, new_matches));
}
