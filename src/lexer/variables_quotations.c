/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_quotations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:08:45 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/22 10:05:17 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_expand_token(char *token, char *var_cont, int *start, int len)
{
	char	*new_token;

	new_token = ft_calloc(*start + ft_strlen(var_cont) + \
	ft_strlen(token + *start + 1 + len) + 1, sizeof(char));
	ft_memmove(new_token, token, *start);
	ft_memmove(new_token + *start, var_cont, ft_strlen(var_cont));
	ft_memmove(new_token + *start + ft_strlen(var_cont), \
	token + *start + 1 + len, ft_strlen(token + *start + 1 + len));
	new_token[*start + ft_strlen(var_cont) + \
	ft_strlen(token + *start + 1 + len)] = '\0';
	free(token);
	*start += ft_strlen(var_cont);
	return (new_token);
}

char	**ft_expand_tokens(char *var_cont, char **old_block, int *start, \
int p[2])
{
	char	**split;
	char	**new_block;
	int		i;
	int		j;

	split = ft_split(var_cont, ' ');
	new_block = ft_calloc(ft_split_count(split) + \
	ft_split_count(old_block), sizeof(char *));
	i = -1;
	while (++i < p[0])
		new_block[i] = old_block[i];
	new_block[i++] = ft_merge_first(old_block[p[0]], *start, split[0]);
	j = 1;
	while (j < ft_split_count(split) - 1)
		new_block[i++] = split[j++];
	new_block[i] = ft_merge_last(old_block[p[0]], *start + p[1] + 1, split[j]);
	j = 0;
	while (old_block[p[0] + ++j])
		new_block[i + j] = old_block[p[0] + j];
	new_block[i + j] = NULL;
	free(old_block);
	free(split);
	return (new_block);
}

void	ft_add_var(int block, int arg, int *start, t_data *data)
{
	char	*var_cont;
	int		len;
	int		param[2];

	len = 0;
	var_cont = ft_get_var_cont(data->tokens[block][arg], &len, start, data);
	if (ft_has_spaces(var_cont) == 0)
		data->tokens[block][arg] = ft_expand_token(data->tokens[block][arg], \
		var_cont, start, len);
	else
	{
		param[0] = arg;
		param[1] = len;
		data->tokens[block] = ft_expand_tokens(var_cont, data->tokens[block], \
		start, param);
	}
	free(var_cont);
}

void	ft_handle_dq(t_data *data, int block, int arg, int i)
{
	int	j;

	j = i + 1;
	while (data->tokens[block][arg][j])
	{
		if (data->tokens[block][arg][j] == '$')
			ft_add_var(block, arg, &j, data);
		if (data->tokens[block][arg][j] == '"')
		{
			ft_remove_quot(data->tokens[block][arg], i, j);
			i = j - 1;
			break ;
		}
		j++;
	}
	return ;
}

void	ft_parse_var(int block, int arg, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->tokens[block][arg][i])
	{
		if (data->tokens[block][arg][i] == '$'
			&& data->tokens[block][arg][i + 1])
			ft_add_var(block, arg, &i, data);
		else if (data->tokens[block][arg][i] == '"'
			&& (ft_quot_closed(&data->tokens[block][arg][i + 1], 34) == TRUE))
			ft_handle_dq(data, block, arg, i);
		else if (data->tokens[block][arg][i] == 39
			&& (ft_quot_closed(&data->tokens[block][arg][i + 1], 39) == TRUE))
		{
			j = i + 1;
			while (data->tokens[block][arg][j] != 39)
				j++;
			ft_remove_quot(data->tokens[block][arg], i, j);
			i = j - 1;
		}
		else
			i++;
	}
}
