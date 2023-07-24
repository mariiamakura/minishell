/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:29:31 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/24 14:51:15 by mparasku         ###   ########.fr       */
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
		pipe(data->pipes[i]); //++error handle to be added++
		i++;
	}
	return (data);
}


int start_pipes(t_data *data)
{
	int i;
	int j;
	
	i = 0;
	j = 0;

	data = init_pipes(data);
	i = 0;
	while (i < data->pipe_num + 1)
	{
		data->child_pid[i] = fork();
		if (data->child_pid[i] == 0)
		{
			if (i == 0) //the 1st cmd
			{
				dup2(data->pipes[i][1], STDOUT_FILENO); //1st cmd write to write end of pipe 0 and read from stdin
			}
			else if (i == data->pipe_num)
			{
				dup2(data->pipes[i - 1][0], STDIN_FILENO); //last cmd reads from last cmd read end and write to stdout
			}
			else 
			{
				dup2(data->pipes[i - 1][0], STDIN_FILENO); // cmd reads from last cmd read pipe (not stdin)
				dup2(data->pipes[i][1], STDOUT_FILENO); //cmd write to it's write end pipe (not stdout)
			}
			j = 0;
			while (j < data->pipe_num)
			{
				close(data->pipes[j][0]);
				close(data->pipes[j][1]);
				j++;
			}
			execve(data->tokens[i][0], data->tokens[i], NULL);
			perror("execve"); // Print an error message if execve fails
			exit(EXIT_FAILURE); 
		}
		i++;
	}
	i = 0;
	while (i < data->pipe_num)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
	int k = 0;
	while (k < i)
	{
		waitpid(data->child_pid[k], NULL, 0);
		k++;
	}
	i = 0;
	while (i < data->pipe_num)
	{
		free(data->pipes[i]);
		i++;
	}
	free(data->pipes);
	free(data->child_pid); 
	return (0);
}

//test : ls | echo hello | cat foo | grep l