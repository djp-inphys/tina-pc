/*
 *
 * ivec.c
 *
 * Routines for dynamically allocated vectors of ints.
 *
 */
#include <stdarg.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

/*
Return an n-vector of ints.
*/
Ivec *ivec_make(int n)
{
    Ivec *v = talloc(Ivec);
    v->n = n;
    v->el = tvector_alloc(0, n, int);
    return(v);
}

/*
Free a vector of ints.
*/
void ivec_free(Ivec *v)
{
    if(v == NULL)
	return;
    tvector_free(v->el, 0, int);
    rfree(v);
}

/*
Copy of a vector of ints.
*/
void ivec_copy(Ivec *v, Ivec *w)
{
    if(v == NULL || w == NULL)
	return;
    tvector_copy_inplace(v->el, w->el, 0, v->n, int);
}

/*
Return a copy of a vector of ints.
*/
Ivec *ivec_make_copy(Ivec *v)
{
    Ivec *newv = ivec_make(v->n);
    ivec_copy(newv, v);
    return(newv);
}
 
/*
Allocate and fill a vector of ints.
*/
Ivec *ivec(int n, ...)
{
    va_list ap;
    int     i;
    Ivec *v = ivec_make(n);

    va_start(ap, n);
    for (i = 0; i < n; i++)
	v->el[i] = (int) va_arg(ap, int);
    va_end(ap);
    return(v);
}

Ivec *ivec_range(int l, int u)
{
    Ivec *v = ivec_make(u-l);
    int i;
    for(i = l; i < u; i++)
	v->el[i-l] = i;
    return(v);
}

/*
Set zero vector.
*/
void ivec_zero(Ivec *v)
{
    int i;
    if(v == NULL)
	return;
    for(i = 0; i < v->n; i++)
	v->el[i] = 0;
}

/*
Set uniform random vector.
*/
void ivec_rand_unif(Ivec *v, int p, int q)
{
    int i;
    if(v == NULL)
	return;
    for(i = 0; i < v->n; i++)
	v->el[i] = (int)floor(rand_unif(p, q)); /* NAT 3/5/95 */
}

/*
Set Gaussian random vector.
*/
void ivec_rand_normal(Ivec *v, int m, int s)
{
    int i;
    if(v == NULL)
	return;
    for(i = 0; i < v->n; i++)
	v->el[i] = (int)floor(rand_normal(m, s)); /* NAT 3/5/95 */
}

/*
Return dot (scalar) product of two vectors.
*/
int ivec_dot(Ivec *v, Ivec *w)
{
    int i;
    int sum;
    if(v == NULL || w == NULL)
	return(0);
    for(sum = 0, i = 0; i < v->n; i++)
	sum += v->el[i]*w->el[i];
    return(sum);
}

/*
Form vector sum of v and w in vector v.
*/
void ivec_sum(Ivec *v, Ivec *w)
{
    int i;
    if(v == NULL || w == NULL)
	return;
    for(i = 0; i < v->n; i++)
	v->el[i] += w->el[i];
}

/*
Form vector difference of v and w in vector v.
*/
void ivec_diff(Ivec *v, Ivec *w)
{
    int i;
    if(v == NULL || w == NULL)
	return;
    for(i = 0; i < v->n; i++)
	v->el[i] -= w->el[i];
}

/*
Form product of scalar k and vector v in vector v.
*/
void ivec_times(int k, Ivec *v)
{
    int i;
    if(v == NULL)
	return;
    for(i = 0; i < v->n; i++)
	v->el[i] *= k;
}

/*
Negate components of vector v.
*/
void ivec_minus(Ivec *v)
{
    int i;
    if(v == NULL)
	return;
    for(i = 0; i < v->n; i++)
	v->el[i] = -v->el[i];
}

/*
Increment components of v by scalar k times those of vector w.
*/
void ivec_accum(Ivec *v, int k, Ivec *w)
{
    int i;
    if(v == NULL || w == NULL)
	return;
    for(i = 0; i < v->n; i++)
	v->el[i] += k*w->el[i];
}

/*
Return squared modulus (length) of vector v.
*/
int ivec_sqrmod(Ivec *v)
{
    int i;
    int sum = 0;
    if(v == NULL)
	return(0);
    for(i = 0; i < v->n; i++)
	sum += v->el[i]*v->el[i];
    return(sum);
}

/*
Return modulus (length) of vector v.
*/
int ivec_mod(Ivec *v)
{
    int i;
    int sum = 0;
    if(v == NULL)
	return(0);
    for(i = 0; i < v->n; i++)
	sum += abs(v->el[i]);
    return((int)sqrt(sum));
}

/*
Return L1 modulus (max element) of vector v.
*/
int ivec_mod1(Ivec *v)
{
    int i;
    int xmax = 0;
    if(v == NULL)
	return(0);
    for(i = 0; i < v->n; i++)
	xmax = MAX(xmax, abs(v->el[i]));
    return(xmax);
}

/*
Return squared distance between points (vectors) v and w.
*/
int ivec_sqrdist(Ivec *v, Ivec *w)
{
    int i;
    int sum = 0;
    if(v == NULL || w == NULL)
	return(0);
    for(i = 0; i < v->n; i++)
    {
	int dx = w->el[i]-v->el[i];
	sum += dx*dx;
    }
    return(sum);
}

/*
Return distance between points (vectors) v and w.
*/
int ivec_dist(Ivec *v, Ivec *w)
{
    int i;
    int sum = 0;
    if(v == NULL || w == NULL)
	return(0);
    for(i = 0; i < v->n; i++)
    {
	int dx = w->el[i]-v->el[i];
	sum += abs(dx);
    }
    return((int)sqrt(sum));
}

void ivec_print(FILE *fp, char *fmt, Ivec *v)
{
    int i;
    if(v == NULL)
    {
	fprintf(fp, "0 :\n");
	return;
    }
    fprintf(fp, "%d : ", v->n);
    for(i = 0; i < v->n; i++)
	fprintf(fp, fmt, v->el[i]);
    fprintf(fp, "\n");
}

Ivec *ivec_read(FILE *fp)
{
    int i, n;
    Ivec *v;
    fscanf(fp, "%d %*s", &n);
    v = ivec_make(n);
    for(i = 0; i < v->n; i++)
        fscanf(fp, "%d", &v->el[i]);
    return(v);
}


/*
Reverse components of vector w into vector v.
*/
void ivec_reverse(Ivec *v, Ivec *w)
{
    int i, n1;
    if(v == NULL)
	return;
    n1 = v->n-1;
    for(i = 0; i < v->n; i++)
	v->el[i] = w->el[n1-i];
}

void ivec_block_get(Ivec *u, int li, Ivec *v)
{
    int i;
    if(u == NULL || v == NULL)
	return;
    for(i = 0; i < v->n; i++)
	v->el[i] = u->el[i+li];
}

void ivec_block_set(Ivec *u, int li, Ivec *v)
{
    int i;
    if(u == NULL || v == NULL)
	return;
    for(i = 0; i < v->n; i++)
	u->el[i+li] = v->el[i];
}

void ivec_index_get(Ivec *u, Ivec *index, Ivec *v)
{
    int i;
    if(u == NULL || v == NULL)
	return;
    for(i = 0; i < v->n; i++)
	v->el[i] = u->el[index->el[i]];
}

void ivec_index_set(Ivec *u, Ivec *index, Ivec *v)
{
    int i;
    if(u == NULL || v == NULL)
	return;
    for(i = 0; i < v->n; i++)
	u->el[index->el[i]] = v->el[i];
}
