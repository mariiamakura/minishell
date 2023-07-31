/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:47:20 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/31 08:34:39 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	//char *input;
	//signal(SIGQUIT, sig_handler);
	if (argc != 1 || !argv[0]) //programm should be run without arguments (only env)
	 return (1);
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (1);
	data->env = envp;
	while (1) 
	{
		if (0 <= ft_parse(data))
		{
			/* int i = 0;
			int j;
			while (i <= data->pipe_num)
			{
				j = 0;
				while(data->tokens[i][j])
				{
					printf("tokens[%d][%d]: %s\n", i , j, data->tokens[i][j]);
					j++;
				}
					printf("tokens[%d][%d]: %s\n", i , j, data->tokens[i][j]);
				i++;
			} */
			start_pipes(data);
			ft_free_tokens(data);
		}
	}
	free(data);
	//print_tokens(data);
	//printf("%d\n", execve(data->tokens[0][0], data->tokens[0], NULL));
}
