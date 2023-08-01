/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:35:32 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/31 16:56:16 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static void	ft_free_path(char *funct_name, char **path_env)
{
	int	i;

	i = 0;
	while (path_env[i])
	{
		free(path_env[i]);
		i++;
	}
	free(path_env);
	free(funct_name);
}

void	ft_add_path(int block, t_data *data)
{
	char	**path_env;
	char	*path_str;
	char	*test;
	char	*funct_name;
	int		i;

	funct_name = ft_strjoin("/", data->tokens[block][0]); //adding '/' before function name
	path_str = ft_getenv(data->env, "PATH");
	path_env = ft_split(path_str, ':');
	i = 0;
	while (path_env[i])
	{
		test = ft_strjoin(path_env[i], funct_name);
		if (access(test, F_OK) == 0)
		{
			free(data->tokens[block][0]);
			data->tokens[block][0] = test;
			break ; //don t free test
		}
		free(test);
		i++;
	}
	ft_free_path(funct_name, path_env);
}
