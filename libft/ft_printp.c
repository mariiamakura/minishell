/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:16:01 by ycardona          #+#    #+#             */
/*   Updated: 2023/06/19 15:21:39 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_tohex(unsigned long int n, int fd, int count)
{
	if (15 < n)
	{
		count = ft_tohex(n / 16, fd, count);
		count = ft_tohex(n % 16, fd, count);
	}
	else
		count = ft_printchar("0123456789abcdef"[n], fd, count);
	return (count);
}

int	ft_printp(unsigned long int n, int fd, int count)
{
	if (n == 0)
		return (ft_printstr("(nil)", fd, count));
	else
	{
		count = ft_printstr("0x", fd, count);
		count = ft_tohex(n, fd, count);
	}
	return (count);
}
