/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:47:20 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/15 12:11:48 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//t_global *g_global;
int	last_exit_global;

void	ft_free_tokens(t_data *data)
{
	int i;
	int	j;

	i = 0;
	while (i < data->pipe_num + 1)
	{
		j = 0;
		while (data->tokens[i][j])
		{
			free(data->tokens[i][j]);
			j++;
		}
		free(data->tokens[i]);
		i++;
	}
	free(data->tokens);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;
	
	if (argc != 1 || !argv[0]) //programm should be run without arguments (only env)
	 return (1);

	data = malloc(sizeof(t_data));
	data->forked = FALSE;
	if (data == NULL)
		return (1);
	data->env = ft_copy_2d_arr(envp);
	last_exit_global = 0;
	init_signals();
	while (1) 
	{
		init_signals();
		if (0 <= ft_parse(data))
		{
			init_pipes(data);
			ft_lexer(data);
			start_pipes(data);
			ft_free_tokens(data);
			free(data->error_flags);
			free_wflags(data, data->pipe_num, FINISHED); //mb do it in the end if data is still needed after pipes
		}
	}
	//print_tokens(data);
	//printf("%d\n", execve(data->tokens[0][0], data->tokens[0], NULL));
}
