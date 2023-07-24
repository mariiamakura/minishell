/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:47:20 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/24 23:33:57 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (1);
	ft_parse(data);
	
	int i = 0;
	int j = 0;
	while (i < data->pipe_num + 1)
	{
		while (data->tokens[i][j])
		{

			printf("%s\n", data->tokens[i][j]);
			j++;
		}
		//printf("null: %s\n", data->tokens[i][j]);
		i++;
	}
	printf("%s\n", data->tokens[0][0]);
	//print_tokens(data);
	//printf("%d\n", execve(data->tokens[0][0], data->tokens[0], NULL));
	//start_pipes(data);
}
