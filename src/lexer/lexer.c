/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:17:17 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/21 10:44:01 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_parse_var_loop(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i <= data->pipe_num)
	{
		j = 0;
		while (data->tokens[i][j])
		{
			ft_parse_var(i, j, data);
			j++;
		}
		i++;
		g_last_exit = 0;
	}
}

void	ft_lexer(t_data *data)
{
	int	i;
	int	j;

	ft_parse_var_loop(data);
	i = -1;
	while (++i <= data->pipe_num)
	{
		j = 0;
		while (data->tokens[i][j] && data->error_flags[i] != TRUE)
		{
			if (data->tokens[i][j][0] == '<' && data->tokens[i][j][1] == '<')
				ft_here_doc(data->tokens[i][j], i, j, data);
			else if (data->tokens[i][j][0] == '>'
				&& data->tokens[i][j][1] == '>')
				ft_redir_app(data->tokens[i][j], i, j, data);
			else if (data->tokens[i][j][0] == '>')
				ft_redir_out(data->tokens[i][j], i, j, data);
			else if (data->tokens[i][j][0] == '<')
				ft_redir_in(data->tokens[i][j], i, j, data);
			else 
				j++;
		}
		if (ft_strlen(data->tokens[i][0]) != 0 && data->error_flags[i] != TRUE)
			ft_add_path(i, data);
	}
}
