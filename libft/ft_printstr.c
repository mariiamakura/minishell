/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:46:11 by ycardona          #+#    #+#             */
/*   Updated: 2023/06/19 15:21:44 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printstr(char *s, int fd, int count)
{
	int	i;

	if (s == NULL)
	{
		write(fd, "(null)", 6);
		return (count + 6);
	}
	i = 0;
	while (s[i])
	{
		count = ft_printchar(s[i], fd, count);
		i++;
	}
	return (count);
}
