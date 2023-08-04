/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:47:20 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/04 14:29:36 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_global *g_global;

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
	init_signals();
	if (data == NULL)
		return (1);
	data->env = envp;
	data->last_exit = 0;
	while (1) 
	{
		if (0 <= ft_parse(data))
		{
			start_pipes(data);
			ft_free_tokens(data);
		}
	}
	free(data);
	//print_tokens(data);
	//printf("%d\n", execve(data->tokens[0][0], data->tokens[0], NULL));
}
