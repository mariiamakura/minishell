/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:39:47 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/09 17:31:08 by mparasku         ###   ########.fr       */
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
# define FT_EXPORT 111
# define FT_UNSET  222


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
	//int	last_exit;
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
void	sig_handler(int signum);
void	sig_handler_child(int signum);
void	sig_handler_parent(int signum);
void	init_signals(void);
void	sig_handler_heredoc(int signum);

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
void	ft_free_2d(char **av);

//buildins
//echo.c 
int ft_echo(char *av[], t_data *data, int index);
void ft_print(char *av[], int i, int flag, int index, t_data *data);
int ft_prem_output(t_data *data, int index);

//cd.c
void ft_cd(char *av[], t_data *data, int index);
void ft_cd_home(t_data *data);
void ft_cd_prev(t_data *data, int index);

//env.c
void ft_env(t_data *data, int index);
char *ft_get_env_value(t_data *data, char *var_name);
void ft_env_declare_x(t_data *data, int index);
char **ft_copy_2d_arr(char **env);
void swap(char **a, char **b);
void print_declare_x(char **temp_env, int index, t_data *data);

//export.c
void ft_export(char *av[], t_data *data, int index);
char *ft_get_var_name(char* av);
int ft_count_arg(char **av);
char **ft_get_multi_var_name(char **av, int num_var, int flag);
int ft_is_var_in_env(t_data *data, char *var_name);
char **ft_add_env_var(char *av, t_data *data);
char **ft_replace_env_var(char *av, t_data *data, char *var_name);
void var_name_error(char *var_name, int flag);

//pwd.c
void ft_pwd(t_data *data, int index);
void ft_update_pwd(t_data *data, int index);
void ft_update_oldpwd(t_data *data, int index);

//ft_unset.c
void ft_unset(char *av[], t_data *data);
char **ft_remove_env(t_data * data, char *var_name);

//exit.c
void ft_exit(t_data *data);
void	ft_free_tokens(t_data *data);

#endif