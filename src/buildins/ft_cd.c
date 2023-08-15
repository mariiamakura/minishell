/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:08:19 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/15 17:53:54 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cd(char *av[], t_data *data, int index)
{
	int		cur_gl;

	cur_gl = 0;
	if (av[1] == NULL)
		last_exit_global = ft_cd_only_home(data);
	else if (ft_strncmp(av[1], "~", ft_strlen("~")) == 0)
		last_exit_global = ft_cd_home(data, av[1]);
	else if (ft_strncmp(av[1], "-", ft_strlen(av[1])) == 0 
		&& ft_strlen(av[1]) == ft_strlen("-"))
	{
		last_exit_global = ft_cd_prev(data, index);
	}
	else
		last_exit_global = ft_go_to_dir(av[1]);
	cur_gl = last_exit_global;
	ft_update_pwd(data, index);
	return (cur_gl);
}

int	ft_cd_home(t_data *data, char *str)
{
	char	*home_dir;
	char	*dir;

	if (str[1] != '\0' && str[1] != '/')
		return (ft_error_cd(str));
	home_dir = ft_get_env_value(data, "HOME");
	if (home_dir == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (1);
	}
	chdir(home_dir);
	if (str[1] == '/' && str[2] != '\0')
	{
		dir = ft_strdup(str + 2);
		last_exit_global = ft_go_to_dir(dir);
		free(dir);
		free(home_dir);
		return (last_exit_global);
	}
	free(home_dir);
	return (0);
}

int	ft_go_to_dir(char *dir)
{
	char	*error;

	if (chdir(dir) != 0)
	{
		error = ft_strjoin("cd: ", dir);
		perror(error);
		free(error);
		return (1);
	}
	return (0);
}

int	ft_error_cd(char *str)
{
	char	*error;

	error = ft_strjoin("minishell: cd: ", str);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd(" : No such file or directory\n", STDERR_FILENO);
	free(error);
	return (1);
}

int	ft_cd_prev(t_data *data, int index)
{
	char	*prev_dir;

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
