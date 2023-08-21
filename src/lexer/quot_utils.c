/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quot_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:42:14 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/21 17:12:45 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_quot_closed(char *str, int quot)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == quot)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	ft_remove_quot(char *str, int first, int last)
{
	size_t	len_sub;
	size_t	len_str;

	len_str = ft_strlen(str);
	if (len_str < 2)
		return ;
	len_sub = ft_strlen(str + (last + 1));
	ft_memmove(str + last, str + (last + 1), len_sub);
	str[len_str - 1] = '\0';
	len_str = ft_strlen(str);
	len_sub = ft_strlen(str + (first + 1));
	ft_memmove(str + first, str + (first + 1), len_sub);
	str[len_str - 1] = '\0';
}
