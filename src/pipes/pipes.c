/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:29:31 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/03 14:14:50 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_pipes(t_data * data)
{
	int i;

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
	ft_lexer(data);
	return (0);
}

int start_pipes(t_data *data)
{
	int i;
	
	i = 0;
	init_pipes(data);
	if (data == NULL)
		return (-1); //maybe return data?
	if (data->pipe_num == 0 && ft_is_builtin(data->tokens[0][0]) == TRUE)//add ft_is_builtin to add_path
	{
		g_global->forked = FALSE;
		if (data->error_flags[0] == TRUE)
			data->last_exit = errno;
		else
		{
			ft_run_builtin(data, 0);
			close_fd(data);
			data->last_exit = 0;
		}
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
				if (data->error_flags[i] == TRUE)
					exit (errno);
				dup2(data->pipes[i][1], STDOUT_FILENO); //cmd write to it's write end pipe (not stdout)
				if (i == 0)
					dup2(data->pipes[data->pipe_num][0], STDIN_FILENO); //using the pipe[pipe_num][0] for input in first child
				else
					dup2(data->pipes[i - 1][0], STDIN_FILENO); // cmd reads from last cmd read pipe (not stdin)
				close_fd(data);
				if (ft_is_builtin(data->tokens[i][0]) == TRUE)
				{
					ft_run_builtin(data, i);
					exit (0);
				}
				else if (execve(data->tokens[i][0], data->tokens[i], data->env) == -1)
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