/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_quotations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:08:45 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/16 11:41:43 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_has_spaces(char *str)
{
	int	i;

	i = 0;
	while ( str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

static void	ft_expand_token(t_data *data, int block, int arg, int *start, char *var_cont, int end)
{
	char	**split;
	int		count1;
	int		count2;
	char	**new_block;
	int		i;
	int		j;

	split = ft_split(var_cont, ' ');
	count1 = 0;
	while (split[count1])
		count1++;
	count2 = 0;
	while (data->tokens[block][count2])
		count2++;
	new_block = ft_calloc(count1 + count2, sizeof(char *));
	//assign the arguments before the argument containing the var to new block
	i = 0;
	while (i < arg)
	{
		new_block[i] = data->tokens[block][i];
		i++;
	}
	//merge the start of the argument with the first argument of the var_cont-split
	new_block[i] = ft_calloc(*start + ft_strlen(split[0]) + 1, sizeof(char));
	ft_memmove(new_block[i], data->tokens[block][arg], *start);
	ft_memmove(new_block[i] + *start, split[0], ft_strlen(split[0]));
	new_block[i][*start + ft_strlen(split[0]) + 1] = '\0';
	free(split[0]);
	i++;
	//assign the middle parts
	j = 1;
	while (j < count1 - 1)
	{
		new_block[i] = split[j];
		i++;
		j++;
	}
	//merge the last part of the argument with the last argument of the var_cont-split
	new_block[i] = ft_calloc(ft_strlen(split[j]) + ft_strlen(data->tokens[block][arg] + *start + end + 1), sizeof(char));
	ft_memmove(new_block[i], split[j], ft_strlen(split[j]));
	ft_memmove(new_block[i] + ft_strlen(split[j]), data->tokens[block][arg] + *start + end + 1, ft_strlen(data->tokens[block][arg] + *start + end + 1));
	new_block[i][ft_strlen(split[j]) + ft_strlen(data->tokens[block][arg] + *start + end + 1)] = '\0';
	free(data->tokens[block][arg]);
	free(split[j]);
	//assign the arguments after the argument containing the var to new block
	j = 1;
	while (data->tokens[block][arg + j])
	{
		new_block[i + j] = data->tokens[block][arg + j];
		j++;
	}
	new_block[i + j] = NULL;
	free(data->tokens[block]);
	data->tokens[block] = new_block;
	free(split);
}

void	ft_add_var(int block, int arg, int *start, t_data *data)
{
	char	*token;
	char	*var_name;
	char	*var_cont;
	char	*new_token;
	int		i;
	int		FLAG;

	token = data->tokens[block][arg];
	FLAG = FALSE;
	i = 0;
	if (data->tokens[block][arg][*start + 1 + i] == '?')
	{
		var_cont = ft_itoa(last_exit_global); //needs to be freed
		i++;
		FLAG = TRUE;
	}
	else if (ft_isdigit(data->tokens[block][arg][*start + 1 + i]) == 1)
	{
		var_cont = "";
		i++;
	}
	else
	{
		while (ft_isalpha(data->tokens[block][arg][*start + 1 + i]) == 1
			|| ft_isdigit(data->tokens[block][arg][*start + 1 + i]) == 1
			|| data->tokens[block][arg][*start + 1 + i] == '_')
			i++;
		var_name = ft_calloc(i + 1, sizeof(char));
		ft_memmove(var_name, token + *start + 1, i);
		var_name[i] = '\0';
		var_cont = ft_getenv(data->env, var_name);
		if (var_cont == NULL)
			var_cont = "";
		free(var_name);
	}
	if (ft_has_spaces(var_cont) == 0)
	{
		new_token = ft_calloc(*start + ft_strlen(var_cont) + ft_strlen(token + *start + 1 + i) + 1, sizeof(char));
		ft_memmove(new_token, token, *start);
		ft_memmove(new_token + *start, var_cont, ft_strlen(var_cont));
		ft_memmove(new_token + *start + ft_strlen(var_cont), token + *start + 1 + i, ft_strlen(token + *start + 1 + i));
		new_token[*start + ft_strlen(var_cont) + ft_strlen(token + *start + 1 + i)] = '\0';
		free(token);
		*start += ft_strlen(var_cont);
		data->tokens[block][arg] = new_token;
	}
	else
		ft_expand_token(data, block, arg, start, var_cont, i);
	if (FLAG == TRUE)
		free(var_cont);
}

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

	if ((len_str = ft_strlen(str)) < 2)
		return;
	len_sub = ft_strlen(str + (last + 1));
	ft_memmove(str + last, str + (last + 1), len_sub);
	str[len_str - 1] = '\0';
	len_str = ft_strlen(str);
	len_sub = ft_strlen(str + (first + 1));
	ft_memmove(str + first, str + (first + 1), len_sub);
	str[len_str - 1] = '\0';
}

void	ft_parse_var(int block, int arg, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->tokens[block][arg][i])
	{
		if (data->tokens[block][arg][i] == '$')
			ft_add_var(block, arg, &i, data);
		else if (data->tokens[block][arg][i] == '"'
			&& (ft_quot_closed(&data->tokens[block][arg][i + 1], 34) == TRUE))
		{
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
		}
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
