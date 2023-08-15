/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulitins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:19:33 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/15 13:41:18 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_builtin(char *str)
{
	if (str == NULL)
		return (FALSE);
	if ((ft_strncmp("echo", str, ft_strlen(str)) == 0 
			&& ft_strlen("echo") == ft_strlen(str))
		|| (ft_strncmp("cd", str, ft_strlen(str)) == 0 
			&& ft_strlen("cd") == ft_strlen(str))
		|| (ft_strncmp("pwd", str, ft_strlen(str)) == 0 
			&& ft_strlen("pwd") == ft_strlen(str))
		|| (ft_strncmp("export", str, ft_strlen(str)) == 0 
			&& ft_strlen("export") == ft_strlen(str))
		|| (ft_strncmp("unset", str, ft_strlen(str)) == 0 
			&& ft_strlen("unset") == ft_strlen(str))
		|| (ft_strncmp("env", str, ft_strlen(str)) == 0 
			&& ft_strlen("env") == ft_strlen(str))
		|| (ft_strncmp("exit", str, ft_strlen(str)) == 0 
			&& ft_strlen("exit") == ft_strlen(str)))
		return (TRUE);
	else
		return (FALSE);
}

int	ft_run_builtin(t_data *data, int i)
{
	if (ft_strncmp("echo", data->tokens[i][0], 
		ft_strlen(data->tokens[i][0])) == 0)
		last_exit_global = ft_echo(data->tokens[i], data, i);
	else if (ft_strncmp("cd", data->tokens[i][0],
		ft_strlen(data->tokens[i][0])) == 0)
		last_exit_global = ft_cd(data->tokens[i], data, i);
	else if (ft_strncmp("env", data->tokens[i][0],
		ft_strlen(data->tokens[i][0])) == 0)
		last_exit_global = ft_env(data->tokens[i], data, i);
	else if (ft_strncmp("export", data->tokens[i][0],
		ft_strlen(data->tokens[i][0])) == 0)
		last_exit_global = ft_export(data->tokens[i], data, i);
	else if (ft_strncmp("pwd", data->tokens[i][0],
		ft_strlen(data->tokens[i][0])) == 0)
		last_exit_global = ft_pwd(data, i);
	else if (ft_strncmp("unset", data->tokens[i][0],
		ft_strlen(data->tokens[i][0])) == 0)
		ft_unset(data->tokens[i], data);
	else if (ft_strncmp("exit", data->tokens[i][0],
		ft_strlen(data->tokens[i][0])) == 0)
		last_exit_global = ft_exit(data->tokens[i], data);
	return (last_exit_global);
}

int	ft_print_error_buildins(char *s1, char *s2)
{
	char	*error;

	error = ft_strjoin(s1, s2);
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(error);
	last_exit_global = 1;
	return (last_exit_global);
}

void	ft_free_2d(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}

char	**ft_copy_2d_arr(char **env)
{
	int		i;
	char	**new_arr;

	i = 0;
	while (env[i])
		i++;
	new_arr = malloc(sizeof(char *) * (i + 1));
	if (new_arr == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_arr[i] = ft_strdup(env[i]);
		if (new_arr[i] == NULL)
		{
			ft_free_2d(new_arr);
			return (NULL);
		}
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}
