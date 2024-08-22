#include <stdio.h>
#include <stdlib.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <string.h>

#define SUBSTRUCT_ALIGNMENT 4
#define ALIGN_VARPTR(start,here,size) \
{ \
   int tab=(int)((here).char_v-(char*)(start))%(size);\
   (here).char_v+=tab?(size)-tab:0;\
   }

static List *serialise_parse(List * lg, void *data, Varptr dp, char **ss);

static List *serialise_parse(List * lg, void *data, Varptr dp, char **ss)
{
    char   *s = *ss;
    int     repeats = 0, exiting = 0;
    static Varptr d, nulld;

    nulld.char_v = NULL;
    if (dp.char_v)
	d = dp;			/* if dp is null use static version d */
    /* else use new value */

    while (*s && !exiting)
    {
	switch (*s++)
	{
	case '0':
	    repeats *= 10;
	    break;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	    repeats *= 10;
	    repeats += *(s - 1) - 48;
	    break;
	case '[':
	case '(':		/* start of a repetition */
	    {
		char   *temp_s = s;

		while (repeats-- > 0)
		{
		    temp_s = s;
		    lg = serialise_parse(lg, data, nulld, &temp_s);
		}
		s = temp_s;	/* the rest of the swap string */
		repeats = 0;
	    }
	    break;
	case ')':
	case ']':
	    exiting = 1;
	    break;
	case '/':
	    {
		char   *end = strchr(s, '/');

		s = end + 1;
	    }
	    break;
	default:
	    {
		do
		{
		    switch (*(s - 1))
		    {
		    case 'b':
		    case 'c':
			d.char_v++;
			break;
		    case 'f':
		    case 'l':
		    case 'i':
		    case 'o':
		    case 'u':
		    case ',':
		    case '.':
		    case 'w':
			ALIGN_VARPTR(data, d, 4);
			d.int_v++;
			break;
		    case 'p':
		    case 's':
			ALIGN_VARPTR(data, d, 4);
			break;
		    case 'h':
		    case 'k':
			ALIGN_VARPTR(data, d, 2);
			d.short_v++;
			break;
		    case 'g':
		    case 'e':
			ALIGN_VARPTR(data, d, 8);
			d.double_v++;
			break;
		    case 't':
			ALIGN_VARPTR(data, d, SUBSTRUCT_ALIGNMENT);
			break;
		    }
		    switch (*(s - 1))
		    {
		    case 'p':	/* pointer types - recurse (later) */
			if (*d.ptr_v)
			{
			    Varptr  td = d;	/* keep d pointer */

			    lg = ts_serialise_gen(lg, *d.ptr_v);
			    d = td;
			}
			d.ptr_v++;
			break;
		    case 's':	/* string */
			if (*d.ptr_v)
			    serialise_item(&lg, *d.ptr_v, strlen(*d.ptr_v));
			d.ptr_v++;
			break;
		    case 't':	/* tagged struct */
			serialise_tagged_sub_item(&lg, d.int_v);
			break;
		    }
		} while (--repeats > 0);
		repeats = 0;
	    }
	    break;
	}
    }


    *ss = s;
    return lg;
}

/********* GLOBAL Variable count - maintains current item count***********/
static int count = 0;

/********* GLOBAL Variable count ***********/

int     ts_serialise_end(void)
{
    int     c = count;

    count = 0;
    return c;
}

int     serialise_item(List ** lgp, void *d, size_t s)
{
    List   *l=NULL, *lg = *lgp;
    int     c, rcode = 0;

    if (s == 0)
    {
	return rcode;
    } else
    {
	if(repeatp_checking_get())
	  for (c = -1, l = lg; l; c--, l = l->next)	/* have we already had
							 * this pointer? */
	    if (l->to == d)
	      break;
	/* else l defaults to new pointer */
	if (l)			/* if we have */
	{
	    /* mprintf("Repeat Item 0x%x %s\n",l->to,
	     * tina_data_info_array[*(int*)l->to - ts_base_id].name); */
	    lg = ref_addtostart(lg, l->to, c);	/* store an offset to
						 * the prev ref */
	    rcode = 0;		/* return code to say don't process
				 * this item further */
	} else
	{
	    /* mprintf("New Item 0x%x %s\n",d,
	     * tina_data_info_array[*(int*)d - ts_base_id].name); */
	    lg = ref_addtostart(lg, d, s);	/* store the new one and
						 * the size */
	    rcode = 1;		/* ok to process this items contents */
	}
	count++;
    }
    *lgp = lg;
    return rcode;
}

int     serialise_tagged_item(List ** lgp, void *data, size_t s)
{
    int     rcode;

    if ((rcode = serialise_item(lgp, data, s)) == 1)
    {
	char   *ss = tina_data_info_array[*(int *) data - ts_base_id].swap_string;
	Varptr  d;

	d.char_v = data;

	d.int_v++;		/* skip over tag */
	*lgp = serialise_parse(*lgp, data, d, &ss);	/* serialise contents */
    }
    return rcode;
}
int     serialise_tagged_sub_item(List ** lgp, void *data)
{
    char   *ss = tina_data_info_array[*(int *) data - ts_base_id].swap_string;
    Varptr  d;

    d.char_v = data;

    d.int_v++;			/* skip over tag */
    *lgp = serialise_parse(*lgp, data, d, &ss);	/* serialise contents */
    return 1;
}

List   *ts_serialise(List * lg, void *data)
{
    size_t  s = tina_data_info_array[*(int *) data - ts_base_id].size;

    /* mprintf("Serialising a %s StructP <0x%x> with %s\n",
     * tina_data_info_array[*(int*)data - ts_base_id].name, data,
     * tina_data_info_array[*(int*)data - ts_base_id].swap_string); */
    serialise_tagged_item(&lg, data, s);
    return lg;
}

List   *ts_serialise_gen(List * lg, void *d)
{
    /* mprintf("ts_serialise_gen(0x%x,0x%x) count %d \n",lg,d,count); */
    if (d)
	lg = tina_data_info_array[*(int *) d - ts_base_id].serialise(lg, d);
    return lg;
}
