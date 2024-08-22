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

List   *ts_deserialise_gen(List * lg, void **data);
int     deserialise_item(List ** lgp, void **data);

List   *deserialise_parse(List * lg, void *data, Varptr dp, char **ss)
{
    char   *s = *ss;
    static Varptr d, nulld;
    int     repeats = 0, exiting = 0;

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
		    s = temp_s;
		    lg = deserialise_parse(lg, data, nulld, &s);
		}
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
		    case '.':
		    case ',':
		    case 'w':
			ALIGN_VARPTR(data, d, 4);
			word_swap(d.char_v);
			d.int_v++;
			break;
		    case 'p':
		    case 's':
			ALIGN_VARPTR(data, d, 4);
			word_swap(d.char_v);
			break;
		    case 'h':
		    case 'k':
			ALIGN_VARPTR(data, d, 2);
			short_swap(d.char_v);
			d.short_v++;
			break;
		    case 'e':
		    case 'g':
			ALIGN_VARPTR(data, d, 8);
			long_swap(d.char_v);
			d.double_v++;
			break;
		    case 't':
			ALIGN_VARPTR(data, d, SUBSTRUCT_ALIGNMENT);
			break;
		    }
		    switch (*(s - 1))
		    {
		    case 'p':
			if (*d.ptr_v)	/* was there data here */
			{
			    Varptr  td = d;	/* keep d pointer */

			    lg = ts_deserialise_gen(lg, d.ptr_v);	/* recurse */
			    d = td;
			}
			d.ptr_v++;
			break;
		    case 's':
			if (*d.ptr_v)	/* was there data here */
			    deserialise_item(&lg, d.ptr_v);
			d.ptr_v++;
			break;
		    case 't':
			deserialise_tagged_sub_item(&lg, d.int_v);
			break;
		    }
		}
		while (--repeats > 0);
		repeats = 0;
	    }
	    break;
	}
    }
    *ss = s;
    return lg;
}
int     deserialise_item(List ** lgp, void **data)
{
    int     rcode = 0;
    List   *lg = *lgp;

    if (!lg)			/* end of lg list (shouldn't happen) */
    {
	*data = NULL;
	rcode = -1;
    } else if (lg->type < 0)	/* duplicate pointer */
    {
	/* mprintf("Getting Repeat Item 0x%x %s\n",lg->to,
	 * tina_data_info_array[*(int*)lg->to - ts_base_id].name); */
	*data = lg->to;
	lg = lg->next;
	rcode = 0;
    } else if (lg->to)		/* normal case */
    {
	/* mprintf("Getting New Item 0x%x %s\n",lg->to,
	 * tina_data_info_array[*(int*)lg->to - ts_base_id].name); */
	*data = lg->to;
	lg = lg->next;
	rcode = 1;
    } else
    {
	/* null pointer */
	/* data = NULL; *//* otherwise give nothing and skip */
	lg = lg->next;
    }

    *lgp = lg;
    return rcode;
}

int     deserialise_tagged_item(List ** lgp, void **data)
{
    int     rcode = 0;
    List   *lg;
    char   *ss;

    if ((rcode = deserialise_item(lgp, data)) == 1)
    {
	Varptr  d;

	d.char_v = *data;

	lg = *lgp;
	word_swap((char *) d.int_v);	/* swap tag field of struct */
	/* mprintf("Deserialising a %s struct\n",
	 * tina_data_info_array[*(int*)*data - ts_base_id].name); */
	ss = tina_data_info_array[*d.int_v - ts_base_id].swap_string;
	d.int_v++;		/* skip over tag */
	lg = deserialise_parse(lg, *data, d, &ss);
	*lgp = lg;
    }
    return rcode;
}
int     deserialise_tagged_sub_item(List ** lgp, void *data)
{
    char   *ss;
    Varptr  d;

    d.char_v = data;

    word_swap((char *) d.int_v);/* swap tag field of struct */
    /* mprintf("Deserialising a %s sub-struct\n",
     * tina_data_info_array[*(int*)data - ts_base_id].name); */
    ss = tina_data_info_array[*(int *) data - ts_base_id].swap_string;
    d.int_v++;			/* skip over tag */
    *lgp = deserialise_parse(*lgp, data, d, &ss);

    return 1;
}

List   *ts_deserialise(List * lg, void **data)
{
    if (lg)
	deserialise_tagged_item(&lg, data);
    return lg;
}

List   *ts_deserialise_gen(List * lg, void **data)
{
    /* mprintf("ts_serialise_gen(0x%x,0x%x) \n",lg,data); */
    if (lg)
    {
	Ts_id   tag = *(int *) (lg->to);	/* use copy because real
						 * one */

	if (lg->type > 0)	/* if not duplicate pointer */
	    word_swap((char *) &tag);	/* will be swapped later     */
	lg = tina_data_info_array[tag - ts_base_id].deserialise(lg, data);
    }
    return lg;
}
