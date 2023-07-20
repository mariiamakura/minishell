/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:39:47 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/20 14:06:09 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# define TRUE 1
# define FALSE 0
# define FUNCTION 555

typedef struct s_token
{
	int type; //redirection, file, Function/Identifier, argument, pipe
	char *content; //argv[1]
	char *path;
}	t_token;

typedef struct s_data
{
	t_token **tokens; //tokens[1] - points to the 1 group
	int pipe_num;
	int fd[2]; //fd[pipe_num][2] - guillaume advise. do we need it though? research
} t_data;

//pipes.c
void start_pipes(t_data *data);

#endif