/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:19:25 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/28 14:07:20 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_has_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_merge_first(char *old_arg, int start, char *sub_split)
{
	char	*new_arg;

	new_arg = ft_calloc(start + ft_strlen(sub_split) + 1, sizeof(char));
	ft_memmove(new_arg, old_arg, start);
	ft_memmove(new_arg + start, sub_split, ft_strlen(sub_split));
	new_arg[start + ft_strlen(sub_split)] = '\0';
	free(sub_split);
	return (new_arg);
}

char	*ft_merge_last(char *old_arg, int end_start, char *sub_split)
{
	char	*new_arg;

	new_arg = ft_calloc(ft_strlen(sub_split) \
	+ ft_strlen(old_arg + end_start) + 1, sizeof(char));
	ft_memmove(new_arg, sub_split, ft_strlen(sub_split));
	ft_memmove(new_arg + ft_strlen(sub_split), old_arg + \
	end_start, ft_strlen(old_arg + end_start));
	new_arg[ft_strlen(sub_split) + ft_strlen(old_arg + end_start)] = '\0';
	free(old_arg);
	free(sub_split);
	return (new_arg);
}

int	ft_split_count(char	**split)
{
	int	count;

	if (split == NULL)
		return (0);
	count = 0;
	while (split[count])
		count++;
	return (count);
}

char	*ft_get_var_cont(char *token, int *len, int *start, t_data *data)
{
	char	*var_cont;
	char	*var_name;

	if (token[*start + 1 + *len] == '?')
		return (var_cont = ft_itoa(g_last_exit), *len += 1, var_cont);
	if (token[*start + 1 + *len] == '0')
	{
		var_cont = ft_calloc(10, sizeof(char));
		return (ft_memmove(var_cont, "minishell", 10), *len += 1, var_cont);
	}
	if (ft_isalpha(token[*start + 1 + *len]) != 1 
		&& token[*start + 1 + *len] != '_')
		return (var_cont = ft_calloc(1, sizeof(char)), *len += 1, var_cont);
	while (ft_isalpha(token[*start + 1 + *len]) == 1
		|| ft_isdigit(token[*start + 1 + *len]) == 1
		|| token[*start + 1 + *len] == '_')
		*len += 1;
	var_name = ft_calloc(*len + 1, sizeof(char));
	ft_memmove(var_name, token + *start + 1, *len);
	var_cont = ft_calloc(ft_strlen(ft_getenv(data->env, var_name)) + 1, \
	sizeof(char));
	ft_memmove(var_cont, ft_getenv(data->env, var_name), \
	ft_strlen(ft_getenv(data->env, var_name)));
	free(var_name);
	return (var_cont);
}
