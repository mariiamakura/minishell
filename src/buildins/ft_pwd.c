/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:31:44 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/11 17:21:01 by mparasku         ###   ########.fr       */
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

int	ft_update_pwd(t_data *data, int index)
{
	char	*current_pwd[3];
	char	*current_path;
	char	*current_temp;

	if (ft_update_oldpwd(data, index) != 0)
		return (1);
	current_temp = getcwd(NULL, 0);
	if (current_temp == NULL)
	{
		perror("minishell: getcwd: ");
		return (1);
	}
	current_path = ft_strjoin("PWD=", current_temp);
	current_pwd[0] = "export";
	current_pwd[1] = current_path;
	current_pwd[2] = NULL;
	ft_export(current_pwd, data, index);
	free(current_temp);
	free(current_path);
	return (0);
}

int	ft_update_oldpwd(t_data *data, int index)
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
	return (0);
}
