/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:08:19 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/08 14:37:56 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_cd(char *av[], t_data *data, int index)
{
	char *dir;

	dir = NULL;
	if (av[1] == NULL)
		ft_cd_home(data);
	else if (ft_strncmp(av[1], "-", ft_strlen(av[1])) == 0)
		ft_cd_prev(data, index);
	else if (chdir(av[1]) != 0)
	{
		dir = ft_strjoin("cd: ", av[1]);
		perror(dir);
		free(dir);
	}
	//char cwd[1024]; 
	//printf("%s\n", getcwd(cwd, sizeof(cwd)));
}

void ft_cd_home(t_data *data)
{
	char *home_dir;

	home_dir = ft_get_env_value(data, "HOME");
	if (home_dir != NULL)
		chdir(home_dir);
	free(home_dir);
}

void ft_cd_prev(t_data *data, int index)
{
	char *prev_dir;

	prev_dir = ft_get_env_value(data, "OLDPWD");
	if (prev_dir != NULL) 
	{
		chdir(prev_dir);
		ft_putstr_fd(prev_dir, data->pipes[index][1]);
		ft_putstr_fd("\n", data->pipes[index][1]);
	}
	else 
		perror("getenv:");
}

// need to be changed to update envp