/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:49:26 by ycardona          #+#    #+#             */
/*   Updated: 2023/06/19 15:21:30 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printi(va_list ap, char c, int count, int *index)
{
	if (c == 'c')
		count = ft_printchar(va_arg(ap, int), 1, count);
	if (c == 's')
		count = ft_printstr(va_arg(ap, char *), 1, count);
	if (c == 'i' || c == 'd')
		count = ft_printnbr(va_arg(ap, int), 1, count);
	if (c == 'x')
		count = ft_printhex(va_arg(ap, unsigned int), 1, count);
	if (c == 'X')
		count = ft_printchex(va_arg(ap, unsigned int), 1, count);
	if (c == 'p')
		count = ft_printp(va_arg(ap, long int), 1, count);
	if (c == 'u')
		count = ft_printuint(va_arg(ap, unsigned int), 1, count);
	if (c == '%')
		count = ft_printchar('%', 1, count);
	*index = *index + 2;
	if (c == '\0')
	{
		count = -1;
		*index = *index - 1;
	}
	return (count);
}
