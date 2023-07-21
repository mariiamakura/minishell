/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:12:06 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/19 16:34:15 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*c_dst;
	const char	*c_src;
	size_t		i;

	if (!(dst || src))
		return (NULL);
	c_dst = (char *) dst;
	c_src = (const char *) src;
	i = 0;
	while (i < n)
	{
		c_dst[i] = c_src[i];
		i++;
	}
	return (c_dst);
}
