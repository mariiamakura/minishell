/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:47:20 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/20 20:15:23 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data	*data;
	
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (1);
	ft_parse(data);
	/* int i = 0;
	int j;
	while (i <= data->pipe_num)
	{
		j = 0;
		while (j < 2)
		{
			printf("%sEND\n", data->tokens[i][j]);
			j++;
		}
		printf("\n");
		i++;
	} */
	//printf("num pipes: %i", data->pipe_num);
	//execve(ft_strjoin("/bin/", tokens[0]), tokens, NULL);
}
