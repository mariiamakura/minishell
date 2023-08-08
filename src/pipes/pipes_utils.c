/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:11:45 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/08 09:09:12 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_wflags(t_data *data, int i, int flag)
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
		while (j < i)
		{
			free(data->pipes[j]);
			j++;
		}
	}
	free(data->pipes);
	free(data->child_pid);
	//free(data); -free where it was malloc or in main
}

void close_fd(t_data *data)
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

void term_processes(t_data * data)
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
	data->last_exit = 130;
	//last_exit_global = 0;
}

void wait_children(t_data *data)
{
	int k;
	int status;
	pid_t	pid;

	k = 0;
	while (k <= data->pipe_num)
	{
		pid = wait(&status);
		//printf("pid: %d  exit: %d\n", pid, status);
		if (pid == data->child_pid[data->pipe_num])
		{
			data->last_exit = status;
		//printf("last-pid: %d  exit: %d\n", pid, status);
		}
		k++;
	}
}
