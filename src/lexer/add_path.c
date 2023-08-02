/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:35:32 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/02 17:16:00 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_getenv(char *envp[], char *var_name)
{
	int		i;
	int		var_len;

	var_len = ft_strlen(var_name);
	i = 0;
	while(envp[i])
	{
		if (ft_strncmp(envp[i], var_name, var_len) == 0 && envp[i][var_len] == '=')
			return (&envp[i][var_len + 1]);
		i++;
	}
	return (NULL);
}

static void	ft_free_path(char **path_env)
{
	int	i;

	i = 0;
	while (path_env[i])
	{
		free(path_env[i]);
		i++;
	}
	free(path_env);
}

int	ft_add_path(int block, t_data *data)
{
	char	**path_env;
	char	*path_str;
	char	*test;
	char	*funct_name;
	int		i;

	if (ft_is_builtin(data->tokens[block][0]) == TRUE)
		return (0);
	if (data->tokens[block][0][0] == '.' && data->tokens[block][0][1] == '/')
	{
		if (access(data->tokens[block][0], F_OK) == 0 && access(data->tokens[block][0], X_OK) == 0)
			return (0);
		funct_name = ft_strjoin("/", data->tokens[block][0] + 2);
	}
	else
	{
		funct_name = ft_strjoin("/", data->tokens[block][0]); //adding '/' before function name
		path_str = ft_getenv(data->env, "PATH");
		path_env = ft_split(path_str, ':');
		i = 0;
		while (path_env[i])
		{
			test = ft_strjoin(path_env[i], funct_name);
			if (access(test, F_OK) == 0)
			{
				if (access(test, X_OK) == 0) //checks if file is exectuable
				{
					free(data->tokens[block][0]);
					ft_free_path(path_env);
					free(funct_name);
					data->tokens[block][0] = test;
					return (0);
				}
			}
			free(test);
			i++;
		}
		ft_free_path(path_env);
	}
	test = ft_strjoin(funct_name + 1, " : command not found\n");
	ft_putstr_fd(test, 2);	
	free(test);
	free(funct_name);
	return (127);
}
