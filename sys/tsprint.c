#include <stdio.h>
#include <stdlib.h>
#include <tina/sys.h>
#include <stdarg.h>
#include <tina/sysfuncs.h>
void    ts_print_gen(void *data);
void    ts_print(void *data);
extern char *strchr(const char *s, int c);

#define SUBSTRUCT_ALIGNMENT 4
#define ALIGN_VARPTR(start,here,size) \
{ \
   int tab=(int)((here).char_v-(char*)(start))%(size);\
    (here).char_v+=tab?(size)-tab:0;\
   }


static char *typefromcode(char c)
{
    switch (c)
    {
	case 'b':
	return "byte";
    case 'c':
	return "char";
    case 'f':
	return "float";
    case 'l':
	return "long";
    case 'w':
    case 'i':
	return "int";
    case 'o':
	return "unsigned long";
    case 'p':
	return "POINTER *";
    case 'u':
	return "unsigned int";
    case 'h':
	return "short";
    case 'k':
	return "unsigned short";
    case 'g':
	return "double";
    case 'e':
	return "long double";
    case 's':
	return "char *";
    case '.':
	return "WOOPS";
    default:
	return NULL;
    }
}

static void print_parse(void *data, Varptr dp, char **ss)
{
    char   *s = *ss;
    int     repeats = 0, exiting = 0;
    static Varptr d, nulld;
    static int arrayp = 0;
    static char *last_name = NULL;
	void *memcpy();

    nulld.char_v = NULL;
    if (dp.char_v)
	d = dp;			/* if dp is null use static version d */
    /* else use new value */
    while (*s && !exiting)
    {
	if (!arrayp)
	{
	    char   *t = typefromcode(*s);

	    if (t)
		mprintf("%s ", t);
	}
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
	    if (last_name)
	    {
		mprintf("%s <%s>[ ", typefromcode(*s), last_name);
		last_name = NULL;
	    } else
		mprintf("%s[ ", typefromcode(*s));
	    arrayp = 1;
	    {
		char   *temp_s = s;

		while (repeats-- > 0)
		{
		    temp_s = s;
		    print_parse(data, nulld, &temp_s);
		}
		arrayp = 0;
		mprintf("];");
		s = temp_s;	/* the rest of the swap string */
		repeats = 0;
	    }
	    break;
	case '(':		/* start of a repetition */
	    {
		char   *temp_s = s;

		while (repeats-- > 0)
		{
		    temp_s = s;
		    print_parse(data, nulld, &temp_s);
		}
		s = temp_s;	/* the rest of the swap string */
		repeats = 0;
	    }
	    break;
	case ']':
	case ')':
	    exiting = 1;
	    break;
	case '/':
	    {
		static char name[256];
		char   *end = strchr(s, '/');

		memcpy(name, s, end - s);
		name[end - s] = 0;
		last_name = name;
		s = end + 1;
	    }
	    break;
	default:
	    {
		if (last_name && *(s - 1) != 't')
		{
		    mprintf("<%s>", last_name);
		    last_name = NULL;
		}
		do
		{
		    switch (*(s - 1))
		    {
		    case 'f':
		    case 'l':
		    case 'i':
		    case 'o':
		    case 'u':
		    case 'p':
		    case 's':
		    case ',':
		    case '.':
		    case 'w':
			ALIGN_VARPTR(data, d, 4);
			break;
		    case 'h':
		    case 'k':
			ALIGN_VARPTR(data, d, 2);
			break;
		    case 'e':
		    case 'g':
			ALIGN_VARPTR(data, d, 8);
			break;
		    case 't':
			ALIGN_VARPTR(data, d, SUBSTRUCT_ALIGNMENT);
			break;
		    }
		    switch (*(s - 1))
		    {
		    case 'b':
			mprintf("0x%x,", *d.char_v++);
			break;
		    case 'c':
			mprintf("%c", *d.uchar_v++);
			break;
		    case 'f':
			mprintf("%g,", *d.float_v++);
			break;
		    case 'l':
			mprintf("%li,", *d.int_v++);
			break;
		    case 'w':
			mprintf("0x%x,", *d.int_v++);
			break;
		    case 'i':
			mprintf("%d,", *d.int_v++);
			break;
		    case 'o':
			mprintf("%lu,", *d.uint_v++);
			break;
		    case '.':
			mprintf("Invalid data code;");
		    case ',':
			d.uint_v++;
			break;
		    case 'u':
			mprintf("%u,", *d.uint_v++);
			break;
		    case 'h':
			mprintf("%hi,", *d.short_v++);
			break;
		    case 'k':
			mprintf("%hu,", *d.ushort_v++);
			break;
		    case 'e':
		    case 'g':
			mprintf("%g,", *d.double_v++);
			break;
			/* case 'e': mprintf("%le, ",*d.l_double_v++);
			 * NO LONG */
			/* DOUBLES */
			break;
		    case 'p':	/* pointer types */
			if (*d.ptr_v)	/* if not a null pointer ,
					 * print_by_tag */
			{
			    Varptr  td = d;	/* keep d pointer */

			    mprintf("0x%x", *d.ptr_v);
			    ts_print_gen(*d.ptr_v);
			    d = td;	/* recover d pointer */
			} else
			    mprintf("NULL,");
			d.ptr_v++;
			break;
		    case 's':	/* string */
			if (*d.ptr_v)	/* if not a null pointer print
					 * string */
			    mprintf("\"%s\",", (char *) *d.ptr_v);
			else
			    mprintf("\"\",");
			d.ptr_v++;
			break;
		    case 't':	/* tagged struct */
			{
			    char   *s = tina_data_info_array[*d.int_v - ts_base_id].swap_string;
			    char   *name = tina_data_info_array[*d.int_v - ts_base_id].name;

			    if (last_name)
				mprintf("struct %s <%s>{", name, last_name);
			    else
				mprintf("struct %s {", name);
			    last_name = NULL;
			    d.int_v++;	/* skip tag */
			    print_parse((void *) (d.int_v - 1), nulld, &s);	/* carry d pointer on */
			    mprintf("}%s;", name);
			}
			break;

		    }
		} while (--repeats > 0);
		repeats = 0;
	    }
	    break;
	}
    }
    *ss = s;
}

/* Take a data pointer. Identify the structures type, get it's swap
 * string from the global table. Parse the swap string, printing
 * various data types. Types 'p'and 't'  recursively descend the data
 * tree. We must also align to short and long word boundaries relative
 * to the start of the structure */
void    ts_print(void *data)
{
    char   *s = tina_data_info_array[*(int *) data - ts_base_id].swap_string;
    char   *name = tina_data_info_array[*(int *) data - ts_base_id].name;
    Varptr  d;

    d.int_v = data;
    d.int_v++;			/* skip over tag */
    mprintf("struct %s {", name);
    print_parse(data, d, &s);
    mprintf("} %s;", name);
}

void    ts_print_gen(void *data)
{
    static int calls = 0;	/* count recursive levels */

    if (data)
    {
	calls++;
	if (repeatp_checker(data))	/* new pointer? */
	    tina_data_info_array[*(int *) data - ts_base_id].print(data);
	else
	    mprintf("RPT struct %s;",
	       tina_data_info_array[*(int *) data - ts_base_id].name);
	calls--;
	if (!calls)
	    repeatp_checker(NULL);	/* reset check list */
    } else
	mprintf("NULL,");
}
