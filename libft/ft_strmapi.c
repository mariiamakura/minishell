/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 11:37:35 by ycardona          #+#    #+#             */
/*   Updated: 2022/12/10 11:49:15 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*s_f;
	unsigned int	i;

	s_f = ft_calloc(ft_strlen(s) + 1, 1);
	if (s_f == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		s_f[i] = (*f)(i, s[i]);
		i++;
	}
	return (s_f);
}
