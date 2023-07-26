/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:05:44 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/26 18:29:29 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_redir_out(char *str, int block, t_data *data)
{
	int	i;
	int	fd;

	i = 1;
	while (str[i] == ' ')
		i++;
	fd = open(str + i, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	data->pipes[block][1] = fd;
}

void	ft_remove_arg(t_data *data, int block, int arg)
{
	char *temp;

	temp = data->tokens[block][arg];
	while (data->tokens[block][arg + 1])
	{
		data->tokens[block][arg] = data->tokens[block][arg + 1];
		arg++;
	}
	data->tokens[block][arg] = NULL;
	free(temp);
}

int	ft_add_path(int i, t_data *data)
{
	char *temp;
	char *path;

	path = "/bin/";

	temp = data->tokens[i][0];
	data->tokens[i][0] = malloc(sizeof(char) * (ft_strlen(data->tokens[i][0]) + ft_strlen(path) + 1));
	ft_memmove(data->tokens[i][0], path, ft_strlen(path));
	ft_memmove(data->tokens[i][0] + ft_strlen(path), temp, ft_strlen(data->tokens[i][0]) +  1);
	free(temp);
	return (0);
}

void	ft_parse_redir(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i <= data->pipe_num)
	{
		j = 0;
		while (data->tokens[i][j])
		{
			if (data->tokens[i][j][0] == '>')
			{
				ft_redir_out(data->tokens[i][j], i, data);
				ft_remove_arg(data, i, j);
			}
			j++;
		}
		ft_add_path(i, data);
		i++;
	}
}