/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:55:54 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/07 17:00:10 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_env(t_data *data, int index)
{
	int j;

	j = 0;
	while (data->env[j])
	{
		ft_putstr_fd(data->env[j], data->pipes[index][1]);
		ft_putstr_fd("\n", data->pipes[index][1]);
		j++;
	}
}

char *ft_get_env_value(t_data *data, char *var_name) 
{
	//to get "HOME"=/usr/mparasku and return usr/mparasku
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

void ft_env_declare_x(t_data *data, int index)
{
	int i;
	char **temp_env;

	i = 0;
	temp_env = ft_copy_2d_arr(data);
	printf("%s\n", temp_env[0]);
	
	ft_free_2d(temp_env);
	index++;
}

char **ft_copy_2d_arr(t_data *data)
{
	int i;
	char **new_arr;

	i = 0;
	new_arr = malloc(sizeof(char *));
	if (new_arr == NULL)
		return (NULL);
	while (data->env[i])
	{
		new_arr[i] = ft_strdup(data->env[i]);
		if (new_arr[i] == NULL)
			return (NULL);
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}