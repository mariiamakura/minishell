/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:39:47 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/04 15:53:24 by ycardona         ###   ########.fr       */
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
#include <errno.h>


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
	int *error_flags;
	int	forked;
	int	last_exit;
} t_data;

extern int	last_exit_global;

//parser
int		ft_parse(t_data *data);
int		ft_split_sub(char *sub_str, int block, t_data *data);
int		ft_count_pipes(char *input);
int		ft_count_args(char *s);
char	*ft_substr_pipe(char *str, unsigned long *start);

//pipes.c
int start_pipes(t_data *data);
int	init_pipes(t_data * data);

//pipes_utils.c
void free_wflags(t_data *data, int i, int flag);
void close_fd(t_data *data);
void wait_children(t_data *data);
void term_processes(t_data * data);

//signals.c
//void	sig_handler(int signum);
void	sig_handler_child(int signum);
void	sig_handler_parent(int signum);
void	init_signals(void);
void	sig_handler_inchild(int signum);

//utils.c just useful for now
void print_tokens(t_data *data);

//lexer
int		ft_lexer(t_data *data);
void	ft_remove_arg(t_data *data, int block, int arg);
int		ft_add_path(int i, t_data *data);
void	ft_parse_var(int block, int arg, t_data *data);
char	*ft_getenv(char *envp[], char *var_name);
void	ft_remove_quot(char *str, int first, int last);
int		ft_here_doc(char *str, int block, int arg, t_data *data);
int		ft_redir_in(char *str, int block, int arg, t_data *data);
int		ft_redir_app(char *str, int block, int arg, t_data *data);
int		ft_redir_out(char *str, int block, int arg, t_data *data);

//builtins
int		ft_is_builtin(char *str);
void    ft_run_builtin(t_data *data, int i);
int		ft_echo(char *av[], int index, t_data *data);
void	ft_print(char *av[], int i, int flag, int index, t_data *data);

#endif