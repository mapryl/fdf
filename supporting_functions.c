#include "supporting_functions.h"
#include "libft/includes/libft.h"

void	ft_swap(int *a, int *b)
{
    int tmp_a;

    tmp_a = *a;
    *a = *b;
    *b = tmp_a;
}

int pack_argb(const t_color col)
{
    int argb = 0;

    argb |= (col.a << 24);
    argb |= (col.r << 16);
    argb |= (col.g << 8);
    argb |= (col.b);

    return argb;
}

int ft_isnumber(const char *str)
{
    if (*str && *str == '-')
        str++;
    while (*str)
    {
        if (!ft_isdigit(*str))
            return -1;
        str++;
    }
    return 0;
}

void throw_error()
{
    //exit(1);
    int i = 0;
}