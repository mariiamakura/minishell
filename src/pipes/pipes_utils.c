/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:11:45 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/03 15:08:03 by ycardona         ###   ########.fr       */
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
	g_global->c_kill_child = FALSE;
	//rl_replace_line("", 0);
	if (data->forked == FALSE)
	{
			rl_redisplay();
	}
	rl_on_new_line();
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
		if (pid == data->child_pid[data->pipe_num])
			data->last_exit = status;
		k++;
	}
}
