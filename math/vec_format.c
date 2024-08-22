/**@(#)Vector (1dimensional array) printing
 */

#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

static void format_header(Vector * v)
{
    format("vector: ");
    format("%d of ", v->n);
    format_vtype(v->vtype);
    format("\n");
}

void    vector_format(Vector * v)
{
    int     i, n;

    if (v == NULL)
    {
	format("vector: NULL");
	return;
    }
    format_header(v);
    n = v->n;
    switch (v->vtype)
    {
    case char_v:
    case uchar_v:
	for (i = 0; i < n; i++)
	{
	    double    vi;

	    VECTOR_GET(v, i, vi);
	    format("%c ", (char)vi);
	}
	break;
    case short_v:
    case ushort_v:
    case int_v:
    case uint_v:
	for (i = 0; i < n; i++)
	{
	    double     vi;

	    VECTOR_GET(v, i, vi);
	    format("%d ", (int)vi);
	}
	break;
    case float_v:
    case double_v:
	for (i = 0; i < n; i++)
	{
	    double  vi;

	    VECTOR_GET(v, i, vi);
	    format("%f ", vi);
	}
	break;
    case complex_v:
	for (i = 0; i < n; i++)
	{
	    Complex vi = {Complex_id};

	    VECTOR_GETZ(v, i, vi);
	    format("(%f %f) ", vi.x, vi.y);
	}
	break;
    }
    format("\n");
}

static void print_header(FILE * fp, Vector * v)
{
    fprintf(fp, "vector: ");
    fprintf(fp, "%d of ", v->n);
    print_vtype(fp, v->vtype);
    fprintf(fp, "\n");
}

void    vector_print(FILE * fp, Vector * v)
{
    int     i, n;

    if (v == NULL)
    {
	fprintf(fp, "vector: NULL");
	return;
    }
    print_header(fp, v);
    n = v->n;
    switch (v->vtype)
    {
    case char_v:
	for (i = 0; i < n; i++)
	{
	    double    vi;

	    VECTOR_GET(v, i, vi);
	    fprintf(fp, "%c ", (char) vi);
	}
	break;
    case uchar_v:
	for (i = 0; i < n; i++)
	{
	    double    vi;

	    VECTOR_GET(v, i, vi);
	    fprintf(fp, "%d ", (char) vi);
	}
	break;
    case short_v:
    case ushort_v:
    case int_v:
    case uint_v:
	for (i = 0; i < n; i++)
	{
	    double     vi;

	    VECTOR_GET(v, i, vi);
	    fprintf(fp, "%d ", (int) vi);
	}
	break;
    case float_v:
    case double_v:
	for (i = 0; i < n; i++)
	{
	    double  vi;

	    VECTOR_GET(v, i, vi);
	    fprintf(fp, "%f ", vi);
	}
	break;
    case complex_v:
	for (i = 0; i < n; i++)
	{
	    Complex vi = {Complex_id};

	    VECTOR_GETZ(v, i, vi);
	    fprintf(fp, "(%f %f) ", vi.x, vi.y);
	}
	break;
    }
    fprintf(fp, "\n");
}

void    vector_pprint(FILE * fp, Vector * v)
{
    int     i, n;

    if (v == NULL)
    {
	fprintf(fp, "vector: NULL");
	return;
    }
    print_header(fp, v);
    n = v->n;
    switch (v->vtype)
    {
    case char_v:
	for (i = 0; i < n; i++)
	{
	    double    vi;

	    VECTOR_GET(v, i, vi);
	    fprintf(fp, "%c ", (char) vi);
	}
	break;
    case uchar_v:
	for (i = 0; i < n; i++)
	{
	    double    vi;

	    VECTOR_GET(v, i, vi);
	    fprintf(fp, "%3d ", (char)vi);
	}
	break;
    case short_v:
    case ushort_v:
    case int_v:
    case uint_v:
	for (i = 0; i < n; i++)
	{
	    double     vi;

	    VECTOR_GET(v, i, vi);
	    fprintf(fp, "%10d ", (int)vi);
	}
	break;
    case float_v:
    case double_v:
	for (i = 0; i < n; i++)
	{
	    double  vi;

	    VECTOR_GET(v, i, vi);
	    fprintf(fp, "%12.6f ", vi);
	}
	break;
    case complex_v:
	for (i = 0; i < n; i++)
	{
	    Complex vi = {Complex_id};

	    VECTOR_GETZ(v, i, vi);
	    fprintf(fp, "(%12.6f %12.6f) ", vi.x, vi.y);
	}
	break;
    }
    fprintf(fp, "\n");
}
