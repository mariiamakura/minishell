/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:11:45 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/16 14:23:42 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_wflags(t_data *data, int i, int flag)
{
	int	j;

	j = 0;
	if (flag == NOT_FINISHED)
	{
		while (j < i)
		{
			free(data->pipes[j]);
			j++;
		}
	}
	else
	{
		while (j <= data->pipe_num)
		{
			free(data->pipes[j]);
			j++;
		}
	}
	free(data->pipes);
	free(data->child_pid);
}

void	close_fd(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->pipe_num)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
}

void	term_processes(t_data *data)
{
	int	j;

	j = 0;
	if (data->forked == TRUE)
	{
		while (j <= data->pipe_num)
		{
			kill(data->child_pid[j], SIGTERM);
			j++;
		}
	}
}

void	wait_children(t_data *data)
{
	int		k;
	int		status;
	pid_t	pid;

	k = 0;
	while (k <= data->pipe_num)
	{
		pid = wait(&status);
		if (pid == data->child_pid[data->pipe_num] && g_last_exit != 130)
		{
			if (data->error_flags[data->pipe_num] == TRUE)
				g_last_exit = errno;
			else if (status != 0)
				g_last_exit = status % 255;
			else
				g_last_exit = 0;
		}
		k++;
	}
}
