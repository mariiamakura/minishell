/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:05:44 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/01 11:42:17 by ycardona         ###   ########.fr       */
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
			if (pipe(pipe_doc) != 0) //for the first block need to set a pipe 
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

void	ft_add_var(int block, int arg, int *start, t_data *data)
{
	char	*token;
	char	*var_name;
	char	*var_cont;
	char	*new_token;
	int		i;

	token = data->tokens[block][arg];
	i = 0;
	while (token[*start + 1 + i] && token[*start + 1 + i] != ' ' &&
		token[*start + 1 + i] != 34 && token[*start + 1 + i] != 39)
		i++;
	var_name = ft_calloc(i + 1, sizeof(char));
	ft_memmove(var_name, token + *start + 1, i);
	var_name[i] = '\0';
	var_cont = ft_getenv(data->env, var_name);
	new_token = ft_calloc(*start + ft_strlen(var_cont) + ft_strlen(token + *start + 1 + i) + 1, sizeof(char));
	ft_memmove(new_token, token, *start);
	ft_memmove(new_token + *start, var_cont, ft_strlen(var_cont));
	ft_memmove(new_token + *start + ft_strlen(var_cont), token + *start + 1 + i, ft_strlen(token + *start + 1 + i));
	new_token[*start + ft_strlen(var_cont) + ft_strlen(token + *start + 1 + i)] = '\0';
	free(token);
	free(var_name);
	*start += i + 1;
	data->tokens[block][arg] = new_token;
}

int	ft_quot_closed(char *str, int quot)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == quot)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	ft_remove_quot(char *str, int first, int last)
{
	size_t	len_sub;
	size_t	len_str;

	if ((len_str = ft_strlen(str)) < 2)
		return;
	len_sub = ft_strlen(str + (last + 1));
	ft_memmove(str + last, str + (last + 1), len_sub);
	str[len_str - 1] = '\0';
	len_str = ft_strlen(str);
	len_sub = ft_strlen(str + (first + 1));
	ft_memmove(str + first, str + (first + 1), len_sub);
	str[len_str - 1] = '\0';
}

void	ft_parse_var(int block, int arg, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->tokens[block][arg][i])
	{
		if (data->tokens[block][arg][i] == '$')
			ft_add_var(block, arg, &i, data);
		if (data->tokens[block][arg][i] == '"'
			&& ft_quot_closed(&data->tokens[block][arg][i + 1], 34) == TRUE)
		{
			j = i + 1;
			while (data->tokens[block][arg][j])
			{
				if (data->tokens[block][arg][j] == '$')
					ft_add_var(block, arg, &j, data);
				if (data->tokens[block][arg][j] == '"')
				{
					ft_remove_quot(data->tokens[block][arg], i, j);
					i = j - 1;
					break ;
				}
				j++;
			}
		}
		if (data->tokens[block][arg][i] == 39
			&& ft_quot_closed(&data->tokens[block][arg][i + 1], 39) == TRUE)
		{
			j = i + 1;
			while (data->tokens[block][arg][j] != 39)
				j++;
			ft_remove_quot(data->tokens[block][arg], i, j);
			i = j - 1;
		}
		i++;
	}
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
			ft_parse_var(i, j, data);
			j++;
		}
		ft_add_path(i, data);
		i++;
	}
	return (0);
}
