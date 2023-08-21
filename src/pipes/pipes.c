/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:29:31 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/21 13:10:29 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_pipes(t_data *data)
{
	int	i;

	i = 0;
	data->child_pid = malloc(sizeof(int) * (data->pipe_num + 1));
	data->pipes = malloc(sizeof(int *) * (data->pipe_num + 1));
	while (i <= data->pipe_num)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		if ((i == 0 && data->pipe_num == 0) || i == data->pipe_num)
		{
			data->pipes[i][0] = STDIN_FILENO;
			data->pipes[i][1] = STDOUT_FILENO;
			break ;
		}
		if (pipe(data->pipes[i]) != 0)
		{
			free_wflags(data, i, NOT_FINISHED);
			data->error_flags[i] = TRUE;
			return (-1);
		}
		i++;
	}
	return (0);
}

void	ft_run_one_buildin(t_data *data)
{
	data->forked = FALSE;
	if (data->error_flags[0] == TRUE)
		g_last_exit = errno;
	else
	{
		ft_run_builtin(data, 0);
		close_fd(data);
	}
}

int	ft_child_configur(t_data *data, int i)
{
	data->child_pid[i] = fork();
	signal(SIGINT, sig_handler_parent);
	if (data->child_pid[i] == 0)
	{
		if (ft_run_child(data, i) == -1)
			return (-1);
	}
	return (0);
}

int	ft_run_child(t_data *data, int i)
{
	signal(SIGINT, sig_handler_child);
	if (data->error_flags[i] == TRUE)
		exit (errno);
	if (ft_strlen(data->tokens[i][0]) == 0)
		exit (0);
	if (ft_is_builtin(data->tokens[i][0]) == TRUE)
	{
		ft_run_builtin(data, i);
		exit (0);
	}
	dup2(data->pipes[i][1], STDOUT_FILENO);
	if (i == 0)
		dup2(data->pipes[data->pipe_num][0], STDIN_FILENO);
	else
		dup2(data->pipes[i - 1][0], STDIN_FILENO);
	close_fd(data);
	if (execve(data->tokens[i][0], data->tokens[i], data->env) == -1)
	{
		perror("execve failed");
		//printf("erro: %d\n", errno);
		//term_processes(data);
		//free_wflags(data, i, FINISHED);
		return (errno);
	}
	return (0);
}

int	start_pipes(t_data *data)
{
	int	i;

	i = 0;
	if (data == NULL)
		return (-1);
	if (data->pipe_num == 0 && ft_is_builtin(data->tokens[0][0]) == TRUE)
		ft_run_one_buildin(data);
	else
	{
		data->forked = TRUE;
		signal(SIGINT, sig_handler_parent);
		while (i <= data->pipe_num)
		{
			if (ft_child_configur(data, i) == -1)
				return (-1);
			i++;
		}
		close_fd(data);
		wait_children(data);
	}
	if (g_last_exit == 130)
		term_processes(data);
	return (0);
}
