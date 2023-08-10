/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:08:19 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/10 15:35:27 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_cd(char *av[], t_data *data, int index)
{
	char *dir;

	dir = NULL;
	if (av[1] == NULL || (ft_strncmp(av[1], "~", ft_strlen(av[1])) == 0 
			&& ft_strlen(av[1]) == ft_strlen("~")))
	{
		last_exit_global = ft_cd_home(data);
	}
	else if (ft_strncmp(av[1], "-", ft_strlen(av[1])) == 0 
			&& ft_strlen(av[1]) == ft_strlen("-"))
	{
		last_exit_global = ft_cd_prev(data, index);
	}
	else if (chdir(av[1]) != 0)
	{
		dir = ft_strjoin("cd: ", av[1]);
		perror(dir);
		free(dir);
		last_exit_global = 1;
		return(last_exit_global);
	}
	ft_update_pwd(data, index);
	return (last_exit_global);
}


int ft_cd_home(t_data *data)
{
	char *home_dir;

	home_dir = ft_get_env_value(data, "HOME");
	if (home_dir == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (1);
	}
	chdir(home_dir);
	free(home_dir);
	return (0);
}

int ft_cd_prev(t_data *data, int index)
{
	char *prev_dir;

	prev_dir = ft_get_env_value(data, "OLDPWD");
	if (prev_dir == NULL) 
	{
		free(prev_dir);
		ft_putstr_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (1);
	}
	chdir(prev_dir);
	ft_putstr_fd(prev_dir, data->pipes[index][1]);
	ft_putstr_fd("\n", data->pipes[index][1]);
	free(prev_dir);
	return (0);
}
