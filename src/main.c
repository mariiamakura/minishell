/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:47:20 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/25 16:51:53 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	//char *input;
	//signal(SIGQUIT, sig_handler);
	t_data	*data;

	data = malloc(sizeof(t_data *));
	if (data == NULL)
		return (-1);
	while (1)
	{
		ft_parse(data);
		start_pipes(data);
	}
}
