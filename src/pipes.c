/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:29:31 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/27 11:55:15 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data *init_pipes(t_data * data)
{
	int i;

	data->child_pid = malloc(sizeof(int) * (data->pipe_num + 1)); //number of processes
	data->pipes = malloc(sizeof(int *) * data->pipe_num + 2); //the num of pipes + 2 
	i = 0;
	while (i <= data->pipe_num + 1)
	{
		data->pipes[i] = malloc(sizeof(int) * 2); //each pipe has read/write ends
		if (i == 0 || i == data->pipe_num + 1)
		{
			data->pipes[i][0] = 0;
			data->pipes[i][1] = 1;
		}
		else 
		{
			if(pipe(data->pipes[i]) != 0)
			{
				free_wflags(data, i, NOT_FINISHED);
				return (NULL);
			}
		} 
		i++;
	}
	ft_parse_redir(data);
	return (data);
}

int start_pipes(t_data *data)
{
	int i;
	
	i = 0;
	data = init_pipes(data);
	if (data == NULL)
		return (-1); //maybe return data?
	i = 0;
	while (i <= data->pipe_num)
	{
		data->child_pid[i] = fork();
		if (data->child_pid[i] == 0)
		{
			dup2(data->pipes[i][0], STDIN_FILENO); // cmd reads from last cmd read pipe (not stdin)
			dup2(data->pipes[i + 1][1], STDOUT_FILENO); //cmd write to it's write end pipe (not stdout)
			close_fd(data);
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
	//close_fd(data);
	wait_children(data); //return the last child process exit status
	//close_fd(data);
	free_wflags(data, i, FINISHED); //mb do it in the end if data is still needed after pipes
	return (0);
}

//test : ls | echo hello | cat foo | grep l