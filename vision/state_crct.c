/**@(#)
**/
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Vector *vector_diff();

void    state_correct(State * state)
{
    int     i;
    int     maxindex = state->maxindex;
    int    *type = state->type->data;
    void  **geom = state->geom->data;
    void  **basis = state->basis->data;
    Vector **x = (Vector **) state->x->data;
    Vector **m = (Vector **) state->m->data;


    for (i = 0; i < maxindex; i++)
    {
	Vector *mi;

	geom_correct(geom[i], type[i], basis[i], x[i]);
	mi = vector_diff(m[i], x[i]);
	vector_free(m[i]);
	m[i] = mi;		/** need an inplace diff **/
	vector_free(x[i]);
	x[i] = NULL;
    }
}

void    state_correct_one(State * state, int i)
{
    int     type = vector_get(state->type, i);
    void   *geom = vector_getp(state->geom, i);
    void   *basis = vector_getp(state->basis, i);
    Vector *x = (Vector *) vector_getp(state->x, i);
    Vector *m = (Vector *) vector_getp(state->m, i);

    geom_correct(geom, type, basis, x);
    vector_putp((void *) vector_diff(m, x), state->m, i);
    vector_free(m);		/** need an inplace diff **/
    vector_putp(NULL, state->x, i);
    vector_free(x);
}
