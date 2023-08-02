/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:08:19 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/02 15:34:20 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_cd(char *av[]/* , t_data *data */)
{
	char *dir;

	dir = NULL;
	if (chdir(av[1]) != 0)
	{
		dir = ft_strjoin("cd: ", av[1]);
		perror(dir);
		free(dir);
	}
	//change pwd?
}