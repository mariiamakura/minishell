/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:24:09 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/21 09:44:19 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_quotations_count(char *str, int quot)
{
	int	j;

	j = 0;
	if (str[j] == quot)
	{
		j++;
		while (str[j])
		{
			if (str[j] == quot)
				return (j);
			j++;
			if (str[j] == '\0')
				return (0);
		}
	}
	return (0);
}

static int	ft_red_count(char *str, int red)
{
	int	j;

	j = 0;
	if (str[j] == red)
	{
		j++;
		if (str[j] == red)
			j++;
		while (str[j] == ' ' || str[j] == '\t')
			j++;
	}
	return (j);
}

static int	ft_arg_len(char *sub_str, int i)
{
	int	j;

	j = 0;
	while (sub_str[i + j] && sub_str[i + j] != ' ' && sub_str[i + j] != '\t')
	{
		j += ft_red_count(&sub_str[i + j], '<');
		j += ft_red_count(&sub_str[i + j], '>');
		j += ft_quotations_count(&sub_str[i + j], 34);
		j += ft_quotations_count(&sub_str[i + j], 39);
		if (sub_str[i + j] == '\0')
			break ;
		j++;
		if (sub_str[i + j] == '<' || sub_str[i + j] == '>')
			break ;
	}
	return (j);
}

int	ft_split_sub(char *sub_str, int block, t_data *data)
{
	int	i;
	int	j;
	int	arg;

	i = 0;
	arg = 0;
	while (sub_str[i])
	{
		if (sub_str[i] != ' ' && sub_str[i] != '\t')
		{
			j = ft_arg_len(sub_str, i);
			data->tokens[block][arg] = ft_calloc(sizeof(char), j + 1);
			if (data->tokens[block][arg] == NULL)
				exit (1);
			ft_memmove(data->tokens[block][arg], sub_str + i, j + 1);
			data->tokens[block][arg][j] = '\0';
			arg++;
			i += j - 1;
		}
		i++;
	}
	return (0);
}
