/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:22:32 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/21 11:30:06 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_red_err(t_data *data, int block, char c)
{
	int	i;

	i = 0;
	while (i <= data->pipe_num)
	{
		data->error_flags[i] = TRUE;
		i++;
	}
	if (c == '\0')
	{
		if (block == data->pipe_num)
			ft_putstr_fd("minishell: syntax error near unexpected token " \
			"`newline'\n", 2);
		else 
			ft_putstr_fd("minishell: syntax error near unexpected token " \
			"`|'\n", 2);
	}
	if (c == '>')
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
	if (c == '<')
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
	errno = 2;
	return (-1);
}

void	ft_remove_arg(t_data *data, int block, int arg)
{
	char	*temp;

	temp = data->tokens[block][arg];
	while (data->tokens[block][arg + 1])
	{
		data->tokens[block][arg] = data->tokens[block][arg + 1];
		arg++;
	}
	data->tokens[block][arg] = NULL;
	free(temp);
}
