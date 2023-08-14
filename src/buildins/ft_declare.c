/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_declare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:17:29 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/14 15:20:08 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	ft_declare_x(t_data *data, int index)
{
	char	**tm;
	int		size;

	tm = ft_copy_2d_arr(data->env);
	size = ft_count_arg(data->env);
	ft_env_declare_sort(tm, size);
	print_declare_x(tm, index, data);
	ft_free_2d(tm);
	return (0);
}

int	ft_env_declare_sort(char **tm, int size)
{
	int	i;
	int	sort_flag;

	sort_flag = FALSE;
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
