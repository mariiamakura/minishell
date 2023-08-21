/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:27:39 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/21 10:12:55 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_all_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' || str[i] != '	')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_ctrl_d(t_data *data)
{
	write(1, "exit\n", 5);
	rl_clear_history();
	ft_free_2d(data->env);
	free(data);
	exit(0);
}

int	ft_parse_init(t_data *data, char *input)
{
	int	i;

	if (input == NULL)
		ft_ctrl_d(data);
	if (ft_all_whitespace(input) == TRUE || *input == '\0')
	{
		g_last_exit = 0;
		free(input);
		return (-1);
	}
	add_history(input);
	data->pipe_num = ft_count_pipes(input);
	data->error_flags = ft_calloc(data->pipe_num + 1, sizeof(int));
	if (data->error_flags == NULL)
		exit (1);
	i = 0;
	while (i <= data->pipe_num)
	{
		data->error_flags[i] = FALSE;
		i++;
	}
	data->tokens = ft_calloc((data->pipe_num + 1), sizeof(char **));
	if (data->tokens == NULL)
		exit (1);
	return (0);
}

int	ft_parse(t_data *data)
{
	int				i;
	int				argc;
	unsigned long	start;
	char			*input;
	char			*sub_str;

	rl_getc_function = rl_getc;
	input = readline(" ~ minishell$ ");
	if (ft_parse_init(data, input) != 0)
		return (-1);
	i = 0;
	start = 0;
	while (i <= data->pipe_num)
	{
		sub_str = ft_substr_pipe(input, &start);
		argc = ft_count_args(sub_str);
		data->tokens[i] = ft_calloc(sizeof(char *), argc + 1);
		if (data->tokens[i] == NULL)
			exit (1);
		ft_split_sub(sub_str, i, data);
		data->tokens[i][argc] = NULL;
		free(sub_str);
		i++;
	}
	return (free(input), 0);
}
