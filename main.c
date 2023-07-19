/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:47:20 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/19 15:15:37 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *input;
	char **tokens;
	int	i;
	
	input = readline(NULL);
	tokens = ft_split(input, ' ');
	i = 0;
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
	execve(ft_strjoin("/bin/", tokens[0]), tokens, NULL);
}
