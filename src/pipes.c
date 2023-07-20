/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:29:31 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/20 14:04:38 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data *create_tokens(t_data *data)
{
	//ls | grep a
	data->tokens = malloc(2 * sizeof(t_token *));
	data->tokens[0] = malloc(sizeof(t_token));
	data->tokens[1] = malloc(sizeof(t_token));
	data->tokens[0]->content = "ls";
	data->tokens[1]->content = "grep a";
	return (data);
}

void free_all(t_data *data)
{
	free(data->tokens[0]);
    free(data->tokens[1]);
    free(data->tokens);
    free(data);
}

void start_pipes(t_data *data)
{
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return ;
	data = create_tokens(data);
	printf("%s\n", data->tokens[0]->content);
	printf("%s\n", data->tokens[1]->content);

	free_all(data);
}


	// char *input;
	// char **tokens;
	// int	i;
	
	// input = readline(NULL);
	// tokens = ft_split(input, ' ');
	// i = 0;
	// while (tokens[i])
	// {
	// 	printf("%s\n", tokens[i]);
	// 	i++;
	// }
	// execve(ft_strjoin("/bin/", tokens[0]), tokens, NULL);