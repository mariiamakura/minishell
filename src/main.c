/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:47:20 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/22 14:44:53 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_last_exit;

void	ft_shlvl_update(t_data *data)
{
	char	*new_shlvl;
	int		i;
	char	*str;
	char	*char_num;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "SHLVL=", ft_strlen("SHLVL=")) == 0)
		{
			str = ft_strdup(data->env[i]);
			char_num = ft_strdup(str + 6);
			free (str);
		}
		i++;
	}
	if (char_num == NULL)
		return ;
	data->shlvl = ft_atoi(char_num);
	free(char_num);
	data->shlvl++;
	char_num = ft_itoa(data->shlvl);
	new_shlvl = ft_strjoin("SHLVL=", char_num);
	free(char_num);
	ft_shlvl_export(data, new_shlvl);
}

void	ft_shlvl_export(t_data *data, char *new_shlvl)
{
	char	*update_shlvl[3];

	update_shlvl[0] = "export";
	update_shlvl[1] = new_shlvl;
	update_shlvl[2] = NULL;
	ft_export(update_shlvl, data, STDOUT_FILENO);
	free(new_shlvl);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	if (argc != 1 || !argv[0])
		return (1);
	data = malloc(sizeof(t_data));
	data->forked = FALSE;
	if (data == NULL)
		return (1);
	data->env = ft_copy_2d_arr(envp);
	ft_shlvl_update(data);
	g_last_exit = 0;
	init_signals();
	while (1) 
	{
		init_signals();
		if (0 <= ft_parse(data))
		{
			init_pipes(data);
			ft_lexer(data);
			start_pipes(data);
			ft_free_tokens(data);
			free(data->error_flags);
			free_wflags(data, data->pipe_num, FINISHED);
		}
	}
}
