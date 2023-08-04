/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulitins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:19:33 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/04 16:00:27 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_builtin(char *str)
{
	if (ft_strncmp("echo", str, ft_strlen(str)) == 0
		|| ft_strncmp("cd", str, ft_strlen(str)) == 0
		|| ft_strncmp("pwd", str, ft_strlen(str)) == 0
		|| ft_strncmp("export", str, ft_strlen(str)) == 0
		|| ft_strncmp("unset", str, ft_strlen(str)) == 0
		|| ft_strncmp("env", str, ft_strlen(str)) == 0
		|| ft_strncmp("exit", str, ft_strlen(str)) == 0)
		return (TRUE);
	else
		return (FALSE);
}

void    ft_run_builtin(t_data *data, int i)
{
    if (ft_strncmp("echo", data->tokens[i][0], ft_strlen(data->tokens[i][0])) == 0)
    {
		ft_echo(data->tokens[i], data, i);
	}
    if (ft_strncmp("cd", data->tokens[i][0], ft_strlen(data->tokens[i][0])) == 0)
	{
        ft_cd(data->tokens[i], data, i);
	}
	if (ft_strncmp("env", data->tokens[i][0], ft_strlen(data->tokens[i][0])) == 0)
	{
		ft_env(data, i);
	}
	if (ft_strncmp("export", data->tokens[i][0], ft_strlen(data->tokens[i][0])) == 0)
	{
		ft_export(data->tokens[i], data, i);
	}
}

void ft_free_2d(char **av)
{
	int i;

	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}