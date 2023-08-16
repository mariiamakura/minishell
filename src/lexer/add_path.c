/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:35:32 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/16 16:06:34 by mparasku         ###   ########.fr       */
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
	return (" ");
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

int	ft_is_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	ft_check_rel_path(int block, t_data *data)
{
	char	*funct_name; 
	char	*path;

	path = ft_strjoin(ft_getenv(data->env, "PWD"), data->tokens[block][0] + 1);
	if (access(path, F_OK) == 0 && access(path, X_OK) == 0 &&  data->tokens[block][0][2] != '\0')
	{
		free(path);
		return (0);
	}
	free(path);
	funct_name = ft_strjoin("minishell: ", data->tokens[block][0]);
	if (data->tokens[block][0][2] == '\0')
	{
		path = ft_strjoin(funct_name, ": Is a directory\n");
		ft_putstr_fd(path, 2);
		free(path);
	}
	else
		perror(funct_name);
	if (errno == 13 || data->tokens[block][0][2] == '\0')
		errno = 126;
	else
		errno = 127;
	free(funct_name);
	data->error_flags[block] = TRUE;
	return (-1);
}

int	ft_is_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '/')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_check_path(int block, t_data *data)
{
	char	*funct_name;
	char	*err_msg; 

	if (access(data->tokens[block][0], F_OK) == 0 && access(data->tokens[block][0], X_OK) == 0
		&& ft_is_slash(data->tokens[block][0]) == FALSE)
		return (0);
	funct_name = ft_strjoin("minishell: ", data->tokens[block][0]);
	if (ft_is_slash(data->tokens[block][0]) == TRUE)
	{
		err_msg = ft_strjoin(funct_name, ": Is a directory\n");
		ft_putstr_fd(err_msg, 2);
		free(err_msg);
	}
	else
		perror(funct_name);
	free(funct_name);
	if (errno == 13 || ft_is_slash(data->tokens[block][0]) == TRUE)
		errno = 126;
	else
		errno = 127;
	data->error_flags[block] = TRUE;
	return (-1);
}

int	ft_check_cmd(char **path_env, char *funct_name, t_data *data, int block)
{
	int		i;
	char	*test;

	i = 0;
	while (path_env[i])
	{
		test = ft_strjoin(path_env[i], funct_name);
		if (access(test, F_OK) == 0 && access(test, X_OK) == 0)
		{
			free(data->tokens[block][0]);
			ft_free_path(path_env);
			free(funct_name);
			data->tokens[block][0] = test;
			return (0);
		}
		free(test);
		i++;
	}
	ft_free_path(path_env);
	free(funct_name);
	funct_name = ft_strjoin(data->tokens[block][0], ": command not found\n");
	ft_putstr_fd(funct_name, 2);
	free(funct_name);
	errno = 127;
	data->error_flags[block] = TRUE;
	return (1);
}

int	ft_add_path(int block, t_data *data)
{
	char	**path_env;
	char	*path_str;
	char	*funct_name; 

	if (data->tokens[block][0] == NULL)
	{
		data->error_flags[block] = TRUE;
		return (-1);
	}
	else if (ft_is_builtin(data->tokens[block][0]) == TRUE)
		return (0);
	else if (data->tokens[block][0][0] == '.' && data->tokens[block][0][1] == '/')
		return (ft_check_rel_path(block, data));
	else if (ft_is_path(data->tokens[block][0]) == TRUE)
		return (ft_check_path(block, data));
	else
	{
		funct_name = ft_strjoin("/", data->tokens[block][0]); //adding '/' before function name
		path_str = ft_getenv(data->env, "PATH");
		path_env = ft_split(path_str, ':');
		return (ft_check_cmd(path_env, funct_name, data, block));
	}		
}
