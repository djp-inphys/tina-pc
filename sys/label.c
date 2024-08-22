/**@(#)
**/

int     new_label(void)
{
    static int label = 0;

    return (label++);
}
