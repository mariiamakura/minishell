/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:59:01 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/21 13:07:51 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_getc(FILE *stream)
{
	char	buffer[1];
	ssize_t	bytes_read;

	bytes_read = read(0, buffer, 1);
	if (bytes_read <= 0)
		return (EOF);
	stream++;
	return (buffer[0]);
}

static char	*ft_add_buffer(char *buffer, char *input)
{
	char	*temp;
	char	*new_buffer;

	temp = ft_strjoin(buffer, input);
	new_buffer = ft_strjoin(temp, "\n");
	free(buffer);
	free(temp);
	return (new_buffer);
}

static char	*ft_get_input(char *delimiter, t_data *data)
{
	char	*input;
	int		i;
	char	*buffer;

	rl_getc_function = ft_getc;
	buffer = ft_calloc(1, sizeof(char));
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
		{
			if (g_last_exit == 130)
			{
				i = -1;
				while (++i <= data->pipe_num)
					data->error_flags[i] = TRUE;
			}
			return (free(input), buffer);
		}
		if (ft_strncmp(delimiter, input, ft_strlen(delimiter) + 1) == 0)
			return (free(input), buffer);
		buffer = ft_add_buffer(buffer, input);
	}
}

int	ft_here_doc(char *str, int block, int arg, t_data *data)
{
	int		i;
	char	*buffer;
	int		pipe_doc[2];

	signal(SIGINT, sig_handler_heredoc);
	i = 2;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0' || str[i] == '>' || str[i] == '<')
		return (ft_red_err(data, block, str[i]));
	buffer = ft_get_input(str + i, data);
	if (g_last_exit == 130)
		data->error_flags[block] = TRUE;
	if (block == 0)
	{
		if (pipe(pipe_doc) != 0)
			return (-1);
		data->pipes[data->pipe_num][0] = pipe_doc[0];
		write(pipe_doc[1], buffer, ft_strlen(buffer));
		close(pipe_doc[1]);
	}
	else
		write(data->pipes[block - 1][1], buffer, ft_strlen(buffer));
	ft_remove_arg(data, block, arg);
	return (free(buffer), 0);
}
