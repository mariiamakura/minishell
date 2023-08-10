/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:22:24 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/10 15:46:33 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_exit(char *av[], t_data *data)
{
	int i;
	int is_number;
	long long exit_status;
	char *error;

	i = 0;
	is_number = TRUE;
	if (ft_count_arg(av) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		last_exit_global = 1;
		return (last_exit_global);
	}
	if (av[1] != NULL)
	{
		while (av[1][i])
		{
			if(ft_isdigit(av[1][i]) == FALSE)
				is_number = FALSE;
			i++;
		}
		exit_status = ft_atoi(av[1]);
		if (exit_status > INT_MAX || exit_status < INT_MIN)
			is_number = FALSE;
	}
	if (is_number == FALSE)
	{
		error = ft_strjoin("minishell: exit: numeric argument required: ", av[1]);
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free(error);
		exit (2);
	}
	write(1, "exit\n", 5);
	rl_clear_history();
	ft_free_tokens(data);
	free(data->error_flags);
	free_wflags(data, data->pipe_num, FINISHED); 
	ft_free_2d(data->env);
	free(data);
	exit(0);
}