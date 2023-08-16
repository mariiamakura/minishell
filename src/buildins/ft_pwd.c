/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:31:44 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/16 15:05:44 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_data *data, int index)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_putstr_fd(cwd, data->pipes[index][1]);
		ft_putstr_fd("\n", data->pipes[index][1]);
		free(cwd);
		return (0);
	}
	else 
	{
		perror("minishell: getcwd: ");
		return (1);
	}
}

void	ft_update_pwd(t_data *data, int index)
{
	char	*current_pwd[3];
	char	*current_path;
	char	*current_temp;

	ft_update_oldpwd(data, index);
	current_temp = getcwd(NULL, 0);
	current_path = ft_strjoin("PWD=", current_temp);
	current_pwd[0] = "export";
	current_pwd[1] = current_path;
	current_pwd[2] = NULL;
	ft_export(current_pwd, data, index);
	free(current_temp);
	free(current_path);
}

void	ft_update_oldpwd(t_data *data, int index)
{
	char	*prev_temp;
	char	*prev;
	char	*av_old_pwd[3];

	prev_temp = ft_get_env_value(data, "PWD");
	prev = ft_strjoin("OLDPWD=", prev_temp);
	av_old_pwd[0] = "export";
	av_old_pwd[1] = prev;
	av_old_pwd[2] = NULL;
	ft_export(av_old_pwd, data, index);
	free(prev);
	free(prev_temp);
}

int	ft_cd_only_home(t_data *data)
{
	char	*home_dir;

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
