/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:39:36 by ycardona          #+#    #+#             */
/*   Updated: 2022/12/09 16:33:10 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*join;

	size = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(size + 1);
	if (join == NULL)
		return (NULL);
	ft_memcpy(join, s1, ft_strlen(s1));
	ft_memcpy(join + ft_strlen(s1), s2, ft_strlen(s2));
	join[size] = '\0';
	return (join);
}
