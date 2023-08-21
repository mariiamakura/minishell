/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:05:44 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/21 11:33:03 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_redir_out(char *str, int block, int arg, t_data *data)
{
	int		i;
	int		fd;
	char	*file_name;

	i = 1;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0' || str[i] == '>' || str[i] == '<')
		return (ft_red_err(data, block, str[i]));
	fd = open(str + i, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	data->pipes[block][1] = fd;
	if (fd == -1)
	{
		file_name = ft_strjoin("minishell: ", str + i);
		perror(file_name);
		free(file_name);
		ft_remove_arg(data, block, arg);
		data->error_flags[block] = TRUE;
		return (1);
	}
	ft_remove_arg(data, block, arg);
	return (0);
}

int	ft_redir_app(char *str, int block, int arg, t_data *data)
{
	int		i;
	int		fd;
	char	*file_name;

	i = 2;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0' || str[i] == '>' || str[i] == '<')
		return (ft_red_err(data, block, str[i]));
	fd = open(str + i, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	data->pipes[block][1] = fd;
	if (fd == -1)
	{
		file_name = ft_strjoin("minishell: ", str + i);
		perror(file_name);
		free(file_name);
		ft_remove_arg(data, block, arg);
		data->error_flags[block] = TRUE;
		return (1);
	}
	ft_remove_arg(data, block, arg);
	return (0);
}

int	ft_redir_in(char *str, int block, int arg, t_data *data)
{
	int		i;
	int		fd;
	char	*file_name;

	i = 1;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0' || str[i] == '>' || str[i] == '<')
		return (ft_red_err(data, block, str[i]));
	fd = open(str + i, O_RDONLY, S_IRUSR | S_IWUSR);
	if (block == 0)
		data->pipes[data->pipe_num][0] = fd;
	else
		data->pipes[block - 1][0] = fd;
	if (fd == -1)
	{
		file_name = ft_strjoin("minishell: ", str + i);
		perror(file_name);
		free(file_name);
		ft_remove_arg(data, block, arg);
		data->error_flags[block] = TRUE;
		return (1);
	}
	ft_remove_arg(data, block, arg);
	return (0);
}
