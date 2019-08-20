/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supporting_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:03:20 by mflannel          #+#    #+#             */
/*   Updated: 2019/08/20 14:50:15 by mapryl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "supporting_functions.h"
#include "../libft/includes/libft.h"
#include "stdio.h"
#include "errno.h"

void	ft_swap(int *a, int *b)
{
	int tmp_a;

	tmp_a = *a;
	*a = *b;
	*b = tmp_a;
}

int		pack_argb(const t_color col)
{
	int argb;

	argb = 0;
	argb |= (col.a << 24);
	argb |= (col.r << 16);
	argb |= (col.g << 8);
	argb |= (col.b);
	return (argb);
}

int		ft_isnumber(const char *str)
{
	if (*str && *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		str++;
	}
	return (0);
}

void	throw_error(char *str)
{
	if (errno == 0)
		ft_putendl_fd(str, 2);
	else
		perror(str);
	exit(1);
}
