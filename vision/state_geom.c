/**@(#)
**/
#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Bool    state_badpair(State * state, int i1, int i2)
{
    if (state == NULL)
    {
	error("state_badpair: null state", non_fatal);
	return (true);
    }
    if (i1 < 0 || i1 >= state->maxindex || i2 < 0 || i2 >= state->maxindex)
    {
	error("state_badpair: index out of range", non_fatal);
	return (true);
    }
    return (false);
}


double  state_angle(State * state, int i1, int i2)
{
    int     type1, type2;
    void   *geom1, *geom2;

    if (state_badpair(state, i1, i2))
	return (1e10);

    type1 = vector_get(state->type, i1);
    type2 = vector_get(state->type, i2);
    geom1 = vector_getp(state->geom, i1);
    geom2 = vector_getp(state->geom, i2);

    return (geom_angle(geom1, type1, geom2, type2));
}

double  state_dist(State * state, int i1, int i2)
{
    int     type1, type2;
    void   *geom1, *geom2;

    if (state == NULL)
    {
	error("state_dist: null state", non_fatal);
	return (1e10);
    }
    if (i1 < 0 || i1 >= state->maxindex || i2 < 0 || i2 >= state->maxindex)
    {
	error("state_dist: index out of range", non_fatal);
	return (1e10);
    }
    type1 = vector_get(state->type, i1);
    type2 = vector_get(state->type, i2);
    geom1 = vector_getp(state->geom, i1);
    geom2 = vector_getp(state->geom, i2);

    return (geom_dist(geom1, type1, geom2, type2));
}
