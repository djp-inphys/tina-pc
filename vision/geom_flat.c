/**@(#)
**/
#include <tina/sys.h>
#include <tina/sysfuncs.h>

List   *geom_list_make_flat(List * list)
{
    List   *flat;

    flat = reclist_list_flat(list, (void *(*) ()) NULL, (int) NULL, NULL);
    (void) reclist_list_free(list, (void (*) ()) NULL, (int) NULL, NULL);
    return (flat);
}

List   *geom_string_make_flat(Tstring * string)
{
    List   *flat;

    flat = reclist_string_flat(string, (void *(*) ()) NULL, (int) NULL, NULL);
    (void) reclist_string_free(string, (void (*) ()) NULL, (int) NULL, NULL);
    return (flat);
}
