/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:58:55 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/10 14:48:57 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_unset(char *av[], t_data *data)
{
	char **var_names;
	int i;
	int arg_num;

	var_names = NULL;
	i = 0;
	arg_num = ft_count_arg(av);
	if (arg_num <= 1)
	{
		ft_putstr_fd("minishell: unset: not enough arguments\n", STDERR_FILENO);
		return;
	}
	var_names = ft_get_multi_var_name(av, arg_num, FT_UNSET);
	while (var_names[i])
	{
		if (var_names[i] == NULL)
			i++;
/* 		if ((ft_strncmp(var_names[i], "OLDPWD", ft_strlen(var_names[i]))) == 0 
			&& ft_strlen(var_names[i]) == ft_strlen("OLDPWD"))
		{
			ft_copy_env_var(data, "OLDPWD");
		} */
		if (ft_is_var_in_env(data, var_names[i]) == TRUE)
			data->env = ft_remove_env(data, var_names[i]);
		i++;
	}
	ft_free_2d(var_names);
}

/* int ft_copy_env_var(t_data *data, char *var_name)
{
	int i;
	int size;
	char *data_env;
	char *path_copy;
	
	i = 0;
	size = 0;
	data_env = NULL;
	path_copy = NULL;
	while (data->env[i])
	{
		data_env = ft_get_var_name(data->env[i]);
		if (ft_strncmp(data_env, var_name, ft_strlen(var_name)) == 0 && 
			ft_strlen(data_env) == ft_strlen(var_name))
		{
			path_copy = ft_strchr(data->env[i], '=');
			data->oldpwd = ft_strdup(path_copy + 1);
		}
		free(data_env);
		i++;
	}
	printf("%s\n", data->oldpwd);
	return (0);
}
 */
char **ft_remove_env(t_data *data, char *var_name)
{
	int size;
	char **new_env;
	int i;
	int j;
	char *data_env;

	size = ft_count_arg(data->env);
	new_env = malloc(sizeof(char *) * size);
	i = 0;
	j = 0;
	while (data->env[i])
	{
		data_env = ft_get_var_name(data->env[i]);
		if (ft_strncmp(data_env, var_name, ft_strlen(var_name)) == 0 && 
			ft_strlen(data_env) == ft_strlen(var_name))
			{
				i++;
			}
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