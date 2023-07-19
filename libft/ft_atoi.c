/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:49:39 by ycardona          #+#    #+#             */
/*   Updated: 2022/12/08 18:35:56 by ycardona         ###   ########.fr       */
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

int	ft_atoi(const char *str)
{
	int	i;
	int	r;
	int	sign;

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
