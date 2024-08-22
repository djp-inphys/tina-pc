/**@(#)Print Tina types
**/

#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>

void    format_vtype(Vartype type)
{
    switch (type)
    {
	case char_v:
	format("char");
	break;
    case uchar_v:
	format("unsigned char");
	break;
    case short_v:
	format("short");
	break;
    case ushort_v:
	format("unsigned short");
	break;
    case int_v:
	format("int");
	break;
    case uint_v:
	format("unsigned int");
	break;
    case float_v:
	format("float");
	break;
    case double_v:
	format("double");
	break;
    case complex_v:
	format("complex");
	break;
    case ptr_v:
	format("void *");
	break;
    }
}

void    print_vtype(FILE * fp, Vartype type)
{
    switch (type)
    {
	case char_v:
	(void) fprintf(fp, "char");
	break;
    case uchar_v:
	(void) fprintf(fp, "unsigned char");
	break;
    case short_v:
	(void) fprintf(fp, "short");
	break;
    case ushort_v:
	(void) fprintf(fp, "unsigned short");
	break;
    case int_v:
	(void) fprintf(fp, "int");
	break;
    case uint_v:
	(void) fprintf(fp, "unsigned int");
	break;
    case float_v:
	(void) fprintf(fp, "float");
	break;
    case double_v:
	(void) fprintf(fp, "double");
	break;
    case complex_v:
	(void) fprintf(fp, "complex");
	break;
    case ptr_v:
	(void) fprintf(fp, "void *");
	break;
    }
}
