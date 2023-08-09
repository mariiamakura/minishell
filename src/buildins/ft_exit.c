/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:22:24 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/09 17:25:19 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_exit(t_data *data)
{
	write(1, "exit\n", 5);
	rl_clear_history();
	ft_free_tokens(data);
	free(data->error_flags);
	free_wflags(data, data->pipe_num, FINISHED); 
	ft_free_2d(data->env);
	free(data);
	exit(-1);
}