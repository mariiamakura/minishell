/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:17:17 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/02 17:56:35 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_lexer(t_data *data) //return open error
{
	int	i;
	int	j;
	int ret;

	i = 0;
	while (i <= data->pipe_num)
	{
		j = 0;
		while (data->tokens[i][j])
		{
			ft_parse_var(i, j, data);
			if (data->tokens[i][j][0] == '<' && data->tokens[i][j][1] == '<')
				ft_here_doc(data->tokens[i][j], i, j, data);
			else if (data->tokens[i][j][0] == '>' && data->tokens[i][j][1] == '>')
			{
				ret = ft_redir_app(data->tokens[i][j], i, j, data);
				// if (ret != 0)
				// 	break ;
			}
			else if (data->tokens[i][j][0] == '>')
			{
				ret = ft_redir_out(data->tokens[i][j], i, j, data);
				// if (ret != 0)
				// 	break ;
			}
			else if (data->tokens[i][j][0] == '<')
			{
				ret = ft_redir_in(data->tokens[i][j], i, j, data);
				// if (ret != 0)
				// 	break ;
			}
			else 
				j++;
		}
		ft_add_path(i, data);
		i++;
	}
	return (0);
}
