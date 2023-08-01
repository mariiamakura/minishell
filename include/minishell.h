/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:39:47 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/01 14:20:08 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>


# define TRUE 1
# define FALSE 0
# define FINISHED 1
# define NOT_FINISHED 0

typedef struct s_data
{
	char ***tokens; //tokens[0] - points to the 0 group (*tokens[]); makes more sense to store them as chars since char *argv[] goes into the execve function
					//tokens[0][0] - points to the first token 
					//token[0][0][0] - points to the first character of the first token 
	int pipe_num;
	int *child_pid;
	int **pipes;
	char **env;
	char *promt;
} t_data;

typedef struct s_global 
{
	int	forked;
	int c_kill_child;
} t_global;

extern t_global *g_global;

//parse.c
int	ft_parse(t_data *data);

//pipes.c
int start_pipes(t_data *data);
t_data *init_pipes(t_data * data);

//pipes_utils.c
void free_wflags(t_data *data, int i, int flag);
void close_fd(t_data *data);
void wait_children(t_data *data);
void term_processes(t_data * data, int i);

//signals.c
void	sig_handler(int signum);
void	init_signals(void);

//utils.c just useful for now
void print_tokens(t_data *data);

//redirection.c
int	ft_parse_redir(t_data *data);
void	ft_remove_arg(t_data *data, int block, int arg);
void	ft_add_path(int i, t_data *data);
char	*ft_getenv(char *envp[], char *var_name);

#endif