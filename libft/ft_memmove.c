/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:00:11 by ycardona          #+#    #+#             */
/*   Updated: 2022/12/10 12:52:03 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*c_src;
	char	*c_dst;
	int		i;

	c_src = (char *) src;
	c_dst = (char *) dst;
	if (src == c_dst || len == 0)
		return (dst);
	if (c_src < c_dst && c_dst - c_src < (int) len)
	{
		i = len - 1;
		while (0 <= i)
		{
			c_dst[i] = c_src[i];
			i--;
		}
		return (dst);
	}
	ft_memcpy(dst, src, len);
	return (dst);
}

// int	main(void)
// {
// 	char	dst1[] = "abcde";
// 	char	dst2[] = "abcde";
// 	memcpy(dst1 + 2, dst1, 3);
// 	memmove(dst2 + 2, dst2, 3);
// 	printf("memcpy: %s\n", dst1);
// 	printf("memmove: %s\n", dst2);
// }
// #include <string.h>
// #include <stdio.h>
// #define SIZE    21
// char target[SIZE] = "a shiny white sphere";
// int main( void )
// {
//   char * p = target + 8;  /* p points at the starting character
//                           of the word we want to replace */
//   char * source = target + 2; /* start of "shiny" */
//   printf( "Before memmove, target is \"%s\"\n", target );
//   memcpy( p, source, 5 );
//   printf( "After memmove, target becomes \"%s\"\n", target );
// }