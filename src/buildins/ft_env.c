/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:55:54 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/03 17:13:34 by mparasku         ###   ########.fr       */
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

char *get_env_value(t_data *data, char *var_name) 
{
	//to get "HOME"=/usr/mparasku and return usr/mparasku
	int i;
	char *new_str;

	i = 0;
	new_str = NULL;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var_name, ft_strlen(var_name)) == 0)
		{
			new_str = ft_strdup(data->env[i]);
			new_str = ft_strchr(new_str, '=');
			if (new_str == 0)
			{
				free(new_str);
				return (NULL);
			}
			else
			{
				return (ft_strdup(new_str + 1));
			}
				
		}
		free(new_str);
		i++;
	}
	return (NULL);
}

