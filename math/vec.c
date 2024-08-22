/*
 *
 * vec.c
 *
 * Routines for dynamically allocated vectors of doubles.
 *
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

/*
Return an n-vector of doubles.
*/
Vec *vec_make(int n)
{
    Vec *v = talloc(Vec);
    v->n = n;
    v->el = tvector_alloc(0, n, double);
    return(v);
}

/*
Free a vector of doubles.
*/
void vec_free(Vec *v)
{
    if(v == NULL)
	return;
    tvector_free(v->el, 0, double);
    rfree(v);
}

/*
Copy of a vector of doubles.
*/
void vec_copy(Vec *v, Vec *w)
{
    if(v == NULL || w == NULL)
	return;
    tvector_copy_inplace(v->el, w->el, 0, v->n, double);
}

/*
Allocate copy of a vector of doubles.
*/
Vec *vec_make_copy(Vec *w)
{
    Vec *v = vec_make(w->n);
    tvector_copy_inplace(v->el, w->el, 0, v->n, double);
    return(v);
}
 
/*
Set zero vector.
*/
void vec_zero(Vec *v)
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
void vec_rand_unif(Vec *v, double p, double q)
{
    int i;
    if(v == NULL)
	return;
    for(i = 0; i < v->n; i++)
	v->el[i] = rand_unif(p, q);
}

/*
Set Gaussian random vector.
*/
void vec_rand_normal(Vec *v, double m, double s)
{
    int i;
    if(v == NULL)
	return;
    for(i = 0; i < v->n; i++)
	v->el[i] = rand_normal(m, s);
}

/*
Return dot (scalar) product of two vectors.
*/
double vec_dot(Vec *v, Vec *w)
{
    int i;
    double sum;
    if(v == NULL || w == NULL)
	return(0.0);
    for(sum = 0, i = 0; i < v->n; i++)
	sum += v->el[i]*w->el[i];
    return(sum);
}

/*
Form vector sum of v and w in vector v.
*/
void vec_sum(Vec *v, Vec *w)
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
void vec_diff(Vec *v, Vec *w)
{
    int i;
    if(v == NULL || w == NULL)
	return;
    for(i = 0; i < v->n; i++)
	v->el[i] -= w->el[i];
}

/*
Form component-wise product of v and w in vector v.
*/
void vec_prod(Vec *v, Vec *w)
{
    int i;
    if(v == NULL || w == NULL)
	return;
    for(i = 0; i < v->n; i++)
	v->el[i] *= w->el[i];
}

/*
Form component-wise quotient of v and w in vector v.
*/
void vec_divide(Vec *v, Vec *w)
{
    int i;
    if(v == NULL || w == NULL)
	return;
    for(i = 0; i < v->n; i++)
	v->el[i] /= w->el[i];
}

/*
Form product of scalar k and vector v in vector v.
*/
void vec_times(double k, Vec *v)
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
void vec_minus(Vec *v)
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
void vec_accum(Vec *v, double k, Vec *w)
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
double vec_sqrmod(Vec *v)
{
    int i;
    double sum = 0;
    if(v == NULL)
	return(0);
    for(i = 0; i < v->n; i++)
	sum += v->el[i]*v->el[i];
    return(sum);
}

/*
Return modulus (length) of vector v.
*/
double vec_mod(Vec *v)
{
    int i;
    double sum = 0;
    if(v == NULL)
	return(0);
    for(i = 0; i < v->n; i++)
	sum += v->el[i]*v->el[i];
    return(sqrt(sum));
}

/*
Normalise vector to unit length.
*/
void vec_unit(Vec *v)
{
    double l = vec_mod(v);
    if(l == 0)
	return;
    vec_times(1.0/l, v);
}

/*
Return L1 modulus (max element) of vector v.
*/
double vec_mod1(Vec *v)
{
    int i;
    double xmax = 0;
    if(v == NULL)
	return(0);
    for(i = 0; i < v->n; i++)
	xmax = MAX(xmax, fabs(v->el[i]));
    return(xmax);
}

/*
Return squared distance between points (vectors) v and w.
*/
double vec_sqrdist(Vec *v, Vec *w)
{
    int i;
    double sum = 0;
    if(v == NULL || w == NULL)
	return(0);
    for(i = 0; i < v->n; i++)
    {
	double dx = w->el[i]-v->el[i];
	sum += dx*dx;
    }
    return(sum);
}

/*
Return distance between points (vectors) v and w.
*/
double vec_dist(Vec *v, Vec *w)
{
    int i;
    double sum = 0;
    if(v == NULL || w == NULL)
	return(0);
    for(i = 0; i < v->n; i++)
    {
	double dx = w->el[i]-v->el[i];
	sum += dx*dx;
    }
    return(sqrt(sum));
}

void vec_print(FILE *fp, char *fmt, Vec *v)
{
    int i;
    if(v == NULL)
    {
	fprintf(fp, "0 :\n");
	return;
    }
    fprintf(fp, "%d :\n", v->n);
    for(i = 0; i < v->n; i++)
	fprintf(fp, fmt, v->el[i]);
    fprintf(fp, "\n");
}

Vec *vec_read(FILE *fp)
{
    int i, n;
    Vec *v;
    fscanf(fp, "%d %*s", &n);
    v = vec_make(n);
    for(i = 0; i < v->n; i++)
	fscanf(fp, "%lf", &v->el[i]);
    return(v);
}

/*
Reverse components of vector w into vector v.
*/
void vec_reverse(Vec *v, Vec *w)
{
    int i, n1;
    if(v == NULL)
	return;
    n1 = v->n-1;
    for(i = 0; i < v->n; i++)
	v->el[i] = w->el[n1-i];
}

void vec_block_get(Vec *u, int li, Vec *v)
{
    int i;
    if(u == NULL || v == NULL)
	return;
    for(i = 0; i < v->n; i++)
	v->el[i] = u->el[i+li];
}

void vec_block_set(Vec *u, int li, Vec *v)
{
    int i;
    if(u == NULL || v == NULL)
	return;
    for(i = 0; i < v->n; i++)
	u->el[i+li] = v->el[i];
}

void vec_index_get(Vec *u, Ivec *index, Vec *v)
{
    int i;
    if(u == NULL || v == NULL)
	return;
    for(i = 0; i < v->n; i++)
	v->el[i] = u->el[index->el[i]];
}

void vec_index_set(Vec *u, Ivec *index, Vec *v)
{
    int i;
    if(u == NULL || v == NULL)
	return;
    for(i = 0; i < v->n; i++)
	u->el[index->el[i]] = v->el[i];
}

double vec_max(Vec *v, int *imax)
{
    int i;
    double vmax = - MAXFLOAT;
    for(i = 0; i < v->n; i++)
    {
	double vi = v->el[i];
	if(vmax < vi)
	{
	    vmax = vi;
	    *imax = i;
	}
    }
    return(vmax);
}

double vec_min(Vec *v, int *imin)
{
    int i;
    double vmin = MAXFLOAT;
    for(i = 0; i < v->n; i++)
    {
	double vi = v->el[i];
	if(vmin > vi)
	{
	    vmin = vi;
	    *imin = i;
	}
    }
    return(vmin);
}
