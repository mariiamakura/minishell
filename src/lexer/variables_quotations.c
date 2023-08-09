/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_quotations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:08:45 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/08 17:41:42 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_add_var(int block, int arg, int *start, t_data *data)
{
	char	*token;
	char	*var_name;
	char	*var_cont;
	char	*new_token;
	int		i;

	token = data->tokens[block][arg];

	i = 0;

	if (data->tokens[block][arg][*start + 1 + i] == '?')
	{
		var_cont = ft_itoa(last_exit_global);
		//last_exit_global = 0;
		i++;
	}
	else if (ft_isdigit(data->tokens[block][arg][*start + 1 + i]) == 1)
	{
		var_cont = "";
		i++;
	}
	else
	{
		while (ft_isalpha(data->tokens[block][arg][*start + 1 + i]) == 1
			|| ft_isdigit(data->tokens[block][arg][*start + 1 + i])
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
	new_token = ft_calloc(*start + ft_strlen(var_cont) + ft_strlen(token + *start + 1 + i) + 1, sizeof(char));
	ft_memmove(new_token, token, *start);
	ft_memmove(new_token + *start, var_cont, ft_strlen(var_cont));
	ft_memmove(new_token + *start + ft_strlen(var_cont), token + *start + 1 + i, ft_strlen(token + *start + 1 + i));
	new_token[*start + ft_strlen(var_cont) + ft_strlen(token + *start + 1 + i)] = '\0';
	free(token);
	*start += ft_strlen(var_cont);
	data->tokens[block][arg] = new_token;
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
