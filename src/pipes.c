/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:29:31 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/26 23:57:59 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data *init_pipes(t_data * data)
{
	int i;

	i = 0;
	data->child_pid = malloc(sizeof(int) * (data->pipe_num + 1)); //number of processes
	data->pipes = malloc(sizeof(int *) * data->pipe_num); //the num of pipes
	while (i < data->pipe_num)
	{
		data->pipes[i] = malloc(sizeof(int) * 2); //each pipe has read/write ends
		if(pipe(data->pipes[i]) != 0)
		{
			free_wflags(data, i, NOT_FINISHED);
			return (NULL);
		} 
		i++;
	}
	ft_parse_redir(data);
	return (data);
}

int one_cmd(t_data *data, int i)
{
	data->child_pid[i] = fork();
	if (data->child_pid[i] == 0)
	{
		if (execve(data->tokens[i][0], data->tokens[i], NULL) == -1)
		{
			perror("execve failed");
			term_processes(data, i);
			free_wflags(data, i, FINISHED);
			return (-1);
		}
		close_fd(data);
	}
	return (0);
}

int start_pipes(t_data *data)
{
	int i;
	
	i = 0;
	data = init_pipes(data);
	if (data == NULL)
		return (-1); //maybe return data?
	i = 0;
	if (data->pipe_num == 0)
	{
		if (one_cmd(data, i) == -1)
			return (-1);
	}
	while (i <= data->pipe_num && data->pipe_num > 0)
	{
		data->child_pid[i] = fork();
		if (data->child_pid[i] == 0)
		{
			if (i == 0) //the 1st cmd
			{
				dup2(data->pipes[i][1], STDOUT_FILENO); //1st cmd write to write end of pipe 0 and read from stdin
				close_fd(data);
			}
			else if (i == data->pipe_num) //the last cmd
			{
				dup2(data->pipes[i - 1][0], STDIN_FILENO); //last cmd reads from last cmd read end and write to stdout
				close_fd(data);
			}
			else 
			{
				dup2(data->pipes[i - 1][0], STDIN_FILENO); // cmd reads from last cmd read pipe (not stdin)
				dup2(data->pipes[i][1], STDOUT_FILENO); //cmd write to it's write end pipe (not stdout)
				close_fd(data);
			}
			if (execve(data->tokens[i][0], data->tokens[i], NULL) == -1)
			{
				perror("execve failed");
				term_processes(data, i);
				free_wflags(data, i, FINISHED);
				return (-1);
			}
		}
		i++;
	}
	close_fd(data);
	wait_children(data); //return the last child process exit status
	free_wflags(data, i, FINISHED); //mb do it in the end if data is still needed after pipes
	return (0);
}

//test : ls | echo hello | cat foo | grep l