/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:49:39 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/16 15:06:43 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if ((9 <= c && c <= 13) || c == ' ')
		return (1);
	else
		return (0);
}

long long	ft_atoi(const char *str)
{
	int			i;
	long long	r;
	int			sign;

	sign = 1;
	i = 0;
	r = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	if ((str[i] == '-' || str[i] == '+') && ft_isdigit(str[i +1]) == 1)
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]) == 1)
	{
		r = 10 * r + str[i] - 48;
		i++;
	}
	return (sign * r);
}
