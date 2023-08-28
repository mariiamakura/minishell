/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:39:47 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/22 15:41:07 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>

# define TRUE 1
# define FALSE 0
# define FINISHED 1
# define NOT_FINISHED 0
# define FT_EXPORT 111
# define FT_UNSET  222

typedef struct s_data
{
	char	***tokens;
	int		pipe_num;
	int		*child_pid;
	int		**pipes;
	char	**env;
	char	*promt;
	int		*error_flags;
	int		forked;
	int		shlvl;
}	t_data;

extern int	g_last_exit;

//main.c 
void		ft_shlvl_update(t_data *data);
void		ft_shlvl_export(t_data *data, char *new_shlvl);

//parse_utils.c
void		ft_quotation(char *str, int *i, int quot);
int			ft_count_pipes(char *input);
//static void	ft_skipp_redir(char *str, int *i, int *count);
int			ft_count_args(char *s);
char		*ft_substr_pipe(char *str, unsigned long *start);

//parse.c
int			ft_all_whitespace(char *str);
int			ft_ctrl_d(t_data *data);
int			ft_parse_init(t_data *data, char *input);
int			ft_parse(t_data *data);

//split_sub.c
//static int	ft_quotations_count(char *str, int quot);
//static int	ft_red_count(char *str, int red);
//static int	ft_arg_len(char *sub_str, int i);
int			ft_split_sub(char *sub_str, int block, t_data *data);

//pipes.c
int			start_pipes(t_data *data);
int			init_pipes(t_data *data);
void		ft_run_one_buildin(t_data *data);
int			ft_run_child(t_data *data, int i);
int			ft_child_configur(t_data *data, int i);

//pipes_utils.c
void		free_wflags(t_data *data, int i, int flag);
void		close_fd(t_data *data);
void		wait_children(t_data *data);
void		term_processes(t_data *data);

//signals.c
void		init_signals(void);
void		sig_handler(int signum);
void		sig_handler_child(int signum);
void		sig_handler_parent(int signum);
void		sig_handler_heredoc(int signum);

//lexer
//add_path_utils.c
char		*ft_getenv(char *envp[], char *var_name);
void		ft_free_path(char **path_env);
int			ft_is_path(char *str);
int			ft_is_slash(char *str);

//add_path.c
int			ft_check_rel_path(int block, t_data *data);
int			ft_check_path(int block, t_data *data);
int			ft_check_cmd(char **path_env, char *funct_name, t_data *data, \
int block);
int			ft_check_dots(int block, t_data *data);
int			ft_add_path(int block, t_data *data);

//heredoc.c
int			ft_getc(FILE *stream);
//static char	*ft_add_buffer(char *buffer, char *input);
//static char	*ft_get_input(char *delimiter, t_data *data);
int			ft_here_doc(char *str, int block, int arg, t_data *data);

//lexer.c
//static void	ft_parse_var_loop(t_data *data);
void		ft_lexer(t_data *data);

//quot_utils.c
int			ft_quot_closed(char *str, int quot);
void		ft_remove_quot(char *str, int first, int last);

//redirection_utils.c
int			ft_red_err(t_data *data, int block, char c);
void		ft_remove_arg(t_data *data, int block, int arg);

//redirection.c
int			ft_redir_out(char *str, int block, int arg, t_data *data);
int			ft_redir_app(char *str, int block, int arg, t_data *data);
int			ft_redir_in(char *str, int block, int arg, t_data *data);

//var_utils.c
int			ft_has_spaces(char *str);
char		*ft_merge_first(char *old_arg, int start, char *sub_split);
char		*ft_merge_last(char *old_arg, int end_start, char *sub_split);
int			ft_split_count(char	**split);
char		*ft_get_var_cont(char *token, int *len, int *start, t_data *data);

//variables_quatations.c
char		*ft_expand_token(char *token, char *var_cont, int *start, int len);
char		**ft_expand_tokens(char *var_cont, char **old_block, int *start, \
int p[2]);
void		ft_add_var(int block, int arg, int *start, t_data *data);
void		ft_handle_dq(t_data *data, int block, int arg, int i);
void		ft_parse_var(int block, int arg, t_data *data);

//builtins_utils.c
int			ft_is_builtin(char *str);
int			ft_run_builtin(t_data *data, int i);
void		ft_free_2d(char **av);
char		**ft_copy_2d_arr(char **env);
int			ft_print_error_buildins(char *s1, char *s2);

//echo.c 
int			ft_echo(char *av[], t_data *data, int index);
void		ft_print(char *av[], int flag, int index, t_data *data);

//cd.c
int			ft_cd(char *av[], t_data *data, int index);
int			ft_cd_home(t_data *data, char *str);
int			ft_cd_prev(t_data *data, int index);
int			ft_error_cd(char *str);
int			ft_go_to_dir(char *dir);

//declare.c
int			ft_declare_x(t_data *data, int index);
int			ft_env_declare_sort(char **tm, int size);
void		swap(char **a, char **b);
void		print_declare_x(char **temp_env, int index, t_data *data);

//env.c
int			ft_env(char *av[], t_data *data, int index);
char		*ft_get_env_value(t_data *data, char *var_name);

//ft_export_utils.c
int			var_name_error_new(char **var, int arg_num);
int			ft_is_var_in_env(t_data *data, char *var_name);
int			ft_count_arg(char **av);
void		ft_free_var_names(char **av, int arg_num);
char		*ft_get_var_name(char *av);

//export.c
int			ft_export(char *av[], t_data *data, int index);
char		**ft_get_multi_var_name(char **av, int num_var, int flag);
char		**ft_add_env_var(char *av, t_data *data);
char		**ft_replace_env_var(char *av, t_data *data, char *var_name);
int			ft_export_loop(int arg_num, t_data *data, char **var_names, \
char **av);

//pwd.c
int			ft_pwd(t_data *data, int index);
void		ft_update_pwd(t_data *data, int index);
void		ft_update_oldpwd(t_data *data, int index);
int			ft_cd_only_home(t_data *data);

//ft_unset.c
int			ft_unset(char *av[], t_data *data);
char		**ft_remove_env(t_data *data, char *var_name, int j);

//exit.c
int			ft_exit(char *av[], t_data *data);
int			exit_error(char *av[]);
void		ft_exit_error(char *s1, char *s2);
void		ft_free_tokens(t_data *data);
void		ft_standard_exit(t_data *data);

#endif