/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:11:45 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/24 18:18:59 by mparasku         ###   ########.fr       */
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
		while (j < i - 1)
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


void wait_children(t_data *data, int i)
{
    int k;
    int status;

    k = 0;
    while (k < i)
    {
        waitpid(data->child_pid[k], &status, 0);
        // if (WIFEXITED(status))
        // {
        //     int exit_status = WEXITSTATUS(status);
        //     printf("Child process %d exited with status: %d\n", k, exit_status);
        // }
        // else
        // {
        //     printf("Child process %d terminated abnormally\n", k);
        // }
        k++;
    }
}