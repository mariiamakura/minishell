/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:57:24 by ycardona          #+#    #+#             */
/*   Updated: 2022/12/13 14:00:26 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*c_s;
	size_t		i;

	c_s = (const char *) s;
	i = 0;
	while (i < n)
	{
		if (c_s[i] == (char) c)
			return ((void *) &c_s[i]);
		i++;
	}
	return (NULL);
}

/* int main(void)
{	
	char s[] = {0, 1, 2 ,3 ,4 ,5};
	printf("%p\n", memchr(s, 3 + 256, 9));
	printf("%p\n", s + 3);
	return (0);
} */