/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:27:39 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/09 15:01:09 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* int	ft_getc(FILE *stream)
{
    char buffer[1]; // Buffer to read a single character
    ssize_t bytesRead;
    bytesRead = read(0, buffer, 1);
    if (bytesRead <= 0) {
		//buffer[0] = '\0';
		//rl_replace_line("", 0);
		return (EOF);
    }
	stream++;
    return (buffer[0]);
} */

int	ft_parse(t_data *data)
{
	char	*input;
	int		i;
	unsigned long start;
	char	*sub_str;
	int		argc;

	rl_getc_function = rl_getc;
	input = readline(" ~ minishell$ ");
	if (input == NULL) //handles ctrl+d
	{
		write(1, "exit\n", 5);
		rl_clear_history();
		free(data);
		exit(-1);
	}
	if (*input == '\0')
	{
		last_exit_global = 0;
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
	data->tokens = ft_calloc((data->pipe_num + 1), sizeof(char **)); //no NULL termination because we know pipe_num
	if (data->tokens == NULL)
		exit (1);
 	i = 0;
	start = 0;
	while (i <= data->pipe_num)
	{
		sub_str = ft_substr_pipe(input, &start); //get substring untill pipe
		argc = ft_count_args(sub_str); //count arguments in substring
		data->tokens[i] = ft_calloc(sizeof(char *), argc + 1);
		if (data->tokens[i] == NULL)
			exit (1);
		ft_split_sub(sub_str, i, data); //split and write the substring into tokens
		data->tokens[i][argc] = NULL;//NULL-termination required for execve
		free(sub_str);
		i++;
	}
	free(input);
	return (0);
}
