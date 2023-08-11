/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:55:54 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/11 18:20:44 by mparasku         ###   ########.fr       */
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

void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void ft_declare_x(t_data *data, int index)
{
	char	**tm;
	int		size;

	tm = ft_copy_2d_arr(data->env);
	size = ft_count_arg(data->env);

	
}

int	ft_env_declare_x(t_data *data, int index)
{
	int		i;
	//char	**tm;
	int		sort_flag;
	//int		size;

	//tm = ft_copy_2d_arr(data->env);
	sort_flag = FALSE;
	//size = ft_count_arg(data->env);
	while (sort_flag != TRUE)
	{
		sort_flag = TRUE;
		i = 0;
		while (i < size - 1)
		{
			if (ft_strncmp(tm[i], tm[i + 1], ft_strlen(tm[i])) > 0)
			{
				swap(&tm[i], &tm[i + 1]);
				sort_flag = FALSE;
			}
			i++;
		}
		size--;
	}
	print_declare_x(tm, index, data);
	ft_free_2d(tm);
	return (0);
}

void	print_declare_x(char **temp_env, int index, t_data *data)
{
	int	i;

	i = 0;
	while (temp_env[i])
	{
		ft_putstr_fd("declare -x ", data->pipes[index][1]);
		ft_putstr_fd(temp_env[i], data->pipes[index][1]);
		ft_putstr_fd("\n", data->pipes[index][1]);
		i++;
	}
}
