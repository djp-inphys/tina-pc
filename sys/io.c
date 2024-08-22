#include <stdio.h>
#include <stdlib.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>

#define TS_MAGIC            0x80008000
#define TS_MAGIC_NEED_SWAP  0x00800080

static int magic=TS_MAGIC;

void    fwrite_ts(FILE * fp, List * lg, int c)
{
    List   *l;
    int rval;

    fwrite(&magic,sizeof(int),1,fp);		 /* put magic no in head of data */
    fwrite(&c, sizeof(int), 1, fp);
    for (l = lg; l; l = l->next)
	rval=fwrite(&(l->type), sizeof(int), 1, fp);
    for (l = lg; l; l = l->next)
	if (l->type > 0)
	    rval=fwrite(l->to, l->type, 1, fp);
}
List   *fread_ts(FILE * fp, int *c)
{
    List   *l = NULL;
    int    *s, count,magic,rval;
    void  **d;

    rval=fread(&magic, sizeof(int),1,fp);		 /* get magic no out of data */
    set_swapping_ts((magic==TS_MAGIC_NEED_SWAP)); /* determine if swapping data */
    rval=fread(c, sizeof(int), 1, fp);
    word_swap((char*)c);
    s = (int *) ralloc(sizeof(int) * (*c));
    d = (void **) ralloc(sizeof(void *) * (*c));
    for (count = 0; count < *c; count++)
    {
	rval=fread(s+count, sizeof(int), 1, fp);
	word_swap((char*)(s+count));
	d[count] = s[count] > 0 ? (void *) ralloc(s[count]) : NULL;
    }
    for (count = *c - 1; count >= 0; count--)
	if (!d[count])
	    d[count] = d[count - s[count]];
    for (count = 0; count < *c; count++)
    {
	l = ref_addtostart(l, d[count], s[count]);
	if (s[count] > 0)
	{
	    rval=fread(l->to, l->type, 1, fp);
	    if(rval!=1) fprintf(stderr,"fread_ts: Error reading data item %i\n",count);
	} 
    }
    rfree(s);
    rfree(d);
    return l;
}


void    buffwrite_ts(char *mem, List * lg, int c)
{
    List   *l;
    Varptr  m;
	void *memcpy();

    m.char_v = mem;		
    *(m.int_v++) = magic;			 /* put magic no into data */
    *(m.int_v++) = c;
    for (l = lg; l; l = l->next)
	*(m.int_v++) = l->type;
    for (l = lg; l; l = l->next)
	if (l->type > 0)
	    memcpy(m.char_v, l->to, l->type), m.char_v += l->type;
}
List   *buffread_ts(char *mem, int *c)
{
    List   *l = NULL;
    Varptr  m;
    int    *s, count,magic;
    void  **d;

    m.char_v = mem;

    magic=*(m.int_v++);				 /* get magic no out */
    set_swapping_ts((magic==TS_MAGIC_NEED_SWAP)); /* determine if swapping */
    word_swap(m.char_v);
    *c = *m.int_v++;
    s = (int *) ralloc(sizeof(int) * (*c));
    d = (void **) ralloc(sizeof(void *) * (*c));
    for (count = 0; count < *c; count++)	 /* ralloc all the data */
						 /* blocks */
    {
	word_swap(m.char_v);
	s[count] = *m.int_v++;
	d[count] = s[count] > 0 ? ralloc(s[count]) : NULL;
    }
    for (count = *c - 1; count >= 0; count--)	/* setup replicated */
						/* pointers */
	if (!d[count])
	    d[count] = d[count - s[count]];
    for (count = 0; count < *c; count++)	/* copy data into blocks */
    {
	l = ref_addtostart(l, d[count], s[count]);
	if (s[count] > 0)
	    memcpy(l->to, m.char_v, l->type), m.char_v += l->type;
    }
    rfree(s);
    rfree(d);
    return l;
}
