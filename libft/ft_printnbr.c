/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:49:21 by ycardona          #+#    #+#             */
/*   Updated: 2023/06/19 15:21:35 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printnbr(int n, int fd, int count)
{
	if (n == -2147483648)
	{
		count = ft_printchar('-', fd, count);
		count = ft_printchar('2', fd, count);
		n = 147483648;
	}
	if (n < 0)
	{
		n = -n;
		count = ft_printchar('-', fd, count);
	}
	if (9 < n)
	{
		count = ft_printnbr(n / 10, fd, count);
		count = ft_printnbr(n % 10, fd, count);
	}
	else
		count = ft_printchar(n + '0', fd, count);
	return (count);
}

/* int main(void)
{
	int a = ft_printf("%d", 10);
	int b = printf("%d", 10);
	printf("  %d  %d\n", a, b);
} */