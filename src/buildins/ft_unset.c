/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:58:55 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/11 18:01:56 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(char *av[], t_data *data)
{
	char	**var_names;
	int		i;
	int		arg_num;
	int		j;

	var_names = NULL;
	i = 0;
	j = 0;
	arg_num = ft_count_arg(av);
	if (arg_num <= 1)
		return (0);
	var_names = ft_get_multi_var_name(av, arg_num, FT_UNSET);
	while (var_names[i])
	{
		if (var_names[i] == NULL)
			i++;
		if (ft_is_var_in_env(data, var_names[i]) == TRUE)
			data->env = ft_remove_env(data, var_names[i], j);
		i++;
	}
	ft_free_2d(var_names);
	return (0);
}

char	**ft_remove_env(t_data *data, char *var_name, int j)
{
	int		size;
	char	**new_env;
	int		i;
	char	*data_env;

	size = ft_count_arg(data->env);
	new_env = malloc(sizeof(char *) * size);
	i = 0;
	while (data->env[i])
	{
		data_env = ft_get_var_name(data->env[i]);
		if (ft_strncmp(data_env, var_name, ft_strlen(var_name)) == 0)
			i++;
		if (data->env[i])
		{
			new_env[j] = ft_strdup(data->env[i]);
			i++;
			j++;
		}
		free(data_env);
	}
	new_env[j] = NULL;
	ft_free_2d(data->env);
	data->env = new_env;
	return (data->env);
}
