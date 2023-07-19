/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:47:20 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/19 17:28:13 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data	*data;
	char *input;
	
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (1);
	input = readline(NULL);
	ft_parse(input, data);
	printf("num pipes: %i", data->pipe_num);
	//execve(ft_strjoin("/bin/", tokens[0]), tokens, NULL);
	free(input);
}
