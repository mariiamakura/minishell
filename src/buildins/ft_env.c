/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:55:54 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/14 15:20:23 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(char *av[], t_data *data, int index)
{
	int		j;
	char	*error;

	j = 0;
	if (av[1] != NULL)
	{
		error = ft_strjoin("minishell: env: Permission denied: ", av[1]);
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free(error);
		return (127);
	}
	while (data->env[j])
	{
		ft_putstr_fd(data->env[j], data->pipes[index][1]);
		ft_putstr_fd("\n", data->pipes[index][1]);
		j++;
	}
	return (0);
}

char	*ft_get_env_value(t_data *data, char *var_name)
{
	int		i;
	char	*new_str;
	char	*res;

	i = 0;
	new_str = NULL;
	res = NULL;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var_name, ft_strlen(var_name)) == 0)
		{
			new_str = ft_strdup(data->env[i]);
			res = ft_strchr(new_str, '=');
			if (res)
			{
				res = ft_strdup(res + 1);
				free(new_str);
				return (res);
			}
		}
		free(new_str);
		new_str = NULL;
		i++;
	}
	return (NULL);
}
