/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:47:20 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/25 17:01:50 by ycardona         ###   ########.fr       */
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

int	main(void)
{
	//char *input;
	//signal(SIGQUIT, sig_handler);
	t_data	*data;

	data = malloc(sizeof(t_data *));
	if (data == NULL)
		return (1);
	ft_parse(data);
	int j;
	int i = 0;
	//printf("new ----- START%sEND   ", data->tokens[0][0]);
	while (i < data->pipe_num + 1)
	{
		j = 0;
		while (data->tokens[i][j])
		{
			printf("START%sEND\n", data->tokens[i][j]);
			j++;
		}
		printf("null: %s\n", data->tokens[i][j]);
		i++;
	}
	ft_free_tokens(data);
	free(data);
	//print_tokens(data);
	//printf("%d\n", execve(data->tokens[0][0], data->tokens[0], NULL));
	//start_pipes(data);
}
