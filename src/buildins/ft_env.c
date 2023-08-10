/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:55:54 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/10 15:53:10 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_env(char *av[], t_data *data, int index)
{
	int j;
	char *error;

	j = 0;
	if (av[1] != NULL)
	{
		error = ft_strjoin("minishell: env: Permission denied: ", av[1]);
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		last_exit_global = 127;
		free(error);
		return (last_exit_global);
	}
	while (data->env[j])
	{
		ft_putstr_fd(data->env[j], data->pipes[index][1]);
		ft_putstr_fd("\n", data->pipes[index][1]);
		j++;
	}
	last_exit_global = 0;
	return(last_exit_global);
}

char *ft_get_env_value(t_data *data, char *var_name) 
{
	int i;
	char *new_str;
	char *res;

	i = 0;
	new_str = NULL;
	res = NULL;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var_name, ft_strlen(var_name)) == 0)
		{
			new_str = ft_strdup(data->env[i]);
			res = ft_strchr(new_str, '=');
			if (new_str == 0)
			{
				free(new_str);
				return (NULL);
			}
			else
			{
				res = ft_strdup(res + 1);
				free(new_str);
				return (res);
			}
				
		} 
		free(new_str);
		i++;
	}
	return (NULL);
}

void swap(char **a, char **b)
{
	char *temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

int ft_env_declare_x(t_data *data, int index)
{
	int i;
	char **temp_env;
	int sort_flag;
	int size;

	i = 0;
	temp_env = ft_copy_2d_arr(data->env);
	sort_flag = FALSE;
	size = ft_count_arg(data->env);
	while (sort_flag != TRUE)
	{
		sort_flag = TRUE;
		i = 0;
		while (i < size - 1)
		{
			if (ft_strncmp(temp_env[i], temp_env[i + 1], ft_strlen(temp_env[i])) > 0)
			{
				swap(&temp_env[i], &temp_env[i + 1]);
				sort_flag = FALSE;
			}
			i++;
		}
		size--;
	}
	print_declare_x(temp_env, index, data);
	ft_free_2d(temp_env);
	return (0);
}

void print_declare_x(char **temp_env, int index, t_data *data)
{
	int i;

	i = 0;
	while (temp_env[i])
	{
		ft_putstr_fd("declare -x ", data->pipes[index][1]);
		ft_putstr_fd(temp_env[i], data->pipes[index][1]);
		ft_putstr_fd("\n", data->pipes[index][1]);
		i++;
	}
}

char **ft_copy_2d_arr(char **env)
{
	int i;
	char **new_arr;

	i = 0;
	while (env[i])
        i++;
	new_arr = malloc(sizeof(char *) * (i + 1));
	if (new_arr == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_arr[i] = ft_strdup(env[i]);
		if (new_arr[i] == NULL)
		{
			ft_free_2d(new_arr);
			return (NULL);
		}
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}