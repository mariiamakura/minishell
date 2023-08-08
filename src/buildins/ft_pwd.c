/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:31:44 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/08 14:40:26 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_pwd(t_data *data, int index)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_putstr_fd(cwd, data->pipes[index][1]);
		ft_putstr_fd("\n", data->pipes[index][1]);
		free(cwd);
	}
	else 
	{
		perror("minishell: pwd: ");
	}
}