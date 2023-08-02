/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:29:31 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/02 17:37:33 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_pipes(t_data * data)
{
	int i;
	int	ret;

	i = 0;
	data->child_pid = malloc(sizeof(int) * (data->pipe_num + 1)); //number of processes
	data->pipes = malloc(sizeof(int *) * (data->pipe_num + 1)); //the num of pipes + 1 (num of processes)
	while (i <= data->pipe_num)
	{
		data->pipes[i] = malloc(sizeof(int) * 2); //each pipe has read/write ends
		if ((i == 0 && data->pipe_num == 0) || i == data->pipe_num) //for single process or the last process
		{
			data->pipes[i][0] = STDIN_FILENO;
			data->pipes[i][1] = STDOUT_FILENO;
			break ;
		}
		if(pipe(data->pipes[i]) != 0)
		{
			free_wflags(data, i, NOT_FINISHED);
			return (-1);
		}
		i++;
	}
	if ((ret = ft_lexer(data) != 0))
		return (ret);
	return (0);
}

int start_pipes(t_data *data)
{
	int i;
	int	ret;
	
	i = 0;
	if ((ret = init_pipes(data)) != 0)
		return (data->last_exit = ret, ret);
	if (data == NULL)
		return (-1); //maybe return data?
	if (data->pipe_num == 0 && ft_is_builtin(data->tokens[0][0]) == TRUE)//add ft_is_builtin to add_path
	{
		g_global->forked = FALSE;
		ft_run_builtin(data);
		close_fd(data);
	}
	else
	{
		g_global->forked = TRUE;
		i = 0;
		while (i <= data->pipe_num)
		{
			data->child_pid[i] = fork();
			if (data->child_pid[i] == 0)
			{
				dup2(data->pipes[i][1], STDOUT_FILENO); //cmd write to it's write end pipe (not stdout)
				if (i == 0)
					dup2(data->pipes[data->pipe_num][0], STDIN_FILENO); //using the pipe[pipe_num][0] for input in first child
				else 
					dup2(data->pipes[i - 1][0], STDIN_FILENO); // cmd reads from last cmd read pipe (not stdin)
				close_fd(data);
				if (execve(data->tokens[i][0], data->tokens[i], data->env) == -1)
				{
					perror("execve failed");
					term_processes(data);
					free_wflags(data, i, FINISHED);
					return (-1);
				}
			}
			i++;
		}
		close_fd(data);
		wait_children(data); //return the last child process exit status
	}
	if (g_global->c_kill_child == TRUE)
	{
		term_processes(data);
	}
	free_wflags(data, i, FINISHED); //mb do it in the end if data is still needed after pipes
	return (0);
}

//test : ls | echo hello | cat foo | grep l