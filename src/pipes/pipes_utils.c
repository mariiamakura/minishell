/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:11:45 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/15 13:08:42 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_wflags(t_data *data, int i, int flag)
{
	int	j;

	j = 0;
	if (flag == NOT_FINISHED)
	{
		while (j < i) //not sure about < or <=
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
		if (pid == data->child_pid[data->pipe_num] && last_exit_global != 130)
		{	
			if (data->error_flags[data->pipe_num] == TRUE) //|| status != 0)
				last_exit_global = errno;
			else if (status != 0)
				last_exit_global = status - 255;
			else
				last_exit_global = 0;
		}
		k++;
	}
}
