/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:53:53 by ycardona          #+#    #+#             */
/*   Updated: 2022/12/03 19:02:20 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src,
size_t size)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (size == 0)
		return (len_src);
	i = 0;
	while (i + len_dst < size - 1 && src[i])
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	if (size > len_dst)
		dst[len_dst + i] = '\0';
	if (size < len_dst)
		return (len_src + size);
	else
		return (len_src + len_dst);
}
