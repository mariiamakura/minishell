/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulitins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:19:33 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/02 12:42:27 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    ft_echo(int i, t_data *data)
{
    data->pipe_num = i;
    printf("this is echo!!\n");
}

int	ft_is_builtin(char *str)
{
	if (ft_strncmp("echo", str, ft_strlen(str)) == 0
		|| ft_strncmp("cd", str, ft_strlen(str)) == 0
		|| ft_strncmp("pwd", str, ft_strlen(str)) == 0
		|| ft_strncmp("export", str, ft_strlen(str)) == 0
		|| ft_strncmp("unset", str, ft_strlen(str)) == 0
		|| ft_strncmp("env", str, ft_strlen(str)) == 0
		|| ft_strncmp("exit", str, ft_strlen(str)) == 0)
		return (TRUE);
	else
		return (FALSE);
}

void    ft_run_builtin(t_data *data)
{
    if (ft_strncmp("echo", data->tokens[0][0], ft_strlen(data->tokens[0][0])) == 0)
        ft_echo(0, data);
}
