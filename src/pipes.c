/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:29:31 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/21 17:38:36 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void start_pipes(t_data *data)
{
	int pipefd[2];
	int i;
	
	i = 0;
	pipe(pipefd);
	data->child_pid = malloc(sizeof(int) * data->pipe_num + 1);
	while (i < data->pipe_num + 1)
	{
		data->child_pid[i] = fork();
		if (data->child_pid[i] == 0 && i + 1 < data->pipe_num + 1) 
		{
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
			execve(data->tokens[i][0], data->tokens[i], NULL);
		}
		if (data->child_pid[i] == 0 && i + 1 == data->pipe_num + 1) 
		{
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
			execve(data->tokens[i][0], data->tokens[i], NULL);
		}
		i++;
	}
	close(pipefd[0]);
	close(pipefd[1]);
	int k = 0;
	while (k < i)
	{
		waitpid(data->child_pid[k], NULL, 0);
		k++;
	}
	return ;
}