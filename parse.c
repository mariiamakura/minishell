/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:27:39 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/19 17:28:07 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_count_pipes(char *split[])
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (split[i][j] == '|')
				count++;
			j++; 
		}
		i++;
	}
	return (count);
}

void	ft_parse(char *input, t_data *data)
{
	char **split_input;
	int i;
	int j;
	int k;
	int	start;


	split_input = ft_split(input, ' ');
	data->pipe_num = ft_count_pipes(split_input);
	data->tokens = malloc(sizeof(t_token) * (data->pipe_num + 1));
	if (data->tokens == NULL)
		exit (1);
	i = 0;
	start = 0;
	while (split_input[start])
	{
		j = 0;
		while (split_input[i][0] != '|' && split_input[i])
			i++;
		data->tokens[j] = malloc(sizeof(t_token) * i); //NULL termination required ???
		k = 0;
		while (k < start + i)
		{
			ft_memmove(data->tokens[j][k].content, split_input[start + k], ft_strlen(split_input[start + k]));
			k++;
		}
		j++;
		i++;
		start = i;
	}
	return ;
}
