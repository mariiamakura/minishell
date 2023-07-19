/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:22:20 by ycardona          #+#    #+#             */
/*   Updated: 2023/06/19 15:21:23 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printhex(unsigned int n, int fd, int count)
{
	if (15 < n)
	{
		count = ft_printhex(n / 16, fd, count);
		count = ft_printhex(n % 16, fd, count);
	}
	else
		count = ft_printchar("0123456789abcdef"[n], fd, count);
	return (count);
}
