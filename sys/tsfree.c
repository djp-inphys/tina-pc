#include <stdio.h>
#include <stdlib.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
void    ts_free_gen(void *data);
void    ts_free_sub_item(void *data);
static int repeat_pointer_checking=1;

void repeatp_checker_off(void)
{
  repeat_pointer_checking=0;
}
void repeatp_checker_on(void)
{
  repeat_pointer_checking=1;
}
int repeatp_checking_get(void)
{
  return repeat_pointer_checking;
}
void repeatp_checking_set(int f)
{
  repeat_pointer_checking=f;
}
#define REP_ARRAY 100
#define SUBSTRUCT_ALIGNMENT 4
#define ALIGN_VARPTR(start,here,size) \
{ \
   int tab=(int)((here).char_v-(char*)(start))%(size);\
     (here).char_v+=tab?(size)-tab:0;\
     }

/* Is this a new pointer? If so don't tell anybody else */
int     repeatp_checker(void *d)/* return 1 if new pointer */
{
  static void **pstack = NULL, **tp;
  static int c = 0, n = REP_ARRAY;
  int     i;
  
  if(!repeat_pointer_checking) return 1; /* switched off so say is new */
  if (pstack == NULL)
    pstack = (void **) malloc(sizeof(void *) * n);
  
  if (d == NULL)		/* reset stored array */
  {
    /* mprintf("Reseting ptr list\n"); */
    pstack = (void **) realloc(pstack, sizeof(void *) * n);
    c = 0;
    n = REP_ARRAY;
    return 0;
  }
  for (tp = pstack, i = 0; i < c; i++)
    if (*tp++ == d)
      break;
  if (i == c)			/* not already done */
  {
    if (c == n)
    {
      n+=REP_ARRAY;
      pstack = (void **) realloc(pstack, sizeof(void *) * n);
      if(!pstack)
      {
	printf("REALLOC Failed in repeatp_checker\n");
	exit(1);
      }
    }
    pstack[c++] = d;
    return 1;			/* indicate new pointer */
  } else
    return 0;			/* indicate repeat pointer */
}

static void free_parse(void *data, Varptr dp, char **ss)
{
    char   *s = *ss;
    int     repeats = 0, exiting = 0;
    static Varptr d, nulld;
    static int arrayp = 0;

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
	    arrayp = 1;
	    {
		char   *temp_s = s;

		while (repeats-- > 0)
		{
		    temp_s = s;
		    free_parse(data, nulld, &temp_s);
		}
		arrayp = 0;
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
		    free_parse(data, nulld, &temp_s);
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
		char   *strchr(const char *s, int c);

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
		    case 'w':
		    case '.':
		    case ',':
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
		    case 'p':	/* pointer types */
			if (*d.ptr_v)
			{
			    Varptr  td = d;	/* keep d pointer */

			    ts_free_gen((int *) (*d.ptr_v));
			    d = td;	/* recover d pointer */
			}
			d.ptr_v++;	/* SMC BUG FIX */
			break;
		    case 's':	/* string */
			if (*d.ptr_v && repeatp_checker(*d.ptr_v))
			    rfree(*d.ptr_v);
			d.ptr_v++;
			break;
		    case 't':	/* tagged struct */
			ts_free_sub_item(d.int_v);
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

void    ts_free_sub_item(void *data)
{
    char   *s = tina_data_info_array[*(int *) data - ts_base_id].swap_string;
    Varptr  d;

    d.ptr_v = data;
    /* mprintf("Freeing a %s sub Struct with %s\n",
     * tina_data_info_array[*d.int_v - ts_base_id].name, s); */
    d.int_v++;			/* skip over tag */
    free_parse(data, d, &s);
}
void    ts_free(void *data)
{
    char   *s;
    Varptr  d;

    if (data)
    {
	s = tina_data_info_array[*(int *) data - ts_base_id].swap_string;
	d.ptr_v = data;
	/* mprintf("Freeing a %s Struct with %s\n",
	 * tina_data_info_array[*d.int_v - ts_base_id].name, s); */
	d.int_v++;		/* skip over tag */
	free_parse(data, d, &s);
	rfree(data);
    }
}

void    ts_free_gen(void *data)
{
    static int calls = 0;
    int rcheck=repeat_pointer_checking;
    repeat_pointer_checking=1;

    if (data)
    {
	if (repeatp_checker(data))
	{
	    calls++;
	    tina_data_info_array[*(int *) data - ts_base_id].free(data);
	    calls--;
	}
	if (calls == 0)
	    repeatp_checker(NULL);	/* reset stored p's */
    }
    repeat_pointer_checking=rcheck;
}
