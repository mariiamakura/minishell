/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:05:44 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/28 20:38:00 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_redir_out(char *str, int block, t_data *data) // maybe close the fd that is redirected??
{
	int	i;
	int	fd;

	i = 1;
	while (str[i] == ' ')
		i++;
	fd = open(str + i, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	data->pipes[block][1] = fd;
}

void	ft_redir_app(char *str, int block, t_data *data)
{
	int	i;
	int	fd;

	i = 2;
	while (str[i] == ' ')
		i++;
	fd = open(str + i, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	data->pipes[block][1] = fd;
}

int	ft_redir_in(char *str, int block, t_data *data) //add test if fd opens fails
{
	int	i;
	int	fd;

	i = 1;
	while (str[i] == ' ')
		i++;
	fd = open(str + i, O_RDONLY, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (-1);
	if (block == 0)
		data->pipes[data->pipe_num][0] = fd; // pipe[pipe_num][0] stores input for first child (its not initialized with pipe())
	else
		data->pipes[block - 1][0] = fd;
	return (0);
}

int	ft_here_doc(char *str, int block, t_data *data) //maybe also close pipes here
{
		int		i;
		char	*delimiter;
		char	*input;
		char	*buffer;
		char	*temp;
		int		pipe_doc[2];
		
		i = 2;
		while (str[i] == ' ')
			i++;
		delimiter = str + i;
		buffer = ft_calloc(1, sizeof(char));
		while (ft_strncmp(delimiter, input = readline("> "), ft_strlen(delimiter) + 1) != 0)
		{
			temp = buffer;
			buffer = ft_strjoin(buffer, input);
			free(temp);
			temp = buffer;
			buffer = ft_strjoin(buffer, "\n");
			free(input);
			free(temp);
		}
		if (block == 0)
		{
			if (pipe(pipe_doc) != 0) //need to set a pipe 
				return (-1);
			data->pipes[data->pipe_num][0] = pipe_doc[0]; //set the read-end in pipes
			write(pipe_doc[1], buffer, ft_strlen(buffer)); //write to pipe this process reads from
			close(pipe_doc[1]);
		}
		else
			write(data->pipes[block - 1][1], buffer, ft_strlen(buffer)); //write to pipe this process reads from

		free(buffer);
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

int	ft_add_path(int i, t_data *data)
{
	char *temp;
	char *test1;
	char *test2;

	temp = data->tokens[i][0];
	test1 = ft_strjoin("/bin/", data->tokens[i][0]);
	test2 = ft_strjoin("/usr/bin/", data->tokens[i][0]);
	if (access(test1, F_OK) == 0)
	{
		data->tokens[i][0] = test1;
		free(test2);
		free(temp);
	}
	else if (access(test2, F_OK) == 0)
	{
		data->tokens[i][0] = test2;
		free(test1);
		free(temp);
	}
	else 
	{
		free(test1);
		free(test2);
	}
	return (0);
}

int	ft_parse_redir(t_data *data) //return open error
{
	int	i;
	int	j;

	i = 0;
	while (i <= data->pipe_num)
	{
		j = 0;
		while (data->tokens[i][j])
		{
			if (data->tokens[i][j][0] == '<' && data->tokens[i][j][1] == '<')
			{
				ft_here_doc(data->tokens[i][j], i, data);
				ft_remove_arg(data, i, j);
				break ;
			}
			if (data->tokens[i][j][0] == '>' && data->tokens[i][j][1] == '>')
			{
				ft_redir_app(data->tokens[i][j], i, data);
				ft_remove_arg(data, i, j);
				break ;
			}
			if (data->tokens[i][j][0] == '>')
			{
				ft_redir_out(data->tokens[i][j], i, data);
				ft_remove_arg(data, i, j);
				break ;
			}
			if (data->tokens[i][j][0] == '<')
			{
				if (ft_redir_in(data->tokens[i][j], i, data) == -1)
					return (-1);
				ft_remove_arg(data, i, j);
				break ;
			}
			j++;
		}
		ft_add_path(i, data);
		i++;
	}
	return (0);
}
