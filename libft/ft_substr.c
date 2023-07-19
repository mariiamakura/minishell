/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:23:21 by ycardona          #+#    #+#             */
/*   Updated: 2022/12/17 00:52:42 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	char	*ss;

	if (*s == '\0' || start > ft_strlen(s) || len == 0)
	{
		sub = malloc(1);
		if (sub == NULL)
			return (NULL);
		*sub = '\0';
		return (sub);
	}
	ss = (char *) s + start;
	if (ft_strlen(ss) < len)
		len = ft_strlen(ss);
	sub = (char *) malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	ft_strlcpy(sub, ss, len + 1);
	return (sub);
}

/* int	main(void)
{
	printf("%p\n", ft_substr("Hallo", 10, 2));
} */