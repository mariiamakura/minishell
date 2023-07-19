/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:33:58 by ycardona          #+#    #+#             */
/*   Updated: 2022/12/09 17:39:55 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inset(char const *set, int c)
{
	if (ft_strchr(set, c) != NULL)
		return (1);
	else
		return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*trim;

	start = 0;
	end = ft_strlen(s1);
	while (ft_inset(set, s1[start]) == 1 && s1[start])
		start++;
	while (ft_inset(set, s1[end - 1]) == 1 && start < end)
		end--;
	trim = ft_substr(s1, start, end - start);
	return (trim);
}

/* int 	main(void)
{
	char s1[] = "  LLcooooool   JJ ";
	printf("%s\n", ft_strtrim(s1, "LJ "));
} */