/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printuint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 23:56:10 by ycardona          #+#    #+#             */
/*   Updated: 2023/06/19 15:21:56 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printuint(unsigned int n, int fd, int count)
{
	if (9 < n)
	{
		count = ft_printuint(n / 10, fd, count);
		count = ft_printuint(n % 10, fd, count);
	}
	else
		count = ft_printchar(n + '0', fd, count);
	return (count);
}
