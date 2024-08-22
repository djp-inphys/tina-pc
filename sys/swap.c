static int swapping_flag = 0;
void    set_swapping_ts(int w)
{
    swapping_flag = w;
}
void    longd_swap(char *d)
{
    union swap
    {
	char    in[16];
	long double out;
    }       Swap;

    if (!swapping_flag)
	return;
    Swap.in[0] = *(d + 15);
    Swap.in[1] = *(d + 14);
    Swap.in[2] = *(d + 13);
    Swap.in[3] = *(d + 12);
    Swap.in[4] = *(d + 11);
    Swap.in[5] = *(d + 10);
    Swap.in[6] = *(d + 9);
    Swap.in[7] = *(d + 8);
    Swap.in[8] = *(d + 7);
    Swap.in[9] = *(d + 6);
    Swap.in[10] = *(d + 5);
    Swap.in[11] = *(d + 4);
    Swap.in[12] = *(d + 3);
    Swap.in[13] = *(d + 2);
    Swap.in[14] = *(d + 1);
    Swap.in[15] = *d;
    *(long double *) d = Swap.out;
}
void    long_swap(char *d)
{
    union swap
    {
	char    in[8];
	double  out;
    }       Swap;

    if (!swapping_flag)
	return;
    Swap.in[0] = *(d + 7);
    Swap.in[1] = *(d + 6);
    Swap.in[2] = *(d + 5);
    Swap.in[3] = *(d + 4);
    Swap.in[4] = *(d + 3);
    Swap.in[5] = *(d + 2);
    Swap.in[6] = *(d + 1);
    Swap.in[7] = *d;
    *(double *) d = Swap.out;
}
void    word_swap(char *d)
{
    union swap
    {
	char    in[4];
	int     out;
    }       Swap;

    if (!swapping_flag)
	return;
    Swap.in[0] = *(d + 3);
    Swap.in[1] = *(d + 2);
    Swap.in[2] = *(d + 1);
    Swap.in[3] = *d;
    *(int *) d = Swap.out;
}
void    short_swap(char *d)
{
    union swap
    {
	char    in[4];
	short   out;
    }       Swap;

    if (!swapping_flag)
	return;
    Swap.in[0] = *(d + 1);
    Swap.in[1] = *d;
    *(short *) d = Swap.out;
}
