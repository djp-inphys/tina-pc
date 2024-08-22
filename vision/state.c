/**@(#)
**/
/**
state.c:
basic statistics structure handling
**/

#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/sysfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void   *geom_basis();

/**
allocate a state
maxnum is estimate of maximum number of geometrical primitives
**/

#define PUSH(x, list) {(list) = ref_addtostart((List *) list, (void *) (x), (int)NULL);}
#define POP(type, x, list) {(x) = (type) (list)->to; (list) = link_rm_el(list);}

State  *state_alloc(int maxnum, double lscale, double accuracy)
{
    State  *state = ts_ralloc(State);
    int     i;

    /** internal indexing has maxnum free places **/
    state->maxnum = maxnum;
    state->maxindex = 0;
    state->freeindex = NULL;
    for (i = maxnum - 1; i >= 0; i--)
	PUSH(i, state->freeindex);

    /** pointers to geometry and statistics information **/
    state->type = vector_alloc(maxnum, int_v);
    state->geom = vector_alloc(maxnum, ptr_v);
    state->basis = vector_alloc(maxnum, ptr_v);
    state->s = matrix_alloc(maxnum, maxnum, matrix_lower, ptr_v);
    state->x = vector_alloc(maxnum, ptr_v);
    state->m = vector_alloc(maxnum, ptr_v);

    state->lscale = lscale;
    state->accuracy = accuracy;

    return (state);
}

/**
free all the memory associated with a state

(except for primlist)
**/

void    state_free(State * state)
{
    int     i, j;
    int    *type = (int *) state->type->data;
    void  **geom = (void **) state->geom->data;
    void  **basis = (void **) state->basis->data;
    Matrix ***s = (Matrix ***) state->s->el.ptr_v;
    Vector **x = (Vector **) state->x->data;
    Vector **m = (Vector **) state->m->data;

    for (i = 0; i < state->maxindex; i++)
    {
	geom_free(geom[i], type[i]);
	rfree((void *) basis[i]);
	vector_free(x[i]);
	vector_free(m[i]);
	matrix_free(s[i][i]);
	for (j = 0; j < i; j++)
	    matrix_free(s[i][j]);
    }

    vector_free(state->type);
    vector_free(state->geom);
    vector_free(state->basis);
    matrix_free(state->s);
    vector_free(state->x);
    vector_free(state->m);
    list_rm((List *) state->freeindex, (void (*) ()) NULL);

    rfree((void *) state);
}

/**
add a new primitive into state
**/

int     state_add(State * state, void *newgeom, int newtype)
{
    int     i;
    int    *type = (int *) state->type->data;
    void  **geom = (void **) state->geom->data;
    void  **basis = (void **) state->basis->data;

    if (state->freeindex == NULL)
    {
	error("state_add: state full", non_fatal);
	return (-1);

	/**
	  int             maxnum = state->maxnum;
	int newmaxnum = maxnum+MAX(1, maxnum/3);
	Matrix       ***s = (Matrix ***) state->s->el.ptr_v;
	Vector        **x = (Vector **) state->x->data;
	Vector        **m = (Vector **) state->m->data;
	message("state_add: extending state length");
	type = ivector_extend(type,  0, maxnum, 0, newmaxnum);
	geom = pvector_extend(geom,  0, maxnum, 0, newmaxnum);
	basis = pvector_extend(basis,  0, maxnum, 0, newmaxnum);
	s = (Matrix ***) plower_extend((void ***) s, 0, maxnum, 0, newmaxnum);
	x = (Vector **) pvector_extend((void **) x, 0, maxnum, 0, newmaxnum);
	m = (Vector **) pvector_extend((void **) m, 0, maxnum, 0, newmaxnum);
	for(i = newmaxnum-1; i >= maxnum; i++)
	    PUSH(i, state->freeindex);
	**/
    }
    POP(int, i, state->freeindex);
    if (state->maxindex == i)
	state->maxindex = i + 1;
    type[i] = newtype;
    geom[i] = geom_copy(newgeom, newtype);
    basis[i] = geom_basis(newgeom, newtype);

    /**
    s[i][i] = matrix_alloc(geom_df(newtype), geom_df(newtype),
	matrix_lower, double_v);
    geom_set_infcov(newtype, s[i][i], state->lscale);
    **/

    /**
    x[i] = vector_alloc(geom_df(newtype), double_v);
    m[i] = vector_alloc(geom_df(newtype), double_v);
    **/
    return (i);
}

State  *state_make(List * list, double accuracy)
{
    List   *ptr;
    int     n, l;
    State  *state;
    Vec3    centre = {Vec3_id};
/*BUGFIX Julian Briggs 1/12/93: was    float   radius;*/
    double    radius;

    geom_hull_get(list, &centre, &radius);
    l = list_length(list);
    n = MAX(3 * l, l + 30);
    state = state_alloc(n, radius, accuracy);

    for (ptr = list; ptr != NULL; ptr = ptr->next)
	(void) state_add_tina(state, ptr->to, LINE3);

    return (state);
}


/**delete prim with given label from prim**/

int     state_delete(State * state, int i)
{
    int     j;
    int    *type = (int *) state->type->data;
    void  **geom = (void **) state->geom->data;
    void  **basis = (void **) state->basis->data;
    Matrix ***s = (Matrix ***) state->s->el.ptr_v;
    Vector **x = (Vector **) state->x->data;
    Vector **m = (Vector **) state->m->data;

    geom_free(geom[i], type[i]);
    type[i] = (int) NULL;
    geom[i] = NULL;
    rfree((void *) basis[i]);
    basis[i] = NULL;
    vector_free(x[i]);
    x[i] = NULL;
    vector_free(m[i]);
    m[i] = NULL;
    for (j = 0; j <= i; j++)
    {
	matrix_free(s[i][j]);
	s[i][j] = NULL;
    }
    if (i == state->maxindex - 1)
	state->maxindex--;
    PUSH(i, state->freeindex);
    return(i);
}
