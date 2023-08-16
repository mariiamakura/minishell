/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:38:37 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/16 15:07:26 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j = 0;
			while (s[i + j] != c && s[i + j])
				j++;
			count++;
			i = i + j - 1;
		}
		i++;
	}
	return (count);
}

static	size_t	ft_subend(char const *s, char c, int i)
{
	size_t	j;

	j = 0;
	while (s[(i + j)] != c && s[(i + j)])
		j++;
	return (j);
}

static void	ft_free(char **split, int k)
{
	while (0 <= --k)
		free(split[k]);
	free(split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		k;

	split = ft_calloc((ft_count(s, c) + 1) * sizeof(char *), 1);
	if (split == NULL)
		return (NULL);
	k = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			split[k] = ft_substr(s, i, ft_subend(s, c, i));
			if (split[k] == NULL)
			{
				ft_free(split, k);
				return (NULL);
			}
			k++;
			i = i + ft_subend(s, c, i) - 1;
		}
		i++;
	}
	return (split);
}
