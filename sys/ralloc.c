/**@(#)Memory allocation (Tina's malloc).
 * @(#)Intelligent wrappers to malloc and free
 * (revised version 24 10 91)
 *
 * 2 additional features
 *
 * 1. test for exhausted memory (giving the option to free some) hence
 * user need not check results of allocation directly
 * note: this option is a pain - commented out.
 *
 * 2. allows efficient (time but perhaps not space) block allocation user
 * provides blocking factor multi block support synchronised free
 *
 * Why no equivalent of realloc?
 * Because we don't know size of original memory, so can't copy data from it.
 */

#include <stdio.h>
#include <string.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>

/* blocking types */
#define NOT_BLOCKED 0
#define BLOCKED_ALLOC 1

#ifdef _ICC
#include <process.h>
#define sleep(n) ProcWait((n)*1000000/(ProcGetPriority()*64))
#else
extern unsigned sleep(unsigned seconds);
#endif

#ifdef IBM
extern void free();
#endif

/* basic repated malloc call */
static void *rep_alloc(unsigned int size)
{
    Align  *cptr = NULL;
    char    mess[256];

    cptr = (Align *) malloc(size);
    /**
    while (cptr == NULL)
    {
	(void) sprintf(mess, " %d out of store: try and free some", size);
	message(mess);
	sleep(5);
	cptr = (Align *) malloc(size);
	if (cptr != NULL)
	    message("store ok");
    }
    **/
    if(cptr == NULL)
    {
	(void) sprintf(mess, "allocating 0 not %d bytes", size);
	message(mess);
    }
    return cptr;
}

static Blk_stat *blk_stat_make(unsigned int label, unsigned int size)
{
    Blk_stat *blk = ts_ralloc(Blk_stat);

    blk->label = label;
    blk->block = (Align *) rep_alloc(size);
    blk->block_list = link_alloc((void *) blk->block, BLOCKED_ALLOC);
    blk->bsize = size;
    blk->n = size;
    return (blk);
}

static void blk_stat_free(Blk_stat * blk_stat)
{
    if (blk_stat == NULL)
	return;

    list_rm(blk_stat->block_list, (void (*) ()) free);
    rfree((void *) blk_stat);
}

/* state variables */
static List *blk_stat_list = NULL;
static Blk_stat *current = NULL;
static unsigned int label = 0;
static Bool blocked_alloc = false;

/* start new blocked allocation list set blocked_alloc true return
 * access key for allocation list */
unsigned int ralloc_new_blocked(unsigned int s)
{
    blocked_alloc = false;
    ++label;
    current = blk_stat_make(label, s);
    blk_stat_list = ref_addtostart(blk_stat_list, (void *) current, (int) label);
    blocked_alloc = true;
    return (label);
}

/* (re)start blocked allocation on list keyed by label */
unsigned int ralloc_start_blocked(unsigned int label)
{
    List   *ptr = link_get_by_type((List *) blk_stat_list, (int) label);
    unsigned int old_label;

    if (ptr == NULL)
    {				/* label does not key an active list */
	blocked_alloc = false;
	return 0;
    }
    old_label = (current == NULL) ? 0 : current->label;

    current = (Blk_stat *) ptr->to;
    blocked_alloc = true;

    return (old_label);
}

/* stop performing blocked allocation */
unsigned int ralloc_end_blocked(void)
{
    unsigned int old_label;

    blocked_alloc = false;
    old_label = (current == NULL) ? 0 : current->label;
    current = NULL;
    return (old_label);
}

/* free up blocked allocation list and delete list entry */
void    ralloc_free_blocked(unsigned int label)
{
    List   *ptr = link_get_by_type(blk_stat_list, (int) label);

    blocked_alloc = false;
    blk_stat_list = list_rm_el(blk_stat_list, ptr, blk_stat_free);
}

/* perform allocation into current blocked allocation list */
static void *blk_alloc(unsigned int size)
{
    Align  *ptr;
    unsigned int ibks;

    if (size > current->bsize)
    {				/* generate special block */
	Align  *block = (Align *) rep_alloc(size);

	blocked_alloc = false;	/* to stop recursion */
	current->block_list = ref_addtostart(current->block_list, (void *) block, BLOCKED_ALLOC);
	blocked_alloc = true;
	return block;
    }
    if (size > current->n)
    {				/* need a new block */
	current->block = (Align *) rep_alloc(current->bsize);
	blocked_alloc = false;	/* to stop recursion */
	current->block_list = ref_addtostart(current->block_list, (void *) current->block, BLOCKED_ALLOC);
	blocked_alloc = true;
	current->n = current->bsize;
    }
    ibks = size / sizeof(Align);
    if (size % sizeof(Align))
	ibks++;
    ptr = current->block;
    current->block += ibks;
    current->n -= ibks * sizeof(Align);

    return ptr;
}

/* malloc wrapper and initialisation */
void   *ralloc(size_t size)
{
    Align  *ptr;

    size += sizeof(Align);
    if (blocked_alloc == true)
    {
	ptr = (Align *) blk_alloc(size);
	(void) memset((char *) ptr, 0, (int) size);
	*(int *) ptr = BLOCKED_ALLOC;
    } else
    {
	ptr = (Align *) rep_alloc(size);
	(void) memset((char *) ptr, 0, (int) size);
	*(int *) ptr = NOT_BLOCKED;
    }
    return ++ptr;
}

/* free wrapper */
void    rfree(void *ptr)
{
    Align  *iptr;

    if (ptr == NULL)
	return;
    iptr = (Align *) ptr;
    iptr--;
    if (*((int *) iptr) == NOT_BLOCKED)
	free((char *) iptr);
}
