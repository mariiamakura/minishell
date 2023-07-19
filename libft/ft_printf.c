/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:56:29 by ycardona          #+#    #+#             */
/*   Updated: 2023/06/19 15:21:18 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	int			i;
	int			count;

	if (str == NULL)
		return (-1);
	va_start(ap, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] != '%' && str[i])
		{
			count = ft_printchar(str[i], 1, count);
			i++;
		}
		if (str[i] == '%')
			count = ft_printi(ap, str[i + 1], count, &i);
	}
	va_end(ap);
	return (count);
}
