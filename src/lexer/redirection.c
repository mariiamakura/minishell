/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:05:44 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/09 15:38:14 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_redir_out(char *str, int block, int arg, t_data *data) // maybe close the fd that is redirected??
{
	int	i;
	int	fd;
	char *file_name;

	i = 1;
	while (str[i] == ' ')
		i++;
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
	return(0);
}

int	ft_redir_app(char *str, int block, int arg, t_data *data)
{
	int	i;
	int	fd;
	char *file_name;

	i = 2;
	while (str[i] == ' ')
		i++;
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

int	ft_redir_in(char *str, int block, int arg, t_data *data) //add test if fd opens fails
{
	int	i;
	int	fd;
	char *file_name;

	i = 1;
	while (str[i] == ' ')
		i++;
	fd = open(str + i, O_RDONLY, S_IRUSR | S_IWUSR);
	if (block == 0)
		data->pipes[data->pipe_num][0] = fd; // pipe[pipe_num][0] stores input for first child (its not initialized with pipe())
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

int	ft_getc(FILE *stream)
{
    char buffer[1]; // Buffer to read a single character
    ssize_t bytesRead;
    bytesRead = read(0, buffer, 1);
    if (bytesRead <= 0) {
		
		return (EOF);
    }
	stream++;
    return (buffer[0]);
}

int	ft_here_doc(char *str, int block, int arg, t_data *data) //maybe also close pipes here
{
		int		i;
		char	*delimiter;
		char	*input;
		char	*buffer;
		char	*temp;
		int		pipe_doc[2];
		
		signal(SIGINT, sig_handler_heredoc);
		i = 2;
		while (str[i] == ' ')
			i++;
		delimiter = str + i;
		buffer = ft_calloc(1, sizeof(char));
		last_exit_global = 0;
		rl_getc_function = ft_getc;
		while (ft_strncmp(delimiter, input = readline("> "), ft_strlen(delimiter) + 1) != 0)
		{
			temp = buffer;
			if (input == NULL)
			{
				free (input);
				if (last_exit_global == 130)
				{
					i = 0;
					while (i <= data->pipe_num)
					{
						data->error_flags[i] = TRUE;
						i++;
					}
				}
				break ;
			}
			buffer = ft_strjoin(buffer, input);
			free(temp);
			temp = buffer;
			buffer = ft_strjoin(buffer, "\n");
			free(input);
			free(temp);
		}
		if (last_exit_global == 130)
			data->error_flags[block] = TRUE;
		if (block == 0)
		{
			if (pipe(pipe_doc) != 0) //for the first block need to set a pipe 
				return (-1);
			data->pipes[data->pipe_num][0] = pipe_doc[0]; //set the read-end in pipes
			write(pipe_doc[1], buffer, ft_strlen(buffer)); //write to pipe this process reads from
			close(pipe_doc[1]);
		}
		else
			write(data->pipes[block - 1][1], buffer, ft_strlen(buffer)); //write to pipe this process reads from
		free(buffer);
		ft_remove_arg(data, block, arg);
		return (0);
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
