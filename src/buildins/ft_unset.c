/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:58:55 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/09 15:04:01 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_unset(char *av[], t_data *data, int index)
{
	char **var_names;
	int i;
	int arg_num;

	var_names = NULL;
	i = 0;
	arg_num = ft_count_arg(av);
	if (ft_count_arg(av) <= 1)
	{
		ft_putstr_fd("minishell: unset: not enough arguments\n", STDERR_FILENO);
		return;
	}
	index++;
	data->pipe_num++;
}