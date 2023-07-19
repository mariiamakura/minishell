/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:53:18 by ycardona          #+#    #+#             */
/*   Updated: 2022/12/13 13:53:01 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *) &(s[i]));
		i++;
	}
	if ((char) c == '\0')
		return ((char *) &(s[i]));
	return (NULL);
}

/* int main(void)
{
	char s[] = "teste";
	printf("%p   |  %p\n", ft_strchr(s, 'e'), strchr(s, 'e'));
} */