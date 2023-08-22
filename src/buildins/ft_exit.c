/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:22:24 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/22 15:11:19 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(char *av[], t_data *data)
{
	int	i;
	int	is_number;

	i = 0;
	is_number = TRUE;
	if (ft_count_arg(av) > 2)
	{
		ft_exit_error("too many arguments", "");
		return (1);
	}
	is_number = exit_error(av);
	if (is_number == FALSE)
	{
		ft_exit_error("numeric argument required: ", av[1]);
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

void	ft_exit_error(char *s1, char *s2)
{
	char	*error;

	error = ft_strjoin(s1, s2);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(error);
}

int	exit_error(char *av[])
{
	int			i;
	long long	exit_status;

	i = 0;
	exit_status = 0;
	if (av[1] != NULL)
	{
		while (av[1][i])
		{
			if (ft_isdigit(av[1][i]) == FALSE)
				return (FALSE);
			i++;
		}
		exit_status = ft_atoi(av[1]);
		if (exit_status > INT_MAX || exit_status < INT_MIN)
			return (FALSE);
	}
	return (TRUE);
}

void	ft_free_tokens(t_data *data)
{
	int	i;
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
